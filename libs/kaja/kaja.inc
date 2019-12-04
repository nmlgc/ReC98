; Function numbers for the PMD and MMD drivers, according to PMDDATA.DOC and
; MMDFUNC.DOC. Functions prefixed with KAJA are available in both drivers.
; Only includes functions that are actually used in the games.

KAJA_SONG_PLAY equ 00h
KAJA_SONG_STOP equ 01h
KAJA_SONG_FADE equ 02h
KAJA_GET_SONG_MEASURE equ 05h
KAJA_GET_SONG_ADDRESS equ 06h
KAJA_GET_VOLUME equ 08h
PMD_GET_DRIVER_VERSION equ 09h
PMD_GET_SE_ADDRESS equ 0Bh
PMD_SE_PLAY equ 0Ch
PMD_GET_WORKAREA_ADDRESS equ 10h

kajacall	macro func, param := <0>
	call	snd_kaja_interrupt pascal, (func shl 8) or (param and 0ffh)
endm

PMD = 60h
MMD = 61h

MMD_TICKS_PER_QUARTER_NOTE = 48

ONKAI_REST = -1

qq struc
	     	dw ? ; 演奏中のアドレス (曲データ先頭番地+1からのoffset)
	     	dw ? ; 演奏が終わった時の戻り先アドレス (同上)
	leng 	db ? ; 現在発音中の音符の 残り Length 値
	qdat 	db ? ; gatetime値。gatetime ≧ 残りLength が成立した時点で、Keyoff
	     	dw ? ; 演奏中の音程。音源によって値は変化する。
	     	dw ? ; Detune ±値
	     	dw ? ; LFO    ±値
	     	dw ? ; ポルタメントの±値（全体）
	     	dw ? ; ポルタメントの±値（一回に変動する値）
	     	dw ? ; ポルタメントの±値（余り。1ずつ減って行く）
	     	db ? ; Volume   値 (FM:0～127 SSG:0～15 PCM:0～255)
	     	db ? ; 音階Shift値 (半音単位、符号付き8bit)
	     	db ? ; LFO DELAY 変動値
	     	db ? ;     SPEED 変動値
	     	db ? ;     STEP  変動値
	     	db ? ;     TIME  変動値
	     	db ? ;     DELAY 設定値
	     	db ? ;     SPEED 設定値
	     	db ? ;     STEP  設定値
	     	db ? ;     TIME  設定値
	     	db ? ; LFOSwitch B0/tone B1/vol B2/同期 B3/portament 1でON
	     	db ? ; Volume PUSH 値 (Wコマンド等で、一時的に音量を変えた時の値 +1)
	     	db ? ; MD command depth 値
	     	db ? ; MD command speed 変動値
	     	db ? ; MD command speed 設定値
	     	db ? ; 旧PSGエンベロープの状態 AL中=0 SR中=1 RR中=2 無し=3 新=-1
	     	db ? ; 新PSGエンベロープの状態 AR中=1 DR中=2 SR中=3 RR中=4 無し=0
	     	db ? ; PSGエンベロープ	新AR	旧AL
	     	db ? ;                  新DR	旧AD
	     	db ? ;                  新SR	旧SR
	     	db ? ;                  新RR	旧RR
	     	db ? ;                  新SL
	     	db ? ;                  新AL
	     	db ? ;                  新AR	旧AL	のカウンタ(変動値)
	     	db ? ;                  新DR		のカウンタ(変動値)
	     	db ? ;                  新SR	旧SR	のカウンタ(変動値)
	     	db ? ;                  新RR	旧RR	のカウンタ(変動値)
	     	db ? ;                  新音量値(0～15)	旧音量値(-15～+15)
	     	db ? ; 拡張フラグ B0:Detune B1:LFO1 B2:Envelope B5:LFO2 1で拡張
	     	db ? ; FM Panning + AMD + PMD / YM2608 0b4h～0b6hに出力する値と同じ
	     	db ? ; PSG の音色 [TONE/NOISE/MIX] YM2203/2608 07HにORする値と同じ
	     	db ? ; 音色番号
	     	db ? ; ループしたら１ 終了したら３
	     	db ? ; FM Carrier位置
	     	db ? ; SLOT 1 の TL値
	     	db ? ; SLOT 3 の TL値
	     	db ? ; SLOT 2 の TL値
	     	db ? ; SLOT 4 の TL値
	     	db ? ; FM slotmask値
	     	db ? ; FM 音色定義用maskdata値
	     	db ? ; LFOの波形 MWで指定する値と同じ
	     	db ? ; PartMask Bit0:INT60HのPart_Mask/1:効果音/6:mコマンド/7:早送り
	     	db ? ; bit0,2～7 / 0でkeyon 1でkeyoff中 , bit1 / 1でkeyoffさせない
	     	db ? ; 音量LFOのマスクslot
	     	db ? ; qの値
	     	db ? ; Qの値
	     	db ? ; HardLFO delay 設定値
	     	db ? ; HardLFO delay 変動値
	     	dw ? ; LFO2    ±値
	     	db ? ; LFO2    DELAY 変動値
	     	db ? ;         SPEED 変動値
	     	db ? ;         STEP  変動値
	     	db ? ;         TIME  変動値
	     	db ? ;         DELAY 設定値
	     	db ? ;         SPEED 設定値
	     	db ? ;         STEP  設定値
	     	db ? ;         TIME  設定値
	     	db ? ; LFO2 MDB command depth 値
	     	db ? ; LFO2 MDB command speed 変動値
	     	db ? ; LFO2 MDB command speed 設定値
	     	db ? ; LFO2 の波形 MWBで指定する値と同じ
	     	db ? ; 音量LFO2のマスクslot
	     	db ? ; LFO1 MDA Counter変動値
	     	db ? ; LFO1 MDA Counter設定値
	     	db ? ; LFO2 MDA Counter変動値
	     	db ? ; LFO2 MDA Counter設定値
	onkai	db ? ; 演奏中の音階　オクターブ×16 + 音階(c～b=0～11),rest=255
	     	db ? ; Slot delay
	     	db ? ; Slot delay counter
	     	db ? ; Slot delay Mask
	     	db ? ; 音色のalg/fb
	     	db ? ; 新音階/休符データを処理したらinc
	     	db ? ; q 最低保証値
	     	dw ? ; ppz8用fnum値上位
	     	db ? ; 演奏中音階データ (転調処理前 / ?fh:rest)
	     	db ? ; マスター転調値
	     	db ? ; q ランダム範囲
	     	db ? ; 予約
qq ends
