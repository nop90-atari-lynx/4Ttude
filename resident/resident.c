/*
 * The code and data defined here is placed in resident RAM
 */
#include <lynx.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <tgi.h>
#include <joystick.h>
#include <6502.h>
#include "LynxSD.h"

//void tgi_atarixy (int, int, unsigned char*);

#define EEPROM_MAGIC "TTTT" // Change this to your own string. 3-5 chars are fine.

signed char SDCheck = -1; // tracks if there is a SD cart with saves enabled. -1 = No check yet, 0 = no SD saves, 1 = SD saves possible 
unsigned int saveBuf[64]; // Buffer for storing SaveData in memory. Only the first 6 bytes are used for checking if data is valid, for the others there is no predefined data structure. Use it as you want
const char SDSavePath[] = "/saves/4ttude.sav"; //rename game.sav to yourprogramname.sav, i.e. the same name of your lnx file
unsigned char * saveptr;

unsigned char halted = 0; // for pause event
unsigned char reset = 0; // for reset event
unsigned char musicEnabled = 1;
unsigned char altview = 1;
unsigned char lastmove = 1;
unsigned char ingame = 0;
unsigned char flipflop = 0;
unsigned char tunenum = 2;
unsigned char menutune = 0;


// For reading writing EEPROM. The data is always 2 bytes, the address range 0..63
extern int __fastcall__ lnx_eeprom_read(unsigned char pos);
extern void __fastcall__ lnx_eeprom_write(unsigned char pos, int val);

void lynx_snd_pause ();
void lynx_snd_continue ();
void __fastcall__ lynx_snd_play (unsigned char channel, unsigned char *music);
void lynx_snd_stop ();
void playPCMSample(void);
void stopPCMSample(void);
void __near__ __fastcall__ openn (int);

typedef struct {
    unsigned char *music0;
    unsigned char *music1;
    unsigned char *music2;
    unsigned char *music3;
} song_t;

extern song_t musicptr;

void intro();
unsigned char menu();
unsigned char selectLevel(unsigned char rank);
unsigned char selectGame(signed char p);
unsigned char select2PMode(void);
unsigned char game(unsigned char level, unsigned char rank);
unsigned int game2P(unsigned char rank1, unsigned char rank2);
unsigned char netgame(unsigned char rank);
void showHistory(unsigned char pos);
void showHistory2P(unsigned char pos1, unsigned char pos2);
void stats(void);
void options(void);
unsigned char askPlayAgain(unsigned char cpu);
void credits(void);
void tutorial(void);

extern int INTRO_FILENR;
extern int MENU_FILENR;
extern int CREDITS_FILENR;
extern int GAME_FILENR;
extern int GAME2P_FILENR;
extern int TUNE0_FILENR;
extern int TUNE1_FILENR;
extern int TUNE2_FILENR;
extern int TUNE3_FILENR;

unsigned char backupPal[32]; // stores the palette before graying the screen in pause mode
unsigned char grayPal[32]; // stores the grayed palette for the pause mode derived from the active palette

//unsigned char firstTime;

void eewrite(unsigned char pos, unsigned int val)
{
	unsigned int check;
	check = lnx_eeprom_read(pos);
	if(check!=val)
		lnx_eeprom_write(pos,val);
}

void writeSaveData(void)
{
	unsigned char i;

	if(SDCheck==1) // use SD
	{
		if (LynxSD_OpenFile(SDSavePath) == FR_OK) {
			LynxSD_WriteFile((void *)saveBuf, 128);
			LynxSD_CloseFile();
		}	
	}
	else if(SDCheck==0) // Try to use EEPROM
	{
		for(i=0;i<64;i++)
		{
			eewrite(i,saveBuf[i]);
		}
	}
}

void readSaveData(void)
{
	unsigned char i;
	FRESULT res;

	if(SDCheck==-1) 
	{
		res = LynxSD_OpenFileTimeout(SDSavePath); 
		if(res == FR_OK)
			SDCheck=2; // SD savefile is ok and next SD access doesn't need to open the file (already opened)
  		else if(res==FR_DISK_ERR) // SD read Timeout -> NO SD
		{
			SDCheck=0; // Try to use EEPROM, if there isn't an EEPROM the functions calls are safe because they don't freeze the code 
		}
		else	
		{
			SDCheck=-2; // The SD answers, but there is no sav file, or some other problem occoured accessing the file -> don't try to use SD and EEPROM anymore (EEPROM calls on SD frezes the code)
		}
	}

	if (SDCheck==0)	// Read the EEPROM	
	{ 
		for(i=0;i<64;i++)
		{
			saveBuf[i]= lnx_eeprom_read(i);
		}
	}
	else if(SDCheck>0) // the value can be 1 or 2
	{
		if(SDCheck==1) //SD sav file enabled
		{
			if (LynxSD_OpenFile(SDSavePath) == FR_OK)
			{
				LynxSD_ReadFile((void *)saveBuf, 128);
				LynxSD_CloseFile();	
			}
		}
		else // //SD sav file enabled and sav file already opened
		{
			SDCheck=1;
			LynxSD_ReadFile((void *)saveBuf, 128);
			LynxSD_CloseFile();	
		}
	}
}

