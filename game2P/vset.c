////////////////////////////////////////////////////////////////////////////////
//
// Filename: 	vset.c
//
// Project:	tttt, a simple 4x4x4 Tic-Tac-Toe Program
//
// Purpose:	Defines a valued set, that is ... a set of elements where
//		every element in the set has a non-zero value associated with
//	it.  We can do operations on this like sets, but also like values.
//
//	How it works: Every possible element has a number associated with it.
//	A zero number means the element is not a member of the set.  A positive
//	number means both that it is an element of the set, and that it has that
//	number as its score or value.
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
#include <stdlib.h>
#include <time.h>
#include <string.h>
//#include <assert.h>
#include "bool.h"
#include "gboard.h"
#include "vset.h"

void	vs2_clear(LPVSET vs) {
	memset(vs, 0, sizeof(VSET));
}

void	vs2_set(LPVSET dst, LPVSET src) {
	memcpy(dst, src, sizeof(VSET));
}

bool	vs2_isempty(LPVSET vs) {
	return (vs->m_active==0)?true:false;
}

bool	vs2_isable(LPVSET vs, signed char spot) {
	if ((spot < 0)||(spot >= NUM_SQUARES))
		return false;
	return (vs->m_data[spot] > 0)?true:false;
}

void	vs2_addscore(LPVSET vs, signed char spot, int delta) {
	if ((spot < 0)||(spot >= NUM_SQUARES))
		return;
	if (vs->m_data[spot] == 0)
		vs->m_active++;
	vs->m_data[spot] += delta;
}

void	vs2_incscore(LPVSET vs, signed char spot) {
	vs_addscore(vs, spot, 1);
}


void	vs2_subscore(LPVSET vs, signed char spot, int delta) {

	if ((spot < 0)||(spot >= NUM_SQUARES)||(delta == 0))
		return;
	if (vs->m_data[spot] >= delta) {
		vs->m_data[spot] -= delta;
		if (vs->m_data[spot] == 0)
			vs->m_active--;
	}
}

void	vs2_decscore(LPVSET vs, signed char spot) {
	vs2_subscore(vs, spot, 1);
}


void	vs2_disable(LPVSET vs, signed char spot) {
	if ((spot < 0)||(spot >= NUM_SQUARES))
		return;
	if (vs->m_data[spot] != 0)
		vs->m_active--;
	vs->m_data[spot] = 0;
}

signed char	vs2_pickmember(LPVSET vs) {
	int	highscore;
	char cnt, chosen, i;

//	assert(vs->m_active > 0);
	// Find the high score, or equivalently the most valuable move
	highscore = vs->m_data[0];
	for(i=0; i<NUM_SQUARES; i++)
		if (vs->m_data[i] > highscore)
			highscore = vs->m_data[i];
	// Reject any less valuable moves
	for(i=0; i<NUM_SQUARES; i++)
		if (vs->m_data[i] < highscore)
			vs2_disable(vs, i);

	// Pick from among the moves remaining
// assert(vs->m_active > 0);
	chosen = rand() % vs->m_active;
//	chosen = clock() % vs->m_active;
	cnt = 0;

	for(i=0; i<NUM_SQUARES; i++)
		if (vs->m_data[i] > 0) {
			if (cnt++ == chosen)
				return i;
		}

	return -1;
}

void	vs2_add(LPVSET vs,LPVSET other) {
	char i;
	for(i=0; i<NUM_SQUARES; i++)
		vs->m_data[i] += other->m_data[i];
	vs->m_active = vs_numactive(vs);
}

void	vs2_sub(LPVSET vs, LPVSET other) {
	char i;
	for(i=0; i<NUM_SQUARES; i++) {
		if (other->m_data[i] > vs->m_data[i])
			vs->m_data[i] = 0;
		else
			vs->m_data[i] -= other->m_data[i];
	} vs->m_active = vs_numactive(vs);
}

void	vs2_combine(LPVSET vs, LPVSET other) {
	VSET	test;
	int	highscore;
	char i;

	if (other->m_active <= 0)
		return;

	if (other->m_active >= NUM_SQUARES)
		return;

	vs_clear(&test);

	highscore = 0;
	for(i=0; i<NUM_SQUARES; i++)
		if (vs->m_data[i] > highscore)
			highscore = vs->m_data[i];
	if (highscore == 0)
		return;

	for(i=0; i<NUM_SQUARES; i++) {
		if (vs->m_data[i] == highscore)
			test.m_data[i] = other->m_data[i];
	}

	test.m_active = vs_numactive(&test);
	if (test.m_active > 0)
		vs_set(vs, &test);
}

int	vs2_numactive(LPVSET vs) {
	char	cnt = 0, i;

	for(i=0; i < NUM_SQUARES; i++)
		if (vs->m_data[i] > 0)
			cnt++;
	return cnt;
}
