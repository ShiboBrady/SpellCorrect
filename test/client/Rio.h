#ifndef RIO_H
#define RIO_H 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#define RIO_BUFFERSIZE 8192
#define ERR_EXIT(m) \
        do { \
                perror(m);\
                exit(EXIT_FAILURE);\
            }while(0)

typedef struct rio_t{
    ssize_t left_;
    char buffer_[RIO_BUFFERSIZE];
    char *bufPtr_;
    int fd_;
}rio_t;

void rio_init(rio_t *r, int fd);
ssize_t rio_read(rio_t *r, char *usrbuf, size_t len);
ssize_t rio_readn(rio_t *r, char *usrbuf, size_t len);
ssize_t rio_readline(rio_t *r, char *usrbuf, size_t len);

#endif  /*RIO_H*/
