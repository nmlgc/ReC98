GAME = 5
include th04/shared.inc

include th05/player/shot_types.inc
; Shot cycle bitflags
SC_1X = 08h ; Triggered 1× per cycle
SC_2X = 02h ; Triggered 2× per cycle
SC_3X = 01h ; Triggered 3× per cycle
SC_6X = 04h ; Triggered 6× per cycle

_player_option_patnum = 26

POINT_ITEMS_MAX = 999
