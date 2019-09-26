include ../Common.mk

thisdir=tunes

objects= \
	TUNE0.o TUNE1.o TUNE2.o TUNE3.o

all: objlist

objlist: $(objects)
	$(RM) objlist
	for obj in $(objects); do $(ECHO) ../$(thisdir)/$$obj >> objlist; done

clean:
	$(RM) objlist $(objects)
