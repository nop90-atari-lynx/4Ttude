
;;; source file for CC65 "remake" compiler
	.include "soundbs.mac"
	.global _musicptr
	.segment "TUNE1_RODATA"
_musicptr:
	.word CHANNEL_0, CHANNEL_1, CHANNEL_2, CHANNEL_3

PATTERN_LENGTH   .set  2560

CHANNEL_0:
	PATTERN ENVIROS
	PATTERN PATTERN_01
	PATTERN PATTERN_05
DO 0
	PATTERN PATTERN_09
	PATTERN PATTERN_13
	PATTERN PATTERN_17
	PATTERN PATTERN_21
	PATTERN PATTERN_25
	PATTERN PATTERN_25
	PATTERN PATTERN_45
	PATTERN PATTERN_45
	PATTERN PATTERN_33
	PATTERN PATTERN_37
	PATTERN PATTERN_09
	PATTERN PATTERN_09
	PATTERN PATTERN_17
	PATTERN PATTERN_21
	PATTERN PATTERN_45
	PATTERN PATTERN_45
	PATTERN PATTERN_49
	PATTERN PATTERN_49
LOOP
CHAN_STOP

CHANNEL_1:
	PATTERN ENVIROS
	PATTERN PATTERN_02
	PATTERN PATTERN_06
DO 0
	PATTERN PATTERN_10
	PATTERN PATTERN_14
	PATTERN PATTERN_18
	PATTERN PATTERN_22
	PATTERN PATTERN_26
	PATTERN PATTERN_26
	PATTERN PATTERN_46
	PATTERN PATTERN_46
	PATTERN PATTERN_34
	PATTERN PATTERN_38
	PATTERN PATTERN_10
	PATTERN PATTERN_10
	PATTERN PATTERN_18
	PATTERN PATTERN_22
	PATTERN PATTERN_46
	PATTERN PATTERN_46
	PATTERN PATTERN_50
	PATTERN PATTERN_50
LOOP
CHAN_STOP

CHANNEL_2:
	PATTERN ENVIROS
	PATTERN PATTERN_03
	PATTERN PATTERN_07
DO 0
	PATTERN PATTERN_11
	PATTERN PATTERN_15
	PATTERN PATTERN_19
	PATTERN PATTERN_23
	PATTERN PATTERN_27
	PATTERN PATTERN_27
	PATTERN PATTERN_47
	PATTERN PATTERN_47
	PATTERN PATTERN_35
	PATTERN PATTERN_39
	PATTERN PATTERN_11
	PATTERN PATTERN_11
	PATTERN PATTERN_19
	PATTERN PATTERN_23
	PATTERN PATTERN_47
	PATTERN PATTERN_47
	PATTERN PATTERN_51
	PATTERN PATTERN_51
LOOP
CHAN_STOP

CHANNEL_3:
	PATTERN ENVIROS
CHAN_STOP

ENVIROS:
	SETPLAYERFREQ $9D,129
	DEF_VOLENV 4,TREMOLO_4
	DEF_VOLENV 5,TREMOLO_5
	DELAY 3
RETURN

TREMOLO_4:
.byte $01,$02,$02,$01,$02,$FE
TREMOLO_5:
.byte $01,$03,$03,$FF,$03,$02,$02,$FE



PATTERN_01:
	DELAY 40
	INSTR2 $00,$00,$03,36,127
	SET_VOLENV 5
	PLAY2 189,$5c,80
	PLAY2 189,$5b,80
	PLAY2 189,$5c,80
	PLAY2 189,$5b,80
	PLAY2 189,$5c,80
	PLAY2 189,$5b,80
	PLAY2 189,$5c,80
	PLAY2 189,$5b,80
	PLAY2 59,$5e,80
	PLAY2 29,$5e,80
	PLAY2 59,$5e,80
	PLAY2 29,$5e,80
	PLAY2 59,$5e,80
	PLAY2 29,$5e,80
	PLAY2 59,$5e,80
	PLAY2 29,$5e,80
	PLAY2 142,$5d,80
	PLAY2 142,$5c,80
	PLAY2 142,$5d,80
	PLAY2 142,$5c,80
	PLAY2 142,$5d,80
	PLAY2 142,$5c,80
	PLAY2 142,$5d,80
	PLAY2 142,$5c,80
	PLAY2 253,$5c,80
	PLAY2 253,$5b,80
	PLAY2 253,$5c,80
	PLAY2 253,$5b,80
	PLAY2 253,$5c,80
	PLAY2 253,$5b,80
	PLAY2 253,$5c,80
	PLAY2 253,$5b,40
RETURN


PATTERN_02:
	DELAY 2560
RETURN


PATTERN_03:
	INSTR2 $00,$00,$07,42,127
	SET_VOLENV 4
	PLAY2 142,$7b,80
	PLAY2 142,$7c,80
	PLAY2 142,$7b,80
	PLAY2 142,$7c,80
	PLAY2 142,$7b,40
	PLAY2 142,$7c,40
	PLAY2 142,$7b,40
	PLAY2 142,$7c,40
	PLAY2 142,$7b,40
	PLAY2 142,$7c,40
	PLAY2 142,$7b,40
	PLAY2 142,$7c,40
	PLAY2 180,$7b,80
	PLAY2 180,$7c,80
	PLAY2 180,$7b,80
	PLAY2 180,$7c,80
	PLAY2 180,$7b,40
	PLAY2 180,$7c,40
	PLAY2 180,$7b,40
	PLAY2 180,$7c,40
	PLAY2 180,$7b,40
	PLAY2 180,$7c,40
	PLAY2 180,$7b,40
	PLAY2 180,$7c,40
	PLAY2 214,$7b,80
	PLAY2 214,$7c,80
	PLAY2 214,$7b,80
	PLAY2 214,$7c,80
	PLAY2 214,$7b,40
	PLAY2 214,$7c,40
	PLAY2 214,$7b,40
	PLAY2 214,$7c,40
	PLAY2 214,$7b,40
	PLAY2 214,$7c,40
	PLAY2 214,$7b,40
	PLAY2 214,$7c,40
	PLAY2 190,$7b,80
	PLAY2 190,$7c,80
	PLAY2 190,$7b,80
	PLAY2 190,$7c,80
	PLAY2 190,$7b,40
	PLAY2 190,$7c,40
	PLAY2 190,$7b,40
	PLAY2 190,$7c,40
	PLAY2 190,$7b,40
	PLAY2 190,$7c,40
	PLAY2 190,$7b,40
	PLAY2 190,$7c,40
RETURN


