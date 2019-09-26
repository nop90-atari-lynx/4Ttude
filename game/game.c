////////////////////////////////////////////////////////////////////////////////
//
// Filename: 	main.c
//
// Project:	

//
// Purpose:	To play a game of 4x4x4 Tic-Tac-Toe.  This includes
//		allocating and initializing all game variables, reading and
//	processing user input, adjudicating whether or not someone has won,
//	and eventually automatically restarting the game upon a win (or loss)
//	when on an embedded (ZipCPU) device.
//
// Creator:	Dan Gisselquist, Ph.D.
//		Gisselquist Technology, LLC
//
////////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017, Gisselquist Technology, LLC
//
// This program is free software (firmware): you can redistribute it and/or
// modify it under the terms of  the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTIBILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
// for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program.  (It's in the $(ROOT)/doc directory, run make with no
// target there if the PDF file isn't present.)  If not, see
// <http://www.gnu.org/licenses/> for a copy.
//
// License:	GPL, v3, as defined and found on www.gnu.org,
//		http://www.gnu.org/licenses/gpl.html
//
//
////////////////////////////////////////////////////////////////////////////////
//
//
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
//#include <assert.h>
#include <6502.h>
#include <lynx.h>
#include <tgi.h>
#include <joystick.h>
#include "gboard.h"
#include "comboset.h"
#include "strategy.h"

#include "palette.pal"

void textxy (int x, int y, unsigned char*);
unsigned char checkInput(void);
void play_Tune(void);
void play_PCM(int n);

	GBOARD		brd;
	COMBOSET	cs;
	STRATEGY	s;
	
signed char posx,posy,posz;
unsigned char moves;
char gbuf[3];
unsigned char oldflipflop;
int lastplayed[64];
unsigned char gridoffset;

extern unsigned char background[];
extern unsigned char grid0[];
extern unsigned char gridSmall[];
extern unsigned char cursor0[];
extern unsigned char cursor1[];
extern unsigned char tile1[];
extern unsigned char tile2[];
extern unsigned char dot0[];
extern unsigned char dot1[];
extern unsigned char dot2[];
extern unsigned char dleft[];
extern unsigned char dright[];

extern unsigned char reset;
extern unsigned char musicEnabled;
extern unsigned char altview;
extern unsigned char lastmove;
extern unsigned char ingame;
extern unsigned char flipflop;

extern int SAMPLE0_FILENR;
extern int SAMPLE1_FILENR;
extern int SAMPLE2_FILENR;

SCB_REHV_PAL sp_bg = 
{
  BPP_4 | TYPE_BACKGROUND,
  REHV,
  0x01,
  0,
  background,
  0, 0, 0x0100, 0x0100,
  { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef }
};

SCB_RENONE_PAL sp_grid = 
{
  BPP_4 | TYPE_NORMAL,
  REUSEPAL,
  0x01,
  0,
  grid0,
  0, 0
};

SCB_RENONE_PAL sp_gridsmall = 
{
  BPP_4 | TYPE_NORMAL,
  REUSEPAL,
  0x01,
  0,
  gridSmall,
  0, 0
};

SCB_RENONE_PAL sp_tile = 
{
  BPP_4 | TYPE_NORMAL,
  REUSEPAL,
  0x01,
  0,
  cursor0,
  0, 0
};

signed char	trainoptions(void) {

	unsigned char i=2;
	unsigned char done=0;
	unsigned char joy=1;
	unsigned char keypressed=1;
	unsigned char blink=32;
	
	while(!done && !reset) 
	{
		tgi_sprite(&sp_bg);

		textxy(3,7,"Training");
		textxy(43,16,"mode");

		textxy(95,25,"Get a hint");
		textxy(95,38,"Undo last move");
		textxy(95,51,"Cancel");
		textxy(85 ,51-(i*13),">");
		if(blink++&32)
			textxy(5,93,"Press A to select an option");
		
		tgi_updatedisplay();
		while (tgi_busy()) ;
		tgi_setpalette(gfx_pal);

		joy = checkInput();
		if(JOY_BTN_FIRE(joy) && !keypressed)
		{
			if (!(i==1 && moves<3)) 
				done=1;
			play_PCM((int)&SAMPLE2_FILENR);
			keypressed=1;
		}
		if(JOY_BTN_UP(joy) && !keypressed)
		{
			i=(i+1)%3;
			play_PCM((int)&SAMPLE2_FILENR);
			keypressed=1;
		}
		if(JOY_BTN_DOWN(joy) && !keypressed)
		{
			i=(i+2)%3;
			play_PCM((int)&SAMPLE2_FILENR);
			keypressed=1;
		}
		if(!joy)
			keypressed=0;
	}
	return (-i-1);
}

