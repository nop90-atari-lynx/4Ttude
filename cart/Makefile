include ../Common.mk

objects= \
	lnxhdr.o \
	directory.o

objlists = \
	../resident/objlist \
	../intro/objlist \
	../credits/objlist \
	../menu/objlist \
	../game/objlist \
	../game2P/objlist \
	../tunes/objlist \
	../samples/objlist

others = \
	@../resident/objlist \
	@../intro/objlist \
	@../credits/objlist \
	@../menu/objlist \
	@../game/objlist \
	@../game2P/objlist \
	@../tunes/objlist \
	@../samples/objlist

target = 4ttude.lnx

all: $(target)

$(target) : $(objects) $(objlists)
	$(CL) -t lynx -o $@ -m lynx.map -C lynx.cfg $(objects) $(others) lynx.lib

clean:
	$(RM) $(objects) $(target) lynx.map

