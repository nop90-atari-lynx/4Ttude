; ***
; CC65 Lynx Library
;
; Shawn Jefferson, June 2004
; 
; ***
;
; void __fastcall__ fade_out(unsigned char interval)
;
; Fade the palette out from the current palette values in hardware
; to an all black palette, waiting (interval * 64us)*2 between palette
; changes.
;
; This routine uses timer5 to time the interval between each palette change.
; Make sure you aren't using timer5 for some other purpose when you call
; this function.  We don't retain use of timer5 after exit.
;
; Nop90 note: changed from original TIMER7 to TIMER5 to avoid conflicts with Chipper


		.include    "lynx.inc"
		.export     _fade_out
		.importzp   tmp1

INTMULT =   5                       ; interval multiplier

		.code

_fade_out:      sta TIMER5           ; timer backup value = interval
		sta TIMER5+2         ; count = interval
		lda #$1E            ; reload, count, 64us
		sta TIMER5+1         ; timer control value
		stz TIMER5+3         ; dynamic control = 0

again:          ldy #15             ; 16 colors in pallette
loop:           lda PALETTE,y
		beq redblue
		dea                 ; decrement rgb value
		sta PALETTE,y 
redblue:        tya
		ora #16             ; index into redblue values
		tay
		lda PALETTE,y
		and #$F0            ; compare red
		beq chkblue
		lda PALETTE,y
		sec
		sbc #$10            ; decrement rgb value
		sta PALETTE,y
chkblue:        lda PALETTE,y
		and #$0F            ; compare blue
		beq cont
		lda PALETTE,y
		dea                 ; decrement rgb value
		sta PALETTE,y

cont:           tya                 ; next palette index
		and #15             ; back to green index
		tay
		dey 
		bpl loop

		ldy #31             ; check palettes same?
checkloop:      lda PALETTE,y
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