unsigned char newRank(unsigned char rank1,unsigned char rank2, unsigned char winner, int moves)
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
signed char	getmove(unsigned char rank) {
	unsigned char joy=1;

	while(joy && !reset)
		joy = checkInput();
	while(!joy && !reset && flipflop==oldflipflop)
		joy = checkInput();
	if(JOY_BTN_FIRE(joy))
	{
		return coordtoint(posx, posy, posz);	
	}
	if(JOY_BTN_FIRE2(joy) && rank==255)
	{
		return trainoptions();	
	}
	if(JOY_BTN_RIGHT(joy))
	{
		posx++;
		if(posx==4)
		{
			posx=0;
			posz= (posz+1)%4;
			play_PCM((int)&SAMPLE1_FILENR);
		}
		else
			play_PCM((int)&SAMPLE2_FILENR);
		return -1;
	}
	if(JOY_BTN_LEFT(joy))
	{
		posx--;
		if(posx==-1)
		{
			posx=3;
			posz= (posz+3)%4;
			play_PCM((int)&SAMPLE1_FILENR);
		}
		else
			play_PCM((int)&SAMPLE2_FILENR);
		return -1;
	}
	if(JOY_BTN_UP(joy))
	{
		posy--;
		if(posy==-1)
		{
			posy=3;
			posz= (posz+3)%4;
			play_PCM((int)&SAMPLE1_FILENR);
		}
		else
			play_PCM((int)&SAMPLE2_FILENR);
		return -1;
	}
	if(JOY_BTN_DOWN(joy))
	{
		posy++;
		if(posy==4)
		{
			posy=0;
			posz= (posz+1)%4;
			play_PCM((int)&SAMPLE1_FILENR);
		}
		else
			play_PCM((int)&SAMPLE2_FILENR);
		return -1;
	}

	return -1;
}

