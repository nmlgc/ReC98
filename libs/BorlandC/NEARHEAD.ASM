;-----------------------------------------------------------------------
; Only three variables are needed to efficiently manage the heap.
;-----------------------------------------------------------------------
                PUBLIC  __first,__last,__rover
                ALIGN   2
__first         dw      0               ;pointer to the first block
__last          dw      0               ;pointer to the last block
__rover         dw      0               ;pointer to an arbitrary free block
