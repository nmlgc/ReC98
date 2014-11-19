; *Not* the original file, but an edit to turn it into an includable slice.
; Changes include:
; * removal of RULES.ASI to eliminate redundancy
; * removal of the 'CODE' segment declaration (for obvious reasons)
; * removal of the ARG directives (they don't compile correctly for some
;   reason)
; * PROC DIST and LABEL DIST being changed to just PROC and LABEL PROC,
;   respectively
; * and a small section of code in ExtendHeap, which is present in the 
;   original Touhou builds, but was not included in the original version of
;   this file.

;[]-----------------------------------------------------------------[]
;|      FARHEAP.ASM                                                  |
;[]-----------------------------------------------------------------[]

;
;       C/C++ Run Time Library - Version 5.0
; 
;       Copyright (c) 1987, 1992 by Borland International
;       All Rights Reserved.
; 

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
HeapInfo        ENDS

UsedHeaderSize  EQU     4
FreeHeaderSize  EQU     10

;-----------------------------------------------------------------------
; Only three variables are needed to efficiently manage the heap.
; These reside in our own code segment for speed.
; We also set aside some scratch save areas.
;-----------------------------------------------------------------------
                PUBLIC  ___first,___last,___rover
;               ALIGN   2
___first        dw      0               ;segment of the first block
___last         dw      0               ;segment of the last block
___rover        dw      0               ;segment of an arbitrary free block
data_seg        dw      ?               ;old ds save area
save_hi         dw      ?               ;for realloc
save_lo         dw      ?

;-----------------------------------------------------------------------------
; Frees the last block on the heap
; free helper function
;-----------------------------------------------------------------------------
; Args:                 Pointer to the block (dx)
; Returns:              void
;-----------------------------------------------------------------------------
FreeLastBlock   PROC    NEAR
                cmp     dx,cs:[___first]           ;are we freeing the ONLY block?
                je      @@KillHeap
                mov     ds,dx
                mov     ds,ds:[prev_real]       ;ds = next-to-last block
                cmp     WORD PTR ds:[prev_real],0       ;is the previous block used?
                je      @@PreviousBlockIsFree
@@PreviousBlockIsUsed:
                mov     cs:___last,ds
                jmp     short @@Cleanup1

@@PreviousBlockIsFree:
                mov     ax,ds
                cmp     ax,cs:[___first]        ;is the previous block the
                je      @@ResetHeap             ;first block in the heap?
                mov     ax,ds:[prev_real2]
                mov     cs:___last,ax
                push    ds                      ;save for call to __brk
                xor     ax,ax
                push    ax
                call    PullFreeBlock
                mov     ds,cs:[data_seg]
                jmp     short @@Cleanup2
@@ResetHeap:
                mov     dx,cs:[___first]
@@KillHeap:
                mov     cs:___first,0
                mov     cs:___last,0
                mov     cs:___rover,0
@@Cleanup1:
                mov     ds,cs:[data_seg]
                push    dx
                xor     ax,ax
                push    ax
@@Cleanup2:
                call    __brk                   ;reset the break level
                add     sp,4                    ;cleanup stack
                ret
FreeLastBlock   ENDP

;-----------------------------------------------------------------------------
; Frees an interior block from within the heap
; free helper function
;-----------------------------------------------------------------------------
; Args:                 Pointer to the block (dx)
; Returns:              void
;-----------------------------------------------------------------------------
FreeInnerBlock  PROC    NEAR
                mov     ds,dx                   ;ds = block to free
                push    ds                      ;save block address
                mov     es,ds:[prev_real]       ;es = previous block
                mov     WORD PTR ds:[prev_real],0       ;mark the block as free
                mov     ds:[prev_real2],es
                cmp     dx,cs:[___first]           ;freeing first block?
                je      @@PreviousBlockIsUsed
                cmp     WORD PTR es:[prev_real],0       ;is the previous block free?
                jne     @@PreviousBlockIsUsed