void drawBoard(void)
{
	char i;
	char x,y,z;

	tgi_sprite(&sp_bg);
	sp_grid.hpos=73 + gridoffset;
	sp_grid.vpos=13;
	for(i=0;i<4;i++)
	{
		tgi_sprite(&sp_grid);
		sp_grid.vpos+=22;
	}

	if(altview)
	{
		sp_gridsmall.hpos=131;
		sp_gridsmall.vpos=13;
		tgi_sprite(&sp_gridsmall);
		sp_gridsmall.vpos=28;
		tgi_sprite(&sp_gridsmall);
		sp_gridsmall.vpos=43;
		tgi_sprite(&sp_gridsmall);
		sp_gridsmall.vpos=58;
		tgi_sprite(&sp_gridsmall);
		sp_gridsmall.hpos=146;
		sp_gridsmall.vpos=13;
		tgi_sprite(&sp_gridsmall);
		sp_gridsmall.vpos=28;
		tgi_sprite(&sp_gridsmall);
		sp_gridsmall.vpos=43;
		tgi_sprite(&sp_gridsmall);
		sp_gridsmall.vpos=58;
		tgi_sprite(&sp_gridsmall);
		sp_tile.data = dleft;
		sp_tile.hpos=131;
		sp_tile.vpos=73;
		tgi_sprite(&sp_tile);
		sp_tile.hpos=146;
		sp_tile.vpos=88;
		tgi_sprite(&sp_tile);
		sp_tile.data = dright;
		sp_tile.hpos=131;
		tgi_sprite(&sp_tile);
		sp_tile.hpos=146;
		sp_tile.vpos=73;
		tgi_sprite(&sp_tile);
	}
	
	for(z=0;z<4;z++)
		for(y=0;y<4;y++)
			for(x=0;x<4;x++)
			{
				if(brd.m_spots[z*16+y*4+x]==GB_WHITE)
				{
					sp_tile.data= tile1;
					sp_tile.hpos= 75 + 9*x + 5* y + gridoffset;
					sp_tile.vpos= 14 + 5*y + 22* z;
					tgi_sprite(&sp_tile);
					
					if(altview)
					{
						sp_tile.data= dot1;
						sp_tile.hpos= 132 + 3*y;
						sp_tile.vpos= 14 + 3*z + 15* x;
						tgi_sprite(&sp_tile);
						sp_tile.hpos= 147 + 3*x;
						sp_tile.vpos= 14 + 3*z + 15* (3-y);
						tgi_sprite(&sp_tile);
						if(x==y)
						{
							if(x==z)
							{
								sp_tile.hpos= 132 + 3*x;
								sp_tile.vpos= 14 + 60 + 3*x;
								tgi_sprite(&sp_tile);
							}
							if(x==3-z)
							{
								sp_tile.hpos= 147 + 3*x;
								sp_tile.vpos= 14 + 75 + 3*x;
								tgi_sprite(&sp_tile);
							}
						}
						if(x==3-y)
						{
							if(x==z)
							{
								sp_tile.hpos= 132 + 3*x;
								sp_tile.vpos= 14 + 75 + 9 - 3*x;
								tgi_sprite(&sp_tile);
							}
							if(x==3-z)
							{
								sp_tile.hpos= 147 + 3*x;
								sp_tile.vpos= 14 + 60 + 9 - 3*x;
								tgi_sprite(&sp_tile);
							}
						}
					}
				}
				
				if(brd.m_spots[z*16+y*4+x]==GB_BLACK)
				{
					sp_tile.data= tile2;
					sp_tile.hpos= 75 + 9*x + 5* y + gridoffset;
					sp_tile.vpos= 14 + 5*y + 22* z;
					tgi_sprite(&sp_tile);
					
					if(altview)
					{
						sp_tile.data= dot2;
						sp_tile.hpos= 132 + 3*y;
						sp_tile.vpos= 14 + 3*z + 15* x;
						tgi_sprite(&sp_tile);
						sp_tile.hpos= 147 + 3*x;
						sp_tile.vpos= 14 + 3*z + 15* (3-y);
						tgi_sprite(&sp_tile);
						if(x==y)
						{
							if(x==z)
							{
								sp_tile.hpos= 132 + 3*x;
								sp_tile.vpos= 14 + 60 + 3*x;
								tgi_sprite(&sp_tile);
							}
							if(x==3-z)
							{
								sp_tile.hpos= 147 + 3*x;
								sp_tile.vpos= 14 + 75 + 3*x;
								tgi_sprite(&sp_tile);
							}
						}
						if(x==3-y)
						{
							if(x==z)
							{
								sp_tile.hpos= 132 + 3*x;
								sp_tile.vpos= 14 + 75 + 9 - 3*x;
								tgi_sprite(&sp_tile);
							}
							if(x==3-z)
							{
								sp_tile.hpos= 147 + 3*x;
								sp_tile.vpos= 14 + 60 + 9 - 3*x;
								tgi_sprite(&sp_tile);
							}
						}
					}
				}
			}
}

/*
 * play_game()
 *
 * Play the game once.  This includes allocating and initializing the board,
 * knowledge/reasoning base (COMBOSET), and the STRATEGY that will be used by
 * the computer.  It also includes requesting the user input, and causing the
 * game board to be printed after ever move of the computers.
 *
 */
