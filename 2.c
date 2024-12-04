#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

int main() {
    int fd1, n, fd2;
    char buf[50];
    fd1 = open("first.txt", O_RDONLY);
    n = read(fd1,buf,50);

    fd2 = open("second.txt", O_CREAT | O_WRONLY, 0777);
    write(fd2, buf, n);
}