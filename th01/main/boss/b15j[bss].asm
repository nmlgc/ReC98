KIKURI_TEAR_COUNT = 10

kikuri_soul_0	equ <_kikuri_souls[0 * size CBossEntity]>
kikuri_soul_1	equ <_kikuri_souls[1 * size CBossEntity]>
kikuri_tear_0	equ <_kikuri_tears[0 * size CBossEntity]>

public _kikuri_souls, _kikuri_tears
_kikuri_souls	CBossEntity 5 dup (<?>)
_kikuri_tears	CBossEntity 10 dup (<?>)