PATTERN_05:
	DELAY 40
	INSTR2 $00,$00,$03,36,127
	SET_VOLENV 5
	PLAY2 189,$5c,80
	PLAY2 189,$5b,80
	PLAY2 189,$5c,80
	PLAY2 189,$5b,80
	PLAY2 189,$5c,80
	PLAY2 189,$5b,80
	PLAY2 189,$5c,80
	PLAY2 189,$5b,80
	PLAY2 59,$5e,80
	PLAY2 29,$5e,80
	PLAY2 59,$5e,80
	PLAY2 29,$5e,80
	PLAY2 59,$5e,80
	PLAY2 29,$5e,80
	PLAY2 59,$5e,80
	PLAY2 29,$5e,80
	PLAY2 142,$5d,80
	PLAY2 142,$5c,80
	PLAY2 142,$5d,80
	PLAY2 142,$5c,80
	PLAY2 142,$5d,80
	PLAY2 142,$5c,80
	PLAY2 142,$5d,80
	PLAY2 142,$5c,80
	PLAY2 253,$5c,80
	PLAY2 253,$5b,80
	PLAY2 253,$5c,80
	PLAY2 253,$5b,80
	PLAY2 253,$5c,80
	PLAY2 253,$5b,80
	PLAY2 253,$5c,80
	PLAY2 253,$5b,40
RETURN


PATTERN_06:
	INSTR2 $00,$00,$07,42,127
	SET_VOLENV 4
	PLAY2 142,$7b,80
	PLAY2 142,$7c,80
	PLAY2 142,$7b,80
	PLAY2 142,$7c,80
	PLAY2 142,$7b,40
	PLAY2 142,$7c,40
	PLAY2 142,$7b,40
	PLAY2 142,$7c,40
	PLAY2 142,$7b,40
	PLAY2 142,$7c,40
	PLAY2 142,$7b,40
	PLAY2 142,$7c,40
	PLAY2 180,$7b,80
	PLAY2 180,$7c,80
	PLAY2 180,$7b,80
	PLAY2 180,$7c,80
	PLAY2 180,$7b,40
	PLAY2 180,$7c,40
	PLAY2 180,$7b,40
	PLAY2 180,$7c,40
	PLAY2 180,$7b,40
	PLAY2 180,$7c,40
	PLAY2 180,$7b,40
	PLAY2 180,$7c,40
	PLAY2 214,$7b,80
	PLAY2 214,$7c,80
	PLAY2 214,$7b,80
	PLAY2 214,$7c,80
	PLAY2 214,$7b,40
	PLAY2 214,$7c,40
	PLAY2 214,$7b,40
	PLAY2 214,$7c,40
	PLAY2 214,$7b,40
	PLAY2 214,$7c,40
	PLAY2 214,$7b,40
	PLAY2 214,$7c,40
	PLAY2 190,$7b,80
	PLAY2 190,$7c,80
	PLAY2 190,$7b,80
	PLAY2 190,$7c,80
	PLAY2 190,$7b,40
	PLAY2 190,$7c,40
	PLAY2 190,$7b,40
	PLAY2 190,$7c,40
	PLAY2 190,$7b,40
	PLAY2 190,$7c,40
	PLAY2 190,$7b,40
	PLAY2 190,$7c,40
RETURN


PATTERN_07:
	INSTR2 $00,$00,$03,36,127
	SET_VOLENV 5
	PLAY2 159,$5b,255
	DELAY 265
	PLAY2 84,$5c,40
	PLAY2 189,$5b,40
	PLAY2 106,$5c,40
	PLAY2 189,$5b,255
	DELAY 265
	PLAY2 106,$5c,40
	PLAY2 189,$5b,40
	PLAY2 84,$5c,40
	PLAY2 159,$5b,255
	DELAY 265
	PLAY2 253,$5a,160
	PLAY2 14,$5e,40
	PLAY2 142,$5b,40
	PLAY2 253,$5a,40
	PLAY2 159,$5b,40
	PLAY2 142,$5b,40
	PLAY2 84,$5c,40
	PLAY2 159,$5b,40
	PLAY2 253,$5a,40
	PLAY2 14,$5e,40
	PLAY2 142,$5b,40
	PLAY2 253,$5a,40
	PLAY2 159,$5b,40
	PLAY2 142,$5b,40
	PLAY2 84,$5c,40
	PLAY2 189,$5b,40
RETURN


PATTERN_09:
	DELAY 40
	INSTR2 $00,$00,$03,36,127
	SET_VOLENV 5
	PLAY2 189,$5c,80
	PLAY2 189,$5b,80
	PLAY2 189,$5c,80
	PLAY2 189,$5b,80
	PLAY2 189,$5c,80
	PLAY2 189,$5b,80
	PLAY2 189,$5c,80
	PLAY2 189,$5b,80
	PLAY2 59,$5e,80
	PLAY2 29,$5e,80
	PLAY2 59,$5e,80
	PLAY2 29,$5e,80
	PLAY2 59,$5e,80
	PLAY2 29,$5e,80
	PLAY2 59,$5e,80
	PLAY2 29,$5e,80
	PLAY2 142,$5d,80
	PLAY2 142,$5c,80
	PLAY2 142,$5d,80
	PLAY2 142,$5c,80
	PLAY2 142,$5d,80
	PLAY2 142,$5c,80
	PLAY2 142,$5d,80
	PLAY2 142,$5c,80
	PLAY2 253,$5c,80
	PLAY2 253,$5b,80
	PLAY2 253,$5c,80
	PLAY2 253,$5b,80
	PLAY2 253,$5c,80
	PLAY2 253,$5b,80
	PLAY2 253,$5c,80
	PLAY2 253,$5b,40
RETURN


PATTERN_10:
	INSTR2 $00,$00,$07,42,127
	SET_VOLENV 4
	PLAY2 142,$7b,80
	PLAY2 142,$7c,80
	PLAY2 142,$7b,80
	PLAY2 142,$7c,80
	PLAY2 142,$7b,40
	PLAY2 142,$7c,40
	PLAY2 142,$7b,40
	PLAY2 142,$7c,40
	PLAY2 142,$7b,40
	PLAY2 142,$7c,40
	PLAY2 142,$7b,40
	PLAY2 142,$7c,40
	PLAY2 180,$7b,80
	PLAY2 180,$7c,80
	PLAY2 180,$7b,80
	PLAY2 180,$7c,80
	PLAY2 180,$7b,40
	PLAY2 180,$7c,40
	PLAY2 180,$7b,40
	PLAY2 180,$7c,40
	PLAY2 180,$7b,40
	PLAY2 180,$7c,40
	PLAY2 180,$7b,40
	PLAY2 180,$7c,40
	PLAY2 214,$7b,80
	PLAY2 214,$7c,80
	PLAY2 214,$7b,80
	PLAY2 214,$7c,80
	PLAY2 214,$7b,40
	PLAY2 214,$7c,40
	PLAY2 214,$7b,40
	PLAY2 214,$7c,40
	PLAY2 214,$7b,40
	PLAY2 214,$7c,40
	PLAY2 214,$7b,40
	PLAY2 214,$7c,40
	PLAY2 190,$7b,80
	PLAY2 190,$7c,80
	PLAY2 190,$7b,80
	PLAY2 190,$7c,80
	PLAY2 190,$7b,40
	PLAY2 190,$7c,40
	PLAY2 190,$7b,40
	PLAY2 190,$7c,40
	PLAY2 190,$7b,40
	PLAY2 190,$7c,40
	PLAY2 190,$7b,40
	PLAY2 190,$7c,40
