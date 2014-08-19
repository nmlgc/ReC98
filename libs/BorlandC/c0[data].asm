;       Magic symbol used by the debug info to locate the data segment
                public DATASEG@
DATASEG@        label   byte

;       The Check string must NOT be moved or changed without
;       changing the null pointer check logic

IFNDEF  __TINY__
NULL            db       4 dup(0)
CheckStr        db      'NULL CHECK'
                db       2 dup (0)
                db       4 dup (0)              ;destructor count
                db       2 dup (0)              ;exception list
                db       4 dup (0)              ;exception vptr
                db       6 dup (0)              ;reserved
ENDIF

CopyRight       db      'Borland C++ - Copyright 1993 Borland Intl.',0

IF      LDATA EQ false
IFNDEF  __TINY__
CheckSum        equ     002B9h
NullCheck       db      'Null pointer assignment', 13, 10, 0
ENDIF
ENDIF

ZeroDivMSG      db      'Divide error', 13, 10, 0
;                       Interrupt vector save areas
;       Interrupt vectors 0,4,5 & 6 are saved at startup and then restored
;       when the program terminates.  The signal/raise functions might
;       steal these vectors during execution.
;       Note: These vectors save area must not be altered
;             without changing the save/restore logic.
PubSym@         _Int0Vector     <dd     0>,             __CDECL__
PubSym@         _Int4Vector     <dd     0>,             __CDECL__
PubSym@         _Int5Vector     <dd     0>,             __CDECL__
PubSym@         _Int6Vector     <dd     0>,             __CDECL__
;                       Miscellaneous variables
PubSym@         _C0argc,        <dw     0>,             __CDECL__
dPtrPub@        _C0argv,        0,                      __CDECL__
dPtrPub@        _C0environ,     0,                      __CDECL__
PubSym@         _envLng,        <dw     0>,             __CDECL__
PubSym@         _envseg,        <dw     0>,             __CDECL__
PubSym@         _envSize,       <dw     0>,             __CDECL__
PubSym@         _psp,           <dw     0>,             __CDECL__
PubSym@         _version,       <label word>,           __CDECL__
PubSym@         _osversion,     <label word>,           __CDECL__
PubSym@         _osmajor,       <db     0>,             __CDECL__
PubSym@         _osminor,       <db     0>,             __CDECL__
PubSym@         errno,          <dw     0>,             __CDECL__
PubSym@         _Exception_list,<dw    -1>,             __CDECL__


;       Memory management variables

IF      LDATA EQ false
PubSym@         __heapbase,     <dw   DGROUP:edata@>,   __CDECL__
ENDIF
IFNDEF __HUGE__
PubSym@         __brklvl,       <dw   DGROUP:edata@>,   __CDECL__
ENDIF
PubSym@         _heapbase,      <dd   0>,       __CDECL__
PubSym@         _brklvl,        <dd   0>,       __CDECL__
PubSym@         _heaptop,       <dd   0>,       __CDECL__

;       If stack in DS and Large data model then override location of __emu

IFDEF   _DSSTACK_
IF      LDATA
public  __emu
__emu   db      044h    DUP (0)
        db      0CCh    DUP (?)
ENDIF
ENDIF