@@PreviousBlockIsFree:
                mov     ax,ds:[bsize]           ;ax = size of this block
                pop     bx
                push    es
                add     es:[bsize],ax           ;add it to the previous block
                mov     cx,es                   ;cx = previous block
                add     dx,ax                   ;dx = next block
                mov     es,dx                   ;es = next block
                cmp     WORD PTR es:[prev_real],0
                jne     @@NextBlockIsUsed
@@NextBlockIsFree:
                mov     es:[prev_real2],cx
                jmp     SHORT @@CheckNextBlock
@@NextBlockIsUsed:
                mov     es:[prev_real],cx
                jmp     SHORT @@CheckNextBlock

@@PreviousBlockIsUsed:
                call    InsertFreeBlock

@@CheckNextBlock:
                pop     es                      ;es = retrieve block
                mov     ax,es                   ;ax = block
                add     ax,es:[bsize]           ;ax = next block
                mov     ds,ax                   ;ds = next block
                cmp     WORD PTR ds:[prev_real],0       ;is next block free?
                je      JoinFreeBlocks
@@AllDone:
                ret
FreeInnerBlock  ENDP

;-----------------------------------------------------------------------------
; Joins two physically adjacent free blocks together
; free helper function
;-----------------------------------------------------------------------------
; Args:                 Pointer to the lower block (es)
;                       Pointer to the upper block (ds)
; Returns:              void
; This routine falls through to PullFreeBlock
;-----------------------------------------------------------------------------
JoinFreeBlocks  PROC    NEAR
                mov     ax,ds:[bsize]           ;ax = size of upper block
                add     es:[bsize],ax           ;add it to lower block size
                mov     ax,es                   ;ax = lower block
                mov     bx,ds                   ;bx = upper block
                add     bx,ds:[bsize]           ;bx = next block
                mov     es,bx                   ;es = next block
                mov     es:[prev_real],ax       ;fixup link
;;;;            jmp     SHORT PullFreeBlock
JoinFreeBlocks  ENDP

;-----------------------------------------------------------------------------
; Removes a block from the free block queue
; free helper function
; malloc helper function
;-----------------------------------------------------------------------------
; Args:                 Pointer to the block (ds)
; Returns:              void
;-----------------------------------------------------------------------------
PullFreeBlock   PROC    NEAR
                mov     bx,ds                   ;bx = this block
                cmp     bx,ds:[next_free]       ;only ONE free block?
                je      @@NoFreeBlocks
                mov     es,ds:[next_free]       ;es = next free block
                mov     ds,ds:[prev_free]       ;ds = previous free block
                mov     ds:[next_free],es
                mov     es:[prev_free],ds
                mov     cs:___rover,ds
                mov     ds,bx
                ret
@@NoFreeBlocks:
                mov     cs:___rover,0
                ret
PullFreeBlock   ENDP

;-----------------------------------------------------------------------------
; Inserts a block into the free block queue
; free helper function
;-----------------------------------------------------------------------------
; Args:                 Pointer to the block (ds)
; Returns:              void
;-----------------------------------------------------------------------------
InsertFreeBlock PROC    NEAR
                mov     ax,cs:[___rover]        ;ax = rover pointer
                or      ax,ax                   ;no free blocks?
                jz      @@FirstFreeBlock
                mov     bx,ss                   ;save ss
                pushf                           ;save interrupt flag
                cli                             ;disable interrupts
                mov     ss,ax                   ;ss = rover pointer
                mov     es,ss:[next_free]       ;es = next free block
                mov     ss:next_free,ds         ;fixup links
                mov     ds:prev_free,ss
                mov     ss,bx                   ;restore ss
                popf                            ;restore interrupt flag
                mov     es:prev_free,ds
                mov     ds:next_free,es
                ret

@@FirstFreeBlock:
                mov     cs:___rover,ds
                mov     ds:[prev_free],ds
                mov     ds:[next_free],ds
                ret
InsertFreeBlock ENDP


;-----------------------------------------------------------------------------
; C callable function to free a memory block
;-----------------------------------------------------------------------------
; Args:                 Pointer to the block to free (stack)
; Returns:              void
;-----------------------------------------------------------------------------
IF LDATA
                PUBLIC  _free
_free           LABEL   PROC
ENDIF
                PUBLIC  _farfree
