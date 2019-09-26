;
; Karri Kaksonen, 2017
;
; This header contains data for emulators like Handy and Mednafen
;
	.import		__BLOCKSIZE__
	.export		__EXEHDR__: absolute = 1


; ------------------------------------------------------------------------
; EXE header
	.segment "EXEHDR"
	.byte	'L','Y','N','X'				; magic
	.word	__BLOCKSIZE__				; bank 0 page size
	.word	0					; bank 1 page size
	.word	1					; version number
	.asciiz	"4Ttude                         "	; 32 bytes cart name
	.asciiz	"Nop90          "			; 16 bytes manufacturer 
	.byte	0					; rotation 1=left
							; rotation 2=right
        .byte   0                                       ; aud bits 1=in use for addressing
        .byte   65                                      ; eeprom -> use 1 for the most common eeprom, 64 to use SD Cart saves, 65 for both
                                                        ; eeprom [2:0] -
                                                        ; 0 - no eeprom
                                                        ; 1 - 93c46 16 bit mode (used in Ttris, SIMIS, Alpine Games, ..., MegaPak I at least)
                                                        ; 2        56
                                                        ; 3 - 93c66 16 bit mode
                                                        ; 4        76
                                                        ; 5 - 93c86 16 bit mode
                                                        ; (remark: size in bits is 2^(value+9) -- (please recheck!)
                                                        ; eeprom [3-5] - reserved - keep it to 0 for further usage
                                                        ; eeprom [6] - 0 - real eeprom, 1 - eeprom as a file in /saves/flappy.hi on SD cart
                                                        ; eeprom [7] - 0 - 16 bit mode, 1 - 8 bit mode
        .byte   0,0,0                                   ; spare
