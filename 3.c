#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

int main() {
    int f, f1, n;
    f = open("read.txt", O_CREAT | O_RDWR, 0777);
    char buf[50];
    lseek(f, 25, SEEK_SET);
    n = read(f, buf, 5);
    f1 = open("write.txt", O_CREAT | O_RDWR, 0777);
    write(f1, buf, n);
}