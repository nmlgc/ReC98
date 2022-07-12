; ReC98
; -----
; Types shared between TH04 and TH05

include th03/arg_bx.inc
include th02/score.inc

; Formats
; --------
include th04/formats/bb.inc
include th04/formats/cfg.inc
include th03/formats/cdg.inc
include th04/formats/map.inc
include th04/formats/scoredat.inc
; --------

include th04/main/player/player.inc

; Bombs
; -----
DEATHBOMB_WINDOW = 8
; -----

; Stages
; ------
MAIN_STAGE_COUNT = 6
STAGE_EXTRA = MAIN_STAGE_COUNT
STAGE_START_INVINCIBILITY_FRAMES = 64
; ------

; Bosses
; ------
BOSS_W = 64
BOSS_H = 64
BOSS_DEFEAT_INVINCIBILITY_FRAMES = 255
; ------

include th02/main/playfld.inc
include th02/main/hud/hud.inc
include th04/hardware/grcg.inc
include th04/hardware/input.inc
include th04/math/randring.inc
include th04/math/motion.inc
include th04/main/hud/overlay.inc
include th04/end/end.inc
