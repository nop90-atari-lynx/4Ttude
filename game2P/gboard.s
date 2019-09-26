;
; File generated by cc65 v 2.13.9
;
	.fopt		compiler,"cc65 v 2.13.9"
	.setcpu		"65C02"
	.smart		on
	.autoimport	on
	.case		on
	.debuginfo	off
	.importzp	sp, sreg, regsave, regbank
	.importzp	tmp1, tmp2, tmp3, tmp4, ptr1, ptr2, ptr3, ptr4
	.macpack	longbranch
	.import		_malloc
	.import		_clock
	.export		_gb2_new
	.export		_gb2_reset
	.export		_coordtoint2
	.export		_opponent2
	.export		_xcoord2
	.export		_ycoord2
	.export		_zcoord2
	.export		_legal2
	.export		_gb2_place
	.export		_inuse2
	.export		_whoseturn2
	.export		_gb2_gameover
	.export		_gb2_winner
	.export		_pieceat2

; ---------------------------------------------------------------
; __near__ struct GBOARD_S* __near__ gb2_new (void)
; ---------------------------------------------------------------

.segment	"GAME2P_CODE"

.proc	_gb2_new: near

.segment	"GAME2P_CODE"

	jsr     decsp2
	ldx     #$00
	lda     #$4B
	jsr     _malloc
	jsr     stax0sp
	jsr     pushax
	jsr     _gb2_reset
	jsr     ldax0sp
	jmp     incsp2

.endproc

; ---------------------------------------------------------------
; void __near__ gb2_reset (__near__ struct GBOARD_S*)
; ---------------------------------------------------------------

.segment	"GAME2P_CODE"

.proc	_gb2_reset: near

.segment	"GAME2P_CODE"

	jsr     decsp1
	ldy     #$04
	jsr     pushwysp
	jsr     _clock
	ldx     #$00
	stz     sreg+1
	stz     sreg
	and     #$01
	jsr     utsteax
	beq     L00ED
	lda     #$01
	bra     L0014
L00ED:	lda     #$02
L0014:	ldy     #$00
	jsr     staspidx
	ldy     #$02
	jsr     ldaxysp
	sta     ptr1
	stx     ptr1+1
	lda     #$00
	ldy     #$01
	sta     (ptr1),y
	iny
	jsr     ldaxysp
	sta     ptr1
	stx     ptr1+1
	lda     #$00
	ldy     #$02
	sta     (ptr1),y
L00F0:	sta     (sp)
	cmp     #$40
	bcs     L001B
	ldy     #$02
	jsr     ldaxysp
	jsr     incax3
	sta     ptr1
	stx     ptr1+1
	lda     (sp)
	clc
	adc     ptr1
	ldx     ptr1+1
	bcc     L00EC
	inx
L00EC:	sta     ptr1
	stx     ptr1+1
	lda     #$00
	sta     (ptr1)
	lda     (sp)
	ina
	bra     L00F0
L001B:	ldy     #$02
	jsr     ldaxysp
	sta     ptr1
	stx     ptr1+1
	lda     #$00
	ldy     #$02
	sta     (ptr1),y
	jmp     incsp3

.endproc

; ---------------------------------------------------------------
; signed char __near__ coordtoint2 (signed char, signed char, signed char)
; ---------------------------------------------------------------

.segment	"GAME2P_CODE"

.proc	_coordtoint2: near

.segment	"GAME2P_CODE"

	ldy     #$02
	lda     (sp),y
	sec
	sbc     #$04
	bvs     L002D
	eor     #$80
L002D:	bmi     L00F1
	lda     (sp),y
	asl     a
	bcc     L0029
L00F1:	ldx     #$FF
	txa
	jmp     incsp3
L0029:	dey
	lda     (sp),y
	sec
	sbc     #$04
	bvs     L0036
	eor     #$80
L0036:	bmi     L00F2
	lda     (sp),y
	asl     a
	bcc     L0032
L00F2:	ldx     #$FF
	txa
	jmp     incsp3
L0032:	lda     (sp)
	sec
	sbc     #$04
	bvs     L003F
	eor     #$80
L003F:	bmi     L00F3
	lda     (sp)
	asl     a
	bcs     L00F3
	ldx     #$00
	bra     L00F5
L00F3:	ldx     #$FF
	txa
	jmp     incsp3
L00F5:	lda     (sp)
	bpl     L0046
	dex
L0046:	jsr     aslax2
	sta     ptr1
	stx     ptr1+1
	ldx     #$00
	ldy     #$01
	lda     (sp),y
	bpl     L0047
	dex
L0047:	clc
	adc     ptr1
	pha
	txa
	adc     ptr1+1
	tax
	pla
	jsr     aslax2
	sta     ptr1
	stx     ptr1+1
	ldx     #$00
	iny
	lda     (sp),y
	bpl     L0048
	dex
L0048:	clc
	adc     ptr1
	pha
	txa
	adc     ptr1+1
	tax
	pla
	jmp     incsp3

.endproc

; ---------------------------------------------------------------
; unsigned char __near__ opponent2 (unsigned char)
; ---------------------------------------------------------------

