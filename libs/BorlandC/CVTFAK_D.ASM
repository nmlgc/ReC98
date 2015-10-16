;-------------------------------------------------------------------------
;               Message texts for 'float not linked' messages
;
; Note : by putting an 'extra' blank in the scanf unique message part we
; save some code space by having a common message length.
;-------------------------------------------------------------------------
;
; Message part unique to the printf() message.
;
RealMSG         db      'print'         ; Unique part of 'printf' message
lgth_UNIQ       equ     $ - RealMSG     ; Length of unique msg parts
;
; Message part unique to the scanf() message(this MUST be same len as print).
;
ScanMSG         db      ' scan'         ; Unique part of 'scanf' message
;
; Message part common to the 'printf and 'scanf' messages.
; NOTE : the 'f' in printf and scanf is common too!.
;
CommonMSG       db      'f : floating point formats not linked', 13, 10
lgth_Common     equ     $ - CommonMSG
                db      0               ; word alignment
