include libs/master.lib/macros.inc

SPARK_W = 8
SPARK_H = 8
SPARK_VRAM_W = (16 / 8)
SPARK_SIZE = (SPARK_VRAM_W * SPARK_H)
SPARK_CELS = 8

if (GAME eq 2)
	SRA_DOT = 0
	SRA_SPRITE = 14

	SPARK_COUNT = 64

	spark_t struc
		SPARK_flag             	db ?
		SPARK_age              	db ?
		SPARK_screen_topleft   	Point 2 dup(<?>)
		SPARK_velocity         	Point <?>
		SPARK_render_as        	db ?
			db ?
		SPARK_angle            	db ?
		SPARK_speed_base       	db ?
			db ?
		SPARK_default_render_as	db ?
	spark_t ends
endif