_farfree        PROC

                push    bp
                mov     bp,sp

                push    si
                push    di

                mov     cs:data_seg,ds
                mov     dx,[bp+8]               ;dx = segment to free
                or      dx,dx                   ;is it NULL
                jz      @@AllDone               ;   yes, skip it
                cmp     dx,cs:[___last]         ;last block in the heap?
                jne     @@InnerBlock
@@LastBlock:
                call    FreeLastBlock
                jmp     SHORT @@AllDone
@@InnerBlock:
                call    FreeInnerBlock
@@AllDone:
                mov     ds,cs:[data_seg]
                pop     di
                pop     si
                pop     bp
                ret
_farfree        ENDP

;-----------------------------------------------------------------------------
; Creates a heap from scratch
; malloc helper function
;-----------------------------------------------------------------------------
; Args:                 Number of paragraphs for the first block requested (ax)
; Returns:              Address of the first byte of user space available
;                       from the heap if successful (dx:ax)
;                       NULL if failure (dx:ax)
;-----------------------------------------------------------------------------
CreateHeap      PROC    NEAR
                push    ax                      ;save the size

                mov     ds,cs:[data_seg]
                xor     ax,ax                   ;align the heap on paragraph
                push    ax
                push    ax
                call    __sbrk                  ;retrieve the break level
                add     sp,4                    ;cleanup stack
                and     ax,000fh
                jz      @@Aligned
                mov     dx,16d
                sub     dx,ax
                xor     ax,ax
                mov     ds,cs:[data_seg]
                push    ax
                push    dx
                call    __sbrk                  ;align the heap
                add     sp,4                    ;cleanup stack
@@Aligned:
                pop     ax                      ;retrieve and save the size
                push    ax

                xor     bx,bx                   ;convert size to long in bx:ax
                mov     bl,ah
                mov     cl,4
                shr     bx,cl
                shl     ax,cl

                mov     ds,cs:[data_seg]
                push    bx
                push    ax
                call    __sbrk                  ;adjust the break level
                add     sp,4                    ;cleanup stack

                pop     bx                      ;retrieve the size

                cmp     ax,-1                   ;failure?
                je      @@NoRoom

                mov     cs:___first,dx          ;update heap pointers
                mov     cs:___last,dx
                mov     ds,dx
                mov     WORD PTR ds:[bsize],bx
                mov     WORD PTR ds:[prev_real],dx   ;just so we know it is used
                mov     ax,UsedHeaderSize
                ret
@@NoRoom:
                xor     ax,ax
                cwd
                ret
CreateHeap      ENDP

;-----------------------------------------------------------------------------
; Attempts to extend the heap.
; malloc helper function
;-----------------------------------------------------------------------------
; Args:                 Number of paragraphs for the block requested (ax)
; Returns:              Address of the first byte of user space available
;                       from the heap if successful (dx:ax)
;                       NULL if failure (dx:ax)
;-----------------------------------------------------------------------------
ExtendHeap      PROC    NEAR

; Touhou code below...
; ---
                push	ax
                mov     ds, cs:data_seg
                xor     ax, ax
                push    ax
                push    ax
                call    __sbrk
                pop     bx
                pop     bx
                and     ax,0Fh
                jz      short @@Aligned
                mov     dx,10h
                sub     dx,ax
                xor     ax,ax
                mov     ds,cs:data_seg
                push    ax
                push    dx
                call    __sbrk
                add     sp,4

@@Aligned:
                pop     ax
; ---
                push    ax                      ;save the size

                xor     bx,bx                   ;convert size to long in bx:ax
                mov     bl,ah
                mov     cl,4
                shr     bx,cl
                shl     ax,cl

                mov     ds,cs:[data_seg]
                push    bx
                push    ax
                call    __sbrk                  ;adjust the break level
                add     sp,4                    ;cleanup stack

                pop     bx                      ;retrieve the size

                cmp     ax,-1                   ;failure?
                je      @@NoRoom

                and     ax,0fh                  ;is it paragraph aligned?
                jnz     @@Misaligned            ;no - go adjust it
