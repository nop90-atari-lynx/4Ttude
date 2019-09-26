
#include <stdlib.h>
#include <stdio.h>
#include <6502.h>
#include <lynx.h>
#include <tgi.h>
#include <joystick.h>

#include "creditsbg.pal"
#include "tutorialbg.pal"
#include "grid.pal"

#define MAXPAGE 16

void textxy (int x, int y, unsigned char*);
unsigned char checkInput(void);
void play_PCM(int n);
void __fastcall__ lynx_snd_play (unsigned char channel, unsigned char *music);
void lynx_snd_stop ();

extern unsigned char creditsbg[];
extern unsigned char tutorialbg[];
extern unsigned char marks000000[];
extern unsigned char marks000001[];
extern unsigned char pressA000000[];
extern unsigned char pressA001000[];

extern const char * tuttxt[11];

extern unsigned char reset;
extern unsigned char musicEnabled;

extern int SAMPLE2_FILENR;

unsigned char* spMarks[2] =  
{
	marks000000, marks000001
};

unsigned char marktype[9]={0,1,2,0,1,0,1,1,2};
unsigned char markstate[9]={0,1,0,1,0,1,0,1,0};

extern unsigned char grid[];
extern unsigned int saveBuf[64]; 
extern unsigned char * saveptr;

char creditstxt[16][44]=
{
"4TTUDE/an advanced 3D/Tic-Tac-Toe          ",
"Atari Lynx 30th/birthday coding/competition",
"Engine core by/Dan Gisseluist/GPL v3      ",
"Game concept/and Lynx/coding by/NOP90      ",
"GFX design by/Martial Daviaud/(MARSS)      ",
"Music adapted/from public/domain tunes     ",
"Menu tune/Moongazer/by Dr. Awesome         ",
"Tune 1/Water Resist/by Ace of/The Zynaps   ",
"Tune 2/Rainbow/by Baroque                  ",
"Tune 3/Volcano/by Leon and/Excess          ",
"Original tunes/are on/modarchive.org       ",
"the digital/copy of this/game is free      ",
"can be freely/published on/web sites       ",
"or in digital/Lynx game/compilations       ",
"Distribution as/Lynx card/is reserved      ",
"Leave comments/on atariage.com/forum!      "
};

SCB_REHV_PAL sp_credits = 
{
  BPP_4 | TYPE_BACKGROUND,
  REHV,
  0x01,
  0,
  creditsbg,
  0, 0, 0x0100, 0x0100,
  { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef }
};

SCB_REHV_PAL sp_mark = 
{
  BPP_4 | TYPE_NORMAL,
  REHV,
  0x01,
  0,
  marks000000,
  63, 16, 0x0100, 0x0100,
  { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef }
};

SCB_REHV_PAL sp_pressA = 
{
  BPP_4 | TYPE_NORMAL,
  REHV,
  0x01,
  0,
  pressA000000,
  130, 95, 0x0100, 0x0100,
  { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef }
};

SCB_REHV_PAL sp_tutorial = 
{
  BPP_4 | TYPE_BACKGROUND,
  REHV,
  0x01,
  0,
  tutorialbg,
  0, 0, 0x0100, 0x0100,
  { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef }
};

SCB_REHV_PAL sp_rankgrid = 
{
  BPP_4 | TYPE_BACKGROUND,
  REHV,
  0x01,
  0,
  grid,
  0, 0, 0x0100, 0x0100,
  { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef }
};

void updatemarks(unsigned int seed)
{
	unsigned char m= (seed>>1)%9;
	markstate[m]=1-markstate[m];
};
void drawmarks(void)
{
	unsigned char i,j;
	for (j=0;j<3;j++)
		for (i=0;i<3;i++)
			if(markstate[j*3+i] && marktype[j*3+i]<2)
			{
				sp_mark.hpos=12+25*i;
				sp_mark.vpos=17+25*j;
				sp_mark.data=spMarks[marktype[j*3+i]];
				tgi_sprite(&sp_mark);
			}
}

