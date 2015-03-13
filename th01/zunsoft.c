/* ReC98
 * -----
 * ZUN Soft logo used in TH01, TH02 and TH03
 */

#include <master.h>

#define CIRCLE_COUNT 4
#define STAR_COUNT 50

const char LOGO_FILENAME[] = "touhou.dat";
static char CIRCLE_COLORS[] = {4, 3, 2, 1};

char page_write;
char page_show;
char tone;
char logo_num;
char wave_len;
char wave_phase;
char wave_amp;
Point circle_pos[CIRCLE_COUNT];
Point star_pos[STAR_COUNT];
int frame;
int circle_speed_x[CIRCLE_COUNT];
int circle_speed_y[CIRCLE_COUNT];
char star_angle;
unsigned char star_speed[STAR_COUNT];

void graph_clear_both(void)
{
	graph_accesspage(1);
	graph_clear();
	graph_accesspage(0);
	graph_clear();
	graph_showpage(0);
}

void zunsoft_init(void)
{
	mem_assign_all();
	graph_start();
	key_beep_off();
	text_systemline_hide();
	text_cursor_hide();
	egc_start();
	graph_clear_both();
	text_clear();
	page_write = 0;
	page_show = 1;
	grc_setclip(96, 100, 543, 299);
	graph_hide();
	super_entry_bfnt(LOGO_FILENAME);
	palette_show();
	palette_black();
	graph_show();
}

void zunsoft_exit(void)
{
	super_free();
	graph_clear_both();
	mem_unassign();
	text_clear();
	egc_start();
}

void pascal vector(int *dx, int *dy, unsigned char angle, int r)
{
	*dx = (r * (long)Cos8(angle)) >> 8;
	*dy = (r * (long)Sin8(angle)) >> 8;
}

void objects_setup(void)
{
	int i;

	circle_pos[0].x = 128;	circle_speed_x[0] = -8;
	circle_pos[0].y = 320;	circle_speed_y[0] = 8;

	circle_pos[1].x = 256;	circle_speed_x[1] = -8;
	circle_pos[1].y = 240;	circle_speed_y[1] = 8;

	circle_pos[2].x = 384;	circle_speed_x[2] = -8;
	circle_pos[2].y = 160;	circle_speed_y[2] = 8;

	circle_pos[3].x = 512;	circle_speed_x[3] = -8;
	circle_pos[3].y = 80;	circle_speed_y[3] = 8;

	frame = 0;
	tone = 0;
	logo_num = 0;
	wave_len = 23;
	wave_phase = 0;
	wave_amp = 0;

	for(i = 0; i < STAR_COUNT; i++) {
		star_pos[i].x = rand() % 640;
		star_pos[i].y = rand() % 400;
		star_speed[i] = (rand() % 32) + 6;
	}
	star_angle = 64;
}

void circles_render_and_update(void)
{
	int i = CIRCLE_COUNT - 1;
	while(i >= 0) {
		grcg_setcolor(GC_RMW, CIRCLE_COLORS[i]);
		grcg_circlefill(circle_pos[i].x, circle_pos[i].y, 96);

		circle_pos[i].x += circle_speed_x[i];
		circle_pos[i].y += circle_speed_y[i];
		if(circle_pos[i].x <= 32 || circle_pos[i].x > 607) {
			circle_speed_x[i] *= -1;
		}
		if(circle_pos[i].y <= 32 || circle_pos[i].y > 367) {
			circle_speed_y[i] *= -1;
		}
		i--;
	}
	grcg_off();
}

void stars_render_and_update(void)
{
	int i;
	grcg_setcolor(GC_RMW, 5);
	for(i = 0; i < STAR_COUNT; i++) {
		int dx, dy;

		grcg_pset(star_pos[i].x, star_pos[i].y);

		vector(&dx, &dy, star_angle, star_speed[i]);
		star_pos[i].x += dx;
		star_pos[i].y += dy;
		if(star_pos[i].x < 0) {
			star_pos[i].x += 640;
		} else if(star_pos[i].x >= 640) {
			star_pos[i].x -= 640;
		}
		if(star_pos[i].y < 0) {
			star_pos[i].y += 400;
		} else if(star_pos[i].y >= 400) {
			star_pos[i].y -= 400;
		}
	}
	star_angle++;
	grcg_off();
}

void wait(void)
{
	do {
		__asm out 0x5F, al
		__asm in  al, 0xA0
	} while((_AL & 0x20) != 0);
	do {
		__asm out 0x5F, al
		__asm in  al, 0xA0
	} while((_AL & 0x20) == 0);
}

void logo_render_and_update(void)
{
	if(frame < 50) {
		return;
	}
	if(frame < 90) {
		if(frame == 55 || frame == 60 || frame == 65) {
			logo_num += 2;
		}
		super_put_8(256, 192, logo_num+0);
		super_put_8(320, 192, logo_num+1);
	} else if(frame < 110) {
		super_wave_put(256, 192, logo_num+0, wave_len, wave_amp, wave_phase);
		super_wave_put(320, 192, logo_num+1, wave_len, wave_amp, wave_phase);
		wave_len--;
		wave_phase += 4;
		wave_amp += 4;
	} else if(frame < 130) {
		if(frame == 110) {
			logo_num += 2;
		}
		super_wave_put(256, 192, logo_num+0, wave_len, wave_amp, wave_phase);
		super_wave_put(320, 192, logo_num+1, wave_len, wave_amp, wave_phase);
		wave_len++;
		wave_phase += 4;
		wave_amp -= 4;
	} else if(frame < 170) {
		if(frame == 155 || frame == 160 || frame == 165) {
			logo_num += 2;
		}
		super_put_8(256, 192, logo_num+0);
		super_put_8(320, 192, logo_num+1);
	}
}

void main(void)
{
	int keygroup, quit;
	// Do some setup if we are running on a PC-9821
	__asm {
		xor  ax, ax
		mov  es, ax
		test byte ptr es:0x45C, 0x40
		jz   hw_setup_done
		mov  al, 0x7
		out  0x6a, al
		mov  al, 0x20
		out  0x6a, al
		mov  al, 0x6
		out  0x6a, al
		// Activate all graphics hardware in 16-color mode
		and  byte ptr es:0x54d, 0x7f
hw_setup_done:
	}
	zunsoft_init();
	objects_setup();
	while(1) {
		if(frame > 180) {
			if(tone <= 0) {
				break;
			}
			palette_settone(tone -= 2);
		} else if(tone < 100) {
			palette_settone(tone += 2);
		}

		grcg_setcolor(GC_RMW, 0);
		grcg_byteboxfill_x(12, 100, 67, 299);
		stars_render_and_update();
		circles_render_and_update();
		logo_render_and_update();
		wait();
		wait();
		__asm {
			mov al, page_write
			mov page_show, al
			out 0xa4, al
			xor page_write, 1
			mov al, page_write
			out 0xa6, al
		}
		quit = 0;
		for(keygroup = 0; keygroup < 8; keygroup++) {
			quit |= key_sense(keygroup);
		}
		if(quit) {
			break;
		}
		frame++;
	};
	zunsoft_exit();
}
