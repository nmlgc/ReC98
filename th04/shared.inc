; ReC98
; -----
; Types shared between TH04 and TH05

include defconv.inc

; Formats
; --------
include th04/formats/bb.inc
include th04/formats/map.inc
; --------

include th04/player/player.inc

; Bombs
; -----
DEATHBOMB_WINDOW = 8
; -----

; Stages
; ------
STAGE_START_INVINCIBILITY_FRAMES = 64
; ------

; Bosses
; ------
BOSS_DEFEAT_INVINCIBILITY_FRAMES = 255
; ------

include th02/hud/hud.inc
include th04/hardware/grcg.inc
include th04/hardware/input.inc
include th04/math/randring.inc
include th04/math/motion.inc
include th04/gaiji/gaiji.inc
include th04/hud/popup.inc
include th02/score.inc