void resetSaveData(void)
{
    int i;
    saveBuf[2]=0;
    strcpy((char*)saveBuf,EEPROM_MAGIC);
    saveBuf[3]=6 | musicEnabled; //Music state,  show alt grids on, show last move on
//	saveBuf[3] = (musicEnabled) & (altview<<1) & (lastmove<<2);
	for(i=4;i<64;i++)
	{
		saveBuf[i]=0; //instead of this you could initialize the savedata with some starting values, like a predefined highscores table.
	}
	writeSaveData();
}

void play_Tune(void)
{
	if(ingame)
	{
		menutune=0;
		tunenum=(tunenum+1)%3;
		if(tunenum==0)
			lynx_load((int)&TUNE1_FILENR);
		else if(tunenum==1)
			lynx_load((int)&TUNE2_FILENR);
		if(tunenum==2)
			lynx_load((int)&TUNE3_FILENR);
		if(musicEnabled)
		{
			lynx_snd_play(0, musicptr.music0);
			lynx_snd_play(1, musicptr.music1);
			lynx_snd_play(2, musicptr.music2);
		}
	}
	else
		if(!menutune)
		{
			lynx_load((int)&TUNE0_FILENR);
			menutune=1;
			if(musicEnabled)
			{
				lynx_snd_play(0, musicptr.music0);
				lynx_snd_play(1, musicptr.music1);
				lynx_snd_play(2, musicptr.music2);
			}
		}
}

void addGame(unsigned char slot, unsigned char rank)
{
	unsigned char pgames;
	unsigned char i;
	
	pgames = saveptr[8+(40*slot)];
	if(pgames<255) 
		saveptr[8+(40*slot)]=++pgames;
	saveptr[9+(40*slot)]=rank;
	if(pgames<39)
		saveptr[9+pgames+(40*slot)]= rank;
	else	
	{
		for(i=0;i<37;i++)
			saveptr[10+i+(40*slot)]= saveptr[10+i+1+(40*slot)];
		saveptr[10+37+(40*slot)]= rank;
	}
}
 
void main(void)
{
    signed char level;
    unsigned char slot,slot2;
    unsigned char playagain;
    unsigned char rank, rank2;
    unsigned char games;
    unsigned char i;
	unsigned char action;
	unsigned char temp;
	unsigned int temp2;
	unsigned char mode;

	saveptr=(unsigned char *)saveBuf;
    
	lynx_load((int)&INTRO_FILENR);
	intro();

	readSaveData();
	if(strcmp((char*)saveBuf,EEPROM_MAGIC)!=0)
		resetSaveData();
	
	musicEnabled = saveptr[6]&1;
	altview = (saveptr[6]>>1)&1;
	lastmove = (saveptr[6]>>2)&1;
	
 	while (1) 
	{
		reset = 0;
		halted = 0;
        ingame=0;
        
		stopPCMSample();
		lynx_load((int)&MENU_FILENR);
		if(!menutune)
		{
			lynx_snd_stop ();
//			lynx_load((int)&TUNE0_FILENR);
			play_Tune();
		}
        action =  menu();
       
        if(action==0)
		{
			slot = selectGame(0);
			if(slot<4)
			{
				if(slot<3)
				{
					games = saveptr[8+(40*slot)];
					rank = saveptr[9+(40*slot)];
					level = selectLevel(rank);
				}
				else
					level = selectLevel(96);

			}
			playagain=1;
			while(playagain && !reset && slot<4 && level>=0)
			{
				stopPCMSample();
				lynx_snd_stop ();
				menutune=0;
				lynx_load((int)&GAME_FILENR);
				if(slot<3)
				{
					rank = game(level,rank);
					if(!reset)
					{
						addGame(slot, rank);
						writeSaveData();	
					}
				}
				else
					game(level,255);
					
				stopPCMSample();
				if(!menutune)
				{
					lynx_snd_stop ();
//					lynx_load((int)&TUNE0_FILENR);
					play_Tune();
				}
				lynx_load((int)&MENU_FILENR);
				if(!reset)
				{
					if(slot<3)
					{
						stopPCMSample();
						lynx_load((int)&CREDITS_FILENR);
						showHistory(slot); 
						stopPCMSample();
						lynx_load((int)&MENU_FILENR);
					}
					playagain=askPlayAgain(1);
					if(playagain==1)
						level = selectLevel(rank);
				}
			}
		}
        else if(action==1)
		{
			mode = select2PMode();
			if(mode==1)
			{
				slot = selectGame(0);
				if(slot<3)
					rank = saveptr[9+(40*slot)];

				playagain=1;
			}
			else if(mode==0)
			{
				slot = selectGame(1);
				if(slot<3)
				{
					rank = saveptr[9+(40*slot)];
					slot2 = selectGame(slot+2);
					if(slot2<3)
					{
						rank2 = saveptr[9+(40*slot2)];
					}
					else
					{
						slot=3;
					}
				}
				playagain=1;
			}
			else
				playagain=0;
			while(playagain && !reset && slot<4)
			{
				stopPCMSample();
				lynx_snd_stop ();
				menutune=0;
				lynx_load((int)&GAME2P_FILENR);
				if(slot<3)
				{
					if(mode==0)
					{
						temp2 = game2P(rank,rank2);
						if(temp2!=255 && !reset)
						{
							rank = temp2&255;
							temp=rank;
							addGame(slot, rank);
							rank2 = temp2>>8;
							addGame(slot2, rank2);
							writeSaveData();	
						}
						else 
							temp=255;
					}
					else
					{
						temp = netgame(rank); 
						if(temp<255 && !reset)
						{
							rank = temp;
							addGame(slot, rank);
							writeSaveData();	
						}
					}
				}
				else
				{
					if(mode==0)
						temp = game2P(255,255);
					else
						temp = netgame(255);
				}
					
				stopPCMSample();
				if(!menutune)
				{
					lynx_snd_stop ();
//					lynx_load((int)&TUNE0_FILENR);
					play_Tune();
				}
				lynx_load((int)&MENU_FILENR);
				if(temp<255 && !reset)
				{
					if(slot<3)
					{
						if(mode==0)
						{
							stopPCMSample();
							lynx_load((int)&CREDITS_FILENR);
							showHistory2P(slot,slot2); 
						}
						else
						{
							stopPCMSample();
							lynx_load((int)&CREDITS_FILENR);
							showHistory(slot); 
						}
						stopPCMSample();
						lynx_load((int)&MENU_FILENR);
					}
					playagain=askPlayAgain(0);
				}
				else
					playagain=0;
			}
		}
		else if (action==2)
		{
			stopPCMSample();
			lynx_load((int)&CREDITS_FILENR);
			stats(); 
		}
		else if (action==3)
		{
			options(); 
			saveptr[6] = musicEnabled & (altview<<1) & (lastmove<<2);
			writeSaveData();	
		}
		else if (action==4)
		{
			stopPCMSample();
			lynx_load((int)&CREDITS_FILENR);
			tutorial();
		}
		else if (action==5)
		{
			stopPCMSample();
			lynx_load((int)&CREDITS_FILENR);
			credits();
		}
    }
}

