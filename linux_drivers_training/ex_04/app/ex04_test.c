/*
file name:		ex04_test.c
purpose:		it's demo codes,show how to use ioctl to get/set value from/to kernel space
author:			guangwei jiang
create time:	Jan13'10

Notes:
	Test Enviroment: Ubuntu9.04 (kernel 2.6.28-17)

modified history:
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#define EX04_IOCTL_MAGIC 'v'

#define EX04_IOCTL_TEST			_IO(EX04_IOCTL_MAGIC, 1000)
#define EX04_IOCTL_GET_VAL		_IOR(EX04_IOCTL_MAGIC , 1001, int)
#define EX04_IOCTL_SET_VAL		_IOW(EX04_IOCTL_MAGIC , 1002, int)

int main()
{
	int rc = 0;
    int fd = -1;
	int test_val = 99;

	printf("ex04_test: Entry++\n");
	
	fd = open("/dev/ex04_dev", O_RDWR);
    if(fd < 0) {
		printf("ex04_test: open /dev/ex04_dev failed, fd=%d!\n", fd);
        rc = -1;
    } else{
        rc = ioctl(fd, EX04_IOCTL_TEST);
		printf("ex04_test: call EX04_IOCTL_TEST, rc(test_val)=%d\n", rc);
        if (rc < 0) {
        }

		// set the test_val to ex04_dev
		rc = ioctl(fd, EX04_IOCTL_SET_VAL, &test_val);
		printf("ex04_test: call EX04_IOCTL_SET_VAL, test_val=%d\n", test_val);
        if (rc < 0) {
        }

		// get the test_val from ex04_dev
		rc = ioctl(fd, EX04_IOCTL_GET_VAL, &test_val);
		printf("ex04_test: call EX04_IOCTL_GET_VAL, test_val=%d\n", test_val);
        if (rc < 0) {
        }

        close(fd);
    }

	printf("ex04_test: rc = %d, exit--\n", rc);

	return rc;
}
