;****************************************************************
; - Orignal code in tailchao's HandyMusic			*
; - Handymusic port to CC65 by karry	                        *
; - playPCMSample standalone file by Nop90			*
;								*
; this version plays a PCM sample on channel 3 diretly from the *
; cart, and uses Counter5 to not conflict with counters used in	*
; Chipper. This needs to stop playing before accessing the cart.*
;								*
; The sample needs to be raw strean off 8kHz 8bit signed	*
;								*
;****************************************************************
; How to use it from C:						*
;								*
; void __near__ __fastcall__ openn (int);			*
; void playPCMSample(void);					*
; void stopPCMSample(void);					*
; ...								*
; stopPCMSample(); // use this before reading cart if playing   *
; openn((int)&SAMPLE0_FILENR);					*
; playPCMSample();						*
;								*
;****************************************************************

	.include	"lynx.inc"
	.include	"zeropage.inc"
	.include	"extzp.inc"
        .import		lynxskip0
        .import		lynxblock
        .interruptor	_PCMMain,1
	.export		_playPCMSample
	.export		_stopPCMSample

;****************************************************************
; stopPCMSample:						*
;	Stops playing a PCM Sample if any                       *
;	                                 	                *
;****************************************************************
_stopPCMSample:
;	sei					; Kill IRQs just for a bit to...
	STZ $FD3D
	STZ $fD15				; Disable IRQ3 in case sample is already playing
;	cli
	rts


;****************************************************************
; playPCMSample:						*
;	Starts playing a PCM Sample using channel and starting  *
;	the read stream using timer 5.  	                *
;****************************************************************
_playPCMSample:
;	sei					; Kill IRQs just for a bit to...
	STZ $FD3D
	STZ $fD15				; Disable IRQ5 in case sample is already playing
;	cli
	LDA #$FF
	STA $FD43				;ATTENREG3
;***********************
; Parse File Directory *
;***********************
	lda _FileStartBlock
	sta _FileCurrBlock                   ; startblock
	jsr lynxblock
	lda _FileBlockOffset
	eor #$FF
	tax
	lda _FileBlockOffset+1
	eor #$FF
	tay
	jsr lynxskip0
;********************
; Setup Timer 5 IRQ *
;********************
	LDA#125
	STA $fd14; T5 Backup (125)
	STA $fd16; T5 Current
	LDA#$D9 ; #$D8 for 8K -> 1ms source period, #SD9 for 4K -> 2ms source period
	STA $fd15; T5 Mode (~4000Hz Reload)
	rts

;****************************************************************
; PCMSample_IRQ:						*
;	Streams a single sample from the cartridge, playing	*
;	it through the direct volume register of channel 0.	*
;	Automatically disabled when playback is finished.	*
;****************************************************************
PCMSample_IRQ:
;echo "HandyMusic PCM IRQ Address: %HPCMSample_IRQ"
;***************************
;* Read one byte from Cart *
;***************************
	DEC _FileFileLen
	bne KeepReading
	DEC _FileFileLen+1
	beq PlayBackDone
KeepReading:
	jsr ReadByte	; Read byte
	sta $fd3a	; Store to Direct Volume reg
	bra ExitIRQ
PlayBackDone:
	STZ $fd15 ; Kill IRQ, Sample is finished.
ExitIRQ:
	rts
;**********************************************************
;* Fetch one byte from cart                               *
;**********************************************************
ReadByte:
	lda $fcb2
IncCartByte:
	inc _FileBlockByte
	bne BailOut
	inc _FileBlockByte+1
	bne BailOut
	jmp lynxblock
BailOut:
	rts


;****************************************************************
; PCMMain:						        *
;	The main entry point.			                *
;****************************************************************
_PCMMain:
	PHA
	lda	INTSET
	and	#TIMER5_INTERRUPT
	beq	@L0
;	sei
	jsr	PCMSample_IRQ
	PLA
	sec
;	cli
	rts
@L0:
	PLA	
	clc
	rts


