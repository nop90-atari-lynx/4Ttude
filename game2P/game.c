
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <6502.h>
#include <lynx.h>
#include <tgi.h>
#include <joystick.h>
#include "gboard.h"
#include "comboset.h"
#include "net.h"

#include "palette.pal"

void textxy(int, int, unsigned char*);
unsigned char checkInput(void);
void play_Tune(void);
void play_PCM(int n);
void __fastcall__ lynx_snd_play (unsigned char channel, unsigned char *music);
void lynx_snd_stop ();
void stopPCMSample(void);

	GBOARD		brd2;
	COMBOSET	cs2;
	
signed char posx2,posy2,posz2;
unsigned char moves2;
unsigned char oldmusic;
unsigned char keypressed;
char gbuf2[5];
unsigned char oldflipflop2;
int lastplayed2[64];
unsigned char gridoffset2;

extern unsigned char background2[];
extern unsigned char grid02[];
extern unsigned char gridSmall2[];
extern unsigned char cursor02[];
extern unsigned char cursor12[];
extern unsigned char tile12[];
extern unsigned char tile22[];
extern unsigned char dot02[];
extern unsigned char dot12[];
extern unsigned char dot22[];
extern unsigned char dleft2[];
extern unsigned char dright2[];

extern unsigned char reset;
extern unsigned char musicEnabled;
extern unsigned char altview;
extern unsigned char lastmove;
extern unsigned char ingame;
extern unsigned char flipflop;
extern unsigned char tunenum;

typedef struct {
    unsigned char *music0;
    unsigned char *music1;
    unsigned char *music2;
    unsigned char *music3;
} song_t;

extern song_t musicptr;

extern int SAMPLE0_FILENR;
extern int SAMPLE1_FILENR;
extern int SAMPLE2_FILENR;
extern int TUNE1_FILENR;
extern int TUNE2_FILENR;
extern int TUNE3_FILENR;

SCB_REHV_PAL sp_bg2 = 
{
  BPP_4 | TYPE_BACKGROUND,
  REHV,
  0x01,
  0,
  background2,
  0, 0, 0x0100, 0x0100,
  { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef }
};

SCB_RENONE_PAL sp_grid2 = 
{
  BPP_4 | TYPE_NORMAL,
  REUSEPAL,
  0x01,
  0,
  grid02,
  0, 0
};

SCB_RENONE_PAL sp_gridsmall2 = 
{
  BPP_4 | TYPE_NORMAL,
  REUSEPAL,
  0x01,
  0,
  gridSmall2,
  0, 0
};

SCB_RENONE_PAL sp_tile2 = 
{
  BPP_4 | TYPE_NORMAL,
  REUSEPAL,
  0x01,
  0,
  cursor02,
  0, 0
};

unsigned char newRank2(unsigned char rank1,unsigned char rank2, unsigned char winner, int moves)
{
	int newrank;
	if(winner==1)
	{
		if(rank1<rank2)
		{
			if((rank2-rank1)>20)
			{
				if(moves<=20)
					newrank =(rank1+30);
				else if(moves<=40)	
					newrank = (rank1+20);
				else 	
					newrank = (rank1+10);
			}
			else if((rank2-rank1)>10)
			{
				if(moves<=20)
					newrank = (rank1+20);
				else if(moves<=40)	
					newrank = (rank1+10);
				else 	
					newrank = (rank1+5);
			}
			else
			{
				if(moves<=20)
					newrank = (rank1+15);
				else if(moves<=40)	
					newrank = (rank1+6);
				else 	
					newrank = (rank1+3);
			}
		}
		else
		{
			if((rank1-rank2)<10)
				newrank = rank1+1;
			else 
				newrank = rank1;
		}
		
	}
	else
	{
		if(rank1>rank2)
		{
			if((rank1-rank2)>20)
			{
				if(moves<=20)
					newrank =(rank1-15);
				else if(moves<=40)	
					newrank = (rank1-10);
				else 	
					newrank = (rank1-5);
			}
			else if((rank1-rank2)>10)
			{
				if(moves<=20)
					newrank = (rank1-10);
				else if(moves<=40)	
					newrank = (rank1-7);
				else 	
					newrank = (rank1-3);
			}
			else
			{
				if(moves<=20)
					newrank = (rank1-7);
				else if(moves<=40)	
					newrank = (rank1-4);
				else 	
					newrank = (rank1-2);
			}
		}
		else
		{
			if((rank1-rank2)<10)
				newrank = rank1-1;
			else 
				newrank = rank1;
		}
	}
	if(newrank>254)
		newrank=254;
	if(newrank<0)
		newrank=0;
	return (unsigned char) newrank;	
};

