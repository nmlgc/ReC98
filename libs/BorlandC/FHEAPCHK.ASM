; *Not* the original file, but an edit to turn it into an includable slice.
; The following things were removed:
; * RULES.ASI to eliminate redundancy
; * any extern data declarations
; * the 'CODE' segment declaration (for obvious reasons)
; * the ARG directives (they don't compile correctly for some reason)
; * PROC DIST and LABEL DIST (replaced with just PROC and LABEL PROC,
;   respectively)

;[]-----------------------------------------------------------------[]
;|      FEAPCHK.ASM                                                  |
;[]-----------------------------------------------------------------[]

;
;       C/C++ Run Time Library - Version 5.0
; 
;       Copyright (c) 1987, 1992 by Borland International
;       All Rights Reserved.
; 

        INCLUDE _HEAP.INC

IF LPROG
  EXTRADISP     equ     2         ; Allow for FAR returns when getting parms
ELSE
  EXTRADISP     equ     0
ENDIF

;-----------------------------------------------------------------------
; Memory Block Header (far heap)
;-----------------------------------------------------------------------
; Each block in the heap, whether allocated or free, has a header.
; For an allocated block, only the first two fields of the header are
; used. For a free block all ten bytes are used.  Blocks are aligned on
; paragraph boundaries, thus the smallest possible block sixteen bytes.
;
; Field       Description
; ---------   ----------------------------------------------------------
; size        total size, in paragraphs, of this block
; prev_real   segment of the physically previous block in the heap
;             prev_real is 0 this block is free, get the prev_real from prev_real2
; prev_free   segment of the logically previous free block
; next_free   segment of the logically next free block
; prev_real2  segment of the physically previous block in the heap
; free_space  first byte of free space available
;
; A doubly-linked queue is maintained of the free blocks and it is important
; to know that ordering of the blocks in this queue is logical rather than
; physical.  If there is only one free block on the heap prev_free and
; next_free point to itself.
;-----------------------------------------------------------------------
bsize           EQU     0
prev_real       EQU     2
prev_free       EQU     4
next_free       EQU     6
prev_real2      EQU     8
free_space      EQU     10

;-----------------------------------------------------------------------
; heapinfo structure (far heap)
;-----------------------------------------------------------------------
; Used by the heapwalk function.
; heapwalk accepts a pointer to a struct of this type.
; On entry, the pointer field contains the address of the previous
; memory block in the heap (NULL for the first call).  The next block
; in the heap is then found and its address is stored in the structure
; along with its size, in bytes, and a 'used' flag.
;-----------------------------------------------------------------------
HeapInfo        STRUC
hi_ptr          dd      ?
hi_size         dd      ?
hi_inuse        dw      ?
                ENDS

UsedHeaderSize  EQU     4
FreeHeaderSize  EQU     10

;-----------------------------------------------------------------------------
; C callable function which checks and verifies the heap.
; Walk through the physical heap and free block queue checking for
; bad links, adjacent free blocks, and sum the free block sizes both
; ways.  If the physical free block sum does not equal the free-block
; queue sum, there is an error.
;
; Args:                 void
; Returns:              _HEAPEMPTY, _HEAPOK, or _HEAPCORRUPT in ax
;-----------------------------------------------------------------------------
IF LDATA
                PUBLIC  _heapcheck
_heapcheck      LABEL   PROC
ENDIF
                PUBLIC  _farheapcheck
_farheapcheck   PROC
                push    si
                push    di
                push    bp
                push    ds

                mov     ax,cs:[___first]
                or      ax,ax
                jnz     @@HeapNotEmpty
                jmp     @@EmptyHeap

@@HeapNotEmpty:
                xor     bx,bx
                push    bx
                push    bx
                call    __sbrk                  ;retrieve the break level
                add     sp,4
                or      ax,ax
                jz      @@GoodOffset
                jmp     @@HeapCorrupt
@@GoodOffset:
                mov     bx,cs:[___last]
                mov     ds,bx
                add     bx,ds:[bsize]
                cmp     bx,dx
                je      @@CheckHeap
                jmp     @@HeapCorrupt
@@CheckHeap:
                mov     ax,cs:[___first]

                xor     cx,cx                   ;cx = sum of physical free
                mov     dx,cx                   ;dx = sum of logical free

                mov     ds,ax                   ;ds = first block in the heap
                add     ax,WORD PTR ds:[bsize]
                mov     es,ax                   ;ax,es = next block in the heap
@@SearchPhysicalLinks:
                cmp     WORD PTR ds:[prev_real],0  ;is this block used?
                jne     @@CheckPhysicalLinks       ;yep, skip this section
                add     cx,ds:[bsize]
                mov     si,ds                   ;si = ds
                cmp     si,cs:[___last]         ;end-of-heap?
                je      @@QueueCheck
                cmp     WORD PTR es:[prev_real],0  ;is the next block free?
                jnz     @@CheckPhysicalLinks
                jmp     @@HeapCorrupt
@@CheckPhysicalLinks:
                mov     si,ds                   ;si = ds
                mov     di,es                   ;di = es
                cmp     si,cs:[___last]         ;end-of-heap?
                je      @@QueueCheck
                cmp     si,di                   ;check those links!
                je      @@HeapCorrupt
                cmp     WORD PTR ds:[bsize],0
                je      @@HeapCorrupt
                cmp     di,cs:[___first]
                jbe     @@HeapCorrupt
                cmp     di,cs:[___last]
                ja      @@HeapCorrupt
                cmp     WORD PTR es:[prev_real],0
                je      @@NextBlockIsFree
@@NextBlockIsUsed:
                cmp     es:[prev_real],si
                jmp     @@CheckPrevReal
@@NextBlockIsFree:
                cmp     es:[prev_real2],si
@@CheckPrevReal:
                jne     @@HeapCorrupt
                mov     ds,di                   ;ds = es
                add     di,WORD PTR ds:[bsize]
                mov     es,di                   ;es = next block in the heap
                jmp     SHORT @@SearchPhysicalLinks

@@QueueCheck:
                mov     ax,cs:[___rover]        ;ax = rover pointer
                or      ax,ax
                jz      @@EvaluateResults
                mov     ds,ax                   ;ds = free block
                mov     si,ax                   ;si = ds
@@QueueLoop:
                cmp     WORD PTR ds:[prev_real],0       ;this block should be free
                jne     @@HeapCorrupt
                cmp     si,cs:[___first]
                jb      @@HeapCorrupt
                cmp     si,cs:[___last]
                jae     @@HeapCorrupt
                add     dx,ds:[bsize]           ;dx += size of this block
                mov     es,ds:[next_free]       ;es = next free block
                mov     di,es                   ;di = es
                cmp     di,ax                   ;done?
                je      @@EvaluateResults
                cmp     si,di                   ;check those links?
                je      @@HeapCorrupt
                cmp     es:[prev_free],si
                jne     @@HeapCorrupt
                mov     si,es                   ;ds = es
                mov     ds,si
                jmp     SHORT @@QueueLoop

@@HeapCorrupt:
                mov     ax,_HEAPCORRUPT
                jmp     SHORT @@AllDone
@@EmptyHeap:
                mov     ax,_HEAPEMPTY
                jmp     SHORT @@AllDone

@@EvaluateResults:
                cmp     cx,dx
                jne     @@HeapCorrupt
@@HeapOK:
                mov     ax,_HEAPOK
@@AllDone:
                pop     ds
                pop     bp
                pop     di
                pop     si
                ret
                ENDP

;-----------------------------------------------------------------------------
; C callable function which checks and verifies a node on the heap.
;-----------------------------------------------------------------------------
; Args:                 node to check (stack)
; Returns:              _HEAPCORRUPT, _BADNODE, _FREEENTRY, or _USEDENTRY in ax
;-----------------------------------------------------------------------------
IF LDATA
                PUBLIC  _heapchecknode
_heapchecknode  LABEL   PROC
ENDIF
                PUBLIC  _farheapchecknode
_farheapchecknode       PROC

                push    bp
                mov     bp,sp
                push    si
                push    di
                push    ds

                call    _farheapcheck           ;make sure heap is OK first
                cmp     ax, _HEAPOK
                jne     @@AllDone

                mov     ax,[bp+8]               ;ax = segment to search for

                mov     si,cs:[___first]        ;si = first block
                mov     di,cs:[___last]         ;di = last block
                mov     bx,si                   ;bx = first block

@@SearchPhysicalLinks:
                mov     ds,bx
                cmp     bx,ax                   ;is this it?
                je      @@Found
                cmp     WORD PTR ds:[prev_real],0
                je      @@BlockIsFree
@@BlockIsUsed:
                cmp     ds:[prev_real],si
                jb      @@HeapCorrupt
                jmp     SHORT @@Around
@@BlockIsFree:
                cmp     ds:[prev_real2],si
                jb      @@HeapCorrupt
@@Around:
                cmp     bx,di
                je      @@NotFound
                ja      @@HeapCorrupt
                mov     cx,bx
                add     bx,ds:[bsize]
                cmp     bx,cx
                jne     @@SearchPhysicalLinks
@@HeapCorrupt:
                mov     ax,_HEAPCORRUPT
                jmp     SHORT @@AllDone
@@EmptyHeap:
                mov     ax,_HEAPEMPTY
                jmp     SHORT @@AllDone
@@NotFound:
                mov     ax,_BADNODE
                jmp     SHORT @@AllDone
@@Found:
                cmp     WORD PTR ds:[prev_real],0
                jnz     @@UsedEntry
@@FreeEntry:
                mov     ax,_FREEENTRY
                jmp     SHORT @@AllDone
@@UsedEntry:
                mov     ax,_USEDENTRY
@@AllDone:
                pop     ds
                pop     di
                pop     si
                pop     bp
                ret
                ENDP

;-----------------------------------------------------------------------------
; C callable function which fills the free areas with a given value
;-----------------------------------------------------------------------------
; Args:                 unsigned int, fill value (stack)
; Returns:              _HEAPEMPTY, _HEAPOK, or _HEAPCORRUPT in ax
;-----------------------------------------------------------------------------
IF LDATA
                PUBLIC  _heapfillfree
_heapfillfree   LABEL   PROC
ENDIF
                PUBLIC  _farheapfillfree
_farheapfillfree        PROC

                push    bp
                mov     bp,sp
                push    si
                push    di

                call    _farheapcheck           ;make sure heap is OK first
                cmp     ax, _HEAPOK
                jne     @@AllDone

                mov     bx,cs:___rover          ;bx = rover pointer
                or      bx,bx
                jz      @@HeapOK

                cld
                mov     ax,[bp+6]               ;ax = fill value
@@QueueLoop:
                mov     es,bx                   ;es,bx = free block
                mov     dx,es:[bsize]           ;dx = size of block (in para)
                mov     si,es:[next_free]       ;si = next free block
                mov     di,free_space
                mov     cx,8 - (free_space/2)
@@FillHerUp:
                rep
                stosw
                xor     di,di
                mov     cx,8
                inc     bx
                mov     es,bx
                dec     dx
                jnz     @@FillHerUp
@@NextBlock:
                cmp     si,cs:[___rover]
                je      @@HeapOK
                or      si,si
                jz      @@HeapCorrupt
                mov     bx,si
                jmp     SHORT @@QueueLoop

@@HeapCorrupt:
                mov     ax,_HEAPCORRUPT
                jmp     SHORT @@AllDone
@@EmptyHeap:
                mov     ax,_HEAPEMPTY
                jmp     SHORT @@AllDone
@@HeapOK:
                mov     ax,_HEAPOK
@@AllDone:
                pop     di
                pop     si
                pop     bp
                ret
                ENDP

;-----------------------------------------------------------------------------
; C callable function which checks the free areas of the heap for a given value
;-----------------------------------------------------------------------------
; Args:                 unsigned int, fill value (stack)
; Returns:              _HEAPOK, _HEAPEMPTY, _BADVALUE, or _HEAPCORRUPT in ax
;-----------------------------------------------------------------------------
IF LDATA
                PUBLIC  _heapcheckfree
_heapcheckfree  LABEL   PROC
ENDIF
                PUBLIC  _farheapcheckfree
_farheapcheckfree       PROC

                push    bp
                mov     bp,sp
                push    si
                push    di

                call    _farheapcheck           ;make sure heap is OK first
                cmp     ax, _HEAPOK
                jne     @@AllDone

                mov     bx,cs:___rover          ;bx = rover pointer
                or      bx,bx
                jz      @@HeapOK

                mov     ax,[bp+6]               ;ax = fill value
                cld
@@QueueLoop:
                mov     es,bx                   ;es,bx = free block
                mov     dx,es:[bsize]           ;dx = size of block (in para)
                mov     si,es:[next_free]       ;si = next free block
                mov     di,free_space
                mov     cx,8 - (free_space/2)
@@CheckHerOut:
                repe
                scasw
                jnz     @@BadValue
                xor     di,di
                mov     cx,8
                inc     bx
                mov     es,bx
                dec     dx
                jnz     @@CheckHerOut
@@NextBlock:
                cmp     si,cs:[___rover]
                je      @@HeapOK
                or      si,si
                jz      @@HeapCorrupt
                mov     bx,si
                jmp     SHORT @@QueueLoop

@@BadValue:
                mov     ax,_BADVALUE
                jmp     SHORT @@AllDone
@@HeapCorrupt:
                mov     ax,_HEAPCORRUPT
                jmp     SHORT @@AllDone
@@EmptyHeap:
                mov     ax,_HEAPEMPTY
                jmp     SHORT @@AllDone
@@HeapOK:
                mov     ax,_HEAPOK
@@AllDone:
                pop     di
                pop     si
                pop     bp
                ret
                ENDP

;-----------------------------------------------------------------------------
; C callable function to walk through the heap node by node
;-----------------------------------------------------------------------------
; Args:                 pointer to a heapinfo structure (stack)
; Returns:              _HEAPOK, _HEAPEMPTY, _HEAPEND in ax
;-----------------------------------------------------------------------------
IF LDATA
                PUBLIC  _heapwalk
_heapwalk       LABEL   PROC
ENDIF
                PUBLIC  _farheapwalk
_farheapwalk    PROC

                push    bp
                mov     bp,sp
                push    si
                push    di

                mov     di,[bp+6]               ;di = offset of struct
IF LDATA
                push    ds
                mov     bx,[bp+8]               ;bx = segment of struct

                cmp     di,0FFF0h               ;psuedo-normalize it
                jb      @@Normalized
                inc     bx
                sub     di,16d
@@Normalized:
                mov     ds,bx                   ;ds:di = struct
ENDIF
                mov     bx,WORD PTR [di+hi_ptr+2]       ;bx = previous block
                or      bx,bx
                jz      @@FirstBlock
                cmp     bx,cs:[___last]         ;last block?
                je      @@HeapEnd
                or      bx,bx                   ;first?
                jne     @@InnerBlock
@@FirstBlock:
                mov     bx,cs:[___first]
                or      bx,bx
                jz      @@HeapEmpty
                mov     es,bx                   ;es = first block
                jmp     SHORT @@SaveInfo
@@InnerBlock:
                mov     es,bx                   ;es = block
                add     bx,es:[bsize]           ;bx = next block
                mov     es,bx                   ;es = next block
@@SaveInfo:
                mov     WORD PTR ds:[di+hi_ptr+2],es    ;save address
                mov     WORD PTR ds:[di+hi_ptr],UsedHeaderSize
                mov     ax,WORD PTR es:[bsize]          ;multiply size * 16
                mov     bx,16d
                mul     bx
                mov     WORD PTR ds:[di+hi_size],ax     ;save it
                mov     WORD PTR ds:[di+hi_size+2],dx
                mov     WORD PTR ds:[di+hi_inuse],0     ;clear in-use flag
                cmp     WORD PTR es:[prev_real], 0      ;is it free?
                je      @@HeapOK
                inc     WORD PTR ds:[di+hi_inuse]      ;set in-use flag
@@HeapOK:
                mov     ax,_HEAPOK
                jmp     SHORT @@AllDone
@@HeapEmpty:
                mov     ax,_HEAPEMPTY
                jmp     SHORT @@AllDone
@@HeapEnd:
                mov     ax,_HEAPEND
@@AllDone:
IF LDATA
                pop     ds
ENDIF
                pop     di
                pop     si
                pop     bp
                ret
                ENDP