unsigned char checkInput(void)
{
	unsigned int col;
	unsigned char i;
	const unsigned char* pal;
	 
	if(!reset)
	do
	{
		if (kbhit()) 
		{
			switch (cgetc()) 
			{
			case 'F':
				tgi_flip();
				break;
			case 'P':
				if(halted)
				{
					halted = 0;
					tgi_setpalette(backupPal); // restore normal palette. No need to wait vsync; data in the screenbuffer are valid
					lynx_snd_continue ();					
				}
				else
				{
					pal = tgi_getpalette(); // let's backup the palette
					for (i=0;i<	16;i++) 
// A simple grayed palette is obtained setting the new r,g, b to the g*0,5 + r*0,25 + b*0,25 . 
// This is an approximate formula that gives a good result considering that there are only 16 shades of gray.					
					{
						backupPal[i] = pal[i];
 						backupPal[i+16] = pal[i+16];
						col = ((backupPal[i]&0xf)*2 + (backupPal[i+16]&0xf) + (backupPal[i+16]>>4)) >> 2;
						grayPal[i] = col;
						grayPal[i+16] = col | (col<<4);
					}	
					tgi_setpalette(grayPal); // set gray palette
					
					halted = 1;
					lynx_snd_pause ();
				}
				break;
			case 'R':
				if(halted)
				{
					halted = 0;
					tgi_setpalette(backupPal); //restore normal palette
					lynx_snd_continue ();					
				}
				reset=1;
				break;
  
			case '1': 
				if(ingame && !halted)
				{
					if(flipflop)
						altview = !altview;
					else
						lastmove = !lastmove;
					flipflop = !flipflop;
				}
				break;
			case '2':
				if(!halted)	
				{
					if(musicEnabled)
					{
						lynx_snd_stop();
						menutune=0;
						if(ingame && tunenum<2)
						{
							stopPCMSample();
							play_Tune();
						}
						else
						musicEnabled = 0;
					} 
					else
					{
						musicEnabled = 1;
						tunenum=2;
						stopPCMSample();
						play_Tune();
					}
				}
				break;

			case '3':// used to clear saves on eeprom pressing Opt1 + Opt2 while game is paused
				if(halted && !ingame)
				{
					resetSaveData();					
				}
				break;

			case '?': 
				break;

			default:
				break;
			}
		}
	} while(halted && !reset);
	
	return joy_read(JOY_1);
}

void play_PCM(int n)
{
	stopPCMSample();
	openn(n);
	playPCMSample();
}

