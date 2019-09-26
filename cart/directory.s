;
; Karri Kaksonen, 2015
;

	.import __BLOCKSIZE__
	.import __STARTOFDIRECTORY__

	.export _MAIN_FILENR : absolute
	.import __STARTUP_LOAD__
	.import __STARTUP_SIZE__
	.import __INIT_SIZE__
	.import __CODE_SIZE__
	.import __DATA_SIZE__
	.import __RODATA_SIZE__

	.export _INTRO_FILENR : absolute
	.import __INTRO_CODE_LOAD__
	.import __INTRO_CODE_SIZE__
	.import __INTRO_DATA_SIZE__
	.import __INTRO_RODATA_SIZE__

	.export _MENU_FILENR : absolute
	.import __MENU_CODE_LOAD__
	.import __MENU_CODE_SIZE__
	.import __MENU_DATA_SIZE__
	.import __MENU_RODATA_SIZE__

	.export _CREDITS_FILENR : absolute
	.import __CREDITS_CODE_LOAD__
	.import __CREDITS_CODE_SIZE__
	.import __CREDITS_DATA_SIZE__
	.import __CREDITS_RODATA_SIZE__

	.export _GAME_FILENR : absolute
	.import __GAME_CODE_LOAD__
	.import __GAME_CODE_SIZE__
	.import __GAME_DATA_SIZE__
	.import __GAME_RODATA_SIZE__

	.export _GAME2P_FILENR : absolute
	.import __GAME2P_CODE_LOAD__
	.import __GAME2P_CODE_SIZE__
	.import __GAME2P_DATA_SIZE__
	.import __GAME2P_RODATA_SIZE__

	.export _TUNE0_FILENR : absolute
	.import __TUNE0_START__
	.import __TUNE0_RODATA_SIZE__
	.export _TUNE1_FILENR : absolute
	.import __TUNE1_START__
	.import __TUNE1_RODATA_SIZE__
	.export _TUNE2_FILENR : absolute
	.import __TUNE2_START__
	.import __TUNE2_RODATA_SIZE__
	.export _TUNE3_FILENR : absolute
	.import __TUNE3_START__
	.import __TUNE3_RODATA_SIZE__

	.export _SAMPLE0_FILENR : absolute
	.import __SAMPLE0_START__
	.import __SAMPLE0_RODATA_SIZE__
	.export _SAMPLE1_FILENR : absolute
	.import __SAMPLE1_START__
	.import __SAMPLE1_RODATA_SIZE__
	.export _SAMPLE2_FILENR : absolute
	.import __SAMPLE2_START__
	.import __SAMPLE2_RODATA_SIZE__
	.export _SAMPLE3_FILENR : absolute
	.import __SAMPLE3_START__
	.import __SAMPLE3_RODATA_SIZE__
	.export _SAMPLE4_FILENR : absolute
	.import __SAMPLE4_START__
	.import __SAMPLE4_RODATA_SIZE__

	.segment "DIRECTORY"

__DIRECTORY_START__:

.macro entry old_off, old_len, new_off, new_block, new_len, new_size, new_addr
new_off=old_off+old_len
new_block=new_off/__BLOCKSIZE__
new_len=new_size
	.byte	<new_block
	.word	(new_off & (__BLOCKSIZE__ - 1))
	.byte	$88
	.word	new_addr
	.word	new_len
.endmacro

; Entry 0 - first executable
_MAIN_FILENR=0
entry __STARTOFDIRECTORY__+(__DIRECTORY_END__-__DIRECTORY_START__), 0, mainoff, mainblock, mainlen, __STARTUP_SIZE__+__INIT_SIZE__+__CODE_SIZE__+__RODATA_SIZE__+__DATA_SIZE__, __STARTUP_LOAD__

_INTRO_FILENR=_MAIN_FILENR+1
entry mainoff, mainlen, introoff, introblock, introlen,__INTRO_CODE_SIZE__+__INTRO_RODATA_SIZE__+__INTRO_DATA_SIZE__, __INTRO_CODE_LOAD__

_MENU_FILENR=_INTRO_FILENR+1
entry introoff, introlen, menuoff, menublock, menulen,__MENU_CODE_SIZE__+__MENU_RODATA_SIZE__+__MENU_DATA_SIZE__, __MENU_CODE_LOAD__

_CREDITS_FILENR=_MENU_FILENR+1
entry menuoff, menulen, creditsoff, creditsblock, creditslen,__CREDITS_CODE_SIZE__+__CREDITS_RODATA_SIZE__+__CREDITS_DATA_SIZE__, __CREDITS_CODE_LOAD__

_GAME_FILENR=_CREDITS_FILENR+1
entry creditsoff, creditslen, gameoff, gameblock, gamelen,__GAME_CODE_SIZE__+__GAME_RODATA_SIZE__+__GAME_DATA_SIZE__, __GAME_CODE_LOAD__

_GAME2P_FILENR=_GAME_FILENR+1
entry gameoff, gamelen, game2poff, game2pblock, game2plen,__GAME2P_CODE_SIZE__+__GAME2P_RODATA_SIZE__+__GAME2P_DATA_SIZE__, __GAME2P_CODE_LOAD__

_TUNE0_FILENR=_GAME2P_FILENR+1
entry game2poff, game2plen, tune0off, tune0block, tune0len,__TUNE0_RODATA_SIZE__, __TUNE0_START__
_TUNE1_FILENR=_TUNE0_FILENR+1
entry tune0off, tune0len, tune1off, tune1block, tune1len,__TUNE1_RODATA_SIZE__, __TUNE1_START__
_TUNE2_FILENR=_TUNE1_FILENR+1
entry tune1off, tune1len, tune2off, tune2block, tune2len,__TUNE2_RODATA_SIZE__, __TUNE2_START__
_TUNE3_FILENR=_TUNE2_FILENR+1
entry tune2off, tune2len, tune3off, tune3block, tune3len,__TUNE3_RODATA_SIZE__, __TUNE3_START__

_SAMPLE0_FILENR=_TUNE3_FILENR+1
entry tune3off, tune3len, sample0off, sample0block, sample0len,__SAMPLE0_RODATA_SIZE__, __SAMPLE0_START__
_SAMPLE1_FILENR=_SAMPLE0_FILENR+1
entry sample0off, sample0len, sample1off, sample1block, sample1len,__SAMPLE1_RODATA_SIZE__, __SAMPLE1_START__
_SAMPLE2_FILENR=_SAMPLE1_FILENR+1
entry sample1off, sample1len, sample2off, sample2block, sample2len,__SAMPLE2_RODATA_SIZE__, __SAMPLE2_START__
_SAMPLE3_FILENR=_SAMPLE2_FILENR+1
entry sample2off, sample2len, sample3off, sample3block, sample3len,__SAMPLE3_RODATA_SIZE__, __SAMPLE3_START__
_SAMPLE4_FILENR=_SAMPLE3_FILENR+1
entry sample3off, sample3len, sample4off, sample4block, sample4len,__SAMPLE4_RODATA_SIZE__, __SAMPLE4_START__
_SAMPLE5_FILENR=_SAMPLE4_FILENR+1

__DIRECTORY_END__:

