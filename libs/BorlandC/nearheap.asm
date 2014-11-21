; *Not* the original file, but an edit to turn it into an includable slice.
; Changes include:
; * removal of RULES.ASI to eliminate redundancy
; * data declarations being moved to a separate file
; * removal of the segment declarations (for obvious reasons)
; * the "Header" structure being renamed to "NEARHEAP_Header" to avoid
;   collisions with master.lib's global bfnt_header structure

;[]-----------------------------------------------------------------[]
;|      NEARHEAP.ASM                                                 |
;[]-----------------------------------------------------------------[]

;
;       C/C++ Run Time Library - Version 5.0
; 
;       Copyright (c) 1987, 1992 by Borland International
;       All Rights Reserved.
; 

IF LDATA EQ false

;-----------------------------------------------------------------------
; Memory Block Header (near heap)
;-----------------------------------------------------------------------
; Each block in the heap, whether allocated or free, has a header.
; For an allocated block, only the first two fields of the header are
; used. For a free block all eight bytes are used, thus the smallest
; possible block is the size of a free header.
;
; Field       Description
; ---------   ----------------------------------------------------------
; size        total size, in bytes, of this block (+1 if the block is in use)
; prev_real   pointer to the physically previous block in the heap
; prev_free   pointer to the logically previous free block
; next_free   pointer to the logically next free block
;
; Note that the size field is also used to indicate whether the block
; is allocated or free.  A doubly-linked queue is maintained of the
; free blocks and it is important to know that ordering of the blocks
; in this queue is logical rather than physical.  If there is only one
; free block on the heap prev_free and next_free point to itself.
;-----------------------------------------------------------------------
NEARHEAP_Header STRUC
bsize           dw      ?
prev_real       dw      ?
prev_free       dw      ?
next_free       dw      ?
NEARHEAP_Header ENDS

;-----------------------------------------------------------------------
; heapinfo structure (near heap)
;-----------------------------------------------------------------------
; Used by the heapwalk function.
; heapwalk accepts a pointer to a struct of this type.
; On entry, the pointer field contains the address of the previous
; memory block in the heap (NULL for the first call).  The next block
; in the heap is then found and its address is stored in the structure
; along with its size, in bytes, and a 'used' flag.
;-----------------------------------------------------------------------
HeapInfo        STRUC
hi_ptr          dw      ?
hi_size         dw      ?
hi_inuse        dw      ?
HeapInfo        ENDS

UsedHeaderSize  EQU     4
FreeHeaderSize  EQU     8

IF LPROG
 EXTRADISP      equ     2         ; Allow for FAR returns when getting parms
ELSE
 EXTRADISP      equ     0
ENDIF

;-----------------------------------------------------------------------------
; C callable function to free a memory block
;-----------------------------------------------------------------------------
; Args:                 Pointer to the block to free (stack)
; Returns:              void
;-----------------------------------------------------------------------------
                PUBLIC  _free
_free           PROC
                push    si
                push    di
                mov     si,sp
                mov     bx,[si+(6+EXTRADISP)]   ;bx = first parameter passed
                sub     bx,UsedHeaderSize       ;bx = the address of the block to free
                jc      @@AllDone               ;skip if NULL
                cmp     bx,[__last]             ;is this the last block in the heap?
                je      @@lastBlock
@@InnerBlock:
                call    FreeInnerBlock          ;free the inner block
                jmp     short @@AllDone
@@LastBlock:
                call    FreeLastBlock           ;free the last block
@@AllDone:
                pop     di                      ;all done
                pop     si
                ret
_free           ENDP

;-----------------------------------------------------------------------------
; Frees the last block on the heap
; free helper function
;-----------------------------------------------------------------------------
; Args:                 Pointer to the block (bx)
; Returns:              void
;-----------------------------------------------------------------------------
FreeLastBlock   PROC NEAR
                cmp     [__first],bx            ;freeing the ONLY block?
                je      @@KillHeap
                mov     si,[bx.prev_real]       ;si = next-to-last block
                test    BYTE PTR [si.NEARHEAP_Header.bsize],01h
                jz      @@PreviousBlockIsFree
@@PreviousBlockIsUsed:
                mov     __last,si
                jmp     short @@ResetBreak      ;done!
@@PreviousBlockIsFree:
                cmp     si,[__first]            ;is the previous block the
                je      @@ResetHeap             ;first block in the heap?

                mov     bx,si                   ;remove the next-to-last block
                call    PullFreeBlock           ;from the free-block queue
                mov     ax,[bx.prev_real]
                mov     __last,ax
                jmp     short @@ResetBreak      ;done!
@@ResetHeap:
                mov     bx,si
;we are freeing the only block so reset the break level and kill the heap
@@KillHeap:
                xor     ax,ax
                mov     __first,ax              ;clear variables
                mov     __last,ax
                mov     __rover,ax
@@ResetBreak:
                push    bx
                call    ___brk                  ;reset the break level
                pop     bx                      ;cleanup stack
                ret
FreeLastBlock   ENDP

;-----------------------------------------------------------------------------
; Frees an interior block from within the heap
; free helper function
;-----------------------------------------------------------------------------
; Args:                 Pointer to the block (bx)
; Returns:              void
;-----------------------------------------------------------------------------
FreeInnerBlock  PROC NEAR
                dec     WORD PTR [bx.NEARHEAP_Header.bsize]
                cmp     bx,[__first]            ;first block?
                je      @@PreviousBlockIsUsed
                mov     si,[bx.prev_real]       ;get the previous block (si)
                mov     ax,[si.NEARHEAP_Header.bsize]
                test    al,01h
                jnz     @@PreviousBlockIsUsed
; join this block to the previous block
@@PreviousBlockIsFree:
                add     ax,[bx.NEARHEAP_Header.bsize]
                mov     [si.NEARHEAP_Header.bsize],ax
                mov     di,[bx.NEARHEAP_Header.bsize]
                add     di,bx
                mov     [di.prev_real],si       ;adjust the prev_real pointer
                mov     bx,si                   ;set up the current block
                jmp     SHORT @@CheckNextBlock
@@PreviousBlockIsUsed:
                call    InsertFreeBlock         ;add it to the free queue
@@CheckNextBlock:
                mov     di,[bx.NEARHEAP_Header.bsize]
                add     di,bx
                mov     ax,[di.NEARHEAP_Header.bsize]
                test    al,01h                  ;is the next block free?
                jz      JoinFreeBlocks          ;join this block to the next
@@AllDone:
                ret                             ;all done
FreeInnerBlock  ENDP

;-----------------------------------------------------------------------------
; Joins two physically adjacent free blocks together
; free helper function
;-----------------------------------------------------------------------------
; Args:                 Pointer to the lower block (bx)
;                       Pointer to the upper block (di)
;                       Size of the upper block, in bytes (ax)
; Returns:              void
; Registers destroyed:  ax si di
; This routine falls through to PullFreeBlock
;-----------------------------------------------------------------------------
JoinFreeBlocks  PROC NEAR
                add     [bx.NEARHEAP_Header.bsize],ax
                mov     si,di                   ;si = the next block after di
                add     si,ax
                mov     [si.prev_real],bx       ;adjust the link
                mov     bx,di
;;;;            jmp     SHORT PullFreeBlock     ;eliminate the upper block
JoinFreeBlocks  ENDP

;-----------------------------------------------------------------------------
; Removes a block from the free block queue
; free helper function
; malloc helper function
;-----------------------------------------------------------------------------
; Args:                 Pointer to the block (bx)
; Returns:              void
;-----------------------------------------------------------------------------
PullFreeBlock   PROC NEAR
                mov     di,[bx.next_free]       ;di = the next free block
                cmp     bx,di                   ;removing the last free block?
                je      @@NoFreeBlocks
                mov     __rover,di
                mov     si,[bx.prev_free]       ;si = previous free block
                mov     [di.prev_free],si       ;adjust the links
                mov     [si.next_free],di
                ret                             ;all done
@@NoFreeBlocks:
                mov     __rover,0
                ret                             ;all done
PullFreeBlock   ENDP

;-----------------------------------------------------------------------------
; Inserts a block into the free block queue
; free helper function
;-----------------------------------------------------------------------------
; Args:                 Pointer to the block (bx)
; Returns:              void
;-----------------------------------------------------------------------------
InsertFreeBlock PROC NEAR
                mov     si,[__rover]            ;si = rover pointer
                or      si,si                   ;no free blocks?
                jz      @@FirstFreeBlock
@@AnotherFreeBlock:
                mov     di,[si.next_free]       ;di = free block after rover
                mov     [si.next_free],bx       ;adjust links
                mov     [di.prev_free],bx
                mov     [bx.next_free],di
                mov     [bx.prev_free],si
                ret
@@FirstFreeBlock:
                mov     __rover,bx
                mov     [bx.prev_free],bx
                mov     [bx.next_free],bx
                ret
InsertFreeBlock ENDP


;-----------------------------------------------------------------------------
; C callable function to allocates a given number of bytes from the heap
;-----------------------------------------------------------------------------
; Args:                 Number of bytes requested (stack)
; Returns:              Address of the first byte of user space available
;                       from the heap if successful (ax)
;                       NULL if failure (ax)
;-----------------------------------------------------------------------------
                PUBLIC  _malloc
_malloc         PROC
                push    si                      ;should be on an odd address
                push    di

                mov     si,sp
                mov     ax,[si+(6+EXTRADISP)]   ;ax = number of bytes requested
                or      ax,ax                   ;does he want zero bytes?
                jz      @@AllDone

                add     ax,UsedHeaderSize+1     ;add the header size
                jc      @@NoCanDo               ;was size too great?
                and     ax,0fffeh               ;force a word boundary
                cmp     ax,FreeHeaderSize
                jae     @@BigEnough
                mov     ax,FreeHeaderSize
@@BigEnough:
                cmp     [__first],0             ;do we have a heap yet?
                jz      @@BuildHeap

                mov     bx,[__rover]            ;bx = rover pointer
                or      bx,bx                   ;are there any free blocks at all?
                jz      @@AddToHeap
                mov     dx,bx                   ;dx = rover pointer
@@SearchHeap:
                cmp     [bx.NEARHEAP_Header.bsize],ax
                jae     @@AllocateBlock         ;big enough to use at all?
@@TooSmall:
                mov     bx,[bx.next_free]       ;move to the next free block
                cmp     bx,dx                   ;at the end of the list?
                jne     @@SearchHeap
@@AddToHeap:
                call    ExtendHeap
                jmp     SHORT @@AllDone
@@DivideFreeBlock:
                call    AllocatePartialBlock
                jmp     SHORT @@AllDone
@@BuildHeap:
                call    CreateHeap
                jmp     SHORT @@AllDone
@@NoCanDo:
                xor     ax,ax
                jmp     SHORT @@AllDone
@@AllocateBlock:
                mov     si,ax                   ;si = smallest divisible block size
                add     si,FreeHeaderSize
                cmp     [bx.NEARHEAP_Header.bsize],si
                jae     @@DivideFreeBlock       ;big enough to break up?
                call    PullFreeBlock           ;remove it from the free-block queue
                inc     [bx.NEARHEAP_Header.bsize]
                mov     ax,bx
                add     ax,UsedHeaderSize
@@AllDone:
                pop     di                      ;all done
                pop     si
                ret
_malloc         ENDP

;-----------------------------------------------------------------------------
; Creates a heap from scratch
; malloc helper function
;-----------------------------------------------------------------------------
; Args:                 Number of bytes for the first block requested (ax)
; Returns:              Address of the first byte of user space available
;                       from the heap if successful (ax)
;                       NULL if failure (ax)
;-----------------------------------------------------------------------------
CreateHeap      PROC NEAR
                push    ax                      ;save the size

                xor     ax,ax                   ;align the heap on word
                push    ax
                push    ax
                call    ___sbrk                 ;retrieve the break level
                pop     bx                      ;cleanup stack
                pop     bx
                and     ax,0001h
                jz      @@Aligned
                xor     dx,dx
                push    dx
                push    ax
                call    ___sbrk                 ;align the heap
                pop     bx                      ;cleanup stack
                pop     bx
@@Aligned:
                pop     ax                      ;retrieve and save the size
                push    ax

                xor     bx,bx                   ;convert size request from
                push    bx                      ;unsigned int to signed long
                push    ax
                call    ___sbrk                 ;adjust the break level
                pop     bx                      ;cleanup stack
                pop     bx
                cmp     ax,-1                   ;failure?
                je      @@NoRoom
                mov     bx,ax                   ;bx = new block
                mov     __first,bx              ;save pointers
                mov     __last,bx
                pop     ax                      ;retrieve the size
                inc     ax                      ;mark it as allocated
                mov     [bx.NEARHEAP_Header.bsize],ax
                add     bx,UsedHeaderSize
                mov     ax,bx
                ret
@@NoRoom:
                pop     bx                      ;clear the size from the stack
                xor     ax,ax
                ret
CreateHeap      ENDP

;-----------------------------------------------------------------------------
; Attempts to extend the heap.
; malloc helper function
;-----------------------------------------------------------------------------
; Args:                 Number of bytes for the block requested (ax)
; Returns:              Address of the first byte of user space available
;                       from the heap if successful (ax)
;                       NULL if failure (ax)
;-----------------------------------------------------------------------------
ExtendHeap      PROC NEAR
                push    ax                      ;save the size
                xor     bx,bx                   ;convert size request from
                push    bx                      ;unsigned int to signed long
                push    ax
                call    ___sbrk                 ;adjust the break level
                pop     bx                      ;cleanup stack
                pop     bx
                cmp     ax,-1                   ;failure?
                je      @@NoRoom
                mov     bx,ax                   ;bx = new block
                mov     ax,[__last]             ;ax = next-to-the-last block
                mov     [bx.prev_real],ax
                mov     __last,bx               ;update last-block pointer
                pop     ax                      ;retrieve the size
                inc     ax                      ;mark it as allocated
                mov     [bx.NEARHEAP_Header.bsize],ax
                add     bx,UsedHeaderSize
                mov     ax,bx
                ret
@@NoRoom:       pop     ax                      ;retrieve the size
                xor     ax,ax
                ret
ExtendHeap      ENDP

;-----------------------------------------------------------------------------
; Divides a free block into two pieces.
; malloc helper function
;-----------------------------------------------------------------------------
; Args:                 Number of bytes for the block requested (ax)
;                       Pointer of the block to divide (bx)
; Returns:              Address of the first byte of user space available
;                       from the heap (ax)
;-----------------------------------------------------------------------------
AllocatePartialBlock    PROC NEAR
                sub     [bx.NEARHEAP_Header.bsize],ax           ;make room!
                mov     si,bx                   ;si = new block address
                add     si,[bx.NEARHEAP_Header.bsize]
                mov     di,si                   ;di = the block after the new block
                add     di,ax
                inc     ax
                mov     [si.NEARHEAP_Header.bsize],ax
                mov     [si.prev_real],bx
                mov     [di.prev_real],si
                add     si,UsedHeaderSize
                mov     ax,si
                ret
AllocatePartialBlock    ENDP

;-----------------------------------------------------------------------------
; Attempts to expand a block, relocating it if necessary
; realloc helper function
;-----------------------------------------------------------------------------
; Args:                 Pointer to the old block (bx)
;                       Size of the block (cx)
;                       Number of bytes requested (ax)
; Returns:              Address of the first byte of user space available
;                       from the heap if successful (bx)
;                       NULL if failure (bx)
;-----------------------------------------------------------------------------

ExpandBlock     PROC NEAR
                mov     bp,sp
                push    bx                      ;[bp-2] = old block
                push    ax                      ;[bp-4] = new size
                push    cx                      ;[bp-6] = old block size
                push    ax
                call    _malloc                 ;ax = data area of new block
                pop     bx                      ;cleanup stack
                mov     bx,ax
                or      ax,ax
                jz      @@AllDone               ;malloc failed
@@MallocOK:
                push    ds                      ;move the data to the new block
                pop     es
                cld
                mov     di,ax                   ;di = data area of new block
                mov     si,[bp-2]               ;si = old block
                mov     cx,[si.NEARHEAP_Header.bsize]
                add     si,UsedHeaderSize       ;si = data area of old block
                push    si                      ;save for call to _free
                sub     cx,UsedHeaderSize+1     ;cx = number of bytes in old data area
@@MoveIt:
                shr     cx,1                    ;cx = number of words in data area
                rep     movsw
                mov     [bp-2],ax               ;save data area of new block in scratch area
                call    _free
                pop     bx                      ;cleanup stack
                mov     bx,[bp-2]
@@AllDone:
                add     sp,6
                ret
ExpandBlock     ENDP

;-----------------------------------------------------------------------------
; Shrinks a block
; realloc helper function
;-----------------------------------------------------------------------------
; Args:                 Pointer to the block (bx)
;                       Size of the block (cx)
;                       Normalized number of bytes requested (dx)
; Returns:              Address of the first byte of user space available
;                       from the heap if successful (bx)
;-----------------------------------------------------------------------------

ShrinkBlock     PROC NEAR
                mov     ax,dx                   ;ax = requested block size
                add     dx,FreeHeaderSize
                cmp     dx,cx
                ja      @@AllDone
                mov     dx,cx                   ;dx = old block size
@@DivideTheBlock:
                cmp     bx,[__last]             ;last block in the heap?
                jne     @@InnerBlock
@@LastBlock:
                mov     [bx.NEARHEAP_Header.bsize],ax
                inc     [bx.NEARHEAP_Header.bsize]
                add     ax,bx
                push    bx                      ;save the old block
                push    ax
                call    ___brk                  ;reset the break level
                pop     bx                      ;cleanup stack
                pop     bx                      ;restore old block
                jmp     SHORT @@AllDone
@@InnerBlock:
                mov     di,bx
                add     di,ax                   ;di = new (free) block
                mov     [di.prev_real],bx
                sub     dx,ax                   ;dx = size of new (free) block
                sub     [bx.NEARHEAP_Header.bsize],dx
                mov     si,di                   ;si = next block after the new one
                add     si,dx
                mov     [si.prev_real],di       ;adjust the link
                inc     dx                      ;mark it as used
                mov     [di.NEARHEAP_Header.bsize],dx
                mov     cx,bx                   ;save the old block
                mov     bx,di
                call    FreeInnerBlock
                mov     bx,cx                   ;restore old block
@@AllDone:
                add     bx,UsedHeaderSize
                ret
ShrinkBlock     ENDP

;-----------------------------------------------------------------------------
; Attempts to reallocate a block
;-----------------------------------------------------------------------------
; Args:                 Pointer to the old block (stack)
;                       Number of bytes requested (stack)
; Returns:              Address of the first byte of user space available
;                       from the heap if successful (ax)
;                       NULL if failure (ax)
;-----------------------------------------------------------------------------
                PUBLIC  _realloc
_realloc        PROC
                push    si
                push    di
                push    bp
                mov     bp,sp

                mov     bx,[bp+(8+EXTRADISP)]   ;bx = pointer to the block to realloc
                mov     ax,[bp+(10+EXTRADISP)]  ;ax = number of bytes requested

                or      ax,ax                   ;does he really want 0 bytes???
                jz      @@FreeIt                ;let's give him what he wants!

                or      bx,bx                   ;did we get a NULL pointer?
                jz      @@MallocIt              ;OK, try to malloc it

                sub     bx,UsedHeaderSize       ;make bx = start of block

                mov     cx,[bx.NEARHEAP_Header.bsize]
                dec     cx
                mov     dx,ax

                add     dx,UsedHeaderSize+1     ;add the header size and
                and     dx,0fffeh               ;force a word boundary
                cmp     dx,FreeHeaderSize
                jae     @@BigEnough
                mov     dx,FreeHeaderSize
@@BigEnough:
                cmp     cx,dx
                jb      @@ExpandIt
                ja      @@ShrinkIt
@@NoChange:
                add     bx,UsedHeaderSize
                jmp     SHORT @@Resized
@@ShrinkIt:
                call    ShrinkBlock
                jmp     SHORT @@Resized
@@ExpandIt:
                call    ExpandBlock
@@Resized:
                mov     ax,bx
                jmp     SHORT @@AllDone
@@MallocIt:
                push    ax
                call    _malloc
                jmp     SHORT @@Cleanup
@@FreeIt:
                push    bx
                call    _free
                xor     ax, ax
@@Cleanup:
                pop     bx                      ;cleanup stack
@@AllDone:
                pop     bp                      ;all done
                pop     di
                pop     si
                ret
_realloc        ENDP
ENDIF
