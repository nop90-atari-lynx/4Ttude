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
	.export		_cr2_init
	.export		_cr2_refresh
	.export		_cr2_register
	.export		_cr2_isable
	.export		_cr2_isects
	.export		_cr2_isownedby

; ---------------------------------------------------------------
; void __near__ cr2_init (__near__ struct COMBOROW_S*, signed char, signed char, signed char, signed char)
; ---------------------------------------------------------------

.segment	"GAME2P_CODE"

.proc	_cr2_init: near

.segment	"GAME2P_CODE"

	ldy     #$05
	jsr     ldaxysp
	sta     ptr1
	stx     ptr1+1
	ldy     #$03
	lda     (sp),y
	ldy     #$05
	sta     (ptr1),y
	jsr     ldaxysp
	sta     ptr1
	stx     ptr1+1
	ldy     #$02
	lda     (sp),y
	ldy     #$06
	sta     (ptr1),y
	dey
	jsr     ldaxysp
	sta     ptr1
	stx     ptr1+1
	ldy     #$01
	lda     (sp),y
	ldy     #$07
	sta     (ptr1),y
	ldy     #$05
	jsr     ldaxysp
	sta     ptr1
	stx     ptr1+1
	lda     (sp)
	ldy     #$08
	sta     (ptr1),y
	dey
	jsr     pushwysp
	jsr     _cr2_refresh
	jmp     incsp6

.endproc

; ---------------------------------------------------------------
; void __near__ cr2_refresh (__near__ struct COMBOROW_S*)
; ---------------------------------------------------------------

.segment	"GAME2P_CODE"

.proc	_cr2_refresh: near

.segment	"GAME2P_CODE"

	jsr     decsp2
	ldy     #$03
	jsr     ldaxysp
	sta     ptr1
	stx     ptr1+1
	lda     #$00
	sta     (ptr1)
	ldy     #$01
	sta     (ptr1),y
	ldy     #$03
	jsr     ldaxysp
	sta     ptr1
	stx     ptr1+1
	lda     #$00
	ldy     #$02
	sta     (ptr1),y
	iny
	jsr     ldaxysp
	sta     ptr1
	stx     ptr1+1
	lda     #$01
	ldy     #$03
	sta     (ptr1),y
	iny
	dea
	sta     (ptr1),y
	ldy     #$01
L00A4:	sta     (sp),y
	cmp     #$03
	bcc     L00A6
	jmp     incsp4
L00A6:	lda     (sp),y
L00A5:	ina
	sta     (sp)
	cmp     #$04
	jcs     L000F
	ldy     #$03
	jsr     ldaxysp
	jsr     incax5
	sta     ptr1
	stx     ptr1+1
	ldy     #$01
	lda     (sp),y
	tay
	lda     (ptr1),y
	jsr     pusha0
	ldy     #$05
	jsr     ldaxysp
	jsr     incax5
	sta     ptr1
	stx     ptr1+1
	ldy     #$02
	lda     (sp),y
	tay
	lda     (ptr1),y
	jsr     tosicmp0
	bcc     L0017
	beq     L0017
	ldy     #$03
	jsr     ldaxysp
	jsr     incax5
	sta     ptr1
	stx     ptr1+1
	lda     (sp)
	tay
	lda     (ptr1),y
	jsr     pusha0
	ldy     #$05
	jsr     ldaxysp
	jsr     incax5
	sta     ptr1
	stx     ptr1+1
	ldy     #$02
	lda     (sp),y
	clc
	adc     ptr1
	ldx     ptr1+1
	bcc     L009D
	inx
L009D:	jsr     pushax
	ldy     #$07
	jsr     ldaxysp
	jsr     incax5
	sta     ptr1
	stx     ptr1+1
	ldy     #$05
	lda     (sp),y
	tay
	lda     (ptr1),y
	ldy     #$00
	jsr     staspidx
	ldy     #$05
	jsr     ldaxysp
	jsr     incax5
	sta     ptr1
	stx     ptr1+1
	ldy     #$03
	lda     (sp),y
	clc
	adc     ptr1
	ldx     ptr1+1
	bcc     L009E
	inx
L009E:	sta     ptr1
	stx     ptr1+1
	lda     (sp)
	sta     (ptr1)
	jsr     incsp2
L0017:	lda     (sp)
	jmp     L00A5
L000F:	ldy     #$01
	lda     (sp),y
	ina
	jmp     L00A4

.endproc

