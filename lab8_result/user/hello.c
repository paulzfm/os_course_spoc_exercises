#include <stdio.h>
#include <ulib.h>

int
main(void) {
    cprintf("Hello world!!.\n");
    cprintf("I am process %d.\n", getpid());

    int fdd = open("/Home/test.txt",O_RDWR);
    char buffer[1020];
    int ret = read(fd, buffer, 100);

    cprintf("hello pass.\n");
    return 0;
}
