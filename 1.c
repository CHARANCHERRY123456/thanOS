#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
int main(){
    pid_t pid1,pid2;
    pid1=fork();
    if(pid1==0){
        printf("The parent process(P) id of p1 is %d and the p1 processor id is %d\n",getppid(),getpid());
        pid2=fork();
        if(pid2==0){
            printf("The parent process id of p2 is %d and the p2 processor id is %d\n",getppid(),getpid());
            execlp("ps","ps","-auxh",NULL);
            perror("execlp failed");
            exit(1);
        }
        else{
            wait(NULL);
        }
    }
    else{
        wait(NULL);
        printf("P : PID = %d , Child P1 PID = %d\n",getpid(),pid1);
    }
}