RETURN


PATTERN_11:
	INSTR2 $00,$00,$03,36,127
	SET_VOLENV 5
	PLAY2 159,$5b,255
	DELAY 265
	PLAY2 84,$5c,40
	PLAY2 189,$5b,40
	PLAY2 106,$5c,40
	PLAY2 189,$5b,255
	DELAY 265
	PLAY2 106,$5c,40
	PLAY2 189,$5b,40
	PLAY2 84,$5c,40
	PLAY2 159,$5b,255
	DELAY 265
	PLAY2 253,$5a,160
	PLAY2 14,$5e,40
	PLAY2 142,$5b,40
	PLAY2 253,$5a,40
	PLAY2 159,$5b,40
	PLAY2 142,$5b,40
	PLAY2 84,$5c,40
	PLAY2 159,$5b,40
	PLAY2 189,$5b,40
	PLAY2 84,$5c,40
	PLAY2 100,$5c,40
	PLAY2 189,$5b,40
	PLAY2 29,$5e,40
	PLAY2 100,$5c,40
	PLAY2 253,$5b,40
	PLAY2 142,$5c,40
RETURN


PATTERN_13:
	DELAY 40
	INSTR2 $00,$00,$03,36,127
	SET_VOLENV 5
	PLAY2 189,$5c,80
	PLAY2 189,$5b,80
	PLAY2 189,$5c,80
	PLAY2 189,$5b,80
	PLAY2 189,$5c,80
	PLAY2 189,$5b,80
	PLAY2 189,$5c,80
	PLAY2 189,$5b,80
	PLAY2 59,$5e,80
	PLAY2 29,$5e,80
	PLAY2 59,$5e,80
	PLAY2 29,$5e,80
	PLAY2 59,$5e,80
	PLAY2 29,$5e,80
	PLAY2 59,$5e,80
	PLAY2 29,$5e,80
	PLAY2 142,$5d,80
	PLAY2 142,$5c,80
	PLAY2 142,$5d,80
	PLAY2 142,$5c,80
	PLAY2 142,$5d,80
	PLAY2 142,$5c,80
	PLAY2 142,$5d,80
	PLAY2 142,$5c,80
	PLAY2 253,$5c,80
	PLAY2 253,$5b,80
	PLAY2 253,$5c,80
	PLAY2 253,$5b,80
	PLAY2 253,$5c,80
	PLAY2 253,$5b,80
	PLAY2 253,$5c,80
	PLAY2 253,$5b,40
RETURN


PATTERN_14:
	INSTR2 $00,$00,$07,42,127
	SET_VOLENV 4
	PLAY2 142,$7b,80
	PLAY2 142,$7c,80
	PLAY2 142,$7b,80
	PLAY2 142,$7c,80
	PLAY2 142,$7b,40
	PLAY2 142,$7c,40
	PLAY2 142,$7b,40
	PLAY2 142,$7c,40
	PLAY2 142,$7b,40
	PLAY2 142,$7c,40
	PLAY2 142,$7b,40
	PLAY2 142,$7c,40
	PLAY2 180,$7b,80
	PLAY2 180,$7c,80
	PLAY2 180,$7b,80
	PLAY2 180,$7c,80
	PLAY2 180,$7b,40
	PLAY2 180,$7c,40
	PLAY2 180,$7b,40
	PLAY2 180,$7c,40
	PLAY2 180,$7b,40
	PLAY2 180,$7c,40
	PLAY2 180,$7b,40
	PLAY2 180,$7c,40
	PLAY2 214,$7b,80
	PLAY2 214,$7c,80
	PLAY2 214,$7b,80
	PLAY2 214,$7c,80
	PLAY2 214,$7b,40
	PLAY2 214,$7c,40
	PLAY2 214,$7b,40
	PLAY2 214,$7c,40
	PLAY2 214,$7b,40
	PLAY2 214,$7c,40
	PLAY2 214,$7b,40
	PLAY2 214,$7c,40
	PLAY2 190,$7b,80
	PLAY2 190,$7c,80
	PLAY2 190,$7b,80
	PLAY2 190,$7c,80
	PLAY2 190,$7b,40
	PLAY2 190,$7c,40
	PLAY2 190,$7b,40
	PLAY2 190,$7c,40
	PLAY2 190,$7b,40
	PLAY2 190,$7c,40
	PLAY2 190,$7b,40
	PLAY2 190,$7c,40
RETURN


PATTERN_15:
	INSTR2 $00,$00,$03,36,127
	SET_VOLENV 5
	PLAY2 253,$5a,120
	PLAY2 142,$5b,40
	PLAY2 159,$5b,160
	PLAY2 253,$5a,200
	PLAY2 14,$5e,40
	PLAY2 253,$5a,40
	PLAY2 142,$5b,40
	PLAY2 159,$5b,40
	PLAY2 142,$5b,40
	PLAY2 159,$5b,40
	PLAY2 84,$5c,40
	PLAY2 159,$5b,40
	PLAY2 84,$5c,40
	PLAY2 189,$5b,40
	PLAY2 159,$5b,40
	PLAY2 159,$5b,40
	PLAY2 84,$5c,40
	PLAY2 189,$5b,40
	PLAY2 159,$5b,40
	PLAY2 159,$5b,80
	PLAY2 189,$5b,80
	PLAY2 189,$5b,255
	DELAY 105
	PLAY2 159,$5b,40
	PLAY2 84,$5c,40
	PLAY2 142,$5b,40
	PLAY2 159,$5b,40
	PLAY2 253,$5a,40
	PLAY2 142,$5b,40
	PLAY2 14,$5e,40
	PLAY2 142,$5b,40
	PLAY2 253,$5a,40
	PLAY2 159,$5b,40
	PLAY2 142,$5b,40
	PLAY2 84,$5c,40
	PLAY2 159,$5b,40
	PLAY2 189,$5b,40
	PLAY2 84,$5c,40
	PLAY2 253,$5b,40
	PLAY2 189,$5b,40
	PLAY2 29,$5e,40
	PLAY2 100,$5c,40
	PLAY2 253,$5b,40
	PLAY2 29,$5e,40
	PLAY2 142,$5c,40
	PLAY2 253,$5b,40
