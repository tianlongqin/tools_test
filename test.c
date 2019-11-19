#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h> 
#include <stdint.h>

#include <serial/serial_func.h>
#include <debug/debug.h>


static inline int serial_init(char *name)
{
	return Tserial_open_with_arg(name, 1, 9600, 8, 1, 'N', 'n');
}

static int serial_read(int fd)
{
	char buf[64];
	int rc;
	struct frame_645 *frame;
	rc = read(fd, buf, sizeof(buf));
	if (rc < 0)
		printf("errno:%d\n", errno);

}

int main(int argc, const char *argv[])
{
	int fd, rc = 0, i;
	int maxfd;
	char buf[64] = {0};
	fd_set set;

	fd = serial_init("/dev/ttymxc4");
	if (fd < 0) {
		printf("serial_open_with_arg failed\n");
		exit(1);
	}

	while (1) {
		FD_ZERO(&set);
		FD_SET(fd, &set);

		select(fd + 1, &set, NULL, NULL, 0);
		if(FD_ISSET(fd, &set)) {
			rc = read(fd, buf, sizeof(buf));
			if (rc < 0)
				printf("errno:%d\n", errno);
			if (rc == 0)
				continue;

			Tprint_hex_dump("serial:", buf, rc);
			memset(buf, 0, sizeof(buf));
		}
	}
}

