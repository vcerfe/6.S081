#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int
main(int argc,char* argv[]){
    if(argc!=2){
        fprintf(2,"ERROR sleep time required");
        exit(1);
    }

    int time = atoi(argv[1]);

    if(time<=0){
        fprintf(2,"ERROR No Vaild");
        exit(1);
    }

    sleep(time);
    exit(0);
}