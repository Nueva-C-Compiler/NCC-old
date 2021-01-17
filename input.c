

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>


#define SECTOR_SIZE 4096

int src; // File descriptor for source code.
char buf1[SECTOR_SIZE];
char buf2[SECTOR_SIZE];

char* current_buf = buf1;
char* standby_buf = buf2;
char* lex_beg = buf1;
char* forward = buf1;

int advance()
{
    if (forward != &current_buf[SECTOR_SIZE]-1) forward++;
    else {
        ssize_t bytes_read = read(src, standby_buf, SECTOR_SIZE);
        if (bytes_read == -1) return -1;
        else if (bytes_read == 0) return 0;
        forward = &standby_buf[0];
        char* tmp = current_buf;
        current_buf = standby_buf;
        standby_buf = tmp;
    }
}

int main(int argc, char** argv) {
    src = open(argv[1], O_RDONLY);
    if (src == -1) {
        printf("Invalid file.\n");
        return -1;
    }
    ssize_t bytes_read = read(src, current_buf, SECTOR_SIZE);
    if (bytes_read == -1) {
        printf("Reading error - check errno.\n");
        return -1;
    }
    else if (bytes_read == 0) return -1;
    while (advance() > 0) {
        printf("%c", *forward);
    }
}



