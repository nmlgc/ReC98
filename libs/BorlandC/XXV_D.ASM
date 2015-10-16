		public ___CPPexceptionList
___CPPexceptionList dd 0
		public ___exceptFlags
___exceptFlags	dw 0
		public ___savedDS
___savedDS	dw 0
		public ___savedSI
___savedSI	dw 0
		public ___terminatePTR
___terminatePTR	dd @terminate$qv	; terminate(void)
		public ___unexpectdPTR
___unexpectdPTR	dd @unexpected$qv	; unexpected(void)
		public ___terminate_DS
___terminate_DS	dw 0
		public ___unexpectd_DS
___unexpectd_DS	dw 0
		public ___throwFileName
___throwFileName dd 0
		public ___throwLineNumber
___throwLineNumber dw 0
		public ___throwExceptionName
___throwExceptionName dd 0
		public ___exceptStaticBuffP
___exceptStaticBuffP dd	0
		public ___exceptMemAllocVars
___exceptMemAllocVars dd 0
		public ___exceptionNameBuff
___exceptionNameBuff db	80h dup(0)
		public ___ExceptStaticXbuff
___ExceptStaticXbuff db	80h dup(0)
