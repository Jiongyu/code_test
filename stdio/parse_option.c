#include <stdio.h>
#include <unistd.h>

static void usage(void)
{
	fprintf(stderr, "usage: multi-thread [-options]\n");
	fprintf(stderr, "  -D str  Set device name\n");
	fprintf(stderr, "  -r val  Set sample rate\n");
	fprintf(stderr, "  -p val  Set period size (in frame)\n");
	fprintf(stderr, "  -b val  Set buffer size (in frame)\n");
	fprintf(stderr, "  -c val  Set number of channels\n");
	fprintf(stderr, "  -f str  Set PCM format\n");
	fprintf(stderr, "  -s str  Set stream direction (playback or capture)\n");
	fprintf(stderr, "  -t val  Set number of threads\n");
	fprintf(stderr, "  -m str  Running mode (avail, status, hwsync, timestamp, delay, random)\n");
	fprintf(stderr, "  -v      Show value\n");
	fprintf(stderr, "  -q      Quiet mode\n");
}


static int parse_options(int argc, char **argv)
{
	int c;

	while ( (c = getopt(argc, argv, "D:r:f:p:b:s:t:m:vq")) != -1) {

		switch (c){
		case 'D':
			break;
		case 'r':
			break;
		case 'p':
			break;
		case 'b':
			break;
		case 'c':
			break;
		case 'f':
			break;
		case 's':
			break;
		case 't':
			break;
		case 'm':
			break;
		case 'v':
			break;
		case 'q':
			break;
        case '?':
		default:
			usage();
			return 1;
		}
	}
    // printf("end\n");
	return 0;
}

static int parse_options_2(int argc, char **argv)
{
    int i;
    for (i = 1 ; i<argc ; i++) {
		if (argv[i][0]=='-') {
			switch (argv[i][1]) {
				case 'h':
					usage();
					break;
				case 'v':
					break;
				case 't':
					break;
				case 'i':
	
					break;
				case 'I':

					break;
				case 'o':

					break;
				case 'O':

					break;
			}			
		}
	}
}

int main(int argc, char  **argv)
{

    if (argc==1) {
		usage();
		exit(0);
	}

    if(parse_options(argc, argv))
        return -1;
    return 0;
}
