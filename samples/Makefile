################ EDIT THESE ########################

# As we are producing a cart we want to put our code
# in a loadable segment so that we can load it in RAM
# when we need it and throw it away after use.
# Without these defines the code would go into the
# main RAM and stay there forever.

# These are the object files we want this makefile to produce
objects= \
	SAMPLE0.o SAMPLE1.o SAMPLE2.o \
	SAMPLE3.o SAMPLE4.o 

# SAMPLEF.o SAMPLEG.o 

############## DONT EDIT BELOW THIS ###############  

# We are compiling for Atari Lynx
SYS=lynx

# These are the names of the tools we use
CO=co65
CC=cc65
AS=ca65
AR=ar65
SP=sp65
CP=cp
RM=rm -f 
ECHO=echo
TOUCH=touch
SPRPCK=sprpck

# The flag for adding stuff to a library
ARFLAGS=a

# The flags for compiling C-code
CFLAGS=-I . -t $(SYS) --add-source -O -Or -Cl -Os

# Include paths we may need for compilations
ifeq ($(CC65_INC),)
	CC65_INC=/usr/lib/cc65/include
endif
ifeq ($(CC65_ASMINC),)
	CC65_ASMINC="$(CC65_INC)/../asminc"
endif

# Rule for making a *.o file out of a *.s file
%.o: %.s
	$(AS) -t lynx -I $(CC65_ASMINC) -o $@ $(AFLAGS) $<

# Rule for making a *.o file out of a *.bin file (for game levels)
%.o : %.raw
	$(ECHO) .global _$* > $*.s
	$(ECHO) .segment \"$*_RODATA\" >> $*.s
	$(ECHO) _$*: .incbin \"$*.raw\" >> $*.s
	$(AS) -t lynx -o $@ $(AFLAGS) $*.s

all: $(objects)
	$(TOUCH) objlist
	$(RM) objlist
	for obj in $(objects); do $(ECHO) ../samples/$$obj >> objlist; done

clean :
	$(TOUCH) $(objects)
	$(RM) $(objects)
	$(TOUCH) objlist
	$(RM) objlist *.s

