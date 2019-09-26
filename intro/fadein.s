; ***
; CC65 Lynx Library
;
; Shawn Jefferson, June 2004
; 
; ***
;
; void __fastcall__ fade_in(char *pal, unsigned char interval)
;
; Fade in the palette from the current palette values in hardware
; to the palette passed in, waiting (interval * 64us)*2 between palette
; changes.  Make sure that an all black palette is in place already (use
; _set_black_pal() to set it up) or wierd things will happen.
;
; This routine uses timer5 to time the interval between each palette change.
; Make sure you aren't using timer5 for some other purpose when you call
; this function.  We don't retain use of timer5 after exit.
;
; Nop90 note: changed from original TIMER7 to TIMER5 to avoid conflicts with Chipper

		.include    "lynx.inc" 
		.export     _fade_in
		.import     popax
		.importzp   ptr1, tmp1

; ptr1 = passed in palette address

INTMULT =   5                       ; interval multiplier

		.code

_fade_in:       sta TIMER5           ; timer backup value = interval
		sta TIMER5+2         ; count = interval
		lda #$1E            ; reload, count, 64us
		sta TIMER5+1         ; timer control value
		stz TIMER5+3         ; dynamic control = 0

		jsr popax           ; get pal address
		sta ptr1 
		stx ptr1+1 

again:          ldy #15             ; 16 colors in palette
loop:           lda PALETTE,y
		cmp (ptr1),y        ; compare palettes
		beq redblue
		ina                 ; increment rgb value
		sta PALETTE,y 
redblue:        tya
		ora #16             ; index into redblue values
		tay
		lda PALETTE,y
		and #$F0            ; compare red
		sta tmp1 
		lda (ptr1),y
		and #$F0
		cmp tmp1
		beq chkblue
		lda PALETTE,y
		clc
		adc #$10            ; increment rgb value
		sta PALETTE,y
chkblue:        lda PALETTE,y
		and #$0F            ; compare blue
		sta tmp1 
		lda (ptr1),y
		and #$0F
		cmp tmp1
		beq cont
		lda PALETTE,y
		ina                 ; increment rgb value
		sta PALETTE,y

cont:           tya                 ; next palette index
		and #15             ; back to green index
		tay
		dey 
		bpl loop

		ldy #31             ; check palettes same?
checkloop:      lda PALETTE,y
		cmp (ptr1),y
		bne wait            ; run through palette again 
		dey
		bpl checkloop
		bra done

wait:           ldy #INTMULT        ; (64us * interval) * INTMULT
waitagain:      lda TIMER5           ; load the backup value
		sta TIMER5+2         ; reset count with backup value
interval:       lda TIMER5+2         ; wait the interval
		bne interval
		dey 
		bne waitagain
		bra again           ; run through palette again

done:           lda #$00            ; timer off
		sta TIMER5+1
		rts
