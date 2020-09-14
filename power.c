#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <asm/ioctl.h>
#include <sys/ioctl.h>
#include <linux/parport.h>
#include <linux/ppdev.h>
#include <string.h>

#define DEVICE "/dev/parport0"

int main(int argc, char **argv)
{
	int fd, ret;
        unsigned char data;

        if (argc != 2) {
            printf("Usage: %s <on|off>\n", argv[0]);
            exit(2);
        } else {
            if (strcmp(argv[1], "on") == 0) {
                data = 0xFF;
            } else if (strcmp(argv[1], "off") == 0) {
                data = 0x00;
            } else {
                printf("Sorry, can't understand argument %s\n", argv[1]);
                printf("Usage: %s <on|off>\n", argv[0]);
                exit(2);
            }
        }

	if ((fd=open(DEVICE, O_RDWR)) < 0) {
             printf("Can't open device %s\n", DEVICE);
             exit(1);
	}

	if (ioctl(fd, PPCLAIM)) {
	    perror("PPCLAIM");
            close(fd);
            exit(1);
	}

        if (ioctl(fd, PPWDATA, &data)) {
             perror("can't write to device");
             exit(1);
        }

        ioctl(fd, PPRELEASE);
        close(fd);
        exit(0);
}
