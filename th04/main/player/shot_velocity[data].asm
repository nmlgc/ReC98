; Precomputed results of `cos(angle)*192` (X) and `sin(angle)*192` (Y), used
; to derive 16-bit X and Y velocities for a shot's motion_t::velocity field
; from an 8-bit angle, with a hardcoded speed of 192 subpixels (= 12 pixels)
; per frame.
public _VELOCITY_192_AT_ANGLE
_VELOCITY_192_AT_ANGLE label Point
	Point < 192,    0>	; 0
	Point < 192,    4>	; 1
	Point < 192,    9>	; 2
	Point < 191,   14>	; 3
	Point < 191,   18>	; 4
	Point < 190,   23>	; 5
	Point < 189,   28>	; 6
	Point < 189,   33>	; 7
	Point < 188,   37>	; 8
	Point < 187,   42>	; 9
	Point < 186,   46>	; 10
	Point < 185,   51>	; 11
	Point < 183,   55>	; 12
	Point < 182,   60>	; 13
	Point < 180,   64>	; 14
	Point < 179,   69>	; 15
	Point < 177,   73>	; 16
	Point < 175,   78>	; 17
	Point < 173,   81>	; 18
	Point < 171,   86>	; 19
	Point < 169,   90>	; 20
	Point < 167,   94>	; 21
	Point < 165,   99>	; 22
	Point < 162,  102>	; 23
	Point < 159,  106>	; 24
	Point < 156,  110>	; 25
	Point < 154,  114>	; 26
	Point < 151,  117>	; 27
	Point < 148,  121>	; 28
	Point < 145,  125>	; 29
	Point < 142,  129>	; 30
	Point < 138,  132>	; 31
	Point < 135,  135>	; 32
	Point < 132,  138>	; 33
	Point < 129,  142>	; 34
	Point < 125,  145>	; 35
	Point < 121,  148>	; 36
	Point < 117,  151>	; 37
	Point < 114,  154>	; 38
	Point < 110,  156>	; 39
	Point < 106,  159>	; 40
	Point < 102,  162>	; 41
	Point <  99,  165>	; 42
	Point <  94,  167>	; 43
	Point <  90,  169>	; 44
	Point <  86,  171>	; 45
	Point <  81,  173>	; 46
	Point <  78,  175>	; 47
	Point <  73,  177>	; 48
	Point <  69,  179>	; 49
	Point <  64,  180>	; 50
	Point <  60,  182>	; 51
	Point <  55,  183>	; 52
	Point <  51,  185>	; 53
	Point <  46,  186>	; 54
	Point <  42,  187>	; 55
	Point <  37,  188>	; 56
	Point <  33,  189>	; 57
	Point <  28,  189>	; 58
	Point <  23,  190>	; 59
	Point <  18,  191>	; 60
	Point <  14,  191>	; 61
	Point <   9,  192>	; 62
	Point <   4,  192>	; 63
	Point <   0,  192>	; 64
	Point <  -5,  192>	; 65
	Point < -10,  192>	; 66
	Point < -15,  191>	; 67
	Point < -19,  191>	; 68
	Point < -24,  190>	; 69
	Point < -29,  189>	; 70
	Point < -33,  189>	; 71
	Point < -38,  188>	; 72
	Point < -42,  187>	; 73
	Point < -47,  186>	; 74
	Point < -51,  185>	; 75
	Point < -56,  183>	; 76
	Point < -60,  182>	; 77
	Point < -65,  180>	; 78
	Point < -69,  179>	; 79
	Point < -74,  177>	; 80
	Point < -78,  175>	; 81
	Point < -82,  173>	; 82
	Point < -87,  171>	; 83
	Point < -91,  169>	; 84
	Point < -95,  167>	; 85
	Point < -99,  165>	; 86
	Point <-103,  162>	; 87
	Point <-107,  159>	; 88
	Point <-111,  156>	; 89
	Point <-114,  154>	; 90
	Point <-118,  151>	; 91
	Point <-122,  148>	; 92
	Point <-126,  145>	; 93
	Point <-129,  142>	; 94
	Point <-133,  138>	; 95
	Point <-136,  135>	; 96
	Point <-139,  132>	; 97
	Point <-143,  129>	; 98
	Point <-146,  125>	; 99
	Point <-149,  121>	; 100
	Point <-152,  117>	; 101
	Point <-155,  114>	; 102
	Point <-157,  110>	; 103
	Point <-160,  106>	; 104
	Point <-162,  102>	; 105
	Point <-165,   99>	; 106
	Point <-168,   94>	; 107
	Point <-170,   90>	; 108
	Point <-172,   86>	; 109
	Point <-174,   81>	; 110
	Point <-176,   78>	; 111
	Point <-178,   73>	; 112
	Point <-180,   69>	; 113
	Point <-181,   64>	; 114
	Point <-183,   60>	; 115
	Point <-184,   55>	; 116
	Point <-186,   51>	; 117
	Point <-186,   46>	; 118
	Point <-188,   42>	; 119
	Point <-189,   37>	; 120
	Point <-189,   33>	; 121
	Point <-190,   28>	; 122
	Point <-191,   23>	; 123
	Point <-192,   18>	; 124
	Point <-192,   14>	; 125
	Point <-192,    9>	; 126
	Point <-192,    4>	; 127
	Point <-192,    0>	; 128
	Point <-192,   -5>	; 129
	Point <-192,  -10>	; 130
	Point <-192,  -15>	; 131
	Point <-192,  -19>	; 132
	Point <-191,  -24>	; 133
	Point <-190,  -29>	; 134
	Point <-189,  -33>	; 135
	Point <-189,  -38>	; 136
	Point <-188,  -42>	; 137
	Point <-186,  -47>	; 138
	Point <-186,  -51>	; 139
	Point <-184,  -56>	; 140
	Point <-183,  -60>	; 141
	Point <-181,  -65>	; 142
	Point <-180,  -69>	; 143
	Point <-178,  -74>	; 144
	Point <-176,  -78>	; 145
	Point <-174,  -82>	; 146
	Point <-172,  -87>	; 147
	Point <-170,  -91>	; 148
	Point <-168,  -95>	; 149
	Point <-165,  -99>	; 150
	Point <-162, -103>	; 151
	Point <-160, -107>	; 152
	Point <-157, -111>	; 153
	Point <-155, -114>	; 154
	Point <-152, -118>	; 155
	Point <-149, -122>	; 156
	Point <-146, -126>	; 157
	Point <-143, -129>	; 158
	Point <-139, -133>	; 159
	Point <-136, -136>	; 160
	Point <-133, -139>	; 161
	Point <-129, -143>	; 162
	Point <-126, -146>	; 163
	Point <-122, -149>	; 164
	Point <-118, -152>	; 165
	Point <-114, -155>	; 166
	Point <-111, -157>	; 167
	Point <-107, -160>	; 168
	Point <-103, -162>	; 169
	Point < -99, -165>	; 170
	Point < -95, -168>	; 171
	Point < -91, -170>	; 172
	Point < -87, -172>	; 173
	Point < -82, -174>	; 174
	Point < -78, -176>	; 175
	Point < -74, -178>	; 176
	Point < -69, -180>	; 177
	Point < -65, -181>	; 178
	Point < -60, -183>	; 179
	Point < -56, -184>	; 180
	Point < -51, -186>	; 181
	Point < -47, -186>	; 182
	Point < -42, -188>	; 183
	Point < -38, -189>	; 184
	Point < -33, -189>	; 185
	Point < -29, -190>	; 186
	Point < -24, -191>	; 187
	Point < -19, -192>	; 188
	Point < -15, -192>	; 189
	Point < -10, -192>	; 190
	Point <  -5, -192>	; 191
	Point <   0, -192>	; 192
	Point <   4, -192>	; 193
	Point <   9, -192>	; 194
	Point <  14, -192>	; 195
	Point <  18, -192>	; 196
	Point <  23, -191>	; 197
	Point <  28, -190>	; 198
	Point <  33, -189>	; 199
	Point <  37, -189>	; 200
	Point <  42, -188>	; 201
	Point <  46, -186>	; 202
	Point <  51, -186>	; 203
	Point <  55, -184>	; 204
	Point <  60, -183>	; 205
	Point <  64, -181>	; 206
	Point <  69, -180>	; 207
	Point <  73, -178>	; 208
	Point <  78, -176>	; 209
	Point <  81, -174>	; 210
	Point <  86, -172>	; 211
	Point <  90, -170>	; 212
	Point <  94, -168>	; 213
	Point <  99, -165>	; 214
	Point < 102, -162>	; 215
	Point < 106, -160>	; 216
	Point < 110, -157>	; 217
	Point < 114, -155>	; 218
	Point < 117, -152>	; 219
	Point < 121, -149>	; 220
	Point < 125, -146>	; 221
	Point < 129, -143>	; 222
	Point < 132, -139>	; 223
	Point < 135, -136>	; 224
	Point < 138, -133>	; 225
	Point < 142, -129>	; 226
	Point < 145, -126>	; 227
	Point < 148, -122>	; 228
	Point < 151, -118>	; 229
	Point < 154, -114>	; 230
	Point < 156, -111>	; 231
	Point < 159, -107>	; 232
	Point < 162, -103>	; 233
	Point < 165,  -99>	; 234
	Point < 167,  -95>	; 235
	Point < 169,  -91>	; 236
	Point < 171,  -87>	; 237
	Point < 173,  -82>	; 238
	Point < 175,  -78>	; 239
	Point < 177,  -74>	; 240
	Point < 179,  -69>	; 241
	Point < 180,  -65>	; 242
	Point < 182,  -60>	; 243
	Point < 183,  -56>	; 244
	Point < 185,  -51>	; 245
	Point < 186,  -47>	; 246
	Point < 187,  -42>	; 247
	Point < 188,  -38>	; 248
	Point < 189,  -33>	; 249
	Point < 189,  -29>	; 250
	Point < 190,  -24>	; 251
	Point < 191,  -19>	; 252
	Point < 191,  -15>	; 253
	Point < 192,  -10>	; 254
	Point < 192,   -5>	; 255
