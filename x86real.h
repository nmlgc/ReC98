// ReC98
// -----
// Declarations for 16-bit x86 Real Mode features: I/O ports, CPU registers,
// interrupts, certain instructions, and segmented memory. Ports to other
// architectures would remove this file and rewrite any code that then causes
// compile errors.

// This is a subset of Turbo C++ 4.0's <dos.h>.
#if !(defined(__TURBOC__) && defined(__MSDOS__) && defined(__DOS_H))

/// Opcodes
/// -------

void __emit__(uint8_t __byte, ...);
void __int__(int16_t __interruptnum);

#define disable()       __emit__((uint8_t)(0xfa)) /* MSC name */
#define enable()        __emit__((uint8_t)(0xfb)) /* MSC name */
#define geninterrupt(i) __int__(i)      /* Interrupt instruction */
/// -------

/// I/O ports
/// ---------

uint8_t  __inportb__(uint16_t __portid);
uint16_t __inportw__(uint16_t __portid);
uint8_t  __outportb__(uint16_t __portid,  uint8_t __value);
uint16_t __outportw__(uint16_t __portid, uint16_t __value);

#define inport(__portid)            __inportw__(__portid)
#define inportb(__portid)           __inportb__(__portid)
#define outport(__portid, __value)  ((void) __outportw__(__portid, __value))
#define outportb(__portid, __value) ((void) __outportb__(__portid, __value))
/// ---------

/// Registers
/// ---------

struct WORDREGS {
    uint16_t ax;
    uint16_t bx;
    uint16_t cx;
    uint16_t dx;
    uint16_t si;
    uint16_t di;
    uint16_t cflag;
    uint16_t flags;
};

struct BYTEREGS {
    uint8_t al;
    uint8_t ah;
    uint8_t bl;
    uint8_t bh;
    uint8_t cl;
    uint8_t ch;
    uint8_t dl;
    uint8_t dh;
};

union REGS {
    struct WORDREGS  w;
    struct BYTEREGS  h;
};

struct SREGS {
    uint16_t es;
    uint16_t cs;
    uint16_t ss;
    uint16_t ds;
};

void segread(struct SREGS *__segp);
/// ---------

/// Interrupts
/// ----------

#ifdef __cplusplus
    void interrupt (__far * getvect(int __interruptno))(...);
    void setvect(int __interruptno, void interrupt (__far *__isr)(...));
#else
    void interrupt (__far * getvect(int __interruptno))();
    void setvect(int __interruptno, void interrupt(__far *__isr)());
#endif

int int86(int __intno, union REGS *__inregs, union REGS *__outregs);
/// ----------

/// Segmented memory
/// ----------------

#define MK_FP(seg,ofs) ((void __seg *)(seg) + (void __near *)(ofs))
#define FP_SEG(fp)     ((uint16_t)(void __seg *)(void __far *)(fp))
#define FP_OFF(fp)     ((uint16_t)(fp))

#define peek(a,b)    (*((int16_t __far * )MK_FP((a),(b))))
#define peekb(a,b)   (*(( int8_t __far * )MK_FP((a),(b))))
#define poke(a,b,c)  (*((int16_t __far * )MK_FP((a),(b))) = (int16_t)(c))
#define pokeb(a,b,c) (*(( int8_t __far * )MK_FP((a),(b))) = ( int8_t)(c))
/// ----------------

#endif