@@GotBlock:
                mov     cx,cs:[___last]         ;cx = old last-block pointer
                mov     cs:___last,dx           ;update last-block pointer
                mov     ds,dx
                mov     WORD PTR ds:[bsize],bx
                mov     WORD PTR ds:[prev_real],cx
                mov     ax,UsedHeaderSize
                ret

; Come here if the break level is not aligned on a paragraph boundary,
; which sometimes happens if both sbrk() and malloc() are used.  Adjust the
; break level and the block address up to the next paragraph boundary.
; The block segment is in DX; the low nibble of the offset is in AX.

@@Misaligned:
                push    bx                      ;save size again
                push    dx                      ;save segment of block
                neg     ax                      ;compute 16 - low nibble
                add     ax,16                   ;to get adjustment amount
                xor     bx,bx
                push    bx
                push    ax
                call    __sbrk                  ;allocate extra bytes
                add     sp,4                    ;clean up stack
                pop     dx                      ;recover segment
                pop     bx                      ;recover size
                cmp     ax,-1                   ;failure
                je      @@NoRoom
                inc     dx                      ;skip to next paragraph
                jmp     @@GotBlock
@@NoRoom:
                xor     ax,ax
                cwd
                ret
ExtendHeap      ENDP

;-----------------------------------------------------------------------------
; Divides a free block into two pieces.
; malloc helper function
;-----------------------------------------------------------------------------
; Args:                 Number of paragraphs for the block requested (ax)
;                       Pointer of the block to divide (ds & dx)
; Returns:              Address of the first byte of user space available
;                       from the heap (dx:ax)
;-----------------------------------------------------------------------------
AllocatePartialBlock    PROC    NEAR
                mov     bx,dx                   ;save block
                sub     ds:[bsize],ax           ;make room for new block
                add     dx,ds:[bsize]
                mov     ds,dx                   ;ds = new block
                mov     ds:[bsize],ax
                mov     ds:[prev_real],bx
                mov     bx,dx                   ;save block
                add     bx,ds:[bsize]
                mov     ds,bx                   ;ds = next block
                mov     ds:[prev_real],dx
                mov     ax,UsedHeaderSize
                ret
AllocatePartialBlock    ENDP

;-----------------------------------------------------------------------------
; C callable function to allocates a given number of bytes from the far heap
;-----------------------------------------------------------------------------
; Args:                 Number of bytes requested (long, stack)
; Returns:              Address of the first byte of user space available
;                       from the heap if successful (dx:ax)
;                       NULL if failure (ds:ax)
;-----------------------------------------------------------------------------
GenericMalloc	PROC
IF LDATA
                PUBLIC  _malloc
_malloc         LABEL   PROC

                push    bp
                mov     bp,sp
                xor     dx,dx
                mov     ax,[bp+6]               ;dx:ax = size requested (long)
                jmp     SHORT @@GotTheSize
ENDIF
                PUBLIC  _farmalloc
_farmalloc      LABEL   PROC

                push    bp
                mov     bp,sp
                mov     dx,[bp+8]
                mov     ax,[bp+6]               ;dx:ax = size requested (long)
@@GotTheSize:
                mov     cx,ax
                or      cx,dx                   ;does he want 0 bytes?
                push    si
                push    di
                mov     cs:data_seg,ds
                jz      @@AllDone
                add     ax,UsedHeaderSize+15    ;add the header size and
                adc     dx,0                    ;force paragraph boundary
                jc      @@NoCanDo               ;size too big?
                test    dx,0fff0h
                jnz     @@NoCanDo               ;size too big?
                mov     cl,4
                shr     ax,cl
                shl     dx,cl
                or      ah,dl                   ;ax = number of paragraphs

                mov     dx,cs:[___first]        ;dx = first block in the heap
                or      dx,dx                   ;is there any heap at all?
                jz      @@BuildHeap

                mov     dx,cs:[___rover]        ;dx = rover pointer
                or      dx,dx
                jz      @@AddToHeap

                mov     bx,dx                   ;bx = rover pointer
@@SearchHeap:
                mov     ds,dx                   ;ds = free block
                cmp     ds:[bsize],ax           ;is it big enough?
                jae     @@AllocateBlock
