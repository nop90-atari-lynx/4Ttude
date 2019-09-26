include ../Common.mk

thisdir=intro

objects= \
	fadein.o fadeout.o \
	title.o nop90.o \
	gerk0.o gerk1.o gerk2.o gerk3.o gerk4.o gerk5.o \
	intro.o 
	

temporaryobjects= \
	*.spr *.pal nop90.s gerk*.s title.s

CODE_SEGMENT=INTRO_CODE
DATA_SEGMENT=INTRO_DATA
RODATA_SEGMENT=INTRO_RODATA
BSS_SEGMENT=INTRO_BSS

SEGMENTS=--code-name $(CODE_SEGMENT) \
	--rodata-name $(RODATA_SEGMENT) \
	--bss-name $(BSS_SEGMENT) \
	--data-name $(DATA_SEGMENT)

all: objlist

objlist: $(objects)
	$(RM) objlist
	for obj in $(objects); do $(ECHO) ../$(thisdir)/$$obj >> objlist; done

clean:
	$(RM) objlist $(temporaryobjects) $(objects)

