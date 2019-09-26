////////////////////////////////////////////////////////////////////////////////
//
// Filename: 	gboard.h
//
// Project:	tttt, a simple 4x4x4 Tic-Tac-Toe Program
//
// Purpose:	Defines the interface(s) that other parts of the game will have
//		with the gameboard itself.
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
#ifndef	GBOARD_H
#define	GBOARD_H

#include "bool.h"

#define	NUM_ON_SIDE	4
#define	NUM_SQUARES	(NUM_ON_SIDE * NUM_ON_SIDE * NUM_ON_SIDE)

typedef	enum	GB_PIECE_E {
	GB_NOONE=0, GB_WHITE, GB_BLACK, GB_TIE
} GB_PIECE;

typedef	struct GBOARD_S {
	char m_lastturn, m_winner, m_nfilled;
	char m_spots[NUM_SQUARES];
	signed char lastWhite;
	signed char lastBlack;
	signed char rankWhite;
	signed char rankBlack;
	signed char cursorBlack;
	signed char cursorWhite;
	signed char netreset;
	unsigned char currMusic;
} GBOARD, *LPGBOARD;

LPGBOARD gb2_new(void);
void	gb2_reset(LPGBOARD brd);
signed char	coordtoint2(signed char x, signed char y, signed char z);
char	opponent2(char who);
char	xcoord2(signed char spt);
char	ycoord2(signed char spt);
char	zcoord2(signed char spt);
bool	legal2(LPGBOARD brd, GB_PIECE who, signed char where);
void	gb2_place(LPGBOARD brd, GB_PIECE who, signed char where);
bool	inuse2(LPGBOARD brd, signed char where);
GB_PIECE whoseturn2(LPGBOARD brd);
bool	gb2_gameover(LPGBOARD brd);
GB_PIECE gb2_winner(LPGBOARD brd);
GB_PIECE pieceat2(LPGBOARD brd, signed char where);
void	gb_print(LPGBOARD brd);


#endif
