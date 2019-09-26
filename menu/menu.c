
#include <stdlib.h>
#include <stdio.h>
#include <6502.h>
#include <lynx.h>
#include <tgi.h>
#include <joystick.h>
#include <time.h>

#include "menubg1.pal"

void textxy (int x, int y, unsigned char*);
unsigned char checkInput(void);
void play_PCM(int n);
void __fastcall__ lynx_snd_play (unsigned char channel, unsigned char *music);
void lynx_snd_stop ();

typedef struct {
    unsigned char *music0;
    unsigned char *music1;
    unsigned char *music2;
    unsigned char *music3;
} song_t;

extern song_t musicptr;

extern unsigned char menubg1[];
extern unsigned char menubg2[];
extern unsigned char menubg3[];
extern unsigned char marker[];
extern unsigned char markeron[];
extern unsigned char select[];

extern unsigned char reset;
extern unsigned char musicEnabled;
extern unsigned char altview;
extern unsigned char lastmove;
extern unsigned int saveBuf[64]; 
extern unsigned char * saveptr;

unsigned char bgcount=0;

unsigned char * menubg[4] = {menubg1,menubg2,menubg3,menubg2};

extern int SAMPLE2_FILENR;

SCB_REHV_PAL sp_menubg = 
{
  BPP_4 | TYPE_BACKGROUND,
  REHV,
  0x01,
  0,
  menubg1,
  0, 0, 0x0100, 0x0100,
  { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef }
};

SCB_REHV_PAL sp_marker = 
{
  BPP_4 | TYPE_NORMAL,
  REHV,
  0x01,
  0,
  marker,
  63, 16, 0x0100, 0x0100,
  { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef }
};

SCB_REHV_PAL sp_select = 
{
  BPP_4 | TYPE_BACKGROUND,
  REHV,
  0x01,
  0,
  select,
  0, 0, 0x0100, 0x0100,
  { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef }
};

char offset[5] = {27,0,30,37,39};

unsigned char menu(void) {
	unsigned long now;
	char i=0;
	char done=0;
	unsigned char joy=1;
	unsigned char keypressed=1;
	sp_marker.data=marker;
	while(!done && !reset) 
	{
		sp_menubg.data=menubg[bgcount>>5];
		bgcount=(bgcount+1)%128;	
		tgi_sprite(&sp_menubg);

		sp_marker.vpos= 16+i*12;
		tgi_sprite(&sp_marker);
		
		tgi_updatedisplay();
		while (tgi_busy()) ;
		tgi_setpalette(menubg1_pal);

		joy = checkInput();
		if(JOY_BTN_FIRE(joy) && !keypressed)
		{
			done=1;
			play_PCM((int)&SAMPLE2_FILENR);
			keypressed =1;
		}
		if(JOY_BTN_UP(joy) && !keypressed)
		{
			i=(i+5)%6;
			play_PCM((int)&SAMPLE2_FILENR);
			keypressed =1;
		}
		if(JOY_BTN_DOWN(joy) && !keypressed)
		{
			i=(i+1)%6;
			play_PCM((int)&SAMPLE2_FILENR);
			keypressed =1;
		}
		if(!joy)
			keypressed =0;
	}

	tgi_sprite(&sp_menubg);
	sp_marker.data=markeron;
	sp_marker.vpos= 16+i*12;
	tgi_sprite(&sp_marker);
	
	tgi_updatedisplay();
	while (tgi_busy()) ;
	tgi_setpalette(menubg1_pal);

	now = clock();
	while (clock() < now + 40);

	return i;
}

