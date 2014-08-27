	public ClipXL, ClipXW, ClipXR, ClipYT, ClipYH, ClipYB
	public ClipYT_seg,ClipYB_adr
	public _ClipXL, _ClipXW, _ClipXR, _ClipYT, _ClipYH, _ClipYB
	public _ClipYT_seg,_ClipYB_adr
_ClipXL label word
ClipXL	dw 0	; 左端(0)
_ClipXW label word
ClipXW dw 639	; 幅(639)
_ClipXR label word
ClipXR dw 639	; 右端
_ClipYT label word
ClipYT dw 0	; てっぺん(0)
_ClipYH label word
ClipYH	dw 399	; 高さ(399)
_ClipYB label word
ClipYB dw 399	; 下端(399)
_ClipYT_seg label word
ClipYT_seg dw 0a800h	; 上端のVRAMセグメント(青プレーン上)
_ClipYB_adr label word
ClipYB_adr dw 399*80	; 下端のVRAMオフセット
