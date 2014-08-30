	public _file_Pointer,file_Pointer
_file_Pointer label dword
file_Pointer	dd	?

	public _file_Buffer,file_Buffer
_file_Buffer label dword
file_Buffer	dd	?

	public _file_BufferPos,file_BufferPos
_file_BufferPos label dword
file_BufferPos dd	?

	public _file_BufPtr,file_BufPtr
_file_BufPtr label word
file_BufPtr	dw	?

	public _file_InReadBuf,file_InReadBuf
_file_InReadBuf label word
file_InReadBuf	dw	?

	public _file_Eof,file_Eof
_file_Eof label word
file_Eof	dw	?

	public _file_ErrorStat,file_ErrorStat
_file_ErrorStat label word
file_ErrorStat	dw	?
