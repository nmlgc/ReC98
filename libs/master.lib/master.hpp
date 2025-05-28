// C++ declarations and ReC98-specific extensions for the subset of master.lib
// used by the original game code.

#ifndef MASTER_HPP
#define MASTER_HPP

#include "libs/master.lib/func.hpp"

/// Original functions (only contains those actually called from ZUN code)
/// ----------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

// "BGM" (only used for Beep sound effects)
// ----------------------------------------

int MASTER_RET bgm_init(int bufsiz);
void MASTER_RET bgm_finish(void);
int MASTER_RET bgm_read_sdata(const char MASTER_PTR *fn);
int MASTER_RET bgm_sound(int num);
// ----------------------------------------

// DOS
// ---
// These use INT 21h syscalls as directly as possible.

int MASTER_RET dos_getch(void);
void MASTER_RET dos_putch(int chr);
void MASTER_RET dos_puts(const char MASTER_PTR * str);
void MASTER_RET dos_puts2(const char MASTER_PTR *string);

void MASTER_RET dos_free(void __seg *seg);
int MASTER_RET dos_create(const char MASTER_PTR *filename, int attrib);
int MASTER_RET dos_close(int fh);
int MASTER_RET dos_write(int fh, const void far *buffer, unsigned len);
long MASTER_RET dos_seek(int fh, long offs, int mode);

long MASTER_RET dos_axdx(int axval, const char MASTER_PTR *strval);
// ---

// EMS
// ---

unsigned MASTER_RET ems_allocate(unsigned long len);
int MASTER_RET ems_exist(void);
int MASTER_RET ems_read(unsigned handle, long offset, void far *mem, long size);
int MASTER_RET ems_setname(unsigned handle, const char MASTER_PTR * name);
unsigned long MASTER_RET ems_space(void);
int MASTER_RET ems_write(
	unsigned handle, long offset, const void far *mem, long size
);
// ---

// Joystick
// --------

extern int js_bexist;
extern unsigned js_stat[2];

int MASTER_RET js_start();	// ZUN removed the [force] parameter

void MASTER_RET js_end(void);
int MASTER_RET js_sense(void);
// --------

// Keyboard
// --------

void MASTER_RET key_start(void);
void MASTER_RET key_end(void);

void MASTER_RET key_beep_on(void);
void MASTER_RET key_beep_off(void);
int MASTER_RET key_sense(int keygroup);

unsigned MASTER_RET key_sense_bios(void);
// --------

// Heap
// ----

void MASTER_RET mem_assign(unsigned top_seg, unsigned parasize);
void MASTER_RET mem_assign_all(void);
int MASTER_RET mem_unassign(void);
int MASTER_RET mem_assign_dos(unsigned parasize);

// Regular
void __seg* MASTER_RET hmem_allocbyte(unsigned bytesize);
void MASTER_RET hmem_free(void __seg* memseg);
// Fast
void __seg* MASTER_RET smem_wget(unsigned bytesize);
void MASTER_RET smem_release(void __seg* memseg);
// ----

// Machine identification
// ----------------------

extern const unsigned __cdecl Machine_State;

unsigned MASTER_RET get_machine(void);

#define PC_AT        	0x0010
#define PC9801       	0x0020
#define FMR          	0x0080	/* 0.23追加 */
#define DOSBOX       	0x8000	/* 0.22k追加 */

#define DESKTOP      	0x0001
#define EPSON        	0x0002
#define PC_MATE      	0x0004
#define HIRESO       	0x0008

#define LANG_US      	0x0001
#define PC_TYPE_MASK 	0x000e
#define PS55         	0x0000
#define DOSV         	0x0002
#define PC_AX        	0x0004
#define J3100        	0x0006
#define DR_DOS       	0x0008
#define MSDOSV       	0x000a
#define VTEXT        	0x0240	/* 0.23追加 */
#define DOSVEXTENTION	0x0040	/* 0.22d追加 */
#define SUPERDRIVERS 	0x0200	/* 0.23追加 */
#define ANSISYS      	0x0100	/* 0.22d追加 */
// ----------------------

// Math
// ----

extern const short __cdecl SinTable8[256], CosTable8[256];
extern long __cdecl random_seed;

