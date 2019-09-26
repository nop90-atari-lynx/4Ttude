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
	.export		_LynxSD_Init
	.export		_LynxSD_LowPowerMode
	.export		_LynxSD_OpenDir
	.export		_LynxSD_ReadDir
	.export		_LynxSD_OpenFile
	.export		_LynxSD_ReadFile
	.export		_LynxSD_WriteFile
	.export		_LynxSD_CloseFile
	.export		_LynxSD_SeekFile
	.export		_LynxSD_GetFileSize
	.export		_LynxSD_ProgramROMFromFile
	.export		_LynxSD_ClearROMBlocks
	.export		_LynxSD_OpenFileTimeout
	.export		_AUXMASK

.segment	"RODATA"

_AUXMASK:
	.byte	$10

; ---------------------------------------------------------------
; void __near__ LynxSD_Init (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_LynxSD_Init: near

.segment	"CODE"

	stz     $FD8A
	lda     #$AA
	sta     $FCB3
	rts

.endproc

; ---------------------------------------------------------------
; void __near__ LynxSD_LowPowerMode (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_LynxSD_LowPowerMode: near

.segment	"CODE"

	lda     #$0A
	jmp     _WriteByte

.endproc

; ---------------------------------------------------------------
; int __near__ __fastcall__ LynxSD_OpenDir (__near__ const unsigned char*)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_LynxSD_OpenDir: near

.segment	"CODE"

	jsr     pushax
	lda     #$00
	jsr     _WriteByte
	jsr     ldax0sp
	jsr     _WriteString
	jsr     _ReadByte
	ldx     #$00
	jmp     incsp2

.endproc

; ---------------------------------------------------------------
; int __near__ __fastcall__ LynxSD_ReadDir (__near__ struct $anon-struct-0001*)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_LynxSD_ReadDir: near

.segment	"CODE"

	jsr     pushax
	jsr     decsp2
	lda     #$01
	jsr     _WriteByte
	jsr     _ReadByte
	ldx     #$00
	jsr     stax0sp
	cmp     #$00
	bne     L0053
	ldy     #$05
	jsr     pushwysp
	ldx     #$00
	lda     #$16
	jsr     _ReadBytes
L0053:	jsr     ldax0sp
	jmp     incsp4

.endproc

; ---------------------------------------------------------------
; int __near__ __fastcall__ LynxSD_OpenFile (__near__ const unsigned char*)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_LynxSD_OpenFile: near

.segment	"CODE"

	jsr     pushax
	lda     #$02
	jsr     _WriteByte
	jsr     ldax0sp
	jsr     _WriteString
	jsr     _ReadByte
	ldx     #$00
	jmp     incsp2

.endproc

; ---------------------------------------------------------------
; int __near__ __fastcall__ LynxSD_ReadFile (__near__ void*, unsigned int)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_LynxSD_ReadFile: near

.segment	"CODE"

	jsr     pushax
	lda     #$05
	jsr     _WriteByte
	jsr     ldax0sp
	jsr     _WriteWord
	ldy     #$05
	jsr     pushwysp
	ldy     #$03
	jsr     ldaxysp
	jsr     _ReadBytes
	jsr     _ReadByte
	ldx     #$00
	jmp     incsp4

.endproc

; ---------------------------------------------------------------
; int __near__ __fastcall__ LynxSD_WriteFile (__near__ void*, unsigned int)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_LynxSD_WriteFile: near

.segment	"CODE"

	jsr     pushax
	lda     #$06
	jsr     _WriteByte
	jsr     ldax0sp
	jsr     _WriteWord
	ldy     #$05
	jsr     pushwysp
	ldy     #$03
	jsr     ldaxysp
	jsr     _WriteBytes
	jsr     _ReadByte
	ldx     #$00
	jmp     incsp4

.endproc

; ---------------------------------------------------------------
; int __near__ LynxSD_CloseFile (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_LynxSD_CloseFile: near

.segment	"CODE"

	lda     #$07
	jsr     _WriteByte
	jsr     _ReadByte
	ldx     #$00
	rts

.endproc

; ---------------------------------------------------------------
; int __near__ __fastcall__ LynxSD_SeekFile (unsigned long)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_LynxSD_SeekFile: near

.segment	"CODE"

	jsr     pusheax
	lda     #$04
	jsr     _WriteByte
	jsr     ldeax0sp
	jsr     _WriteDword
	jsr     _ReadByte
	ldx     #$00
	jmp     incsp4

.endproc

; ---------------------------------------------------------------
; unsigned long __near__ LynxSD_GetFileSize (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_LynxSD_GetFileSize: near

.segment	"CODE"

	lda     #$03
	jsr     _WriteByte
	jmp     _ReadDword

.endproc

; ---------------------------------------------------------------
; int __near__ __fastcall__ LynxSD_ProgramROMFromFile (unsigned int, unsigned char, unsigned int, unsigned char)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_LynxSD_ProgramROMFromFile: near

.segment	"CODE"

	jsr     pusha
	lda     (sp)
	beq     L0081
	ldy     #$03
	lda     (sp),y
	ora     #$10
	sta     (sp),y
L0081:	lda     #$08
	jsr     _WriteByte
	ldy     #$05
	jsr     ldaxysp
	jsr     _WriteWord
	ldy     #$03
	lda     (sp),y
	jsr     _WriteByte
	ldy     #$02
	jsr     ldaxysp
	jsr     _WriteWord
	jsr     _ReadByte
	ldx     #$00
	jmp     incsp6

.endproc

; ---------------------------------------------------------------
; int __near__ __fastcall__ LynxSD_ClearROMBlocks (unsigned int, unsigned int, unsigned char)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_LynxSD_ClearROMBlocks: near

.segment	"CODE"

	jsr     pusha
	lda     (sp)
	beq     L008F
	ldy     #$02
	jsr     ldaxysp
	pha
	txa
	ora     #$80
	tax
	pla
	ldy     #$01
	jsr     staxysp
L008F:	lda     #$09
	jsr     _WriteByte
	ldy     #$04
	jsr     ldaxysp
	jsr     _WriteWord
	ldy     #$02
	jsr     ldaxysp
	jsr     _WriteWord
	jsr     _ReadByte
	ldx     #$00
	jmp     incsp5

.endproc

; ---------------------------------------------------------------
; int __near__ __fastcall__ LynxSD_OpenFileTimeout (__near__ void*)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_LynxSD_OpenFileTimeout: near

.segment	"CODE"

	jsr     pushax
	jsr     push0
L00C6:	lda     _AUXMASK
	and     $FD8B
	pha
	pla
	beq     L00C3
	jsr     ldax0sp
	sta     regsave
	stx     regsave+1
	ina
	bne     L00A4
	inx
L00A4:	jsr     stax0sp
	lda     regsave+1
	cmp     #$75
	bne     L00A5
	lda     regsave
	cmp     #$30
L00A5:	bcc     L00C6
L00C3:	jsr     ldax0sp
	cmp     #$30
	txa
	sbc     #$75
	bcc     L00C9
	ldx     #$00
	bra     L00C5
L00C9:	lda     #$02
	sta     $FCB3
	ldy     #$03
	jsr     ldaxysp
	jsr     _WriteString
	ldx     #$00
	txa
	jsr     stax0sp
L00CA:	lda     _AUXMASK
	and     $FD8B
	tax
	bne     L00B7
	jsr     ldax0sp
	sta     regsave
	stx     regsave+1
	ina
	bne     L00B9
	inx
L00B9:	jsr     stax0sp
	lda     regsave+1
	cmp     #$75
	bne     L00BA
	lda     regsave
	cmp     #$30
L00BA:	bcc     L00CA
L00B7:	ldx     #$00
	ldy     #$01
	lda     (sp),y
	cmp     #$75
	bne     L00BE
	lda     (sp)
	cmp     #$30
L00BE:	bcs     L00C5
	lda     $FCB2
	jmp     incsp4
L00C5:	lda     #$01
	jmp     incsp4

.endproc

; ---------------------------------------------------------------
; void __near__ __fastcall__ WriteByte (unsigned char)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_WriteByte: near

.segment	"CODE"

	jsr     pusha
L00CB:	lda     _AUXMASK
	and     $FD8B
	pha
	pla
	bne     L00CB
	lda     (sp)
	sta     $FCB3
	jmp     incsp1

.endproc

; ---------------------------------------------------------------
; void __near__ __fastcall__ WriteBytes (__near__ unsigned char*, unsigned int)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_WriteBytes: near

.segment	"CODE"

	jsr     pushax
	bra     L0011
L000F:	ldy     #$03
	jsr     ldaxysp
	sta     regsave
	stx     regsave+1
	ina
	bne     L0015
	inx
L0015:	ldy     #$02
	jsr     staxysp
	lda     (regsave)
	jsr     _WriteByte
L0011:	jsr     ldax0sp
	sta     regsave
	stx     regsave+1
	jsr     decax1
	jsr     stax0sp
	lda     regsave
	ora     regsave+1
	bne     L000F
	jmp     incsp4

.endproc

; ---------------------------------------------------------------
; void __near__ __fastcall__ WriteWord (unsigned int)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_WriteWord: near

.segment	"CODE"

	jsr     pushax
	lda     sp
	ldx     sp+1
	jsr     pushax
	ldx     #$00
	lda     #$02
	jsr     _WriteBytes
	jmp     incsp2

.endproc

; ---------------------------------------------------------------
; void __near__ __fastcall__ WriteDword (unsigned long)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_WriteDword: near

.segment	"CODE"

	jsr     pusheax
	lda     sp
	ldx     sp+1
	jsr     pushax
	ldx     #$00
	lda     #$04
	jsr     _WriteBytes
	jmp     incsp4

.endproc

; ---------------------------------------------------------------
; unsigned char __near__ ReadByte (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_ReadByte: near

.segment	"CODE"

L00CC:	lda     _AUXMASK
	and     $FD8B
	tax
	beq     L00CC
	ldx     #$00
	lda     $FCB2
	rts

.endproc

; ---------------------------------------------------------------
; void __near__ __fastcall__ ReadBytes (__near__ unsigned char*, unsigned int)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_ReadBytes: near

.segment	"CODE"

	jsr     pushax
	bra     L002A
L0028:	ldy     #$03
	jsr     ldaxysp
	sta     regsave
	stx     regsave+1
	ina
	bne     L002D
	inx
L002D:	ldy     #$02
	jsr     staxysp
	lda     regsave
	ldx     regsave+1
	jsr     pushax
	jsr     _ReadByte
	ldy     #$00
	jsr     staspidx
L002A:	jsr     ldax0sp
	sta     regsave
	stx     regsave+1
	jsr     decax1
	jsr     stax0sp
	lda     regsave
	ora     regsave+1
	bne     L0028
	jmp     incsp4

.endproc

; ---------------------------------------------------------------
; unsigned long __near__ ReadDword (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_ReadDword: near

.segment	"CODE"

	jsr     decsp4
	lda     sp
	ldx     sp+1
	jsr     pushax
	ldx     #$00
	lda     #$04
	jsr     _ReadBytes
	jsr     ldeax0sp
	jmp     incsp4

.endproc

; ---------------------------------------------------------------
; void __near__ __fastcall__ WriteString (__near__ const unsigned char*)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_WriteString: near

.segment	"CODE"

	jsr     pushax
	jsr     decsp1
L0035:	ldy     #$02
	jsr     ldaxysp
	sta     regsave
	stx     regsave+1
	ina
	bne     L003A
	inx
L003A:	ldy     #$01
	jsr     staxysp
	lda     (regsave)
	sta     (sp)
	jsr     _WriteByte
	lda     (sp)
	bne     L0035
	jmp     incsp3

.endproc
