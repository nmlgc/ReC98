ifndef WILD

;This is the symbol which pulls in _setargv
                public __setargv__
__setargv__     equ    0

                db      0                       ;near call
                db      16                      ;priority 16
                dw      offset __setargv
                dw      0                       ;0 in the original file
endif