@@TooSmall:
                mov     dx,ds:[next_free]       ;dx = next free block
                cmp     dx,bx                   ;are we done?
                jne     @@SearchHeap
@@AddToHeap:
                call    ExtendHeap
                jmp     SHORT @@AllDone
@@BuildHeap:
                call    CreateHeap
                jmp     SHORT @@AllDone
@@DivideFreeBlock:
                call    AllocatePartialBlock
                jmp     SHORT @@AllDone
@@NoCanDo:
                xor     ax,ax
                cwd
                jmp     SHORT @@AllDone
@@AllocateBlock:
                ja      @@DivideFreeBlock
                call    PullFreeBlock           ;remove it from the free-block queue
                mov     bx,ds:[prev_real2]      ;mark it as allocated
                mov     ds:[prev_real],bx
                mov     ax,UsedHeaderSize
@@AllDone:
                mov     ds,cs:[data_seg]
                pop     di
                pop     si
@@Exit:
                pop     bp
                ret
GenericMalloc   ENDP

;-----------------------------------------------------------------------------
; Attempts to expand a block, relocating it if necessary
; realloc helper function
;-----------------------------------------------------------------------------
; Args:                 Pointer to the old block (bx)
;                       Number of paragraphs requested (ax)
; Returns:              Address of the first byte of user space available
;                       from the heap if successful (dx:ax)
;                       NULL if failure (dx:ax)
;-----------------------------------------------------------------------------

ExpandBlock     PROC    NEAR
                push    bx                      ;save the old block
                mov     si,cs:[save_hi]         ;get size parms from _farrealloc
                push    si                      ;setup for _farmalloc
                mov     si,cs:[save_lo]         ;get size parms from _farrealloc
                push    si                      ;setup for _farmalloc
                call    _farmalloc
                add     sp,4                    ;cleanup stack
                or      dx,dx
                jnz     @@MallocOK
@@MallocFailed:
                pop     bx                      ;cleanup stack
                ret
@@MallocOK:
                pop     ds                      ;ds = old block
                mov     es,dx                   ;es = new block
                push    es                      ;save new block
                push    ds                      ;save old block for _farfree
                push    bx

                mov     dx,ds:[bsize]           ;dx = old block size
@@MoveFirstBlock:
                cld
                dec     dx                      ;subtract one paragraph
                mov     di,UsedHeaderSize
                mov     si,di
                mov     cx,(16d-UsedHeaderSize)/2
                rep     movsw
                or      dx,dx
                jz      @@FreeOldBlock
                mov     ax,es                   ;increment segments
                inc     ax
                mov     es,ax
                mov     ax,ds
                inc     ax
                mov     ds,ax
@@MoveLoop:
                xor     di,di
                mov     si,di
                mov     cx,dx                   ;cx = paragraphs remaining
                cmp     cx,1000h
                jbe     @@MoveIt
                mov     cx,1000h
@@MoveIt:       shl     cx,1                    ;cx = number of words
                shl     cx,1
                shl     cx,1
                rep     movsw
                sub     dx,1000h
                jbe     @@FreeOldBlock
                mov     ax,es                   ;increment segments
                add     ax,1000h                ;add 64k
                mov     es,ax
                mov     ax,ds
                add     ax,1000h                ;add 64k
                mov     ds,ax
                jmp     SHORT @@MoveLoop
@@FreeOldBlock:
                mov     ds,cs:[data_seg]
                call    _farfree                ;free the old block
                add     sp,4                    ;cleanup stack

                pop     dx
                mov     ax,UsedHeaderSize
@@AllDone:
                ret
ExpandBlock     ENDP

;-----------------------------------------------------------------------------
; Shrinks a block
; realloc helper function
;-----------------------------------------------------------------------------
; Args:                 Pointer to the block (bx)
;                       Size of the block (cx)
;                       Normalized number of paragraphs requested (ax)
; Returns:              Address of the first byte of user space available
;                       from the heap if successful (dx:ax)
;-----------------------------------------------------------------------------

ShrinkBlock     PROC    NEAR
                cmp     bx,cs:[___last]         ;last block in the heap?
                je      @@LastBlock