unsigned char game(unsigned char level, unsigned char rank)
{
	unsigned char i,x,y,z;
	unsigned char joy=1;
	unsigned char keypressed=1;
	unsigned char done=0;
	int	mv=-1;
	int	hint;

	for(i=0;i<64;i++)
		lastplayed[i]=-1;
	gb_reset(&brd);
	set_difficulty(&s, level);
	cs_init(&cs);
	ingame = 1;

	play_Tune();

	posx=0;
	posy=0;
	posz=0;
	moves=1;

	while(!gb_gameover(&brd) && !reset)
	{
		hint=-1;
			
		if (brd.m_lastturn ==GB_WHITE) do {
			oldflipflop = flipflop;
			if(altview)
				gridoffset=0;
			else
				gridoffset=26;
//draw board
			drawBoard();

			if(hint>-1)
			{
				x=hint&3;
				y=(hint>>2)&3;
				z=(hint>>4)&3;
				sp_tile.data= cursor1;
				sp_tile.hpos= 75 + 9*x + 5*y + gridoffset;
				sp_tile.vpos= 14 + 5*y + 22*z;
				tgi_sprite(&sp_tile);
			}

			if(lastmove && moves >1)
			{
				x=lastplayed[moves-2]&3;
				y=(lastplayed[moves-2]>>2)&3;
				z=(lastplayed[moves-2]>>4)&3;
				sp_tile.data= cursor1;
				sp_tile.hpos= 75 + 9*x + 5*y + gridoffset;
				sp_tile.vpos= 14 + 5*y + 22*z;
				tgi_sprite(&sp_tile);
			}

			sp_tile.data= cursor0;
			sp_tile.hpos= 75 + 9*posx + 5* posy + gridoffset;
			sp_tile.vpos= 14 + 5*posy + 22* posz;
			tgi_sprite(&sp_tile);

			if(altview)
			{

				sp_tile.data= dot0;
				sp_tile.hpos= 132 + 3*posy;
				sp_tile.vpos= 14 + 3*posz + 15* posx;
				tgi_sprite(&sp_tile);
				sp_tile.hpos= 147 + 3*posx;
				sp_tile.vpos= 14 + 3*posz + 15* (3-posy);
				tgi_sprite(&sp_tile);

				if(posx==posy)
				{
					if(posx==posz)
					{
						sp_tile.hpos= 132 + 3*posx;
						sp_tile.vpos= 14 + 60 + 3*posx;
						tgi_sprite(&sp_tile);
					}
					if(posx==3-posz)
					{
						sp_tile.hpos= 147 + 3*posx;
						sp_tile.vpos= 14 + 75 + 3*posx;
						tgi_sprite(&sp_tile);
					}
				}
				if(posx==3-posy)
				{
					if(posx==posz)
					{
						sp_tile.hpos= 132 + 3*posx;
						sp_tile.vpos= 14 + 75 + 9 - 3*posx;
						tgi_sprite(&sp_tile);
					}
					if(posx==3-posz)
					{
						sp_tile.hpos= 147 + 3*posx;
						sp_tile.vpos= 14 + 60 + 9 - 3*posx;
						tgi_sprite(&sp_tile);
					}
				}
			}
			
			textxy(4,7,"Your turn");
			textxy(43+(moves<10?2:0),16,"move");
			sprintf(gbuf,"%i",moves);
			textxy(65+(moves<10?2:0),16,gbuf);

			tgi_updatedisplay();
			while (tgi_busy()) ;
			tgi_setpalette(gfx_pal);

			mv = getmove(rank);

			if(mv==-2)
			{
				brd.m_spots[lastplayed[moves-2]]= GB_NOONE;
				brd.m_spots[lastplayed[moves-3]]= GB_NOONE;
				lastplayed[moves-2]=-1;
				lastplayed[moves-3]=-1;
				moves = moves-2;
			}

			if(mv==-3)
			{
				drawBoard();
				textxy(3,7,"Searching");
				tgi_updatedisplay();
//				set_difficulty(&s, 10);
//				hint=makemove(&s, &brd, &cs, GB_WHITE);
				hint=makemove(&s, &brd, &cs, GB_BLACK);
//				set_difficulty(&s, level);
				while (tgi_busy()) ;
			}

		} while(!legal(&brd, GB_BLACK, mv) && !reset);

		if(!reset)
		{
			if(mv>=0) //to handle first move white
			{
				lastplayed[moves-1] = mv;
				gb_place(&brd, GB_BLACK, mv);
				moves++;
			}

			drawBoard();
			textxy(6,7,"CPU turn");
			textxy(43+(moves<10?2:0),16,"move");
			sprintf(gbuf,"%i",moves);
			textxy(65+(moves<10?2:0),16,gbuf);
			tgi_updatedisplay();
			while (tgi_busy()) ;
			tgi_setpalette(gfx_pal);
			play_PCM((int)&SAMPLE0_FILENR);
			
			if (!cs_place(&cs,  GB_BLACK, mv)) {
				mv = makemove(&s, &brd, &cs, GB_WHITE);
				lastplayed[moves-1] = mv;
				moves++;
				play_PCM((int)&SAMPLE0_FILENR);
				gb_place(&brd, GB_WHITE, mv);
				if (cs_place(&cs,  GB_WHITE, mv))
					brd.m_winner = GB_WHITE;
			} else
				brd.m_winner = GB_BLACK;
		}
	}
	i=16;
	while(!done && !reset)
	{
		// Print the final (winning) copy of the board
		drawBoard();

		if(brd.m_winner==GB_BLACK)
		{
			textxy(7,7,"You win");
		}
		else if(brd.m_winner==GB_WHITE)
		{
			textxy(5,7,"CPU wins");
		}
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
	return newRank(rank, level*24, (brd.m_winner==GB_BLACK)?1:2, moves);
}