.segment	"GAME2P_CODE"

.proc	_opponent2: near

.segment	"GAME2P_CODE"

	ldx     #$00
	lda     (sp)
	cmp     #$01
	bne     L00F7
	ina
	jmp     incsp1
L00F7:	lda     (sp)
	cmp     #$02
	bne     L00F8
	dea
	jmp     incsp1
L00F8:	txa
	jmp     incsp1

.endproc

; ---------------------------------------------------------------
; unsigned char __near__ xcoord2 (signed char)
; ---------------------------------------------------------------

.segment	"GAME2P_CODE"

.proc	_xcoord2: near

.segment	"GAME2P_CODE"

	lda     (sp)
	sec
	sbc     #$40
	bvs     L0059
	eor     #$80
L0059:	bmi     L00F9
	lda     (sp)
	asl     a
	bcs     L00F9
	ldx     #$00
	bra     L00FB
L00F9:	ldx     #$00
	lda     #$FF
	jmp     incsp1
L00FB:	lda     (sp)
	bpl     L005F
	dex
L005F:	jsr     pushax
	ldx     #$00
	lda     #$04
	jsr     tosmoda0
	jmp     incsp1

.endproc

; ---------------------------------------------------------------
; unsigned char __near__ ycoord2 (signed char)
; ---------------------------------------------------------------

.segment	"GAME2P_CODE"

.proc	_ycoord2: near

.segment	"GAME2P_CODE"

	lda     (sp)
	sec
	sbc     #$40
	bvs     L0066
	eor     #$80
L0066:	bmi     L00FC
	lda     (sp)
	asl     a
	bcs     L00FC
	ldx     #$00
	bra     L00FE
L00FC:	ldx     #$00
	lda     #$FF
	jmp     incsp1
L00FE:	lda     (sp)
	bpl     L006D
	dex
L006D:	jsr     asrax2
	jsr     pushax
	ldx     #$00
	lda     #$04
	jsr     tosmoda0
	jmp     incsp1

.endproc

; ---------------------------------------------------------------
; unsigned char __near__ zcoord2 (signed char)
; ---------------------------------------------------------------

.segment	"GAME2P_CODE"

.proc	_zcoord2: near

.segment	"GAME2P_CODE"

	lda     (sp)
	sec
	sbc     #$40
	bvs     L0074
	eor     #$80
L0074:	bmi     L00FF
	lda     (sp)
	asl     a
	bcs     L00FF
	ldx     #$00
	bra     L0101
L00FF:	ldx     #$00
	lda     #$FF
	jmp     incsp1
L0101:	lda     (sp)
	bpl     L007B
	dex
L007B:	jsr     asrax4
	jmp     incsp1

.endproc

; ---------------------------------------------------------------
; int __near__ legal2 (__near__ struct GBOARD_S*, int, signed char)
; ---------------------------------------------------------------

.segment	"GAME2P_CODE"

.proc	_legal2: near

.segment	"GAME2P_CODE"

	ldy     #$04
	jsr     ldaxysp
	sta     ptr1
	stx     ptr1+1
	ldy     #$01
	lda     (ptr1),y
	beq     L007E
	ldx     #$00
	txa
	jmp     incsp5
L007E:	iny
	lda     (sp),y
	bne     L010B
	dey
	lda     (sp),y
	cmp     #$02
	beq     L0081
	iny
L010B:	lda     (sp),y
	bne     L0103
	dey
	lda     (sp),y
	cmp     #$01
	beq     L0081
L0103:	ldx     #$00
	txa
	jmp     incsp5
L0081:	iny
	lda     (sp),y
	bne     L010C
	dey
	lda     (sp),y
	cmp     #$01
	bne     L008A
	ldy     #$04
	jsr     ldaxysp
	sta     ptr1
	stx     ptr1+1
	lda     (ptr1)
	cmp     #$02
	beq     L008A
	ldx     #$00
	txa
	jmp     incsp5
L008A:	ldy     #$02
L010C:	lda     (sp),y
	bne     L010D
	dey
	lda     (sp),y
	cmp     #$02
	bne     L010D
	ldy     #$04
	jsr     ldaxysp
	sta     ptr1
	stx     ptr1+1
	lda     (ptr1)
	cmp     #$01
	beq     L010D
	ldx     #$00
	txa
	jmp     incsp5
L010D:	lda     (sp)
	asl     a
	bcs     L0108
	lda     (sp)
	sec
	sbc     #$40
	bvs     L00A1
	eor     #$80
L00A1:	bpl     L009A
L0108:	ldx     #$00
	txa
	jmp     incsp5
L009A:	ldy     #$04
	jsr     ldaxysp
	jsr     incax3
	sta     ptr1
	stx     ptr1+1
	ldx     #$00
	lda     (sp)
	bpl     L00A7
	dex
L00A7:	clc
	adc     ptr1
	sta     ptr1
	txa
	adc     ptr1+1
	sta     ptr1+1
	ldx     #$00
	lda     (ptr1)
	beq     L0109
	txa
	jmp     incsp5
L0109:	ina
	jmp     incsp5

.endproc

