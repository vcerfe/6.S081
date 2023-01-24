#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"
#define MAX_LEN 100
   
int main(int argc, char *argv[]) {
    char *command = argv[1];
	char bf;
	char paramv[MAXARG][MAX_LEN]; 
	char *m[MAXARG];
   
	while (1) {
		int count = argc-1;  
		memset(paramv, 0, MAXARG * MAX_LEN);
		// copy the parameter of command
		for (int i=1; i<argc; i++) {
			strcpy(paramv[i-1], argv[i]);
		}
   
		int cursor = 0; 
		int flag = 0; 
		int read_result;
   
		while (((read_result = read(0, &bf, 1))) > 0 && bf != '\n') {
			if (bf == ' ' && flag == 1) {
				count++;
				cursor = 0;
				flag = 0;
			}
			else if (bf != ' ') {
				paramv[count][cursor++] = bf;
				flag = 1;
			}
		}


		for (int i=0; i<MAXARG-1; i++) {
			m[i] = paramv[i];
		}
		m[MAXARG-1] = 0;
		if (fork() == 0) {
			exec(command, m);
			exit(0);
		} else {
			wait((int *) 0);
		}
		if (read_result <= 0) {
			break;
		}
	}
	exit(0);
}