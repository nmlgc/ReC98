ifdef   WILD
 ExtSym@        _argc,          WORD,                   __CDECL__
 dPtrExt@       _argv,                                  __CDECL__
else
 PubSym@        _argc,          <dw     0>,             __CDECL__
 dPtrPub@       _argv,          0,                      __CDECL__
endif
SavedReturn     dw              ?
SavedDS2        dw              ?
SavedReturn2    dw              ?
SavedSI         dw              ?
SavedDI         dw              ?
