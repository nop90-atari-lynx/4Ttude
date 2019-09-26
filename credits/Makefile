include ../Common.mk

thisdir=credits

objects= \
	tutorialbg.o creditsbg.o marks.o grid.o pressA.o tuttxt.o credits.o

temporaryobjects= \
	*.spr *.pal *.s 

CODE_SEGMENT=CREDITS_CODE
DATA_SEGMENT=CREDITS_DATA
RODATA_SEGMENT=CREDITS_RODATA
BSS_SEGMENT=CREDITS_BSS

SEGMENTS=--code-name $(CODE_SEGMENT) \
	--rodata-name $(RODATA_SEGMENT) \
	--bss-name $(BSS_SEGMENT) \
	--data-name $(DATA_SEGMENT)

all: objlist

objlist: $(objects)
	$(RM) objlist
	for obj in $(objects); do $(ECHO) ../$(thisdir)/$$obj >> objlist; done

marks.o : marks.bmp
	$(SPRPCK) -t6 -p2 -r002001 -S017017 $< 
	$(ECHO) .global _marks000000 > $*.s
	$(ECHO) .global _marks000001 >> $*.s
	$(ECHO) .segment \"$(RODATA_SEGMENT)\" >> $*.s
	$(ECHO) _marks000000: .incbin \"marks000000.spr\" >> $*.s
	$(ECHO) _marks000001: .incbin \"marks000001.spr\" >> $*.s
	$(AS) -t lynx -o $@ $(AFLAGS) $*.s

pressA.o : pressA.bmp
	$(SPRPCK) -t6 -p2 -r001002 -S029007 $< 
	$(ECHO) .global _pressA000000 > $*.s
	$(ECHO) .global _pressA001000 >> $*.s
	$(ECHO) .segment \"$(RODATA_SEGMENT)\" >> $*.s
	$(ECHO) _pressA000000: .incbin \"pressA000000.spr\" >> $*.s
	$(ECHO) _pressA001000: .incbin \"pressA001000.spr\" >> $*.s
	$(AS) -t lynx -o $@ $(AFLAGS) $*.s

clean:
	$(RM) objlist $(temporaryobjects) $(objects) 