/*
 * getmove
 *

 */
signed char	getmove2(void) {
	unsigned char joy=1;

//	while(joy && !reset)
		joy = checkInput();
//	while(!joy && !reset && flipflop==oldflipflop2)
//		joy = checkInput();
	if(JOY_BTN_FIRE(joy) && !keypressed)
	{
		keypressed=1;
		return coordtoint2(posx2, posy2, posz2);	
	}
	if(JOY_BTN_RIGHT(joy) && !keypressed)
	{
		keypressed=1;
		posx2++;
		if(posx2==4)
		{
			posx2=0;
			posz2= (posz2+1)%4;
			play_PCM((int)&SAMPLE1_FILENR);
		}
		else
			play_PCM((int)&SAMPLE2_FILENR);
		return -1;
	}
	if(JOY_BTN_LEFT(joy) && !keypressed)
	{
		keypressed=1;
		posx2--;
		if(posx2==-1)
		{
			posx2=3;
			posz2= (posz2+3)%4;
			play_PCM((int)&SAMPLE1_FILENR);
		}
		else
			play_PCM((int)&SAMPLE2_FILENR);
		return -1;
	}
	if(JOY_BTN_UP(joy) && !keypressed)
	{
		keypressed=1;
		posy2--;
		if(posy2==-1)
		{
			posy2=3;
			posz2= (posz2+3)%4;
			play_PCM((int)&SAMPLE1_FILENR);
		}
		else
			play_PCM((int)&SAMPLE2_FILENR);
		return -1;
	}
	if(JOY_BTN_DOWN(joy) && !keypressed)
	{
		keypressed=1;
		posy2++;
		if(posy2==4)
		{
			posy2=0;
			posz2= (posz2+1)%4;
			play_PCM((int)&SAMPLE1_FILENR);
		}
		else
			play_PCM((int)&SAMPLE2_FILENR);
		return -1;
	}

	if(!joy)
		keypressed=0;
		
	return -1;
}