#define Sin8(t) SinTable8[(t) & 0xff]
#define Cos8(t) CosTable8[(t) & 0xff]

int MASTER_RET iatan2(int y, int x);
int MASTER_RET isqrt(long x);
int MASTER_RET ihypot(int x, int y);

#define irand_init(seed) \
	(random_seed = (seed))
int MASTER_RET irand(void);
// ----

// Optionally buffered single-file I/O
// -----------------------------------

#define SEEK_CUR    1
#define SEEK_END    2
#define SEEK_SET    0

int MASTER_RET file_ropen(const char MASTER_PTR *filename);
int MASTER_RET file_read(void far *buf, unsigned wsize);
long MASTER_RET file_size(void);
int MASTER_RET file_create(const char MASTER_PTR *filename);
int MASTER_RET file_append(const char MASTER_PTR *filename);
int MASTER_RET file_write(const void far *buf, unsigned wsize);
void MASTER_RET file_seek(long pos, int dir);
void MASTER_RET file_close(void);
int MASTER_RET file_exist(const char MASTER_PTR *filename);
int MASTER_RET file_delete(const char MASTER_PTR *filename);
// -----------------------------------

// Packfiles
// ---------

extern unsigned char __cdecl pfkey; // 復号化キー
extern unsigned __cdecl bbufsiz;    // バッファサイズ

void MASTER_RET pfstart(const unsigned char MASTER_PTR *parfile);
void MASTER_RET pfend(void);
#define pfsetbufsiz(bufsiz) \
	bbufsiz = bufsiz;
// ---------

// Resident data
// -------------

void __seg* MASTER_RET resdata_exist(
      const char MASTER_PTR *id, unsigned idlen, unsigned parasize
);
void __seg* MASTER_RET resdata_create(
      const char MASTER_PTR *id, unsigned idlen, unsigned parasize
);

#define resdata_free(seg) \
	dos_free(seg)
// -------------

// Resident palettes
// -----------------

int MASTER_RET respal_exist(void);
int MASTER_RET respal_create(void);
void MASTER_RET respal_get_palettes(void);
void MASTER_RET respal_set_palettes(void);
void MASTER_RET respal_free(void);
// -----------------

// VSync
// -----

// Incremented by 1 on every VSync interrupt. Can be manually reset to 0 to
// simplify frame delay loops.
extern volatile unsigned int __cdecl vsync_Count1, vsync_Count2;

void MASTER_RET vsync_start(void);
void MASTER_RET vsync_end(void);
// -----
#ifdef __cplusplus
}
#endif
/// ----------------------------------------------------------------------

/// Inlined extensions
/// ------------------

#ifdef __cplusplus
// Type-safe hmem_* memory allocation
template<class T> struct HMem {
	static T __seg* alloc(unsigned int size_in_elements) {
		return reinterpret_cast<T __seg *>(hmem_allocbyte(
			size_in_elements * sizeof(T)
		));
	}

	static void free(T far *&block) {
		hmem_free(reinterpret_cast<void __seg *>(block));
	}

	static void free(T __seg *&block) {
		hmem_free(reinterpret_cast<void __seg *>(block));
	}
};

// Type-safe resident structure allocation and retrieval
template <class T> struct ResData {
	static unsigned int id_len() {
		return (sizeof(reinterpret_cast<T *>(0)->id) - 1);
	}

	static T __seg* create(const char MASTER_PTR *id) {
		return reinterpret_cast<T __seg *>(resdata_create(
			id, id_len(), ((sizeof(T) + 0xF) >> 4)
		));
	}

	static T __seg* exist(const char MASTER_PTR *id) {
		return reinterpret_cast<T __seg *>(resdata_exist(
			id, id_len(), ((sizeof(T) + 0xF) >> 4)
		));
	}

	// Workarounds for correct code generation
	static T __seg* create_with_id_from_pointer(const char *&id) {
		return reinterpret_cast<T __seg *>(resdata_create(
			id, id_len(), ((sizeof(T) + 0xF) >> 4)
		));
	}

	static T __seg* exist_with_id_from_pointer(const char *&id) {
		return reinterpret_cast<T __seg *>(resdata_exist(
			id, id_len(), ((sizeof(T) + 0xF) >> 4)
		));
	}
};
#endif
/// ------------------

#endif /* MASTER_HPP */