; ---------------------------------------------------------------
; void __near__ gb2_place (__near__ struct GBOARD_S*, int, signed char)
; ---------------------------------------------------------------

.segment	"GAME2P_CODE"

.proc	_gb2_place: near

.segment	"GAME2P_CODE"

	ldy     #$04
	jsr     ldaxysp
	jsr     incax3
	sta     ptr1
	stx     ptr1+1
	ldx     #$00
	lda     (sp)
	bpl     L00AD
	dex
L00AD:	clc
	adc     ptr1
	sta     ptr1
	txa
	adc     ptr1+1
	sta     ptr1+1
	ldy     #$01
	lda     (sp),y
	sta     (ptr1)
	ldy     #$04
	jsr     ldaxysp
	sta     ptr1
	stx     ptr1+1
	ldy     #$01
	lda     (sp),y
	sta     (ptr1)
	ldy     #$04
	jsr     ldaxysp
	jsr     pushax
	sta     ptr1
	stx     ptr1+1
	ldy     #$02
	lda     (ptr1),y
	ina
	jsr     staspidx
	jmp     incsp5

.endproc

; ---------------------------------------------------------------
; int __near__ inuse2 (__near__ struct GBOARD_S*, signed char)
; ---------------------------------------------------------------

.segment	"GAME2P_CODE"

.proc	_inuse2: near

.segment	"GAME2P_CODE"

	lda     (sp)
	asl     a
	bcs     L010E
	lda     (sp)
	sec
	sbc     #$40
	bvs     L00BA
	eor     #$80
L00BA:	bpl     L00B3
L010E:	ldx     #$00
	lda     #$01
	jmp     incsp3
L00B3:	ldy     #$02
	jsr     ldaxysp
	jsr     incax3
	sta     ptr1
	stx     ptr1+1
	ldx     #$00
	lda     (sp)
	bpl     L00C0
	dex
L00C0:	clc
	adc     ptr1
	sta     ptr1
	txa
	adc     ptr1+1
	sta     ptr1+1
	ldx     #$00
	lda     (ptr1)
	beq     L00B2
	lda     #$01
	jmp     incsp3
L00B2:	jmp     incsp3

.endproc

; ---------------------------------------------------------------
; int __near__ whoseturn2 (__near__ struct GBOARD_S*)
; ---------------------------------------------------------------

.segment	"GAME2P_CODE"

.proc	_whoseturn2: near

.segment	"GAME2P_CODE"

	jsr     ldax0sp
	sta     ptr1
	stx     ptr1+1
	ldy     #$01
	lda     (ptr1),y
	beq     L0111
	ldx     #$00
	bra     L0110
L0111:	jsr     ldax0sp
	sta     ptr1
	stx     ptr1+1
	lda     (ptr1)
	cmp     #$01
	bne     L00CA
	ldx     #$00
	ina
	jmp     incsp2
L00CA:	jsr     ldax0sp
	sta     ptr1
	stx     ptr1+1
	ldx     #$00
	lda     (ptr1)
	cmp     #$02
	bne     L0110
	dea
	jmp     incsp2
L0110:	txa
	jmp     incsp2

.endproc

; ---------------------------------------------------------------
; int __near__ gb2_gameover (__near__ struct GBOARD_S*)
; ---------------------------------------------------------------

.segment	"GAME2P_CODE"

.proc	_gb2_gameover: near

.segment	"GAME2P_CODE"

	jsr     pushw0sp
	jsr     _whoseturn2
	cpx     #$00
	bne     L00D8
	cmp     #$00
	bne     L0112
	ina
	jmp     incsp2
L00D8:	ldx     #$00
L0112:	txa
	jmp     incsp2

.endproc

; ---------------------------------------------------------------
; int __near__ gb2_winner (__near__ struct GBOARD_S*)
; ---------------------------------------------------------------

.segment	"GAME2P_CODE"

.proc	_gb2_winner: near

.segment	"GAME2P_CODE"

	jsr     ldax0sp
	sta     ptr1
	stx     ptr1+1
	ldy     #$01
	lda     (ptr1),y
	ldx     #$00
	jmp     incsp2

.endproc

; ---------------------------------------------------------------
; int __near__ pieceat2 (__near__ struct GBOARD_S*, signed char)
; ---------------------------------------------------------------

.segment	"GAME2P_CODE"

.proc	_pieceat2: near

.segment	"GAME2P_CODE"

	lda     (sp)
	asl     a
	bcs     L0113
	lda     (sp)
	sec
	sbc     #$40
	bvs     L00E6
	eor     #$80
L00E6:	bpl     L00DF
L0113:	ldx     #$00
	txa
	jmp     incsp3
L00DF:	ldy     #$02
	jsr     ldaxysp
	jsr     incax3
	sta     ptr1
	stx     ptr1+1
	ldx     #$00
	lda     (sp)
	bpl     L00EB
	dex
L00EB:	clc
	adc     ptr1
	sta     ptr1
	txa
	adc     ptr1+1
	sta     ptr1+1
	lda     (ptr1)
	ldx     #$00
	jmp     incsp3

.endproc