RETURN


PATTERN_17:
	DELAY 40
	INSTR2 $00,$00,$03,36,127
	SET_VOLENV 5
	PLAY2 189,$5c,80
	PLAY2 189,$5b,80
	PLAY2 189,$5c,80
	PLAY2 189,$5b,80
	PLAY2 189,$5c,80
	PLAY2 189,$5b,80
	PLAY2 189,$5c,80
	PLAY2 189,$5b,80
	PLAY2 59,$5e,80
	PLAY2 29,$5e,80
	PLAY2 59,$5e,80
	PLAY2 29,$5e,80
	PLAY2 59,$5e,80
	PLAY2 29,$5e,80
	PLAY2 59,$5e,80
	PLAY2 29,$5e,80
	PLAY2 142,$5d,80
	PLAY2 142,$5c,80
	PLAY2 142,$5d,80
	PLAY2 142,$5c,80
	PLAY2 142,$5d,80
	PLAY2 142,$5c,80
	PLAY2 142,$5d,80
	PLAY2 142,$5c,80
	PLAY2 253,$5c,80
	PLAY2 253,$5b,80
	PLAY2 253,$5c,80
	PLAY2 253,$5b,80
	PLAY2 253,$5c,80
	PLAY2 253,$5b,80
	PLAY2 253,$5c,80
	PLAY2 253,$5b,40
RETURN


PATTERN_18:
	INSTR2 $00,$00,$07,42,127
	SET_VOLENV 4
	PLAY2 142,$7b,80
	PLAY2 142,$7c,80
	PLAY2 142,$7b,80
	PLAY2 142,$7c,80
	PLAY2 142,$7b,40
	PLAY2 142,$7c,40
	PLAY2 142,$7b,40
	PLAY2 142,$7c,40
	PLAY2 142,$7b,40
	PLAY2 142,$7c,40
	PLAY2 142,$7b,40
	PLAY2 142,$7c,40
	PLAY2 180,$7b,80
	PLAY2 180,$7c,80
	PLAY2 180,$7b,80
	PLAY2 180,$7c,80
	PLAY2 180,$7b,40
	PLAY2 180,$7c,40
	PLAY2 180,$7b,40
	PLAY2 180,$7c,40
	PLAY2 180,$7b,40
	PLAY2 180,$7c,40
	PLAY2 180,$7b,40
	PLAY2 180,$7c,40
	PLAY2 214,$7b,80
	PLAY2 214,$7c,80
	PLAY2 214,$7b,80
	PLAY2 214,$7c,80
	PLAY2 214,$7b,40
	PLAY2 214,$7c,40
	PLAY2 214,$7b,40
	PLAY2 214,$7c,40
	PLAY2 214,$7b,40
	PLAY2 214,$7c,40
	PLAY2 214,$7b,40
	PLAY2 214,$7c,40
	PLAY2 190,$7b,80
	PLAY2 190,$7c,80
	PLAY2 190,$7b,80
	PLAY2 190,$7c,80
	PLAY2 190,$7b,40
	PLAY2 190,$7c,40
	PLAY2 190,$7b,40
	PLAY2 190,$7c,40
	PLAY2 190,$7b,40
	PLAY2 190,$7c,40
	PLAY2 190,$7b,40
	PLAY2 190,$7c,40
RETURN


PATTERN_19:
	INSTR2 $00,$00,$03,36,127
	SET_VOLENV 5
	PLAY2 253,$5b,255
	DELAY 265
	PLAY2 253,$5b,40
	PLAY2 189,$5b,40
	PLAY2 29,$5e,255
	DELAY 305
	PLAY2 29,$5e,40
	PLAY2 253,$5b,40
	PLAY2 142,$5c,255
	DELAY 305
	PLAY2 253,$5b,40
	PLAY2 29,$5e,40
	PLAY2 253,$5b,240
	PLAY2 142,$5c,40
	PLAY2 159,$5c,40
	PLAY2 84,$5d,255
	DELAY 105
RETURN


PATTERN_21:
	DELAY 40
	INSTR2 $00,$00,$03,36,127
	SET_VOLENV 5
	PLAY2 189,$5c,80
	PLAY2 189,$5b,80
	PLAY2 189,$5c,80
	PLAY2 189,$5b,80
	PLAY2 189,$5c,80
	PLAY2 189,$5b,80
	PLAY2 189,$5c,80
	PLAY2 189,$5b,80
	PLAY2 59,$5e,80
	PLAY2 29,$5e,80
	PLAY2 59,$5e,80
	PLAY2 29,$5e,80
	PLAY2 59,$5e,80
	PLAY2 29,$5e,80
	PLAY2 59,$5e,80
	PLAY2 29,$5e,80
	PLAY2 142,$5d,80
	PLAY2 142,$5c,80
	PLAY2 142,$5d,80
	PLAY2 142,$5c,80
	PLAY2 142,$5d,80
	PLAY2 142,$5c,80
	PLAY2 142,$5d,80
	PLAY2 142,$5c,80
	PLAY2 253,$5c,80
	PLAY2 253,$5b,80
	PLAY2 253,$5c,80
	PLAY2 253,$5b,80
	PLAY2 253,$5c,80
	PLAY2 253,$5b,80
	PLAY2 253,$5c,80
	PLAY2 253,$5b,40
RETURN


PATTERN_22:
	INSTR2 $00,$00,$07,42,127
	SET_VOLENV 4
	PLAY2 142,$7b,80
	PLAY2 142,$7c,80
	PLAY2 142,$7b,80
	PLAY2 142,$7c,80
	PLAY2 142,$7b,40
	PLAY2 142,$7c,40
	PLAY2 142,$7b,40
	PLAY2 142,$7c,40
	PLAY2 142,$7b,40
	PLAY2 142,$7c,40
	PLAY2 142,$7b,40
	PLAY2 142,$7c,40
	PLAY2 180,$7b,80
	PLAY2 180,$7c,80
	PLAY2 180,$7b,80
	PLAY2 180,$7c,80
	PLAY2 180,$7b,40
	PLAY2 180,$7c,40
	PLAY2 180,$7b,40
	PLAY2 180,$7c,40
	PLAY2 180,$7b,40
	PLAY2 180,$7c,40
	PLAY2 180,$7b,40
	PLAY2 180,$7c,40
	PLAY2 214,$7b,80
	PLAY2 214,$7c,80
	PLAY2 214,$7b,80
	PLAY2 214,$7c,80
	PLAY2 214,$7b,40
	PLAY2 214,$7c,40
	PLAY2 214,$7b,40
	PLAY2 214,$7c,40
	PLAY2 214,$7b,40
	PLAY2 214,$7c,40
	PLAY2 214,$7b,40
	PLAY2 214,$7c,40
	PLAY2 190,$7b,80
	PLAY2 190,$7c,80
	PLAY2 190,$7b,80
	PLAY2 190,$7c,80
	PLAY2 190,$7b,40
	PLAY2 190,$7c,40
	PLAY2 190,$7b,40
	PLAY2 190,$7c,40
	PLAY2 190,$7b,40
	PLAY2 190,$7c,40
	PLAY2 190,$7b,40
	PLAY2 190,$7c,40
