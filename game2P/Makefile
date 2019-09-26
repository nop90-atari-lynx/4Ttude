include ../Common.mk

thisdir=game2P

objects= \
	dleft2.o dright2.o dot02.o dot12.o dot22.o tile12.o tile22.o cursor02.o cursor12.o grid02.o grid12.o gridSmall2.o background2.o \
	net.o game.o comborow.o comboset.o gboard.o 

temporaryobjects= \
	*.spr *.pal *.s 

CODE_SEGMENT=GAME2P_CODE
DATA_SEGMENT=GAME2P_DATA
RODATA_SEGMENT=GAME2P_RODATA
BSS_SEGMENT=GAME2P_BSS

SEGMENTS=--code-name $(CODE_SEGMENT) \
	--rodata-name $(RODATA_SEGMENT) \
	--bss-name $(BSS_SEGMENT) \
	--data-name $(DATA_SEGMENT)

all: objlist

objlist: $(objects)
	$(RM) objlist
	for obj in $(objects); do $(ECHO) ../$(thisdir)/$$obj >> objlist; done

background2.o : gfx2.bmp
	$(SPRPCK) -t6 -p0 $<
	$(RM) $*.obj
	$(CP) gfx2.pal palette.pal
	$(SPRPCK) -t6 -p2 -S160102 $<
	$(ECHO) .global _background2 > $*.s
	$(ECHO) .segment \"$(RODATA_SEGMENT)\" >> $*.s
	$(ECHO) _background2: .incbin \"gfx2.spr\" >> $*.s
	$(AS) -t lynx -o $@ $(AFLAGS) $*.s

grid02.o : gfx2.bmp
	$(SPRPCK) -t6 -p2 -o160000 -S057021 $<
	$(ECHO) .global _grid02 > $*.s
	$(ECHO) .segment \"$(RODATA_SEGMENT)\" >> $*.s
	$(ECHO) _grid02: .incbin \"gfx2.spr\" >> $*.s
	$(AS) -t lynx -o $@ $(AFLAGS) $*.s

grid12.o : gfx2.bmp
	$(SPRPCK) -t6 -p2 -o160021 -S037037 $<
	$(ECHO) .global _grid12 > $*.s
	$(ECHO) .segment \"$(RODATA_SEGMENT)\" >> $*.s
	$(ECHO) _grid12: .incbin \"gfx2.spr\" >> $*.s
	$(AS) -t lynx -o $@ $(AFLAGS) $*.s
gridSmall2.o : gfx2.bmp
	$(SPRPCK) -t6 -p2 -o160058 -S013013 $<
	$(ECHO) .global _gridSmall2 > $*.s
	$(ECHO) .segment \"$(RODATA_SEGMENT)\" >> $*.s
	$(ECHO) _gridSmall2: .incbin \"gfx2.spr\" >> $*.s
	$(AS) -t lynx -o $@ $(AFLAGS) $*.s
cursor02.o : gfx2.bmp
	$(SPRPCK) -t6 -p2 -o217004 -S011004 $<
	$(ECHO) .global _cursor02 > $*.s
	$(ECHO) .segment \"$(RODATA_SEGMENT)\" >> $*.s
	$(ECHO) _cursor02: .incbin \"gfx2.spr\" >> $*.s
	$(AS) -t lynx -o $@ $(AFLAGS) $*.s
cursor12.o : gfx2.bmp
	$(SPRPCK) -t6 -p2 -o217000 -S011004 $<
	$(ECHO) .global _cursor12 > $*.s
	$(ECHO) .segment \"$(RODATA_SEGMENT)\" >> $*.s
	$(ECHO) _cursor12: .incbin \"gfx2.spr\" >> $*.s
	$(AS) -t lynx -o $@ $(AFLAGS) $*.s
tile12.o : gfx2.bmp
	$(SPRPCK) -t6 -p2 -o217008 -S011004 $<
	$(ECHO) .global _tile12 > $*.s
	$(ECHO) .segment \"$(RODATA_SEGMENT)\" >> $*.s
	$(ECHO) _tile12: .incbin \"gfx2.spr\" >> $*.s
	$(AS) -t lynx -o $@ $(AFLAGS) $*.s
tile22.o : gfx2.bmp
	$(SPRPCK) -t6 -p2 -o217016 -S011004 $<
	$(ECHO) .global _tile22 > $*.s
	$(ECHO) .segment \"$(RODATA_SEGMENT)\" >> $*.s
	$(ECHO) _tile22: .incbin \"gfx2.spr\" >> $*.s
	$(AS) -t lynx -o $@ $(AFLAGS) $*.s
dot02.o : gfx2.bmp
	$(SPRPCK) -t6 -p2 -o199045 -S002002 $<
	$(ECHO) .global _dot02 > $*.s
	$(ECHO) .segment \"$(RODATA_SEGMENT)\" >> $*.s
	$(ECHO) _dot02: .incbin \"gfx2.spr\" >> $*.s
	$(AS) -t lynx -o $@ $(AFLAGS) $*.s
dot12.o : gfx2.bmp
	$(SPRPCK) -t6 -p2 -o199047 -S002002 $<
	$(ECHO) .global _dot12 > $*.s
	$(ECHO) .segment \"$(RODATA_SEGMENT)\" >> $*.s
	$(ECHO) _dot12: .incbin \"gfx2.spr\" >> $*.s
	$(AS) -t lynx -o $@ $(AFLAGS) $*.s
dot22.o : gfx2.bmp
	$(SPRPCK) -t6 -p2 -o199049 -S002002 $<
	$(ECHO) .global _dot22 > $*.s
	$(ECHO) .segment \"$(RODATA_SEGMENT)\" >> $*.s
	$(ECHO) _dot22: .incbin \"gfx2.spr\" >> $*.s
	$(AS) -t lynx -o $@ $(AFLAGS) $*.s
dleft2.o : gfx2.bmp
	$(SPRPCK) -t6 -p2 -o173058 -S013013 $<
	$(ECHO) .global _dleft2 > $*.s
	$(ECHO) .segment \"$(RODATA_SEGMENT)\" >> $*.s
	$(ECHO) _dleft2: .incbin \"gfx2.spr\" >> $*.s
	$(AS) -t lynx -o $@ $(AFLAGS) $*.s 
dright2.o : gfx2.bmp
	$(SPRPCK) -t6 -p2 -o186058 -S013013 $<
	$(ECHO) .global _dright2 > $*.s
	$(ECHO) .segment \"$(RODATA_SEGMENT)\" >> $*.s
	$(ECHO) _dright2: .incbin \"gfx2.spr\" >> $*.s
	$(AS) -t lynx -o $@ $(AFLAGS) $*.s

clean:
	$(RM) objlist $(temporaryobjects) $(objects)
