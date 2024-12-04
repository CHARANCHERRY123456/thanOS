#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

int main(){
    int f1, f2, n, m;
    char buf[50];
    f1 = open("read.txt", O_RDWR);
    n = read(f1, buf, 30);
    f2 = open("write1.txt", O_APPEND);
    write(f2, buf, n);
    lseek(f2, -5, SEEK_END);
    m = read(f2, buf, 5);
    write(2, buf, m);
}