void drawBoard2(void)
{
	char i;
	char x,y,z;

	tgi_sprite(&sp_bg2);
	sp_grid2.hpos=73 + gridoffset2;
	sp_grid2.vpos=13;
	for(i=0;i<4;i++)
	{
		tgi_sprite(&sp_grid2);
		sp_grid2.vpos+=22;
	}

	if(altview)
	{
		sp_gridsmall2.hpos=131;
		sp_gridsmall2.vpos=13;
		tgi_sprite(&sp_gridsmall2);
		sp_gridsmall2.vpos=28;
		tgi_sprite(&sp_gridsmall2);
		sp_gridsmall2.vpos=43;
		tgi_sprite(&sp_gridsmall2);
		sp_gridsmall2.vpos=58;
		tgi_sprite(&sp_gridsmall2);
		sp_gridsmall2.hpos=146;
		sp_gridsmall2.vpos=13;
		tgi_sprite(&sp_gridsmall2);
		sp_gridsmall2.vpos=28;
		tgi_sprite(&sp_gridsmall2);
		sp_gridsmall2.vpos=43;
		tgi_sprite(&sp_gridsmall2);
		sp_gridsmall2.vpos=58;
		tgi_sprite(&sp_gridsmall2);
		sp_tile2.data = dleft2;
		sp_tile2.hpos=131;
		sp_tile2.vpos=73;
		tgi_sprite(&sp_tile2);
		sp_tile2.hpos=146;
		sp_tile2.vpos=88;
		tgi_sprite(&sp_tile2);
		sp_tile2.data = dright2;
		sp_tile2.hpos=131;
		tgi_sprite(&sp_tile2);
		sp_tile2.hpos=146;
		sp_tile2.vpos=73;
		tgi_sprite(&sp_tile2);
	}
	
	for(z=0;z<4;z++)
		for(y=0;y<4;y++)
			for(x=0;x<4;x++)
			{
				if(brd2.m_spots[z*16+y*4+x]==GB_WHITE)
				{
					sp_tile2.data= tile12;
					sp_tile2.hpos= 75 + 9*x + 5* y + gridoffset2;
					sp_tile2.vpos= 14 + 5*y + 22* z;
					tgi_sprite(&sp_tile2);
					
					if(altview)
					{
						sp_tile2.data= dot12;
						sp_tile2.hpos= 132 + 3*y;
						sp_tile2.vpos= 14 + 3*z + 15* x;
						tgi_sprite(&sp_tile2);
						sp_tile2.hpos= 147 + 3*x;
						sp_tile2.vpos= 14 + 3*z + 15* (3-y);
						tgi_sprite(&sp_tile2);
						if(x==y)
						{
							if(x==z)
							{
								sp_tile2.hpos= 132 + 3*x;
								sp_tile2.vpos= 14 + 60 + 3*x;
								tgi_sprite(&sp_tile2);
							}
							if(x==3-z)
							{
								sp_tile2.hpos= 147 + 3*x;
								sp_tile2.vpos= 14 + 75 + 3*x;
								tgi_sprite(&sp_tile2);
							}
						}
						if(x==3-y)
						{
							if(x==z)
							{
								sp_tile2.hpos= 132 + 3*x;
								sp_tile2.vpos= 14 + 75 + 9 - 3*x;
								tgi_sprite(&sp_tile2);
							}
							if(x==3-z)
							{
								sp_tile2.hpos= 147 + 3*x;
								sp_tile2.vpos= 14 + 60 + 9 - 3*x;
								tgi_sprite(&sp_tile2);
							}
						}
					}
				}
				
				if(brd2.m_spots[z*16+y*4+x]==GB_BLACK)
				{
					sp_tile2.data= tile22;
					sp_tile2.hpos= 75 + 9*x + 5* y + gridoffset2;
					sp_tile2.vpos= 14 + 5*y + 22* z;
					tgi_sprite(&sp_tile2);
					
					if(altview)
					{
						sp_tile2.data= dot22;
						sp_tile2.hpos= 132 + 3*y;
						sp_tile2.vpos= 14 + 3*z + 15* x;
						tgi_sprite(&sp_tile2);
						sp_tile2.hpos= 147 + 3*x;
						sp_tile2.vpos= 14 + 3*z + 15* (3-y);
						tgi_sprite(&sp_tile2);
						if(x==y)
						{
							if(x==z)
							{
								sp_tile2.hpos= 132 + 3*x;
								sp_tile2.vpos= 14 + 60 + 3*x;
								tgi_sprite(&sp_tile2);
							}
							if(x==3-z)
							{
								sp_tile2.hpos= 147 + 3*x;
								sp_tile2.vpos= 14 + 75 + 3*x;
								tgi_sprite(&sp_tile2);
							}
						}
						if(x==3-y)
						{
							if(x==z)
							{
								sp_tile2.hpos= 132 + 3*x;
								sp_tile2.vpos= 14 + 75 + 9 - 3*x;
								tgi_sprite(&sp_tile2);
							}
							if(x==3-z)
							{
								sp_tile2.hpos= 147 + 3*x;
								sp_tile2.vpos= 14 + 60 + 9 - 3*x;
								tgi_sprite(&sp_tile2);
							}
						}
					}
				}
			}
}

void changeTune(unsigned char tune)
{
	if(tune==3)
	{
		if(musicEnabled)
		{
			lynx_snd_stop();
			musicEnabled=0;
			tunenum=2;
		}
	}
	else
	{
		stopPCMSample();
		tunenum=tune;
		if(musicEnabled)
			lynx_snd_stop();
		else
			musicEnabled=1;
		if(tunenum==0)
			lynx_load((int)&TUNE1_FILENR);
		else if(tunenum==1)
			lynx_load((int)&TUNE2_FILENR);
		if(tunenum==2)
			lynx_load((int)&TUNE3_FILENR);
		lynx_snd_play(0, musicptr.music0);
		lynx_snd_play(1, musicptr.music1);
		lynx_snd_play(2, musicptr.music2);
	}
}