void credits(void) 
{

	char i=0;
	char done=0;
	unsigned char joy=1;
	unsigned char keypressed=1;
	char creditbuf[43];
	unsigned int counter=0;	
	char j,k;
	creditbuf[43]=0;
	k=15;
	while(!done && !reset) 
	{

		if(counter == 0)
		{
			for(j=0;j<44;j++)
				creditbuf[j]=' ';
			j=0;
			k=(k+1)%16;
		};
		if(counter&15)		
		{
			if(counter&1)
				updatemarks(counter);
			if(j<43)
				creditbuf[j]=creditstxt[k][j];
			j++;
		};
		counter++;
		if(j>128)
			counter=0;
	
		tgi_sprite(&sp_credits);
		drawmarks();
		textxy(93,34,creditbuf);
		tgi_updatedisplay();
		while (tgi_busy()) ;
		tgi_setpalette(creditsbg_pal);

		joy = checkInput();
		if(JOY_BTN_FIRE(joy) && !keypressed)
		{
			done=1;
			keypressed =1;
		}

		if(!joy)
			keypressed =0;
	}

}

void tutorial(void) 
{
	unsigned char page=0;
	char done=0;
	unsigned char joy=1;
	unsigned char keypressed=1;
	char tutorialbuf[14];

	while(!done && !reset) 
	{
		tgi_sprite(&sp_tutorial);
		sprintf(tutorialbuf, "Page %i", page+1);
		textxy(124,23,tutorialbuf);
		textxy(10,32,(char*)tuttxt[page]);
		tgi_updatedisplay();
		while (tgi_busy());
		tgi_setpalette(tutorialbg_pal);

		joy = checkInput();
		if(JOY_BTN_FIRE(joy) && !keypressed)
		{
			done=1;
			keypressed =1;
		}
		if(JOY_BTN_RIGHT(joy) && page<MAXPAGE-1 && !keypressed)
		{
			page++;
			keypressed =1;
		}
		if(JOY_BTN_LEFT(joy) && page>0 && !keypressed)
		{
			page--;
			keypressed =1;
		}
		if(!joy)
			keypressed =0;
	}
}

void showHistory(unsigned char pos) {

	char buf[21];
	unsigned char joy=1;
	unsigned char i;
	unsigned char games;
	unsigned char done=0;
	unsigned char count=0;
	unsigned char keypressed=1;

	while(!done && !reset)
	{

		tgi_setcolor(13);

		tgi_sprite(&sp_rankgrid);

		games = saveptr[8+(40*pos)];


		if(games>0)
		{
			textxy(80,1,"Games");
			if(games==255)
				textxy(106,1,"254+");
			else
			{
				sprintf(buf, "%i",games);
				textxy(106,1,buf);
			}
			sprintf(buf, "Slot %i         Rank %i",pos+1,saveptr[9+(40*pos)]/24);
		}
		else
			sprintf(buf, "Slot %i         Empty",pos+1);
		textxy(1,1,buf);

			for(i=1;i<10;i++)
			{
				sprintf(buf, "%i",i);
				textxy(31,91 - i*8,buf);
			}
			sprintf(buf, "%i",10);
			textxy(27,11,buf);
			
		if(games>0)
		{
			if (games < 38)
			{
				tgi_line(41,95, 43, 95-(saveptr[10+(40*pos)]/3));
				for(i=0;i<games-1;i++)
					tgi_line(43+3*i,95-(saveptr[10+i+(40*pos)]/3), 46+3*i, 95-(saveptr[11+i+(40*pos)]/3));
			}
			else
				for(i=0;i<38;i++)
					tgi_line(40+3*i,95-(saveptr[10+i+(40*pos)]/3), 43+3*i, 95-(saveptr[11+i+(40*pos)]/3));
		}
		
		if(count++&16)
			sp_pressA.data=pressA000000;
		else	
			sp_pressA.data=pressA001000;
		tgi_sprite(&sp_pressA);
			
		tgi_updatedisplay();
		while (tgi_busy()) ;
		tgi_setpalette(grid_pal);

		joy = checkInput();
		if(joy && !keypressed)
			done=1;
		if(!joy)
			keypressed=0;
	}
}