; ---------------------------------------------------------------
; int __near__ cr2_register (__near__ struct COMBOROW_S*, int, signed char)
; ---------------------------------------------------------------

.segment	"GAME2P_CODE"

.proc	_cr2_register: near

.segment	"GAME2P_CODE"

	lda     #$04
	jsr     pusha0
	ldy     #$06
	jsr     ldaxysp
	ldy     #$02
	jsr     ldaidx
	jsr     tossubax
	jsr     pusha
	jsr     decsp1
	ldy     #$06
	jsr     ldaxysp
	ldy     #$04
	jsr     ldaxidx
	stx     tmp1
	ora     tmp1
	bne     L003C
	tax
	jmp     incsp7
L003C:	lda     #$00
	sta     (sp)
	tax
L00AC:	lda     (sp)
	ldy     #$01
	cmp     (sp),y
	txa
	bcc     L00AF
	jmp     incsp7
L00AF:	ldy     #$06
	jsr     ldaxysp
	jsr     incax5
	sta     ptr1
	stx     ptr1+1
	lda     (sp)
	tay
	ldx     #$00
	lda     (ptr1),y
	sta     ptr1
	stz     ptr1+1
	ldy     #$02
	lda     (sp),y
	bpl     L004A
	dex
L004A:	cpx     ptr1+1
	jne     L0041
	cmp     ptr1
	jne     L0041
	ldy     #$06
	jsr     ldaxysp
	jsr     pushax
	ldy     #$02
	jsr     ldaidx
	ina
	jsr     staspidx
	lda     (sp)
	jsr     pusha0
	lda     #$04
	jsr     pusha0
	ldy     #$0A
	jsr     ldaxysp
	ldy     #$02
	jsr     ldaidx
	jsr     tossubax
	jsr     tosicmp
	beq     L004C
	ldy     #$06
	jsr     ldaxysp
	jsr     incax5
	sta     ptr1
	stx     ptr1+1
	lda     (sp)
	clc
	adc     ptr1
	ldx     ptr1+1
	bcc     L00A8
	inx
L00A8:	jsr     pushax
	ldy     #$08
	jsr     ldaxysp
	jsr     incax5
	jsr     pushax
	lda     #$04
	jsr     pusha0
	ldy     #$0C
	jsr     ldaxysp
	ldy     #$02
	jsr     ldaidx
	jsr     tossubax
	jsr     tosaddax
	sta     ptr1
	stx     ptr1+1
	ldy     #$00
	lda     (ptr1)
	jsr     staspidx
	ldy     #$06
	jsr     ldaxysp
	jsr     incax5
	jsr     pushax
	lda     #$04
	jsr     pusha0
	ldy     #$0A
	jsr     ldaxysp
	ldy     #$02
	jsr     ldaidx
	jsr     tossubax
	jsr     tosaddax
	sta     ptr1
	stx     ptr1+1
	ldy     #$02
	lda     (sp),y
	sta     (ptr1)
L004C:	ldy     #$06
	jsr     ldaxysp
	jsr     ldaxi
	ldy     #$03
	cmp     (sp),y
	bne     L0055
	txa
	iny
	cmp     (sp),y
	bne     L0055
	ldy     #$06
	jsr     ldaxysp
	ldy     #$02
	jsr     ldaidx
	cmp     #$04
	bne     L0057
	ldx     #$00
	lda     #$01
	jmp     incsp7
L0057:	ldx     #$00
	bra     L00AA
L0055:	ldy     #$06
	jsr     ldaxysp
	jsr     ldaxi
	cpx     #$00
	bne     L00AD
	cmp     #$00
	beq     L005B
L00AD:	ldy     #$06
	jsr     ldaxysp
	sta     ptr1
	stx     ptr1+1
	lda     #$00
	ldy     #$03
	sta     (ptr1),y
	iny
	sta     (ptr1),y
	ldy     #$06
	jsr     ldaxysp
	sta     ptr1
	stx     ptr1+1
	lda     #$00
	sta     (ptr1)
	ldy     #$01
	sta     (ptr1),y
	tax
	tya
	jmp     incsp7
L005B:	ldy     #$06
	jsr     ldaxysp
	sta     ptr1
	stx     ptr1+1
	ldy     #$04
	jsr     ldaxysp
	sta     (ptr1)
	ldy     #$01
	txa
	sta     (ptr1),y
	ldx     #$00
	bra     L00AA
