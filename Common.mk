CC=cc65
AS=ca65
CL=cl65
SP=sp65
CP=cp
RM=rm -f
ECHO=echo
TOUCH=touch
SPRPCK=sprpck

ifeq ($(CC65_HOME),)
	CC65_HOME=/usr/local/lib/cc65
endif
ifeq ($(CC65_INC),)
	CC65_INC=$(CC65_HOME)/include
endif
ifeq ($(CC65_ASMINC),)
	CC65_ASMINC=$(CC65_HOME)/asminc
endif

# Rule for making a *.o file out of a *.c file
%.o: %.c
	$(CC) -t lynx -O3 $(CFLAGS) $(SEGMENTS) -o $(patsubst %c, %s, $(notdir $<)) $<
	$(AS) -t lynx -o $@ $(AFLAGS) $(*).s
#	$(RM) $*.s

# Rule for making a *.o file out of a *.s file
%.o: %.s
	$(AS) -t lynx -I $(CC65_ASMINC) -o $@ $(AFLAGS) $<

# Rule for making a *.c file out of a *.pcx file
%.c : %.pcx
	$(SP) -r $< -c lynx-sprite,mode=packed -w $*.c,ident=$*,bytesperline=8

# Rule for making a *.o file out of a *.bmp file - Note: this uses a modified version of sprpck that fixex .pal generation fron newer bmp formats (NOP90)
%.o : %.bmp
	$(SPRPCK) -t6 -p0 $<
	$(RM) $*.obj
	$(CP) $*.pal $*.pal.bak
	$(SPRPCK) -t6 -p2 $<
	$(ECHO) .global _$* > $*.s
	$(ECHO) .segment \"$(RODATA_SEGMENT)\" >> $*.s
	$(ECHO) _$*: .incbin \"$*.spr\" >> $*.s
	$(AS) -t lynx -o $@ $(AFLAGS) $*.s
	$(CP) $*.pal.bak $*.pal
	$(RM) $*.pal.bak