@@InnerBlock:
                mov     di,bx                   ;di = old block
                add     di,ax                   ;di = new block
                mov     es,di                   ;es = new block
                mov     si,cx                   ;si = old block size
                sub     si,ax                   ;si -= new block size
                mov     es:[bsize],si           ;setup new block
                mov     es:[prev_real],bx
                push    es                      ;save for _farfree

                push    ax

                mov     es,bx                   ;es = original block
                mov     es:[bsize],ax
                mov     dx,bx                   ;dx = old block
                add     dx,cx                   ;dx = block after new
                mov     es,dx                   ;es = block after new
                cmp     WORD PTR es:[prev_real],0       ;is it used?
                je      @@NextIsFree
@@NextIsUsed:
                mov     es:[prev_real],di
                jmp     SHORT @@UnlinkIt
@@NextIsFree:
                mov     es:[prev_real2],di
@@UnlinkIt:
                mov     si,bx                   ;si = old block
                call    _farfree
                add     sp,4                    ;cleanup stack
                mov     dx,si
                mov     ax,UsedHeaderSize
                ret
@@LastBlock:
                push    bx                      ;save block
                mov     es,bx
                mov     es:[bsize],ax
                add     bx,ax
                push    bx
                xor     ax,ax
                push    ax
                call    __brk                   ;reset the break level
                add     sp,4                    ;cleanup stack

                pop     dx                      ;restore block
                mov     ax,UsedHeaderSize
                ret
ShrinkBlock     ENDP

;-----------------------------------------------------------------------------
; Attempts to reallocate a block
;-----------------------------------------------------------------------------
; Args:                 Pointer to the old block (stack)
;                       Number of bytes requested (stack)
; Returns:              Address of the first byte of user space available
;                       from the heap if successful (dx:ax)
;                       NULL if failure (dx:ax)
;-----------------------------------------------------------------------------
GenericRealloc	PROC
IF LDATA
                PUBLIC  _realloc
_realloc        LABEL   PROC

                push    bp
                mov     bp,sp
                xor     dx,dx
                jmp     SHORT @@GetTheSize
ENDIF
                PUBLIC  _farrealloc
_farrealloc     LABEL   PROC

                push    bp
                mov     bp,sp
                mov     dx,[bp+12]
@@GetTheSize:
                mov     ax,[bp+10]              ;dx:ax = size requested (long)
                mov     bx,[bp+8]               ;bx = segment to realloc

                push    si
                push    di
                mov     cs:data_seg,ds
                mov     cs:save_hi,dx
                mov     cs:save_lo,ax

                or      bx,bx                   ;is it a null pointer?
                jz      @@MallocIt

                mov     cx,ax
                or      cx,dx                   ;does he want 0 bytes?
                jz      @@FreeIt

                add     ax,UsedHeaderSize+15    ;add the header size and
                adc     dx,0                    ;force paragraph boundary
                jc      @@RetNull               ;size too big?
                test    dx,0fff0h
                jnz     @@RetNull               ;size too big?
                mov     cl,4
                shr     ax,cl
                shl     dx,cl
                or      ah,dl                   ;ax = number of paragraphs

                mov     es,bx                   ;es = segment to realloc
                mov     cx,es:[bsize]           ;cx = current block size
                cmp     cx,ax
                jb      @@ExpandIt
                ja      @@ShrinkIt
@@NoChange:
                mov     dx,bx
                mov     ax,UsedHeaderSize
                jmp     SHORT @@AllDone
@@ShrinkIt:
                call    ShrinkBlock
                jmp     SHORT @@AllDone
@@ExpandIt:
                call    ExpandBlock
                jmp     SHORT @@AllDone
@@MallocIt:
                push    dx
                push    ax
                call    _farmalloc
                add     sp,4                    ;cleanup stack
                jmp     SHORT @@AllDone
@@FreeIt:
                push    bx
                push    ax                      ;has a zero left over
                call    _farfree
                add     sp,4                    ;cleanup stack
@@RetNull:
                xor     ax, ax
                cwd
@@AllDone:
                mov     ds,cs:[data_seg]
                pop     di
                pop     si
                pop     bp
                ret
GenericRealloc  ENDP
