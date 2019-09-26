////////////////////////////////////////////////////////////////////////////////
//
// Filename: 	gboard.c
//
// Project:	tttt, a simple 4x4x4 Tic-Tac-Toe Program
//
// Purpose:	Implements the interface between the board and the rest of the
//		game.
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
//#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gboard.h"

LPGBOARD	gb2_new(void) {
	LPGBOARD	brd;

	brd = (LPGBOARD)malloc(sizeof(GBOARD));
	gb2_reset(brd);
	return brd;
}

void	gb2_reset(LPGBOARD brd) {
	char i;
	brd->m_lastturn = (clock()&1)?GB_WHITE:GB_BLACK;
	brd->m_winner   = GB_NOONE;
	brd->m_nfilled  = 0;
	for(i=0; i<NUM_SQUARES; i++)
		brd->m_spots[i] = GB_NOONE;
	brd->m_nfilled  = 0;
}

signed char	coordtoint2(signed char x, signed char y, signed char z) {
	if ((x >= NUM_ON_SIDE)||(x < 0))
		return -1;
	if ((y >= NUM_ON_SIDE)||(y < 0))
		return -1;
	if ((z >= NUM_ON_SIDE)||(z < 0))
		return -1;

	return (z * NUM_ON_SIDE + y) * NUM_ON_SIDE + x;
}

char opponent2(char who) {
	if (who == GB_WHITE)
		return GB_BLACK;
	else if (who == GB_BLACK)
		return GB_WHITE;
	else
		return GB_NOONE;
}

char	xcoord2(signed char spt) {
	if ((spt >= NUM_SQUARES)||(spt < 0))
		return -1;
	return spt % NUM_ON_SIDE;
}

char	ycoord2(signed char spt) {
	if ((spt >= NUM_SQUARES)||(spt < 0))
		return -1;
	return (spt / NUM_ON_SIDE)%NUM_ON_SIDE;
}

char	zcoord2(signed char spt) {
	if ((spt >= NUM_SQUARES)||(spt < 0))
		return -1;
	return (spt / (NUM_ON_SIDE*NUM_ON_SIDE));
}

bool	legal2(LPGBOARD brd, GB_PIECE who, signed char where) {
	if (brd->m_winner != GB_NOONE)
		return false;
	if ((who != GB_BLACK)&&(who != GB_WHITE))
		return false;
	if ((who == GB_WHITE)&&(brd->m_lastturn != GB_BLACK))
		return false;
	if ((who == GB_BLACK)&&(brd->m_lastturn != GB_WHITE))
		return false;
	if ((where < 0)||(where >= NUM_SQUARES))
		return false;
	if (brd->m_spots[where] != GB_NOONE)
		return false;
	return true;
}
	
void	gb2_place(LPGBOARD brd, GB_PIECE who, signed char where) {
/*
	if (!legal(brd, who, where)) {
		printf("ILLEGAL-MOVE ATTEMPTED: %s tried to move to %d",
			(who == GB_BLACK)?"black"
			:(who == GB_WHITE)?"white"
			: "? someone ?", where);
	}
*/
	brd->m_spots[where] = who;
	brd->m_lastturn = who;
	brd->m_nfilled++;
}

bool	inuse2(LPGBOARD brd, signed char where) {
	if ((where < 0)||(where >= NUM_SQUARES))
		return true;
	return (brd->m_spots[where] != GB_NOONE)?true:false;
}

GB_PIECE whoseturn2(LPGBOARD brd) {
	if (brd->m_winner != GB_NOONE)
		return GB_NOONE;
	else if (brd->m_lastturn == GB_WHITE)
		return GB_BLACK;
	else if (brd->m_lastturn == GB_BLACK)
		return GB_WHITE;
	else
/*
		printf("Cannot tell whose turn it is from %d (%s)\n", 
			brd->m_lastturn,
			(brd->m_lastturn == GB_BLACK)?"black"
			:(brd->m_lastturn == GB_WHITE)?"white"
			: "? someone ?");
*/
	return GB_NOONE;
}

bool	gb2_gameover(LPGBOARD brd) {
	return	(whoseturn2(brd) == GB_NOONE)?true:false;
}

GB_PIECE gb2_winner(LPGBOARD brd) {
	return brd->m_winner;
}

GB_PIECE pieceat2(LPGBOARD brd, signed char where) {
	if ((where < 0)||(where >= NUM_SQUARES))
		return	GB_NOONE;
	return	brd->m_spots[where];
}


