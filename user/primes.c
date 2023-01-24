#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define READ 0
#define WRITE 1

void func(int* p);

int
main(int argc,char* argv[]){
    int pip[2];
    pipe(pip);
    int pid = fork();
    if(pid < 0)
        exit(1);
    else if(pid == 0){
        func(pip);
    }
    else{
        close(pip[READ]);
        int i=2;
        for(i=2;i<36;++i){
            write(pip[WRITE],&i,sizeof(int));
        }
        close(pip[WRITE]);
        wait((int*) 0);
    }
    exit(0);
}

void func(int* p){
    close(p[WRITE]);

    int num,num1;
    int p1[2];
    int read_con = read(p[READ],&num1,sizeof(int));
    if(read_con == 0){
        exit(0);
    }
    
    printf("prime %d\n",num1);
    pipe(p1);

    int pid = fork();
    if(pid<0)
        exit(1);
    else if(pid == 0){
        func(p1);
    }
    else{
        close(p1[READ]);
        while(read(p[READ],&num,sizeof(int))){
            if(num%num1){
                write(p1[WRITE],&num,sizeof(int));
            }
        }
        close(p1[WRITE]);
        close(p[READ]);
        wait((int*)0);
        exit(0);
    }
}