RETURN


PATTERN_23:
	INSTR2 $00,$00,$03,36,127
	SET_VOLENV 5
	PLAY2 253,$5b,255
	DELAY 265
	PLAY2 253,$5b,40
	PLAY2 189,$5b,40
	PLAY2 29,$5e,255
	DELAY 305
	PLAY2 29,$5e,40
	PLAY2 253,$5b,40
	PLAY2 142,$5c,255
	DELAY 305
	PLAY2 253,$5b,40
	PLAY2 29,$5e,40
	PLAY2 253,$5b,240
	PLAY2 142,$5c,40
	PLAY2 159,$5c,40
	PLAY2 84,$5d,255
	DELAY 105
RETURN


PATTERN_25:
	DELAY 40
	INSTR2 $00,$00,$03,36,127
	SET_VOLENV 5
	PLAY2 189,$5c,80
	PLAY2 189,$5b,80
	PLAY2 189,$5c,80
	PLAY2 189,$5b,80
	PLAY2 189,$5c,80
	PLAY2 189,$5b,80
	PLAY2 189,$5c,80
	PLAY2 189,$5b,80
	PLAY2 59,$5e,80
	PLAY2 29,$5e,80
	PLAY2 59,$5e,80
	PLAY2 29,$5e,80
	PLAY2 59,$5e,80
	PLAY2 29,$5e,80
	PLAY2 59,$5e,80
	PLAY2 29,$5e,80
	PLAY2 142,$5d,80
	PLAY2 142,$5c,80
	PLAY2 142,$5d,80
	PLAY2 142,$5c,80
	PLAY2 142,$5d,80
	PLAY2 142,$5c,80
	PLAY2 142,$5d,80
	PLAY2 142,$5c,80
	PLAY2 253,$5c,80
	PLAY2 253,$5b,80
	PLAY2 253,$5c,80
	PLAY2 253,$5b,80
	PLAY2 253,$5c,80
	PLAY2 253,$5b,80
	PLAY2 253,$5c,80
	PLAY2 253,$5b,40
RETURN


PATTERN_26:
	INSTR2 $00,$00,$07,42,127
	SET_VOLENV 4
	PLAY2 142,$7b,80
	PLAY2 142,$7c,80
	PLAY2 142,$7b,80
	PLAY2 142,$7c,80
	PLAY2 142,$7b,40
	PLAY2 142,$7c,40
	PLAY2 142,$7b,40
	PLAY2 142,$7c,40
	PLAY2 142,$7b,40
	PLAY2 142,$7c,40
	PLAY2 142,$7b,40
	PLAY2 142,$7c,40
	PLAY2 180,$7b,80
	PLAY2 180,$7c,80
	PLAY2 180,$7b,80
	PLAY2 180,$7c,80
	PLAY2 180,$7b,40
	PLAY2 180,$7c,40
	PLAY2 180,$7b,40
	PLAY2 180,$7c,40
	PLAY2 180,$7b,40
	PLAY2 180,$7c,40
	PLAY2 180,$7b,40
	PLAY2 180,$7c,40
	PLAY2 214,$7b,80
	PLAY2 214,$7c,80
	PLAY2 214,$7b,80
	PLAY2 214,$7c,80
	PLAY2 214,$7b,40
	PLAY2 214,$7c,40
	PLAY2 214,$7b,40
	PLAY2 214,$7c,40
	PLAY2 214,$7b,40
	PLAY2 214,$7c,40
	PLAY2 214,$7b,40
	PLAY2 214,$7c,40
	PLAY2 190,$7b,80
	PLAY2 190,$7c,80
	PLAY2 190,$7b,80
	PLAY2 190,$7c,80
	PLAY2 190,$7b,40
	PLAY2 190,$7c,40
	PLAY2 190,$7b,40
	PLAY2 190,$7c,40
	PLAY2 190,$7b,40
	PLAY2 190,$7c,40
	PLAY2 190,$7b,40
	PLAY2 190,$7c,40
RETURN


PATTERN_27:
	INSTR2 $00,$00,$03,36,127
	SET_VOLENV 5
	PLAY2 253,$5a,120
	PLAY2 142,$5b,40
	PLAY2 159,$5b,160
	PLAY2 253,$5a,200
	PLAY2 14,$5e,40
	PLAY2 253,$5a,40
	PLAY2 142,$5b,40
	PLAY2 159,$5b,40
	PLAY2 142,$5b,40
	PLAY2 159,$5b,40
	PLAY2 84,$5c,40
	PLAY2 159,$5b,40
	PLAY2 84,$5c,40
	PLAY2 189,$5b,40
	PLAY2 159,$5b,40
	PLAY2 159,$5b,40
	PLAY2 84,$5c,40
	PLAY2 189,$5b,40
	PLAY2 159,$5b,40
	PLAY2 159,$5b,80
	PLAY2 189,$5b,80
	PLAY2 189,$5b,255
	DELAY 105
	PLAY2 159,$5b,40
	PLAY2 84,$5c,40
	PLAY2 142,$5b,40
	PLAY2 159,$5b,40
	PLAY2 253,$5a,40
	PLAY2 142,$5b,40
	PLAY2 14,$5e,40
	PLAY2 142,$5b,40
	PLAY2 253,$5a,40
	PLAY2 159,$5b,40
	PLAY2 142,$5b,40
	PLAY2 84,$5c,40
	PLAY2 159,$5b,40
	PLAY2 189,$5b,40
	PLAY2 84,$5c,40
	PLAY2 253,$5b,40
	PLAY2 189,$5b,40
	PLAY2 29,$5e,40
	PLAY2 100,$5c,40
	PLAY2 253,$5b,40
	PLAY2 29,$5e,40
	PLAY2 142,$5c,40
	PLAY2 253,$5b,40
RETURN


