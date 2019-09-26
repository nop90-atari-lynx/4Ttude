#include <stdlib.h>
#include <6502.h>
#include <lynx.h>
#include <tgi.h>
#include <conio.h>
#include <peekpoke.h>
#include <joystick.h>
#include <time.h>
#include <serial.h>

#include "nop90.pal"
#include "title.pal"
#include "gerk0.pal"

void inpUpdate(void);

#define FPS 60

extern int SAMPLE3_FILENR;
extern int SAMPLE4_FILENR;

extern unsigned char gerk0[];
extern unsigned char gerk1[];
extern unsigned char gerk2[];
extern unsigned char gerk3[];
extern unsigned char gerk4[];
extern unsigned char gerk5[];
extern unsigned char nop90[];
extern unsigned char title[];

void lynx_snd_init ();
void play_PCM(int n);
extern unsigned char reset;

unsigned char checkInput(void);

void __fastcall__ fade_in(char *pal, unsigned char interval);
void __fastcall__ fade_out(unsigned char interval);

SCB_REHV_PAL sp_fade = 
{
  BPP_4 | TYPE_BACKGROUND,
  REHV,
  0x01,
  0,
  nop90,
  0, 0, 0x0100, 0x0100,
  { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef }
};

SCB_REHV_PAL sp_title = 
{
  BPP_4 | TYPE_BACKGROUND,
  REHV,
  0x01,
  0,
  title,
  0, 0, 0x0100, 0x0100,
  { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef }
};

SCB_REHV_PAL sp_gerk = 
{
  BPP_4 | TYPE_NORMAL,
  REHV,
  0x01,
  0,
  gerk0,
  0, 0, 0x0100, 0x0100,
  { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef }
};

static char black_pal[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

void gerk(void)
{
	unsigned int zoom;
	unsigned int count;
	
	tgi_clear();
	tgi_updatedisplay();
	while (tgi_busy()) ;
    tgi_setpalette(gerk0_pal);

	sp_gerk.hpos=60;
	sp_gerk.vpos=10;

	for(zoom=0;zoom<=0x100;zoom+=4)
	{
		tgi_clear();
		sp_gerk.hpos=60+((256-zoom)/4);
		sp_gerk.vpos=10+((256-zoom)/4);
		sp_gerk.hsize=zoom;
		sp_gerk.vsize=zoom;
		tgi_sprite(&sp_gerk);
		tgi_updatedisplay();
		while (tgi_busy()) ;
	}
	for(count=0;count<=128;count++)
	{
		tgi_clear();
		sp_gerk.data=gerk1;
		sp_gerk.hpos=60;
		sp_gerk.vpos=10;
		tgi_sprite(&sp_gerk);
		sp_gerk.data=gerk4;
		sp_gerk.hpos=60;
		sp_gerk.vpos=10-(count>21 && count< 42?2:0);
		tgi_sprite(&sp_gerk);
		sp_gerk.data=gerk2;
		sp_gerk.hpos=60+((count<21)?-1:0)+((count>42)?+1:0);
//		sp_gerk.vpos=10-(conunt>21 && count< 42?2:0;
		tgi_sprite(&sp_gerk);
		sp_gerk.data=gerk3;
		sp_gerk.hpos=60-((count>32 && count<64)?5:0)-((count>96)?5:0);
		sp_gerk.vpos=10;
		tgi_sprite(&sp_gerk);
		tgi_updatedisplay();
		while (tgi_busy()) ;
	}
	play_PCM((int)&SAMPLE3_FILENR);
	for(count=0;count<64;count++)
	{
		tgi_clear();
		sp_gerk.data=gerk1;
		sp_gerk.hpos=60;
		sp_gerk.vpos=10;
		tgi_sprite(&sp_gerk);
		sp_gerk.data=gerk2;
		tgi_sprite(&sp_gerk);
		sp_gerk.data=gerk3;
		tgi_sprite(&sp_gerk);
		sp_gerk.data=gerk4;
		tgi_sprite(&sp_gerk);
		sp_gerk.data=gerk5;
		sp_gerk.hpos=10-((count>16 && count<32)?5:0)-((count>48)?5:0);
		sp_gerk.vpos=22;
		tgi_sprite(&sp_gerk);
		tgi_updatedisplay();
		while (tgi_busy()) ;
	}
	for(count=0;count<=128;count++)
	{
		tgi_clear();
		sp_gerk.data=gerk1;
		sp_gerk.hpos=60;
		sp_gerk.vpos=10;
		tgi_sprite(&sp_gerk);
		sp_gerk.data=gerk4;
		sp_gerk.hpos=60;
		sp_gerk.vpos=10-(count>21 && count< 42?2:0);
		tgi_sprite(&sp_gerk);
		sp_gerk.data=gerk2;
		sp_gerk.hpos=60+((count<21)?-1:0)+((count>42)?+1:0);
//		sp_gerk.vpos=10-(conunt>21 && count< 42?2:0;
		tgi_sprite(&sp_gerk);
		sp_gerk.data=gerk3;
		sp_gerk.hpos=60-((count>32 && count<64)?5:0)-((count>96)?5:0);
		sp_gerk.vpos=10;
		tgi_sprite(&sp_gerk);
		tgi_updatedisplay();
		while (tgi_busy()) ;
	}
	sp_gerk.data=gerk0;
	sp_gerk.hpos=60;
	sp_gerk.vpos=10;
	while (sp_gerk.hpos<170)
	{
		tgi_clear();
		tgi_sprite(&sp_gerk);
		tgi_updatedisplay();
		while (tgi_busy()) ;
		sp_gerk.hpos+=4;
	}
}

void intro(void) 
{
	unsigned long now;
	struct ser_params params = {
		SER_BAUD_62500, 
		SER_BITS_8,     // only 8 data bits is supported
		SER_STOP_1,     // only 1 stop bit is supported
		SER_PAR_ODD,   // mark, space, even, odd is supported
		SER_HS_NONE     // only "none" is supported
	};

	tgi_install(&tgi_static_stddrv);
	tgi_init();
	tgi_setframerate(FPS);
	joy_install(&joy_static_stddrv);
	ser_install(&lynx_comlynx);
	lynx_snd_init();
	CLI();
	ser_open(&params);
	
	gerk();
	while (tgi_busy()) ;
    tgi_setpalette(black_pal);
	sp_fade.data=nop90;
	tgi_sprite(&sp_fade);
	tgi_updatedisplay();
	while (tgi_busy()) ;
	fade_in(nop90_pal, 100);
	now = clock();
	while (clock() < now + 120);
    fade_out(100);
	tgi_sprite(&sp_title);
	tgi_updatedisplay();
	while (tgi_busy()) ;
	fade_in(title_pal, 100);
	play_PCM((int)&SAMPLE4_FILENR);
	now = clock();
	while (clock() < now + 120);
    fade_out(100);
}
