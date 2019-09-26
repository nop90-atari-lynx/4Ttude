all:
	"$(MAKE)" -C game;
	"$(MAKE)" -C game2P;
	"$(MAKE)" -C menu;
	"$(MAKE)" -C credits;
	"$(MAKE)" -C intro;
	"$(MAKE)" -C resident;
	"$(MAKE)" -C tunes;
	"$(MAKE)" -C samples;
	"$(MAKE)" -C cart;
	cp cart/4ttude.lnx 4ttude.lnx

clean:
	"$(MAKE)" -C cart clean;
	"$(MAKE)" -C menu clean;
	"$(MAKE)" -C game clean;
	"$(MAKE)" -C game2P clean;
	"$(MAKE)" -C credits clean;
	"$(MAKE)" -C intro clean;
	"$(MAKE)" -C resident clean;
	"$(MAKE)" -C tunes clean;
	"$(MAKE)" -C samples clean;
	rm -f 4ttude.lnx