PATTERN_33:
	DELAY 40
	INSTR2 $00,$00,$07,42,127
	SET_VOLENV 4
	PLAY2 142,$7c,80
	PLAY2 142,$7b,80
	PLAY2 142,$7c,80
	PLAY2 142,$7b,80
	PLAY2 142,$7c,80
	PLAY2 142,$7b,80
	PLAY2 142,$7c,80
	PLAY2 142,$7b,80
	PLAY2 180,$7c,80
	PLAY2 180,$7b,80
	PLAY2 180,$7c,80
	PLAY2 180,$7b,80
	PLAY2 180,$7c,80
	PLAY2 180,$7b,80
	PLAY2 180,$7c,80
	PLAY2 180,$7b,80
	PLAY2 214,$7c,80
	PLAY2 214,$7b,80
	PLAY2 214,$7c,80
	PLAY2 214,$7b,80
	PLAY2 214,$7c,80
	PLAY2 214,$7b,80
	PLAY2 214,$7c,80
	PLAY2 214,$7b,80
	PLAY2 190,$7c,80
	PLAY2 190,$7b,80
	PLAY2 190,$7c,80
	PLAY2 190,$7b,80
	PLAY2 190,$7c,80
	PLAY2 190,$7b,80
	PLAY2 190,$7c,80
	PLAY2 190,$7b,40
RETURN


PATTERN_34:
	INSTR2 $00,$00,$03,36,127
	SET_VOLENV 5
	PLAY2 189,$5b,40
	PLAY2 253,$5a,40
	PLAY2 142,$5b,40
	PLAY2 253,$5a,40
	PLAY2 159,$5b,40
	PLAY2 142,$5b,40
	PLAY2 84,$5c,40
	PLAY2 159,$5b,40
	PLAY2 189,$5b,40
	PLAY2 84,$5c,40
	PLAY2 159,$5b,40
	PLAY2 84,$5c,40
	PLAY2 142,$5b,40
	PLAY2 159,$5b,40
	PLAY2 84,$5c,40
	PLAY2 159,$5b,40
	PLAY2 189,$5b,40
	PLAY2 253,$5a,40
	PLAY2 142,$5b,40
	PLAY2 253,$5a,40
	PLAY2 159,$5b,40
	PLAY2 142,$5b,40
	PLAY2 84,$5c,40
	PLAY2 159,$5b,40
	PLAY2 189,$5b,40
	PLAY2 84,$5c,40
	PLAY2 159,$5b,40
	PLAY2 84,$5c,40
	PLAY2 142,$5b,40
	PLAY2 159,$5b,40
	PLAY2 84,$5c,40
	PLAY2 159,$5b,40
	PLAY2 189,$5b,40
	PLAY2 253,$5a,40
	PLAY2 142,$5b,40
	PLAY2 253,$5a,40
	PLAY2 159,$5b,40
	PLAY2 142,$5b,40
	PLAY2 84,$5c,40
	PLAY2 159,$5b,40
	PLAY2 189,$5b,40
	PLAY2 84,$5c,40
	PLAY2 159,$5b,40
	PLAY2 84,$5c,40
	PLAY2 142,$5b,40
	PLAY2 159,$5b,40
	PLAY2 84,$5c,40
	PLAY2 189,$5b,40
	PLAY2 84,$5c,40
	PLAY2 253,$5b,40
	PLAY2 100,$5c,40
	PLAY2 253,$5b,40
	PLAY2 189,$5b,40
	PLAY2 253,$5b,40
	PLAY2 84,$5c,40
	PLAY2 253,$5b,40
	PLAY2 159,$5b,40
	PLAY2 253,$5b,40
	PLAY2 189,$5b,40
	PLAY2 253,$5b,40
	PLAY2 84,$5c,40
	PLAY2 253,$5b,40
	PLAY2 100,$5c,40
	PLAY2 253,$5b,40
RETURN


PATTERN_35:
	INSTR2 $00,$00,$03,36,127
	SET_VOLENV 5
	PLAY2 189,$5c,255
	DELAY 385
	PLAY2 59,$5e,255
	DELAY 385
	PLAY2 142,$5d,255
	DELAY 385
	PLAY2 253,$5c,255
	DELAY 385
RETURN


PATTERN_37:
	DELAY 40
	INSTR2 $00,$00,$07,42,127
	SET_VOLENV 4
	PLAY2 142,$7c,80
	PLAY2 142,$7b,80
	PLAY2 142,$7c,80
	PLAY2 142,$7b,80
	PLAY2 142,$7c,80
	PLAY2 142,$7b,80
	PLAY2 142,$7c,80
	PLAY2 142,$7b,80
	PLAY2 180,$7c,80
	PLAY2 180,$7b,80
	PLAY2 180,$7c,80
	PLAY2 180,$7b,80
	PLAY2 180,$7c,80
	PLAY2 180,$7b,80
	PLAY2 180,$7c,80
	PLAY2 180,$7b,80
	PLAY2 214,$7c,80
	PLAY2 214,$7b,80
	PLAY2 214,$7c,80
	PLAY2 214,$7b,80
	PLAY2 214,$7c,80
	PLAY2 214,$7b,80
	PLAY2 214,$7c,80
	PLAY2 214,$7b,80
	PLAY2 190,$7c,80
	PLAY2 190,$7b,80
	PLAY2 190,$7c,80
	PLAY2 190,$7b,80
	PLAY2 190,$7c,80
	PLAY2 190,$7b,80
	PLAY2 190,$7c,80
	PLAY2 190,$7b,40
RETURN


