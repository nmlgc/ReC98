; Dos Error Codes

EZERO     equ  0 ; Error 0
EINVFNC   equ  1 ; Invalid function number
ENOFILE   equ  2 ; File not found
ENOPATH   equ  3 ; Path not found
ECONTR    equ  7 ; Memory blocks destroyed
EINVMEM   equ  9 ; Invalid memory block address
EINVENV   equ 10 ; Invalid environment
EINVFMT   equ 11 ; Invalid format
EINVACC   equ 12 ; Invalid access code
EINVDAT   equ 13 ; Invalid data
EINVDRV   equ 15 ; Invalid drive specified
ECURDIR   equ 16 ; Attempt to remove CurDir
ENOTSAM   equ 17 ; Not same device
ENMFILE   equ 18 ; No more files

ENOENT    equ  2 ; No such file or directory
EMFILE    equ  4 ; Too many open files
EACCES    equ  5 ; Permission denied
EBADF     equ  6 ; Bad file number
ENOMEM    equ  8 ; Not enough core
EFAULT    equ 14 ; Unknown error
ENODEV    equ 15 ; No such device
EINVAL    equ 19 ; Invalid argument
E2BIG     equ 20 ; Arg list too long
ENOEXEC   equ 21 ; Exec format error
EXDEV     equ 22 ; Cross-device link
ENFILE    equ 23 ; UNIX - not MSDOS
ECHILD    equ 24 ; Unix/DOS
ENOTTY    equ 25 ; UNIX - not MSDOS
ETXTBSY   equ 26 ; UNIX - not MSDOS
EFBIG     equ 27 ; UNIX - not MSDOS
ENOSPC    equ 28 ; UNIX - not MSDOS
ESPIPE    equ 29 ; UNIX - not MSDOS
EROFS     equ 30 ; UNIX - not MSDOS
EMLINK    equ 31 ; UNIX - not MSDOS
EPIPE     equ 32 ; UNIX - not MSDOS
EDOM      equ 33 ; Math argument
ERANGE    equ 34 ; Result too large
EEXIST    equ 35 ; File already exists
EDEADLOCK equ 36 ; Locking violation
EPERM     equ 37 ; UNIX - not MSDOS
ESRCH     equ 38 ; UNIX - not MSDOS
EINTR     equ 39 ; UNIX - not MSDOS
EIO       equ 40 ; UNIX - not MSDOS
ENXIO     equ 41 ; UNIX - not MSDOS
EAGAIN    equ 42 ; UNIX - not MSDOS
ENOTBLK   equ 43 ; UNIX - not MSDOS
EBUSY     equ 44 ; UNIX - not MSDOS
ENOTDIR   equ 45 ; UNIX - not MSDOS
EISDIR    equ 46 ; UNIX - not MSDOS
EUCLEAN   equ 47 ; UNIX - not MSDOS
