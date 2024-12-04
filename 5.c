#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<unistd.h>
int main(){
pid_t pid1,pid2;
int status;
printf("The parent process ID is %d\n",getpid());
pid1=fork();
if(pid1<0){
        perror("Fork failed\n");
        exit(1);
    }
    if(pid1==0){
        printf("The parent process(P) id of p1 is %d and the p1 processor id is %d\n",getppid(),getpid());
        exit(10);
    }
    else{
        pid2=fork();
        if(pid2<0){
        perror("Fork failed\n");
        exit(1);
    }
    if(pid2==0){
        printf("The parent process(P) id of p2 is %d and the p2 processor id is %d\n",getppid(),getpid());
        exit(20);
    }
    
    else{
        waitpid(pid1, &status, 0);
        printf("Parent Process P : P1 terminated with exit status = %d\n",WEXITSTATUS(status));

        waitpid(pid2, &status, 0);
        printf("Parent Process P : P2 terminated with exit status = %d\n",WEXITSTATUS(status));
    }
    }
}
