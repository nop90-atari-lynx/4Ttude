include ../Common.mk

thisdir=menu

objects= \
	marker.o markeron.o menubg1.o menubg2.o menubg3.o select.o menu.o

temporaryobjects= \
	*.spr *.pal *.s 

CODE_SEGMENT=MENU_CODE
DATA_SEGMENT=MENU_DATA
RODATA_SEGMENT=MENU_RODATA
BSS_SEGMENT=MENU_BSS

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

