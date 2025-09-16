HALFHEARTS_MAX = 10

ROUND_START_INVINCIBILITY_FRAMES = 50

MISS_INVINCIBILITY_FRAMES = 110
MISS_DAMAGE_MAX = 6
KNOCKBACK_FRAMES = 64

SPELL_AUTOFIRE_FRAMES = 128
CHARGE_AT_AVAIL_RING_SIZE = 64

GAUGE_MAX = (0FFh shl 4)

player_stuff_t struc
	center	Point ?
	is_hit	db ?
	PLAYER_unused_1	db ?
	invincibility_time db ?
	halfhearts	db ?
	playchar_paletted	db ?
	speed_base	speed_t <?>
	shot_mode	 db ?
	patnum_movement	db ?
	patnum_glow db ?
	knockback_time	db ?
	move_lock_time	db ?
	knockback_angle db ?
	knockback_length db ?
	knockback_active db ?
	is_cpu	db ?
	cpu_dodge_strategy db ?
	gauge_charge_speed db ?
	gauge_charged	 dw ?
	gauge_avail	 dw ?
	cpu_charge_at_avail_ring_p db ?
	bombs	 db ?
	hyper_active	db ?
	lose_anim_time	db ?
	human_movement_last dw ?
	shot_active	db ?
	spell_ready_frames db ?
	cpu_charge_at_avail_ring db CHARGE_AT_AVAIL_RING_SIZE dup(?)
	hyper	 dw ?
	hyper_func	dw ?
	chargeshot_add	dd ?
	rounds_won	db ?
		align 2
	cpu_safety_frames dw ?
	combo_bonus_max dw ?
	combo_hits_max	db ?
	miss_damage_next db ?
	cpu_frame	 dw ?
	gauge_attacks_fired db ?
	boss_attacks_fired db ?
	boss_attacks_reversed db ?
	boss_panics_fired db ?
		align 16
player_stuff_t ends

public _p1, _p2, _players
_players label player_stuff_t
_p1	player_stuff_t <?>
_p2	player_stuff_t <?>