PATTERN_38:
	INSTR2 $00,$00,$03,36,127
	SET_VOLENV 5
	PLAY2 189,$5b,40
	PLAY2 253,$5a,40
	PLAY2 142,$5b,40
	PLAY2 253,$5a,40
	PLAY2 159,$5b,40
	PLAY2 142,$5b,40
	PLAY2 84,$5c,40
	PLAY2 159,$5b,40
	PLAY2 189,$5b,40
	PLAY2 84,$5c,40
	PLAY2 159,$5b,40
	PLAY2 84,$5c,40
	PLAY2 142,$5b,40
	PLAY2 159,$5b,40
	PLAY2 84,$5c,40
	PLAY2 159,$5b,40
	PLAY2 189,$5b,40
	PLAY2 253,$5a,40
	PLAY2 142,$5b,40
	PLAY2 253,$5a,40
	PLAY2 159,$5b,40
	PLAY2 142,$5b,40
	PLAY2 84,$5c,40
	PLAY2 159,$5b,40
	PLAY2 189,$5b,40
	PLAY2 84,$5c,40
	PLAY2 159,$5b,40
	PLAY2 84,$5c,40
	PLAY2 142,$5b,40
	PLAY2 159,$5b,40
	PLAY2 84,$5c,40
	PLAY2 159,$5b,40
	PLAY2 189,$5b,40
	PLAY2 253,$5a,40
	PLAY2 142,$5b,40
	PLAY2 253,$5a,40
	PLAY2 159,$5b,40
	PLAY2 142,$5b,40
	PLAY2 84,$5c,40
	PLAY2 159,$5b,40
	PLAY2 189,$5b,40
	PLAY2 84,$5c,40
	PLAY2 159,$5b,40
	PLAY2 84,$5c,40
	PLAY2 142,$5b,40
	PLAY2 159,$5b,40
	PLAY2 84,$5c,40
	PLAY2 189,$5b,40
	PLAY2 84,$5c,40
	PLAY2 253,$5b,40
	PLAY2 100,$5c,40
	PLAY2 253,$5b,40
	PLAY2 189,$5b,40
	PLAY2 253,$5b,40
	PLAY2 84,$5c,40
	PLAY2 253,$5b,40
	PLAY2 159,$5b,40
	PLAY2 253,$5b,40
	PLAY2 189,$5b,40
	PLAY2 253,$5b,40
	PLAY2 84,$5c,40
	PLAY2 253,$5b,40
	PLAY2 100,$5c,40
	PLAY2 253,$5b,40
RETURN


PATTERN_39:
	INSTR2 $00,$00,$03,36,127
	SET_VOLENV 5
	PLAY2 189,$5c,255
	DELAY 385
	PLAY2 59,$5e,255
	DELAY 385
	PLAY2 142,$5d,255
	DELAY 385
	PLAY2 253,$5c,255
	DELAY 385
RETURN


PATTERN_45:
	DELAY 40
	INSTR2 $00,$00,$03,36,127
	SET_VOLENV 5
	PLAY2 189,$5c,80
	PLAY2 189,$5b,80
	PLAY2 189,$5c,80
	PLAY2 189,$5b,80
	PLAY2 189,$5c,80
	PLAY2 189,$5b,80
	PLAY2 189,$5c,80
	INSTR2 $00,$00,$00,10,127
	PLAY2 149,$7b,80
	INSTR2 $00,$00,$03,36,127
	SET_VOLENV 5
	PLAY2 59,$5e,80
	PLAY2 29,$5e,80
	PLAY2 59,$5e,80
	PLAY2 29,$5e,80
	PLAY2 59,$5e,80
	PLAY2 29,$5e,80
	PLAY2 59,$5e,80
	PLAY2 84,$5c,80
	PLAY2 142,$5d,80
	PLAY2 142,$5c,80
	PLAY2 142,$5d,80
	PLAY2 142,$5c,80
	PLAY2 142,$5d,80
	PLAY2 142,$5c,80
	PLAY2 142,$5d,80
	PLAY2 84,$5c,80
	PLAY2 253,$5c,80
	PLAY2 253,$5b,80
	PLAY2 253,$5c,80
	PLAY2 253,$5b,80
	PLAY2 253,$5c,80
	PLAY2 253,$5b,80
	PLAY2 84,$5c,80
	PLAY2 84,$5c,40
RETURN


PATTERN_46:
	INSTR2 $00,$00,$03,36,127
	SET_VOLENV 5
	PLAY2 189,$5b,40
	PLAY2 253,$5a,40
	PLAY2 142,$5b,40
	PLAY2 253,$5a,40
	PLAY2 159,$5b,40
	PLAY2 253,$5a,40
	PLAY2 84,$5c,40
	PLAY2 253,$5a,40
	PLAY2 189,$5b,40
	PLAY2 253,$5a,40
	PLAY2 142,$5b,40
	PLAY2 253,$5a,40
	PLAY2 159,$5b,40
	PLAY2 253,$5a,40
	PLAY2 84,$5c,40
	PLAY2 253,$5a,40
	PLAY2 189,$5b,40
	PLAY2 159,$5b,40
	PLAY2 84,$5c,40
	PLAY2 159,$5b,40
	PLAY2 189,$5b,40
	PLAY2 159,$5b,40
	PLAY2 106,$5c,40
	PLAY2 159,$5b,40
	PLAY2 29,$5e,40
	PLAY2 159,$5b,40
	PLAY2 84,$5c,40
	PLAY2 159,$5b,40
	PLAY2 189,$5b,40
	PLAY2 159,$5b,40
	PLAY2 106,$5c,40
	PLAY2 159,$5b,40
	PLAY2 29,$5e,40
	PLAY2 189,$5b,40
	PLAY2 106,$5c,40
	PLAY2 189,$5b,40
	PLAY2 29,$5e,40
	PLAY2 189,$5b,40
	PLAY2 253,$5b,40
	PLAY2 189,$5b,40
	PLAY2 142,$5c,40
	PLAY2 189,$5b,40
	PLAY2 106,$5c,40
	PLAY2 189,$5b,40
	PLAY2 29,$5e,40
	PLAY2 189,$5b,40
	PLAY2 253,$5b,40
	PLAY2 189,$5b,40
	PLAY2 142,$5c,40
	PLAY2 84,$5c,40
	PLAY2 189,$5b,40
	PLAY2 84,$5c,40
	PLAY2 100,$5c,40
	PLAY2 84,$5c,40
	PLAY2 29,$5e,40
	PLAY2 84,$5c,40
	PLAY2 253,$5b,40
	PLAY2 84,$5c,40
	PLAY2 189,$5b,40
	PLAY2 84,$5c,40
	PLAY2 100,$5c,40
	PLAY2 84,$5c,40
	PLAY2 29,$5e,40
	PLAY2 84,$5c,40
RETURN


