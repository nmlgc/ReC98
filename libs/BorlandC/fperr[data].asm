f_errors	struc
FPEtype		dw ?
dPtr@		string, ?
f_errors	ends

fp_errors	f_errors <81h, aDomain>
		f_errors <82h, aDenormal>
		f_errors <83h, aDivideBy0>
		f_errors <84h, aOverflow>
		f_errors <85h, aUnderflow>
		f_errors <86h, aPartialLossOfP>
		f_errors <87h, aStackFault>
aDomain		db 'Domain',0
aDenormal	db 'Denormal',0
aDivideBy0	db 'Divide by 0',0
aOverflow	db 'Overflow',0
aUnderflow	db 'Underflow',0
aPartialLossOfP	db 'Partial loss of precision',0
aStackFault	db 'Stack fault',0
aFloatingPointE	db 'Floating point error: %s.',0Ah,0