unsigned char netgame(unsigned char rank)
{
	unsigned char playerID;
	unsigned char x,y,z,i;
	unsigned char joy=1;
	unsigned char keypressed=1;
	unsigned char done=0;
	unsigned char blink=32;
	int	mv=-1;

	ingame = 1;

	play_Tune();
	
	if(musicEnabled)
		oldmusic=tunenum;
	else
		oldmusic = 3;
	
	brd2.currMusic = oldmusic;
	if(netConnect())
		playerID=GB_BLACK;
	else 	
	{
		playerID=GB_WHITE;
		keypressed=1;
		while(!netListen() && !reset)
		{
			tgi_sprite(&sp_bg2);

			textxy(48,40,"WAITING PLAYER 2");
			if(blink++&32)
				textxy(49,93,"Press B to cancel");
			
			tgi_updatedisplay();
			while (tgi_busy()) ;
			tgi_setpalette(gfx2_pal);

			joy = checkInput();
			if(JOY_BTN_FIRE2(joy))
			{
				ingame = 0;
				return 255;
			}
			if(!joy)
				keypressed=0;
		}
	}
		
	gb2_reset(&brd2);
	cs2_init(&cs2);

	posx2=0;
	posy2=0;
	posz2=0;
	moves2=1;

	// white: fill board with rank info and send to slave
	if(playerID==GB_WHITE)
	{
		brd2.lastBlack=-1;
		brd2.lastWhite=-1;
		brd2.cursorBlack=0;
		brd2.cursorWhite=0;
		brd2.netreset=0;
		if(musicEnabled)
			brd2.currMusic=tunenum;
		else	
			brd2.currMusic=3;
		brd2.rankWhite=rank;
		netSendData((char *)&brd2,sizeof(brd2));
		netReceiveData((char *)&brd2,sizeof(brd2));
	}
	else
	{
	// black: fills rank info e send back the board
		netReceiveData((char *)&brd2,sizeof(brd2));
		brd2.rankBlack=rank;
		netSendData((char *)&brd2,sizeof(brd2));
	}
	
	oldmusic=brd2.currMusic;
	changeTune(oldmusic);
	
// let's start
	while(!gb2_gameover(&brd2) && !brd2.netreset) {

		if(brd2.m_lastturn !=playerID)
		{
			do {
				oldflipflop2 = flipflop;
				if(altview)
					gridoffset2=0;
				else
					gridoffset2=26;
//draw board
				drawBoard2();

				if(lastmove && brd2.lastBlack>=0)
				{
					x=brd2.lastBlack&3;
					y=(brd2.lastBlack>>2)&3;
					z=(brd2.lastBlack>>4)&3;
					sp_tile2.data= cursor12;
					sp_tile2.hpos= 75 + 9*x + 5*y + gridoffset2;
					sp_tile2.vpos= 14 + 5*y + 22*z;
					tgi_sprite(&sp_tile2);
				}
				if(lastmove && brd2.lastWhite>=0)
				{
					x=brd2.lastWhite&3;
					y=(brd2.lastWhite>>2)&3;
					z=(brd2.lastWhite>>4)&3;
					sp_tile2.data= cursor12;
					sp_tile2.hpos= 75 + 9*x + 5*y + gridoffset2;
					sp_tile2.vpos= 14 + 5*y + 22*z;
					tgi_sprite(&sp_tile2);
				}

				sp_tile2.data= cursor02;
				sp_tile2.hpos= 75 + 9*posx2 + 5* posy2 + gridoffset2;
				sp_tile2.vpos= 14 + 5*posy2 + 22* posz2;
				tgi_sprite(&sp_tile2);

				if(altview)
				{

					sp_tile2.data= dot02;
					sp_tile2.hpos= 132 + 3*posy2;
					sp_tile2.vpos= 14 + 3*posz2 + 15* posx2;
					tgi_sprite(&sp_tile2);
					sp_tile2.hpos= 147 + 3*posx2;
					sp_tile2.vpos= 14 + 3*posz2 + 15* (3-posy2);
					tgi_sprite(&sp_tile2);

					if(posx2==posy2)
					{
						if(posx2==posz2)
						{
							sp_tile2.hpos= 132 + 3*posx2;
							sp_tile2.vpos= 14 + 60 + 3*posx2;
							tgi_sprite(&sp_tile2);
						}
						if(posx2==3-posz2)
						{
							sp_tile2.hpos= 147 + 3*posx2;
							sp_tile2.vpos= 14 + 75 + 3*posx2;
							tgi_sprite(&sp_tile2);
						}
					}
					if(posx2==3-posy2)
					{
						if(posx2==posz2)
						{
							sp_tile2.hpos= 132 + 3*posx2;
							sp_tile2.vpos= 14 + 75 + 9 - 3*posx2;
							tgi_sprite(&sp_tile2);
						}
						if(posx2==3-posz2)
						{
							sp_tile2.hpos= 147 + 3*posx2;
							sp_tile2.vpos= 14 + 60 + 9 - 3*posx2;
							tgi_sprite(&sp_tile2);
						}
					}
				}
				
				textxy(4,7,"Your turn");
				textxy(43+(moves2<10?2:0),16,"move");
				sprintf(gbuf2,"%i",moves2);
				textxy(65+(moves2<10?2:0),16,gbuf2);
				textxy(3,26,"Your rank");
				textxy(3,34,"vs rank");
				sprintf(gbuf2,"%i",rank/24);
				textxy(41,26,gbuf2);
				sprintf(gbuf2,"%i",((playerID==GB_WHITE)?brd2.rankBlack:brd2.rankWhite)/24);
				textxy(33,34,gbuf2);

				tgi_updatedisplay();
				while (tgi_busy()) ;
				tgi_setpalette(gfx2_pal);

				mv = getmove2();
				if(playerID==GB_WHITE)
					brd2.cursorWhite=coordtoint2(posx2,posy2,posz2);
				else
					brd2.cursorBlack=coordtoint2(posx2,posy2,posz2);
				
				brd2.netreset=reset;
				if(musicEnabled)
					oldmusic=tunenum;
				else
					oldmusic = 3;
				brd2.currMusic=oldmusic;
				netSendData((char *)&brd2,sizeof(brd2));
				netReceiveData((char *)&brd2,sizeof(brd2));
				if(brd2.currMusic!=oldmusic)
					changeTune(brd2.currMusic);
				reset|=brd2.netreset;
			} while(!legal2(&brd2, playerID, mv) && !brd2.netreset);

			if(!brd2.netreset)
			{
				gb2_place(&brd2, playerID, mv);
				if(playerID==GB_WHITE)
					brd2.lastWhite=mv;
				else
					brd2.lastBlack=mv;
				if (cs2_place(&cs2,  playerID, mv))
					brd2.m_winner = playerID;
				play_PCM((int)&SAMPLE0_FILENR);
				netSendData((char *)&brd2,sizeof(brd2));
				netReceiveData((char *)&brd2,sizeof(brd2));
			}
		}
		else
		{
			do {
				if(altview)
					gridoffset2=0;
				else
					gridoffset2=26;
				drawBoard2();
				if(lastmove && brd2.lastBlack>=0)
				{
					x=brd2.lastBlack&3;
					y=(brd2.lastBlack>>2)&3;
					z=(brd2.lastBlack>>4)&3;
					sp_tile2.data= cursor12;
					sp_tile2.hpos= 75 + 9*x + 5*y + gridoffset2;
					sp_tile2.vpos= 14 + 5*y + 22*z;
					tgi_sprite(&sp_tile2);
				}
				if(lastmove && brd2.lastWhite>=0)
				{
					x=brd2.lastWhite&3;
					y=(brd2.lastWhite>>2)&3;
					z=(brd2.lastWhite>>4)&3;
					sp_tile2.data= cursor12;
					sp_tile2.hpos= 75 + 9*x + 5*y + gridoffset2;
					sp_tile2.vpos= 14 + 5*y + 22*z;
					tgi_sprite(&sp_tile2);
				}

				if(playerID==GB_BLACK)
				{
					x=brd2.cursorWhite&3;
					y=(brd2.cursorWhite>>2)&3;
					z=(brd2.cursorWhite>>4)&3;
					sp_tile2.data= cursor02;
					sp_tile2.hpos= 75 + 9*x + 5*y + gridoffset2;
					sp_tile2.vpos= 14 + 5*y + 22*z;
					tgi_sprite(&sp_tile2);
				}
				if(playerID==GB_WHITE)
				{
					x=brd2.cursorBlack&3;
					y=(brd2.cursorBlack>>2)&3;
					z=(brd2.cursorBlack>>4)&3;
					sp_tile2.data= cursor02;
					sp_tile2.hpos= 75 + 9*x + 5*y + gridoffset2;
					sp_tile2.vpos= 14 + 5*y + 22*z;
					tgi_sprite(&sp_tile2);
				}

				textxy(4,7,"Opponent");
				textxy(43+(moves2<10?2:0),16,"Move");
				sprintf(gbuf2,"%i",moves2);
				textxy(65+(moves2<10?2:0),16,gbuf2);
				textxy(3,26,"Your rank");
				textxy(3,34,"vs rank");
				sprintf(gbuf2,"%i",rank/24);
				textxy(41,26,gbuf2);
				sprintf(gbuf2,"%i",((playerID==GB_WHITE)?brd2.rankBlack:brd2.rankWhite)/24);
				textxy(33,34,gbuf2);
				tgi_updatedisplay();
				while (tgi_busy()) ;
				tgi_setpalette(gfx2_pal);
				netReceiveData((char *)&brd2,sizeof(brd2));
				if(brd2.currMusic!=oldmusic)
					changeTune(brd2.currMusic);
				checkInput();
				if(musicEnabled)
					oldmusic=tunenum;
				else
					oldmusic = 3;
				brd2.currMusic=oldmusic;
				brd2.netreset|=reset;
				netSendData((char *)&brd2,sizeof(brd2));
				reset=brd2.netreset;
			} while (brd2.m_lastturn ==playerID && !brd2.netreset);
			play_PCM((int)&SAMPLE0_FILENR);
		}

		moves2++;

	}

	i=16;

	// Print the final (winning) copy of the board
	while(!done && !reset)
	{
		drawBoard2();

		if(brd2.m_winner==playerID)
			textxy(7,7,"You win");
		else if(brd2.m_winner!=GB_NOONE)
			textxy(5,7,"You lose");
		else
			textxy(13,7,"Even");

		if(i++&16)
			textxy(3,93,"Press A");

		tgi_updatedisplay();
		while (tgi_busy()) ;

		joy = checkInput();
		if(JOY_BTN_FIRE(joy) && !keypressed)
			done = 1;
		if(!joy)
			keypressed =0;
	}

		ingame = 0;
		// calculate and return new rank
	if(!reset)
	{
		if (rank==255)
			return 0;
		else
			return newRank2((playerID==GB_WHITE)?brd2.rankWhite:brd2.rankBlack, (playerID==GB_WHITE)?brd2.rankBlack:brd2.rankWhite, (brd2.m_winner==playerID)?1:2, moves2);
	}
	else
		return 255;
}