unsigned char select2PMode(void) 
{
	char sel = 0;
	char done=0;
	unsigned char joy=1;

//	sp_menubg.data=menubg[2];
	
	while(!done && !reset) 
	{
		tgi_sprite(&sp_select);

		textxy(5,10,"SELECT A 2 PLAYERS MODE");

		textxy(15,30 ,"Same console");
		textxy(15,50 ,"Comlynx connection");
		
		textxy(5,30 +20*sel,">");

		tgi_updatedisplay();
		while (tgi_busy()) ;
		tgi_setpalette(menubg1_pal);

		while(joy && !reset)
			joy = checkInput();
		while(!joy && !reset)
			joy = checkInput();
		if(JOY_BTN_FIRE(joy))
		{
			done=1;
			play_PCM((int)&SAMPLE2_FILENR);
		}
		if(JOY_BTN_FIRE2(joy))
		{
			done=1;
			sel=2;
			play_PCM((int)&SAMPLE2_FILENR);
		}
		if(JOY_BTN_UP(joy)) 
		{
			sel = (sel+1)%2;
			play_PCM((int)&SAMPLE2_FILENR);
		}
		if(JOY_BTN_DOWN(joy))
		{
			sel = (sel+1)%2;
			play_PCM((int)&SAMPLE2_FILENR);
		}
	}
	return sel;
}


unsigned char selectGame(signed char p) {

	char i;
	char sel = 0;
	char done=0;
	unsigned char joy=1;
	char buf[35];

//	sp_menubg.data=menubg[2];
	
	while(!done && !reset) 
	{
		tgi_sprite(&sp_select);

		if(p==0)
			textxy(5,10,"SELECT A SAVE SLOT");
		else if(p==1)
			textxy(5,10,"SELECT P1 SAVE SLOT");
		else 
			textxy(5,10,"SELECT P2 SAVE SLOT");

		for (i=0;i<3;i++)
		{
			if(i!=(p-2))
			{
				if(saveptr[8+(40*i)])
				{
					if(saveptr[8+(40*i)]==255)
						sprintf(buf, "Slot %i : Rank %i   Gamed 254+",i+1,saveptr[9+(40*i)]/24);
					else
						sprintf(buf, "Slot %i : Rank %i   Games %i",i+1,saveptr[9+(40*i)]/24,saveptr[8+(40*i)] );
				}
				else
					sprintf(buf, "Slot %i : Empty",i+1);
				textxy(15,28 +18*i,buf);
			}
		}

		textxy(15,82,"Play Unranked");
		
		textxy(5,28 +18*sel,">");

		tgi_updatedisplay();
		while (tgi_busy()) ;
		tgi_setpalette(menubg1_pal);

		while(joy && !reset)
			joy = checkInput();
		while(!joy && !reset)
			joy = checkInput();
		if(JOY_BTN_FIRE(joy) && sel!=(p-2))
		{
			done=1;
			play_PCM((int)&SAMPLE2_FILENR);
		}
		if(JOY_BTN_FIRE2(joy))
		{
			done=1;
			sel=4;
			play_PCM((int)&SAMPLE2_FILENR);
		}
		if(JOY_BTN_UP(joy)) 
		{
			sel = (sel+3)%4;
			play_PCM((int)&SAMPLE2_FILENR);
		}
		if(JOY_BTN_DOWN(joy))
		{
			sel = (sel+1)%4;
			play_PCM((int)&SAMPLE2_FILENR);
		}
	}
	return sel;
}

signed char selectLevel(unsigned char rank) {

	signed char i=(rank/24)+1;
	char done=0;
	unsigned char joy=1;
	unsigned char blink=32;
	unsigned char keypressed=1;
	char buf[5];

	if(i>10)
		i=10;
	
//	sp_menubg.data=menubg[2];
	
	while(!done && !reset) 
	{
		tgi_sprite(&sp_select);

		textxy(5,10,"SELECT THE CPU STRENGTH");

		textxy(15,30,"CPU strength:");
		sprintf(buf, "%i",i);
		textxy(70,30,buf);
		textxy(15,54,"( 0 : Weak     10 : Strong )");

		if(blink++&32)
			textxy(5,93,"Press A to start the game");
		
		tgi_updatedisplay();
		while (tgi_busy()) ;
		tgi_setpalette(menubg1_pal);

		joy = checkInput();

		if(JOY_BTN_FIRE(joy) & !keypressed)
		{
			done=1;
			play_PCM((int)&SAMPLE2_FILENR);
			keypressed=1;
		}
		if(JOY_BTN_FIRE2(joy) & !keypressed)
		{
			i=-1;
			done=1;
			play_PCM((int)&SAMPLE2_FILENR);
			keypressed=1;
		}
		if((JOY_BTN_UP(joy) || JOY_BTN_RIGHT(joy)) && i<10  & !keypressed)
		{
			i++;
			play_PCM((int)&SAMPLE2_FILENR);
			keypressed=1;
		}
		if((JOY_BTN_DOWN(joy) || JOY_BTN_LEFT(joy))&& i>0  & !keypressed)
		{
			i--;
			play_PCM((int)&SAMPLE2_FILENR);
			keypressed=1;
		}
		if(!joy)
			keypressed=0;
	}
	return i;
}