PATTERN_47:
	INSTR2 $00,$00,$03,36,127
	SET_VOLENV 5
	PLAY2 189,$5c,40
	PLAY2 189,$5c,40
	PLAY2 189,$5c,40
	PLAY2 189,$5c,40
	PLAY2 189,$5c,40
	PLAY2 189,$5c,40
	PLAY2 189,$5c,40
	PLAY2 189,$5c,40
	PLAY2 189,$5c,40
	PLAY2 189,$5c,40
	PLAY2 189,$5c,40
	PLAY2 189,$5c,40
	PLAY2 189,$5c,40
	PLAY2 189,$5c,40
	PLAY2 189,$5c,40
	PLAY2 189,$5c,40
	PLAY2 59,$5e,40
	PLAY2 59,$5e,40
	PLAY2 59,$5e,40
	PLAY2 59,$5e,40
	PLAY2 59,$5e,40
	PLAY2 59,$5e,40
	PLAY2 59,$5e,40
	PLAY2 59,$5e,40
	PLAY2 59,$5e,40
	PLAY2 59,$5e,40
	PLAY2 59,$5e,40
	PLAY2 59,$5e,40
	PLAY2 59,$5e,40
	PLAY2 59,$5e,40
	PLAY2 59,$5e,40
	PLAY2 59,$5e,40
	PLAY2 142,$5c,40
	PLAY2 142,$5c,40
	PLAY2 142,$5c,40
	PLAY2 142,$5c,40
	PLAY2 142,$5c,40
	PLAY2 142,$5c,40
	PLAY2 142,$5c,40
	PLAY2 142,$5c,40
	PLAY2 142,$5c,40
	PLAY2 142,$5c,40
	PLAY2 142,$5c,40
	PLAY2 142,$5c,40
	PLAY2 142,$5c,40
	PLAY2 142,$5c,40
	PLAY2 142,$5c,40
	PLAY2 142,$5c,40
	PLAY2 100,$5c,40
	PLAY2 100,$5c,40
	PLAY2 100,$5c,40
	PLAY2 100,$5c,40
	PLAY2 100,$5c,40
	PLAY2 100,$5c,40
	PLAY2 100,$5c,40
	PLAY2 100,$5c,40
	PLAY2 100,$5c,40
	PLAY2 100,$5c,40
	PLAY2 100,$5c,40
	PLAY2 100,$5c,40
	PLAY2 100,$5c,40
	PLAY2 100,$5c,40
	PLAY2 100,$5c,40
	PLAY2 100,$5c,40
RETURN


PATTERN_49:
	DELAY 40
	INSTR2 $00,$00,$03,36,127
	SET_VOLENV 5
	PLAY2 189,$5c,80
	PLAY2 189,$5b,80
	PLAY2 189,$5c,80
	PLAY2 189,$5b,80
	PLAY2 189,$5c,80
	PLAY2 189,$5b,80
	PLAY2 189,$5c,80
	PLAY2 189,$5b,80
	PLAY2 59,$5e,80
	PLAY2 29,$5e,80
	PLAY2 59,$5e,80
	PLAY2 29,$5e,80
	PLAY2 59,$5e,80
	PLAY2 29,$5e,80
	PLAY2 59,$5e,80
	PLAY2 29,$5e,80
	PLAY2 142,$5d,80
	PLAY2 142,$5c,80
	PLAY2 142,$5d,80
	PLAY2 142,$5c,80
	PLAY2 142,$5d,80
	PLAY2 142,$5c,80
	PLAY2 142,$5d,80
	PLAY2 142,$5c,80
	PLAY2 253,$5c,80
	PLAY2 253,$5b,80
	PLAY2 253,$5c,80
	PLAY2 253,$5b,80
	PLAY2 253,$5c,80
	PLAY2 253,$5b,80
	PLAY2 253,$5c,80
	PLAY2 253,$5b,40
RETURN


PATTERN_50:
	INSTR2 $00,$00,$07,42,127
	SET_VOLENV 4
	PLAY2 142,$7b,80
	PLAY2 142,$7c,80
	PLAY2 142,$7b,80
	PLAY2 142,$7c,80
	PLAY2 142,$7b,40
	PLAY2 142,$7c,40
	PLAY2 142,$7b,40
	PLAY2 142,$7c,40
	PLAY2 142,$7b,40
	PLAY2 142,$7c,40
	PLAY2 142,$7b,40
	PLAY2 142,$7c,40
	PLAY2 180,$7b,80
	PLAY2 180,$7c,80
	PLAY2 180,$7b,80
	PLAY2 180,$7c,80
	PLAY2 180,$7b,40
	PLAY2 180,$7c,40
	PLAY2 180,$7b,40
	PLAY2 180,$7c,40
	PLAY2 180,$7b,40
	PLAY2 180,$7c,40
	PLAY2 180,$7b,40
	PLAY2 180,$7c,40
	PLAY2 214,$7b,80
	PLAY2 214,$7c,80
	PLAY2 214,$7b,80
	PLAY2 214,$7c,80
	PLAY2 214,$7b,40
	PLAY2 214,$7c,40
	PLAY2 214,$7b,40
	PLAY2 214,$7c,40
	PLAY2 214,$7b,40
	PLAY2 214,$7c,40
	PLAY2 214,$7b,40
	PLAY2 214,$7c,40
	PLAY2 190,$7b,80
	PLAY2 190,$7c,80
	PLAY2 190,$7b,80
	PLAY2 190,$7c,80
	PLAY2 190,$7b,40
	PLAY2 190,$7c,40
	PLAY2 190,$7b,40
	PLAY2 190,$7c,40
	PLAY2 190,$7b,40
	PLAY2 190,$7c,40
	PLAY2 190,$7b,40
	PLAY2 190,$7c,40
RETURN


PATTERN_51:
	INSTR2 $00,$00,$03,36,127
	SET_VOLENV 5
	PLAY2 253,$5a,120
	PLAY2 142,$5b,40
	PLAY2 159,$5b,160
	PLAY2 253,$5a,200
	PLAY2 14,$5e,40
	PLAY2 253,$5a,40
	PLAY2 142,$5b,40
	PLAY2 159,$5b,40
	PLAY2 142,$5b,40
	PLAY2 159,$5b,40
	PLAY2 84,$5c,40
	PLAY2 159,$5b,40
	PLAY2 84,$5c,40
	PLAY2 189,$5b,40
	PLAY2 159,$5b,40
	PLAY2 159,$5b,40
	PLAY2 84,$5c,40
	PLAY2 189,$5b,40
	PLAY2 159,$5b,40
	PLAY2 159,$5b,80
	PLAY2 189,$5b,80
	PLAY2 189,$5b,255
	DELAY 105
	PLAY2 159,$5b,40
	PLAY2 84,$5c,40
	PLAY2 142,$5b,40
	PLAY2 159,$5b,40
	PLAY2 253,$5a,40
	PLAY2 142,$5b,40
	PLAY2 14,$5e,40
	PLAY2 142,$5b,40
	PLAY2 253,$5a,40
	PLAY2 159,$5b,40
	PLAY2 142,$5b,40
	PLAY2 84,$5c,40
	PLAY2 159,$5b,40
	PLAY2 189,$5b,40
	PLAY2 84,$5c,40
	PLAY2 253,$5b,40
	PLAY2 189,$5b,40
	PLAY2 29,$5e,40
	PLAY2 100,$5c,40
	PLAY2 253,$5b,40
	PLAY2 29,$5e,40
	PLAY2 142,$5c,40
	PLAY2 253,$5b,40
RETURN
