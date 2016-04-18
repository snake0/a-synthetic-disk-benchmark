#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define SIZE (4*1024)

int main (int argc, char *argv[]) {

        int fd;
        off_t file_size, num, i;
        char buf[SIZE];

        fd = open(argv[1], O_RDWR | O_CREAT , S_IRWXU);
        if(fd == -1) {printf("open %s fail!\n", argv[1]); exit(1);}

        memset(buf, 0x20, 8);

        file_size = 1024*1024*1024;
        //file_size = 512*512*512;
        num = file_size/SIZE;

        for(i = 0; i < num; i++)
                write(fd, buf, SIZE);

        close(fd);
        return 0;
}
