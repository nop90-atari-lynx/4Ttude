include ../Common.mk

thisdir=game

objects= \
	dleft.o dright.o dot0.o dot1.o dot2.o tile1.o tile2.o cursor0.o cursor1.o grid0.o grid1.o gridSmall.o background.o \
	game.o comborow.o comboset.o gboard.o strategy.o vset.o 

temporaryobjects= \
	*.spr *.pal *.s 

CODE_SEGMENT=GAME_CODE
DATA_SEGMENT=GAME_DATA
RODATA_SEGMENT=GAME_RODATA
BSS_SEGMENT=GAME_BSS

SEGMENTS=--code-name $(CODE_SEGMENT) \
	--rodata-name $(RODATA_SEGMENT) \
	--bss-name $(BSS_SEGMENT) \
	--data-name $(DATA_SEGMENT)

all: objlist

objlist: $(objects)
	$(RM) objlist
	for obj in $(objects); do $(ECHO) ../$(thisdir)/$$obj >> objlist; done

background.o : gfx.bmp
	$(SPRPCK) -t6 -p0 $<
	$(RM) $*.obj
	$(CP) gfx.pal palette.pal
	$(SPRPCK) -t6 -p2 -S160102 $<
	$(ECHO) .global _background > $*.s
	$(ECHO) .segment \"$(RODATA_SEGMENT)\" >> $*.s
	$(ECHO) _background: .incbin \"gfx.spr\" >> $*.s
	$(AS) -t lynx -o $@ $(AFLAGS) $*.s

grid0.o : gfx.bmp
	$(SPRPCK) -t6 -p2 -o160000 -S057021 $<
	$(ECHO) .global _grid0 > $*.s
	$(ECHO) .segment \"$(RODATA_SEGMENT)\" >> $*.s
	$(ECHO) _grid0: .incbin \"gfx.spr\" >> $*.s
	$(AS) -t lynx -o $@ $(AFLAGS) $*.s

grid1.o : gfx.bmp
	$(SPRPCK) -t6 -p2 -o160021 -S037037 $<
	$(ECHO) .global _grid1 > $*.s
	$(ECHO) .segment \"$(RODATA_SEGMENT)\" >> $*.s
	$(ECHO) _grid1: .incbin \"gfx.spr\" >> $*.s
	$(AS) -t lynx -o $@ $(AFLAGS) $*.s
gridSmall.o : gfx.bmp
	$(SPRPCK) -t6 -p2 -o160058 -S013013 $<
	$(ECHO) .global _gridSmall > $*.s
	$(ECHO) .segment \"$(RODATA_SEGMENT)\" >> $*.s
	$(ECHO) _gridSmall: .incbin \"gfx.spr\" >> $*.s
	$(AS) -t lynx -o $@ $(AFLAGS) $*.s
cursor0.o : gfx.bmp
	$(SPRPCK) -t6 -p2 -o217004 -S011004 $<
	$(ECHO) .global _cursor0 > $*.s
	$(ECHO) .segment \"$(RODATA_SEGMENT)\" >> $*.s
	$(ECHO) _cursor0: .incbin \"gfx.spr\" >> $*.s
	$(AS) -t lynx -o $@ $(AFLAGS) $*.s
cursor1.o : gfx.bmp
	$(SPRPCK) -t6 -p2 -o217000 -S011004 $<
	$(ECHO) .global _cursor1 > $*.s
	$(ECHO) .segment \"$(RODATA_SEGMENT)\" >> $*.s
	$(ECHO) _cursor1: .incbin \"gfx.spr\" >> $*.s
	$(AS) -t lynx -o $@ $(AFLAGS) $*.s
tile1.o : gfx.bmp
	$(SPRPCK) -t6 -p2 -o217008 -S011004 $<
	$(ECHO) .global _tile1 > $*.s
	$(ECHO) .segment \"$(RODATA_SEGMENT)\" >> $*.s
	$(ECHO) _tile1: .incbin \"gfx.spr\" >> $*.s
	$(AS) -t lynx -o $@ $(AFLAGS) $*.s
tile2.o : gfx.bmp
	$(SPRPCK) -t6 -p2 -o217016 -S011004 $<
	$(ECHO) .global _tile2 > $*.s
	$(ECHO) .segment \"$(RODATA_SEGMENT)\" >> $*.s
	$(ECHO) _tile2: .incbin \"gfx.spr\" >> $*.s
	$(AS) -t lynx -o $@ $(AFLAGS) $*.s
dot0.o : gfx.bmp
	$(SPRPCK) -t6 -p2 -o199045 -S002002 $<
	$(ECHO) .global _dot0 > $*.s
	$(ECHO) .segment \"$(RODATA_SEGMENT)\" >> $*.s
	$(ECHO) _dot0: .incbin \"gfx.spr\" >> $*.s
	$(AS) -t lynx -o $@ $(AFLAGS) $*.s
dot1.o : gfx.bmp
	$(SPRPCK) -t6 -p2 -o199047 -S002002 $<
	$(ECHO) .global _dot1 > $*.s
	$(ECHO) .segment \"$(RODATA_SEGMENT)\" >> $*.s
	$(ECHO) _dot1: .incbin \"gfx.spr\" >> $*.s
	$(AS) -t lynx -o $@ $(AFLAGS) $*.s
dot2.o : gfx.bmp
	$(SPRPCK) -t6 -p2 -o199049 -S002002 $<
	$(ECHO) .global _dot2 > $*.s
	$(ECHO) .segment \"$(RODATA_SEGMENT)\" >> $*.s
	$(ECHO) _dot2: .incbin \"gfx.spr\" >> $*.s
	$(AS) -t lynx -o $@ $(AFLAGS) $*.s
dleft.o : gfx.bmp
	$(SPRPCK) -t6 -p2 -o173058 -S013013 $<
	$(ECHO) .global _dleft > $*.s
	$(ECHO) .segment \"$(RODATA_SEGMENT)\" >> $*.s
	$(ECHO) _dleft: .incbin \"gfx.spr\" >> $*.s
	$(AS) -t lynx -o $@ $(AFLAGS) $*.s 
dright.o : gfx.bmp
	$(SPRPCK) -t6 -p2 -o186058 -S013013 $<
	$(ECHO) .global _dright > $*.s
	$(ECHO) .segment \"$(RODATA_SEGMENT)\" >> $*.s
	$(ECHO) _dright: .incbin \"gfx.spr\" >> $*.s
	$(AS) -t lynx -o $@ $(AFLAGS) $*.s

clean:
	$(RM) objlist $(temporaryobjects) $(objects)
