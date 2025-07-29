#pragma option -zCPLATFORM_TEXT

#include "platform/x86real/doserror.hpp"
#include "libs/master.lib/master.hpp"
#include <dos.h>
#include <errno.h>

const char near* dos_strerror(void)
{
	switch(errno) {
	case ENOENT:
		return "No such file or directory";
	case ENOMEM:
		return "Not enough memory";
	case EINVAL:
		return "Invalid function number";
	case E2BIG:
		// __IOerror() maps DOS error 10 to this rather than EINVENV?
		return ((_doserrno == 10) ? "Invalid environment" : "Arg list too big");
	case ENOEXEC:
		return "Exec format error";
	default:
		return "Unknown error";
	}
}

void dos_print_error(const char *s1, const char *s2, const char *s3)
{
	dos_puts2(_argv[0]);
	dos_puts2(": ");
	dos_puts2(s1);
	if(s2) {
		dos_puts2(s2);
	}
	if(s3) {
		dos_puts2(s3);
	}
	dos_puts2(": ");
	dos_puts2(dos_strerror());
	dos_puts2("\n");
}
