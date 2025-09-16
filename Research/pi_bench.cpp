// .PI loading and blitting benchmark
// ----------------------------------

#include "libs/master.lib/master.hpp"
#include "libs/master.lib/pc98_gfx.hpp"
#include "libs/piloadc/piloadm.hpp"
#include "platform/x86real/pc98/blit_low.hpp"
#include "platform/x86real/pc98/graph.hpp"
#include <mem.h>
#include <stdio.h>

void report_pi_error(int ret)
{
	switch(ret) {
	case FileNotFound:
		printf("file not found\n");
		break;
	case InsufficientMemory:
		printf("insufficient memory\n");
		break;
	case InvalidData:
		printf("invalid data\n");
		break;
	}
}

static char near PiLoadBuffer[0x4000];

int piload_blit(const char *fn, PiHeader *, void far **)
{
	if(!file_ropen(fn)) {
		return FileNotFound;
	}
	int ret = PiBlit(PiLoadBuffer, sizeof(PiLoadBuffer), 0, 0, 0, file_read);
	file_close();
	return ret;
}

int piload_load_load(const char *fn, PiHeader *header, void far **pixels)
{
	const char *buf_aligned;
	if(!file_ropen(fn)) {
		return FileNotFound;
	}
	int ret = PiLoadHeader(PiLoadBuffer, sizeof(PiLoadBuffer), file_read, 0);
	if(ret < 0) {
		goto err_with_file;
	}
	*pixels = hmem_alloc(ret);
	if(*pixels == nullptr) {
		ret = InsufficientMemory;
		goto err_with_file;
	}
	// Very ugly...
	header->maexlen = (static_cast<uint16_t>(ret) / PLANE_COUNT);

	ret = PiLoadPlanes(FP_SEG(*pixels), PiLoadBuffer, sizeof(PiLoadBuffer));
	buf_aligned = reinterpret_cast<const char near *>(
		(FP_OFF(PiLoadBuffer) + 15) & ~15
	);
	header->xsize = *reinterpret_cast<const uint16_t *>(buf_aligned + 0x134);
	header->ysize = *reinterpret_cast<const uint16_t *>(buf_aligned + 0x136);
	header->palette = *reinterpret_cast<const Palette8 *>(buf_aligned + 0x100);
err_with_file:
	file_close();
	return ret;
}

void piload_load_blit(const PiHeader *header, const void far *pixels)
{
	const vram_byte_amount_t vram_w = (header->xsize / BYTE_DOTS);
	const uint16_t plane_size = header->maexlen;
	blit_source.dots_start.fp = pixels;
	blitter_set_source_region(0, 0, vram_w, header->ysize, vram_w);
	const Blitter __ds& b = blitter_init_noclip(0, 0);
	b.write(SEG_PLANE_B);
	blit_source.dots_start.part.seg += plane_size;
	b.write(SEG_PLANE_R);
	blit_source.dots_start.part.seg += plane_size;
	b.write(SEG_PLANE_G);
	blit_source.dots_start.part.seg += plane_size;
	b.write(SEG_PLANE_E);
}

void piload_load_free(PiHeader *, void far *pixels)
{
	hmem_free(reinterpret_cast<void __seg *>(pixels));
}

void master_blit(const PiHeader *header, const void far *pixels)
{
	const uint8_t huge *row_p = static_cast<const uint8_t far *>(pixels);
	for(screen_x_t y = 0; y < header->ysize; y++) {
		graph_pack_put_8(0, y, row_p, header->xsize);
		row_p += (header->xsize / 2);
	}
}

void master_free(PiHeader *header, void far *pixels)
{
	graph_pi_free(header, pixels);
}

int pi_bench(
	int (*load_func)(const char *, PiHeader *, void far **),
	void (*blit_func)(const PiHeader *, const void far *),
	void (*free_func)(PiHeader *, void far *),
	const char *category,
	const char *fn
)
{
	const char *load_label = (blit_func ? "Load" : "Load and blit");
	PiHeader header;
	void far *pixels = nullptr;

	vsync_wait();
	vsync_Count1 = 0;
	int ret = load_func(fn, &header, &pixels);
	if(ret != NoError) {
		report_pi_error(ret);
		return ret;
	}
	printf("\n* %s:\n", category);
	printf("  * %s: %d frames", load_label, vsync_Count1);

	if(blit_func) {
		vsync_wait();
		vsync_Count1 = 0;
		palette_set_all(header.palette);
		palette_show();
		blit_func(&header, pixels);
		printf("\n  * Blit: %d frames", vsync_Count1);
	}

	if(free_func) {
		free_func(&header, &pixels);
	}

	return ret;
}

int __cdecl main(int argc, char **argv)
{
	graph_accesspage(0);
	graph_showpage(0);
	if(argc == 1) {
		printf("Usage: %s file.pi [file.pi...]", argv[0]);
		return 1;
	}

	blitter_use_write_640();

	graph_show_16color_400line();
	vsync_start();
	for (int i = 1; i < argc; ++i) {
		if(i != 1) {
			printf("\n");
		}
		printf("%s: ", argv[i]);
		graph_clear();
		if(pi_bench(
			graph_pi_load_pack,
			master_blit,
			master_free,
			"master.lib graph_pi_load_pack() / graph_pack_put_8()",
			argv[i]
		)) {
			continue;
		}
		graph_clear();
		if(pi_bench(
			piload_blit, nullptr, nullptr, "PiLoad (directly to VRAM)", argv[i]
		)) {
			continue;
		}
		graph_clear();
		if(pi_bench(
			piload_load_load,
			piload_load_blit,
			piload_load_free,
			"PiLoad (via main memory)",
			argv[i]
		)) {
			continue;
		}
	}
	vsync_end();
	return 0;
}
