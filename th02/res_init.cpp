#ifndef ERROR_NOT_RESIDENT
	#define ERROR_NOT_RESIDENT "�킽���A�܂����܂���悧"
#endif
#ifndef REMOVED
	#define REMOVED "����Ȃ�A�܂�����炢����"
#endif
#ifndef INITIALIZED
	#define INITIALIZED "����ł́A��낵�����肢���܂�"
#endif

#define arg_is(arg, capital, small) \
	((arg[0] == '-'    ) || (arg[0] == '/'  )) && \
	((arg[1] == capital) || (arg[1] == small))

int main(int argc, const unsigned char **argv)
{
	resident_t __seg *seg;
#if (GAME == 5)
	int i;
	resident_t far *resident;
	uint8_t far *resident_bytes;
	const char *res_id = RES_ID;
#else
	const char *res_id = RES_ID;
	int i;
	uint8_t far *resident_bytes;
#endif

	seg = ResData<resident_t>::exist_with_id_from_pointer(res_id);
	dos_puts2("\n\n" LOGO "\n");
	graph_clear();
#ifdef RES_INIT_TOP
	RES_INIT_TOP;
#endif
	if(argc == 2) {
		if(arg_is(argv[1], 'R', 'r')) {
			if(!seg) {
				dos_puts2(ERROR_NOT_RESIDENT "\n\n");
				return 1;
			}
			dos_free(seg);
			dos_puts2(REMOVED "\n\n");
			return 0;
		} else if(arg_is(argv[1], 'D', 'd')) {
			debug = 1;
		} else {
			dos_puts2("����ȃI�v�V�����t�����Ă��A�����ł�����\n\n");
			seg = seg; /* optimization barrier #1 */
			return 1;
		}
	}
	if(seg) {
		dos_puts2("�킽���A���łɂ��܂��悧\n\n");
		argv = argv; /* optimization barrier #2 */
		return 1;
	}
	seg = ResData<resident_t>::create_with_id_from_pointer(res_id);
	if(!seg) {
		dos_puts2("���܂���A�킽���̋��ꏊ���Ȃ��́I\n\n");
		optimization_barrier();
		return 1;
	}
	resident_bytes = reinterpret_cast<uint8_t far *>(seg);
	dos_puts2(INITIALIZED "\n\n");
	for(i = (ResData<resident_t>::id_len() + 1); i < sizeof(resident_t); i++) {
		resident_bytes[i] = 0;
	}
	RES_INIT_BOTTOM;
	return 0;
}
