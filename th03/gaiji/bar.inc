; Enemy health / dream / power bars
G_BAR = 020h
g_BAR_01W = 020h
g_BAR_02W = 021h
g_BAR_03W = 022h
g_BAR_04W = 023h
g_BAR_05W = 024h
g_BAR_06W = 025h
g_BAR_07W = 026h
g_BAR_08W = 027h
g_BAR_09W = 028h
g_BAR_10W = 029h
g_BAR_11W = 02Ah
g_BAR_12W = 02Bh
g_BAR_13W = 02Ch
g_BAR_14W = 02Dh
g_BAR_15W = 02Eh
g_BAR_16W = 02Fh

BAR_GAIJI_MAX = 16

if GAME ge 4
	; 8 regular bar cell sprites with 16 pixels filled in TH04. TH05 has *MAX♡
	; drawn on the last three.
	  g_BAR_MAX = 030h
	g_BAR_MAX_0 = 030h
	g_BAR_MAX_1 = 031h
	g_BAR_MAX_2 = 032h
	g_BAR_MAX_3 = 033h
	g_BAR_MAX_4 = 034h
	g_BAR_MAX_5 = 035h
	g_BAR_MAX_6 = 036h
	g_BAR_MAX_7 = 037h
endif