unsigned int game2P(unsigned char rank1, unsigned char rank2)
{
	unsigned char i,x,y,z;
	unsigned char joy=1;
	unsigned char keypressed=1;
	unsigned char done=0;
	int	mv=-1;
	unsigned int temp;

	ingame = 1;

	play_Tune();
	
	if(musicEnabled)
		oldmusic=tunenum;
	else
		oldmusic = 3;
	
	gb2_reset(&brd2);
	cs2_init(&cs2);

	posx2=0;
	posy2=0;
	posz2=0;
	moves2=1;

		brd2.lastBlack=-1;
		brd2.lastWhite=-1;
		brd2.cursorBlack=0;
		brd2.cursorWhite=0;

// let's start
	while(!gb2_gameover(&brd2) && !reset) {

		do {
			oldflipflop2 = flipflop;
			if(altview)
				gridoffset2=0;
			else
				gridoffset2=26;
//draw board
			drawBoard2();

			if(lastmove && brd2.lastBlack>=0)
			{
				x=brd2.lastBlack&3;
				y=(brd2.lastBlack>>2)&3;
				z=(brd2.lastBlack>>4)&3;
				sp_tile2.data= cursor12;
				sp_tile2.hpos= 75 + 9*x + 5*y + gridoffset2;
				sp_tile2.vpos= 14 + 5*y + 22*z;
				tgi_sprite(&sp_tile2);
			}
			if(lastmove && brd2.lastWhite>=0)
			{
				x=brd2.lastWhite&3;
				y=(brd2.lastWhite>>2)&3;
				z=(brd2.lastWhite>>4)&3;
				sp_tile2.data= cursor12;
				sp_tile2.hpos= 75 + 9*x + 5*y + gridoffset2;
				sp_tile2.vpos= 14 + 5*y + 22*z;
				tgi_sprite(&sp_tile2);
			}

			sp_tile2.data= cursor02;
			sp_tile2.hpos= 75 + 9*posx2 + 5* posy2 + gridoffset2;
			sp_tile2.vpos= 14 + 5*posy2 + 22* posz2;
			tgi_sprite(&sp_tile2);

			if(altview)
			{

				sp_tile2.data= dot02;
				sp_tile2.hpos= 132 + 3*posy2;
				sp_tile2.vpos= 14 + 3*posz2 + 15* posx2;
				tgi_sprite(&sp_tile2);
				sp_tile2.hpos= 147 + 3*posx2;
				sp_tile2.vpos= 14 + 3*posz2 + 15* (3-posy2);
				tgi_sprite(&sp_tile2);

				if(posx2==posy2)
				{
					if(posx2==posz2)
					{
						sp_tile2.hpos= 132 + 3*posx2;
						sp_tile2.vpos= 14 + 60 + 3*posx2;
						tgi_sprite(&sp_tile2);
					}
					if(posx2==3-posz2)
					{
						sp_tile2.hpos= 147 + 3*posx2;
						sp_tile2.vpos= 14 + 75 + 3*posx2;
						tgi_sprite(&sp_tile2);
					}
				}
				if(posx2==3-posy2)
				{
					if(posx2==posz2)
					{
						sp_tile2.hpos= 132 + 3*posx2;
						sp_tile2.vpos= 14 + 75 + 9 - 3*posx2;
						tgi_sprite(&sp_tile2);
					}
					if(posx2==3-posz2)
					{
						sp_tile2.hpos= 147 + 3*posx2;
						sp_tile2.vpos= 14 + 60 + 9 - 3*posx2;
						tgi_sprite(&sp_tile2);
					}
				}
			}
			
			
			if(brd2.m_lastturn==GB_BLACK)
				textxy(8,7,"P1 turn");
			else
				textxy(8,7,"P2 turn");
			textxy(43+(moves2<10?2:0),16,"move");
			sprintf(gbuf2,"%i",moves2);
			textxy(65+(moves2<10?2:0),16,gbuf2);
			if(rank1<255)
			{
				textxy(3,24,"P1 rank");
				textxy(3,34,"P2 rank");
				sprintf(gbuf2,"%i",rank1/24);
				textxy(32,24,gbuf2);
				sprintf(gbuf2,"%i",rank2/24);
				textxy(32,34,gbuf2);
			}
			else
				textxy(3,24,"Unranked");
			
			tgi_updatedisplay();
			while (tgi_busy()) ;
			tgi_setpalette(gfx2_pal);

			mv = getmove2();
			if(brd2.m_lastturn==GB_BLACK)
				brd2.cursorWhite=coordtoint2(posx2,posy2,posz2);
			else
				brd2.cursorBlack=coordtoint2(posx2,posy2,posz2);
			
		} while(!legal2(&brd2, (brd2.m_lastturn==GB_BLACK)?GB_WHITE:GB_BLACK, mv) && !reset);

		if(!reset)
		{
			if(brd2.m_lastturn==GB_BLACK)
			{
				gb2_place(&brd2, GB_WHITE, mv);
				brd2.lastWhite=mv;
				if (cs2_place(&cs2,  GB_WHITE, mv))
					brd2.m_winner = GB_WHITE;
			}
			else
			{
				gb2_place(&brd2, GB_BLACK, mv);
				brd2.lastBlack=mv;
				if (cs2_place(&cs2,  GB_BLACK, mv))
					brd2.m_winner = GB_BLACK;
			}
			moves2++;
			play_PCM((int)&SAMPLE0_FILENR);
		}
	}
	i=16;
	keypressed = 1;
	// Print the final (winning) copy of the board
	while(!done && !reset)
	{
		drawBoard2();

		if(brd2.m_winner==GB_WHITE)
			textxy(7,7,"P1 wins");
		else if(brd2.m_winner!=GB_NOONE)
			textxy(7,7,"P2 wins");
		else
			textxy(13,7,"Even");

		if(i++&16)
			textxy(3,93,"Press A");

		tgi_updatedisplay();
		while (tgi_busy()) ;

		joy = checkInput();
		if(JOY_BTN_FIRE(joy) && !keypressed)
			done = 1;
		if(!joy)
			keypressed = 0;
	}

		ingame = 0;
		// calculate and return new rank
	if(!reset)
	{
		if (rank1==255)
			return 0;
		else
		{
			temp = newRank2(rank1, rank2, (brd2.m_winner==GB_WHITE)?1:2, moves2);
			temp = temp | (newRank2(rank2, rank1, (brd2.m_winner==GB_WHITE)?2:1, moves2)<<8);
			return temp;
		}
	}
	else
		return 255;
}
