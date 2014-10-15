; DOS error list
e_badFunction          equ   1
e_fileNotFound         equ   2
e_pathNotFound         equ   3
e_tooManyOpen          equ   4
e_accessDenied         equ   5
e_badHandle            equ   6
e_mcbDestroyed         equ   7
e_outOfMemory          equ   8
e_badBlock             equ   9
e_badEnviron           equ  10
e_badFormat            equ  11
e_badAccess            equ  12
e_badData              equ  13
; reserved             equ  14
e_badDrive             equ  15
e_isCurrentDir         equ  16
e_notSameDevice        equ  17
e_noMoreFiles          equ  18
e_readOnly             equ  19
e_unknownUnit          equ  20
e_notReady             equ  21
e_unknownCommand       equ  22
e_dataError            equ  23
e_badRequestLength     equ  24
e_seekError            equ  25
e_unknownMedia         equ  26
e_sectorNotFound       equ  27
e_outOfPaper           equ  28
e_writeFault           equ  29
e_readFault            equ  30
e_generalFault         equ  31
e_sharing              equ  32
e_lock                 equ  33
e_diskChange           equ  34
e_FCBunavailable       equ  35
e_sharingOverflow      equ  36
; reserved             equ  37..49
e_networkUnsupported   equ  50
e_notListening         equ  51
e_dupNameOnNet         equ  52
e_nameNotOnNet         equ  53
e_netBusy              equ  54
e_netDeviceGone        equ  55
e_netCommandLimit      equ  56
e_netHardError         equ  57
e_wrongNetResponse     equ  58
e_netError             equ  59
e_remoteIncompatible   equ  60
e_printQueueFull       equ  61
e_printFileSpace       equ  62
e_printFileDeleted     equ  63
e_netNameDeleted       equ  64
e_netAccessDenied      equ  65              ; same as 5
e_netDeviceWrong       equ  66
e_netNameNotFound      equ  67              ; same as 53
e_netNameLimit         equ  68
e_netBIOSlimit         equ  69
e_paused               equ  70
e_netRequestRefused    equ  71
e_redirectionPaused    equ  72
; reserved             equ  73..79
e_fileExists           equ  80
; reserved             equ  81
e_cannotMake           equ  82
e_failInt24            equ  83
e_redirectionLimit     equ  84
e_dupRedirection       equ  85
e_password             equ  86
e_parameter            equ  87
e_netDevice            equ  88

e_dosFinalError        equ  88
