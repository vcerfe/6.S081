#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define WRITE 1
#define READ 0

int
main(int argc,char* argv[]){
    int p1[2];
    int p2[2];
    int buf[1];
    pipe(p1);
    pipe(p2);

    int pid = fork();
    if(pid < 0)
        exit(1);
    else if(pid == 0){

        read(p1[READ],buf,1);
        printf("%d: received ping\n",getpid());
        write(p2[WRITE],"w",1);
        close(p2[WRITE]);
        close(p1[READ]);
        close(p2[READ]);
        close(p1[WRITE]);
        exit(0);
    }
    else{

        write(p1[WRITE],"g",1);
        read(p2[READ],buf,1);
        printf("%d: received pong\n",getpid());
        close(p1[WRITE]);
        close(p2[READ]);
        close(p1[READ]);
        close(p2[WRITE]);
        exit(0);
    }
}