L0041:	ldx     #$00
	lda     (sp)
	ina
	sta     (sp)
	jmp     L00AC
L00AA:	txa
	jmp     incsp7

.endproc

; ---------------------------------------------------------------
; int __near__ cr2_isable (__near__ struct COMBOROW_S*, signed char)
; ---------------------------------------------------------------

.segment	"GAME2P_CODE"

.proc	_cr2_isable: near

.segment	"GAME2P_CODE"

	jsr     decsp1
	lda     #$00
L00B3:	sta     (sp)
	lda     (sp)
	jsr     pusha0
	ldy     #$05
	jsr     ldaxysp
	ldy     #$02
	jsr     ldaidx
	jsr     tosicmp
	bcs     L006A
	ldy     #$03
	jsr     ldaxysp
	jsr     incax5
	sta     ptr1
	stx     ptr1+1
	lda     (sp)
	tay
	ldx     #$00
	lda     (ptr1),y
	sta     ptr1
	stz     ptr1+1
	ldy     #$01
	lda     (sp),y
	bpl     L0074
	dex
L0074:	cpx     ptr1+1
	bne     L006B
	cmp     ptr1
	bne     L006B
	ldx     #$00
	tya
	jmp     incsp4
L006B:	lda     (sp)
	ina
	bra     L00B3
L006A:	ldx     #$00
	txa
	jmp     incsp4

.endproc

; ---------------------------------------------------------------
; int __near__ cr2_isects (__near__ struct COMBOROW_S*, __near__ struct COMBOROW_S*)
; ---------------------------------------------------------------

.segment	"GAME2P_CODE"

.proc	_cr2_isects: near

.segment	"GAME2P_CODE"

	jsr     decsp2
	ldy     #$05
	jsr     ldaxysp
	ldy     #$04
	jsr     ldaxidx
	stx     tmp1
	ora     tmp1
	jeq     L007F
	ldy     #$03
	jsr     ldaxysp
	ldy     #$04
	jsr     ldaxidx
	stx     tmp1
	ora     tmp1
	jeq     L007F
	lda     #$00
	ldy     #$01
L00BC:	sta     (sp),y
	lda     (sp),y
	jsr     pusha0
	lda     #$04
	jsr     pusha0
	ldy     #$09
	jsr     ldaxysp
	ldy     #$02
	jsr     ldaidx
	jsr     tossubax
	jsr     tosicmp
	bcs     L007F
	lda     #$00
L00BB:	sta     (sp)
	lda     (sp)
	jsr     pusha0
	lda     #$04
	jsr     pusha0
	ldy     #$07
	jsr     ldaxysp
	ldy     #$02
	jsr     ldaidx
	jsr     tossubax
	jsr     tosicmp
	bcs     L0080
	ldy     #$05
	jsr     ldaxysp
	jsr     incax5
	sta     ptr1
	stx     ptr1+1
	ldy     #$01
	lda     (sp),y
	tay
	lda     (ptr1),y
	jsr     pusha0
	ldy     #$05
	jsr     ldaxysp
	jsr     incax5
	sta     ptr1
	stx     ptr1+1
	ldy     #$02
	lda     (sp),y
	tay
	lda     (ptr1),y
	jsr     tosicmp0
	bne     L0088
	ldx     #$00
	lda     #$01
	jmp     incsp6
L0088:	lda     (sp)
	ina
	bra     L00BB
L0080:	ldy     #$01
	lda     (sp),y
	ina
	bra     L00BC
L007F:	ldx     #$00
	txa
	jmp     incsp6

.endproc

; ---------------------------------------------------------------
; int __near__ cr2_isownedby (__near__ struct COMBOROW_S*, int)
; ---------------------------------------------------------------

.segment	"GAME2P_CODE"

.proc	_cr2_isownedby: near

.segment	"GAME2P_CODE"

	ldy     #$03
	jsr     ldaxysp
	ldy     #$03
	sta     ptr1
	stx     ptr1+1
	lda     (ptr1),y
	iny
	ora     (ptr1),y
	beq     L0098
	jsr     ldax0sp
	sta     sreg
	stx     sreg+1
	ldy     #$03
	jsr     ldaxysp
	jsr     ldaxi
	cpx     sreg+1
	bne     L0098
	cmp     sreg
	beq     L0096
L0098:	ldx     #$00
	txa
	jmp     incsp4
L0096:	ldx     #$00
	lda     #$01
	jmp     incsp4

.endproc

