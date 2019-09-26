include ../Common.mk

thisdir=resident

objects= \
	LynxSD.o \
	lynxeeprom.o \
	lynx-snd.o \
	playpcm.o \
	font.o \
	text.o \
	resident.o

temporaryobjects= \
	font*.spr font*.pal font*.s

CODE_SEGMENT=CODE
DATA_SEGMENT=DATA
RODATA_SEGMENT=RODATA
BSS_SEGMENT=BSS

SEGMENTS=--code-name $(CODE_SEGMENT) \
	--rodata-name $(RODATA_SEGMENT) \
	--bss-name $(BSS_SEGMENT) \
	--data-name $(DATA_SEGMENT)

all: objlist

objlist: $(objects)
	$(RM) objlist
	for obj in $(objects); do $(ECHO) ../$(thisdir)/$$obj >> objlist; done

font.o : font.bmp
	$(SPRPCK) -t6 -p2 -r026003 -S006009 $< 
	$(ECHO) .global _font000000 > $*.s
	$(ECHO) .global _font000001 >> $*.s
	$(ECHO) .global _font000002 >> $*.s
	$(ECHO) .global _font000003 >> $*.s
	$(ECHO) .global _font000004 >> $*.s
	$(ECHO) .global _font000005 >> $*.s
	$(ECHO) .global _font000006 >> $*.s
	$(ECHO) .global _font000007 >> $*.s
	$(ECHO) .global _font000008 >> $*.s
	$(ECHO) .global _font000009 >> $*.s
	$(ECHO) .global _font000010 >> $*.s
	$(ECHO) .global _font000011 >> $*.s
	$(ECHO) .global _font000012 >> $*.s
	$(ECHO) .global _font000013 >> $*.s
	$(ECHO) .global _font000014 >> $*.s
	$(ECHO) .global _font000015 >> $*.s
	$(ECHO) .global _font000016 >> $*.s
	$(ECHO) .global _font000017 >> $*.s
	$(ECHO) .global _font000018 >> $*.s
	$(ECHO) .global _font000019 >> $*.s
	$(ECHO) .global _font000020 >> $*.s
	$(ECHO) .global _font000021 >> $*.s
	$(ECHO) .global _font000022 >> $*.s
	$(ECHO) .global _font000023 >> $*.s
	$(ECHO) .global _font000024 >> $*.s
	$(ECHO) .global _font000025 >> $*.s
	$(ECHO) .global _font001000 >> $*.s
	$(ECHO) .global _font001001 >> $*.s
	$(ECHO) .global _font001002 >> $*.s
	$(ECHO) .global _font001003 >> $*.s
	$(ECHO) .global _font001004 >> $*.s
	$(ECHO) .global _font001005 >> $*.s
	$(ECHO) .global _font001006 >> $*.s
	$(ECHO) .global _font001007 >> $*.s
	$(ECHO) .global _font001008 >> $*.s
	$(ECHO) .global _font001009 >> $*.s
	$(ECHO) .global _font001010 >> $*.s
	$(ECHO) .global _font001011 >> $*.s
	$(ECHO) .global _font001012 >> $*.s
	$(ECHO) .global _font001013 >> $*.s
	$(ECHO) .global _font001014 >> $*.s
	$(ECHO) .global _font001015 >> $*.s
	$(ECHO) .global _font001016 >> $*.s
	$(ECHO) .global _font001017 >> $*.s
	$(ECHO) .global _font001018 >> $*.s
	$(ECHO) .global _font001019 >> $*.s
	$(ECHO) .global _font001020 >> $*.s
	$(ECHO) .global _font001021 >> $*.s
	$(ECHO) .global _font001022 >> $*.s
	$(ECHO) .global _font001023 >> $*.s
	$(ECHO) .global _font001024 >> $*.s
	$(ECHO) .global _font001025 >> $*.s
	$(ECHO) .global _font002000 >> $*.s
	$(ECHO) .global _font002001 >> $*.s
	$(ECHO) .global _font002002 >> $*.s
	$(ECHO) .global _font002003 >> $*.s
	$(ECHO) .global _font002004 >> $*.s
	$(ECHO) .global _font002005 >> $*.s
	$(ECHO) .global _font002006 >> $*.s
	$(ECHO) .global _font002007 >> $*.s
	$(ECHO) .global _font002008 >> $*.s
	$(ECHO) .global _font002009 >> $*.s
	$(ECHO) .global _font002010 >> $*.s
	$(ECHO) .global _font002011 >> $*.s
	$(ECHO) .global _font002012 >> $*.s
	$(ECHO) .global _font002013 >> $*.s
	$(ECHO) .global _font002014 >> $*.s
	$(ECHO) .global _font002015 >> $*.s
	$(ECHO) .global _font002016 >> $*.s
	$(ECHO) .global _font002017 >> $*.s
	$(ECHO) .global _font002018 >> $*.s
	$(ECHO) .global _font002019 >> $*.s
	$(ECHO) .segment \"$(RODATA_SEGMENT)\" >> $*.s
	$(ECHO) _font000000: .incbin \"font000000.spr\" >> $*.s
	$(ECHO) _font000001: .incbin \"font000001.spr\" >> $*.s
	$(ECHO) _font000002: .incbin \"font000002.spr\" >> $*.s
	$(ECHO) _font000003: .incbin \"font000003.spr\" >> $*.s
	$(ECHO) _font000004: .incbin \"font000004.spr\" >> $*.s
	$(ECHO) _font000005: .incbin \"font000005.spr\" >> $*.s
	$(ECHO) _font000006: .incbin \"font000006.spr\" >> $*.s
	$(ECHO) _font000007: .incbin \"font000007.spr\" >> $*.s
	$(ECHO) _font000008: .incbin \"font000008.spr\" >> $*.s
	$(ECHO) _font000009: .incbin \"font000009.spr\" >> $*.s
	$(ECHO) _font000010: .incbin \"font000010.spr\" >> $*.s
	$(ECHO) _font000011: .incbin \"font000011.spr\" >> $*.s
	$(ECHO) _font000012: .incbin \"font000012.spr\" >> $*.s
	$(ECHO) _font000013: .incbin \"font000013.spr\" >> $*.s
	$(ECHO) _font000014: .incbin \"font000014.spr\" >> $*.s
	$(ECHO) _font000015: .incbin \"font000015.spr\" >> $*.s
	$(ECHO) _font000016: .incbin \"font000016.spr\" >> $*.s
	$(ECHO) _font000017: .incbin \"font000017.spr\" >> $*.s
	$(ECHO) _font000018: .incbin \"font000018.spr\" >> $*.s
	$(ECHO) _font000019: .incbin \"font000019.spr\" >> $*.s
	$(ECHO) _font000020: .incbin \"font000020.spr\" >> $*.s
	$(ECHO) _font000021: .incbin \"font000021.spr\" >> $*.s
	$(ECHO) _font000022: .incbin \"font000022.spr\" >> $*.s
	$(ECHO) _font000023: .incbin \"font000023.spr\" >> $*.s
	$(ECHO) _font000024: .incbin \"font000024.spr\" >> $*.s
	$(ECHO) _font000025: .incbin \"font000025.spr\" >> $*.s
	$(ECHO) _font001000: .incbin \"font001000.spr\" >> $*.s
	$(ECHO) _font001001: .incbin \"font001001.spr\" >> $*.s
	$(ECHO) _font001002: .incbin \"font001002.spr\" >> $*.s
	$(ECHO) _font001003: .incbin \"font001003.spr\" >> $*.s
	$(ECHO) _font001004: .incbin \"font001004.spr\" >> $*.s
	$(ECHO) _font001005: .incbin \"font001005.spr\" >> $*.s
	$(ECHO) _font001006: .incbin \"font001006.spr\" >> $*.s
	$(ECHO) _font001007: .incbin \"font001007.spr\" >> $*.s
	$(ECHO) _font001008: .incbin \"font001008.spr\" >> $*.s
	$(ECHO) _font001009: .incbin \"font001009.spr\" >> $*.s
	$(ECHO) _font001010: .incbin \"font001010.spr\" >> $*.s
	$(ECHO) _font001011: .incbin \"font001011.spr\" >> $*.s
	$(ECHO) _font001012: .incbin \"font001012.spr\" >> $*.s
	$(ECHO) _font001013: .incbin \"font001013.spr\" >> $*.s
	$(ECHO) _font001014: .incbin \"font001014.spr\" >> $*.s
	$(ECHO) _font001015: .incbin \"font001015.spr\" >> $*.s
	$(ECHO) _font001016: .incbin \"font001016.spr\" >> $*.s
	$(ECHO) _font001017: .incbin \"font001017.spr\" >> $*.s
	$(ECHO) _font001018: .incbin \"font001018.spr\" >> $*.s
	$(ECHO) _font001019: .incbin \"font001019.spr\" >> $*.s
	$(ECHO) _font001020: .incbin \"font001020.spr\" >> $*.s
	$(ECHO) _font001021: .incbin \"font001021.spr\" >> $*.s
	$(ECHO) _font001022: .incbin \"font001022.spr\" >> $*.s
	$(ECHO) _font001023: .incbin \"font001023.spr\" >> $*.s
	$(ECHO) _font001024: .incbin \"font001024.spr\" >> $*.s
	$(ECHO) _font001025: .incbin \"font001025.spr\" >> $*.s
	$(ECHO) _font002000: .incbin \"font002000.spr\" >> $*.s
	$(ECHO) _font002001: .incbin \"font002001.spr\" >> $*.s
	$(ECHO) _font002002: .incbin \"font002002.spr\" >> $*.s
	$(ECHO) _font002003: .incbin \"font002003.spr\" >> $*.s
	$(ECHO) _font002004: .incbin \"font002004.spr\" >> $*.s
	$(ECHO) _font002005: .incbin \"font002005.spr\" >> $*.s
	$(ECHO) _font002006: .incbin \"font002006.spr\" >> $*.s
	$(ECHO) _font002007: .incbin \"font002007.spr\" >> $*.s
	$(ECHO) _font002008: .incbin \"font002008.spr\" >> $*.s
	$(ECHO) _font002009: .incbin \"font002009.spr\" >> $*.s
	$(ECHO) _font002010: .incbin \"font002010.spr\" >> $*.s
	$(ECHO) _font002011: .incbin \"font002011.spr\" >> $*.s
	$(ECHO) _font002012: .incbin \"font002012.spr\" >> $*.s
	$(ECHO) _font002013: .incbin \"font002013.spr\" >> $*.s
	$(ECHO) _font002014: .incbin \"font002014.spr\" >> $*.s
	$(ECHO) _font002015: .incbin \"font002015.spr\" >> $*.s
	$(ECHO) _font002016: .incbin \"font002016.spr\" >> $*.s
	$(ECHO) _font002017: .incbin \"font002017.spr\" >> $*.s
	$(ECHO) _font002018: .incbin \"font002018.spr\" >> $*.s
	$(ECHO) _font002019: .incbin \"font002019.spr\" >> $*.s
	$(AS) -t lynx -o $@ $(AFLAGS) $*.s

clean:
	$(RM) objlist $(temporaryobjects) $(objects)