void showHistory2P(unsigned char pos1, unsigned char pos2) {

	char buf[21];
	unsigned char joy=1;
	unsigned char i;
	unsigned char games;
	unsigned char done=0;
	unsigned char count=0;
	unsigned char keypressed=1;

	while(!done && !reset)
	{
		tgi_setcolor(13);

		tgi_sprite(&sp_rankgrid);

		textxy(5,38,"P1");
		textxy(5,48,"P2");
		tgi_line(15,42, 25, 42);
		
		games = saveptr[8+(40*pos1)];

		sprintf(buf, "Rank P1 %i",saveptr[9+(40*pos1)]/24);

		textxy(1,1,buf);

		for(i=1;i<10;i++)
		{
			sprintf(buf, "%i",i);
			textxy(31,91 - i*8,buf);
		}
		sprintf(buf, "%i",10);
		textxy(27,11,buf);

		if (games < 38)
		{
			tgi_line(41,95, 43, 95-(saveptr[10+(40*pos1)]/3));
			for(i=0;i<games-1;i++)
				tgi_line(43+3*i,95-(saveptr[10+i+(40*pos1)]/3), 46+3*i, 95-(saveptr[11+i+(40*pos1)]/3));
		}
		else
			for(i=0;i<38;i++)
				tgi_line(40+3*i,95-(saveptr[10+i+(40*pos1)]/3), 43+3*i, 95-(saveptr[11+i+(40*pos1)]/3));



		games = saveptr[8+(40*pos2)];

		sprintf(buf, "Rank P2 %i",saveptr[9+(40*pos2)]/24);

		textxy(51,1,buf);

		tgi_setcolor(12);
		tgi_line(15,52, 25, 52);

		if (games < 38)
		{
			tgi_line(41,95, 43, 95-(saveptr[10+(40*pos2)]/3));
			for(i=0;i<games-1;i++)
				tgi_line(43+3*i,95-(saveptr[10+i+(40*pos2)]/3), 46+3*i, 95-(saveptr[11+i+(40*pos2)]/3));
		}
		else
			for(i=0;i<38;i++)
				tgi_line(40+3*i,95-(saveptr[10+i+(40*pos2)]/3), 43+3*i, 95-(saveptr[11+i+(40*pos2)]/3));

		if(count++&16)
			sp_pressA.data=pressA000000;
		else	
			sp_pressA.data=pressA001000;
		tgi_sprite(&sp_pressA);
			
		tgi_updatedisplay();
		while (tgi_busy()) ;
		tgi_setpalette(grid_pal);

		joy = checkInput();
		if(joy && !keypressed)
			done=1;
		if(!joy)
			keypressed=0;
	}
}

void stats(void) {

	char buf[21];
	unsigned char joy=1;
	unsigned char i;
	unsigned char games;
	unsigned char pos=0;
	char done=0;

	while(!done && !reset) 
	{
		tgi_setcolor(13);

		tgi_sprite(&sp_rankgrid);

		games = saveptr[8+(40*pos)];


		if(games>0)
		{
			textxy(80,1,"Games");
			if(games==255)
				textxy(106,1,"254+");
			else
			{
				sprintf(buf, "%i",games);
				textxy(106,1,buf);
			}
			sprintf(buf, "< Slot %i >    Rank %i",pos+1,saveptr[9+(40*pos)]/24);
		}
		else
			sprintf(buf, "< Slot %i >    Empty",pos+1);
		textxy(1,1,buf);

		for(i=1;i<10;i++)
		{
			sprintf(buf, "%i",i);
			textxy(31,91 - i*8,buf);
		}
		sprintf(buf, "%i",10);
		textxy(27,11,buf);

		if(games>0)
		{
			if (games < 38)
			{
				tgi_line(41,95, 43, 95-(saveptr[10+(40*pos)]/3));
				for(i=0;i<games-1;i++)
					tgi_line(43+3*i,95-(saveptr[10+i+(40*pos)]/3), 46+3*i, 95-(saveptr[11+i+(40*pos)]/3));
			}
			else
				for(i=0;i<38;i++)
					tgi_line(40+3*i,95-(saveptr[10+i+(40*pos)]/3), 43+3*i, 95-(saveptr[11+i+(40*pos)]/3));
		}

		tgi_updatedisplay();
		while (tgi_busy()) ;
		tgi_setpalette(grid_pal);

		while(joy && !reset)
			joy = checkInput();
		while(!joy && !reset)
			joy = checkInput();

		if(JOY_BTN_RIGHT(joy))
			pos=(pos+1)%3;
		if(JOY_BTN_LEFT(joy))
			pos=(pos+2)%3;
		if(JOY_BTN_FIRE(joy))
			done=1;
	}
}
