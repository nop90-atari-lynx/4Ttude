#include <stdlib.h>
#include <string.h>
#include <lynx.h>
#include <tgi.h>

extern unsigned char font000000[];
extern unsigned char font000001[];
extern unsigned char font000002[];
extern unsigned char font000003[];
extern unsigned char font000004[];
extern unsigned char font000005[];
extern unsigned char font000006[];
extern unsigned char font000007[];
extern unsigned char font000008[];
extern unsigned char font000009[];
extern unsigned char font000010[];
extern unsigned char font000011[];
extern unsigned char font000012[];
extern unsigned char font000013[];
extern unsigned char font000014[];
extern unsigned char font000015[];
extern unsigned char font000016[];
extern unsigned char font000017[];
extern unsigned char font000018[];
extern unsigned char font000019[];
extern unsigned char font000020[];
extern unsigned char font000021[];
extern unsigned char font000022[];
extern unsigned char font000023[];
extern unsigned char font000024[];
extern unsigned char font000025[];
extern unsigned char font001000[];
extern unsigned char font001001[];
extern unsigned char font001002[];
extern unsigned char font001003[];
extern unsigned char font001004[];
extern unsigned char font001005[];
extern unsigned char font001006[];
extern unsigned char font001007[];
extern unsigned char font001008[];
extern unsigned char font001009[];
extern unsigned char font001010[];
extern unsigned char font001011[];
extern unsigned char font001012[];
extern unsigned char font001013[];
extern unsigned char font001014[];
extern unsigned char font001015[];
extern unsigned char font001016[];
extern unsigned char font001017[];
extern unsigned char font001018[];
extern unsigned char font001019[];
extern unsigned char font001020[];
extern unsigned char font001021[];
extern unsigned char font001022[];
extern unsigned char font001023[];
extern unsigned char font001024[];
extern unsigned char font001025[];
extern unsigned char font002000[];
extern unsigned char font002001[];
extern unsigned char font002002[];
extern unsigned char font002003[];
extern unsigned char font002004[];
extern unsigned char font002005[];
extern unsigned char font002006[];
extern unsigned char font002007[];
extern unsigned char font002008[];
extern unsigned char font002009[];
extern unsigned char font002010[];
extern unsigned char font002011[];
extern unsigned char font002012[];
extern unsigned char font002013[];
extern unsigned char font002014[];
extern unsigned char font002015[];
extern unsigned char font002016[];
extern unsigned char font002017[];
extern unsigned char font002018[];
extern unsigned char font002019[];



unsigned char* spFont[72] =  
{
	font000000,font000001,font000002,font000003,font000004,font000005,font000006,font000007,font000008,font000009,font000010,font000011,font000012,
	font000013,font000014,font000015,font000016,font000017,font000018,font000019,font000020,font000021,font000022,font000023,font000024,font000025,
	font001000,font001001,font001002,font001003,font001004,font001005,font001006,font001007,font001008,font001009,font001010,font001011,font001012,
	font001013,font001014,font001015,font001016,font001017,font001018,font001019,font001020,font001021,font001022,font001023,font001024,font001025,
	font002000,font002001,font002002,font002003,font002004,font002005,font002006,font002007,font002008,font002009,font002010,font002011,font002012,
	font002013,font002014,font002015,font002016,font002017,font002018,font002019
};
/*
unsigned char CharSize[68] =  
{
	5,5,5,5,5,5,5,5,3,3,5,5,5,
	5,5,5,5,5,5,5,5,5,5,5,5,5,
	5,5,5,5,5,5,5,5,2,3,4,4,6,
	5,5,5,5,5,6,4,5,6,6,6,5,6,
	4,4,4,4,4,4,4,4,4,4,3,3,5,
	4,4,4
};
*/
unsigned char CharSize[72] =  
{
	5,5,5,5,5,5,5,5,3,3,5,5,5,
	5,5,5,5,5,5,5,5,5,5,5,5,5,
	4,4,4,5,4,4,4,4,3,3,4,3,6,
	5,4,4,5,4,5,3,5,5,6,5,5,5,
	4,4,4,4,4,4,4,4,4,4,3,4,5,
	5,5,5,5,5,5,4
};

SCB_REHV_PAL sp_font = 
{
  BPP_4 | TYPE_NORMAL,
  REHV,
  0x01,
  0,
  font000000,
  0, 0, 0x0100, 0x0100,
  { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef }
}; 
  
signed char getCharTile(unsigned char ch)
{

	if((ch>='A')&&(ch<='Z'))	
		return (ch -'A'); 
	if((ch>='a')&&(ch<='z'))	
		return (ch -'a'+26); 
	if((ch>='0')&&(ch<='9'))
		return (ch -'0'+52); 
	if(ch==':')	
		return 62; 
	if(ch==';')	
		return 63; 
	if(ch=='!')	
		return 64; 
	if(ch=='-')	
		return 65; 
	if(ch=='+')	
		return 66; 
	if(ch=='<')	
		return 67; 
	if(ch=='>')	
		return 68; 
	if(ch=='(')	
		return 69; 
	if(ch==')')	
		return 70; 
	if(ch=='.')	
		return 71; 
	if(ch=='/')	
		return -2; 
	return -1;
}

void textxy(int x, int y, unsigned char * text)
{
	char i;
	signed char ch;
	sp_font.vpos=y;
	sp_font.hpos=x;
	for(i=0;text[i];i++) 
	{
		ch=getCharTile(text[i]);
		if (ch==-2)
		{
			sp_font.vpos+=9;
			sp_font.hpos=x;
		}
		else if(ch>=0)
		{
			sp_font.data=spFont[ch];
			tgi_sprite(&sp_font);
			sp_font.hpos+=CharSize[ch];
		}
		else
			sp_font.hpos+=2;
	}
}