unsigned char askPlayAgain(unsigned char cpu)
{

	unsigned char i=1+cpu;
	unsigned char done=0;
	unsigned char joy=1;
	unsigned char keypressed=1;
	unsigned char blink=32;

//	sp_menubg.data=menubg[2];
	
	while(!done && !reset) 
	{
		tgi_sprite(&sp_select);

		textxy(5,10,"PLAY AGAIN?");

		textxy(30,35,"Yes");
		if(cpu)
		{
			textxy(30,50,"Yes, changing CPU strength");
			textxy(30,65,"No");
		}
		else
			textxy(30,50,"No");
		textxy(20 ,50 + 15*cpu -(i*15),">");
		if(blink++&32)
			textxy(5,93,"Press A to select an option");
		
		tgi_updatedisplay();
		while (tgi_busy()) ;
		tgi_setpalette(menubg1_pal);

		joy = checkInput();

		if(JOY_BTN_FIRE(joy) && !keypressed)
		{
			done=1;
			play_PCM((int)&SAMPLE2_FILENR);
			keypressed=1;
		}
		if(JOY_BTN_UP(joy) && !keypressed)
		{
			i=(i+1)%(2+cpu);
			play_PCM((int)&SAMPLE2_FILENR);
			keypressed=1;
		}
		if(JOY_BTN_DOWN(joy) && !keypressed)
		{
			i=(i+1+cpu)%(2+cpu);
			play_PCM((int)&SAMPLE2_FILENR);
			keypressed=1;
		}
		if(!joy)
			keypressed=0;
	}
	return i;
}

void options(void) {

	unsigned char i=0;
	unsigned char done=0;
	unsigned char joy=1;
	unsigned char keypressed=1;
	unsigned char blink=32;

//	sp_menubg.data=menubg[2];
	
	while(!done && !reset) 
	{
		tgi_sprite(&sp_select);

		textxy(5,10,"GAME OPTIONS");

		textxy(15,30,"Show alternate views:");
		textxy(15,45,"Show last move:");
		textxy(15,60,"Musics:");
		textxy(15,75,"Save and exit options menu");

		textxy(5,30 + (i*15),">");

		if(altview)
			textxy(130,30,"Yes");
		else
			textxy(130,30,"No");

		if(lastmove)
			textxy(130,45,"Yes");
		else
			textxy(130,45,"No");
		
		if(musicEnabled)
			textxy(130,60,"On");
		else
			textxy(130,60,"Off");
		
		if(blink++&32)
			textxy(5,93,"Press A to change options");
		
		tgi_updatedisplay();
		while (tgi_busy()) ;
		tgi_setpalette(menubg1_pal);

		joy = checkInput();
		if(JOY_BTN_FIRE(joy) && !keypressed)
		{
			if(i==0)
				altview = !altview;
			else if(i==1)
				lastmove = !lastmove;
			else if(i==2)
			{
				musicEnabled = !musicEnabled;
				if(musicEnabled)
				{
					lynx_snd_play(0, musicptr.music0);
					lynx_snd_play(1, musicptr.music1);
					lynx_snd_play(2, musicptr.music2);
				}
				else
					lynx_snd_stop();
			}
			else if(i==3)
				done=1;
			play_PCM((int)&SAMPLE2_FILENR);
			keypressed=1;
		}
		if(JOY_BTN_UP(joy) && !keypressed)
		{
			i=(i+3)%4;
			play_PCM((int)&SAMPLE2_FILENR);
			keypressed=1;
		}
		if(JOY_BTN_DOWN(joy) && !keypressed)
		{
			i=(i+1)%4;
			play_PCM((int)&SAMPLE2_FILENR);
			keypressed=1;
		}
		if(!joy)
			keypressed=0;
	}
}

