#include <stdio.h>
#include <stdlib.h>
#include "integral.h"
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


void func(void* args){

	int *d = (int*) args;
	int a = *d;
	printf("%d\n", a);


}


void main(void){
	int p = 4;
	int data[] = {0,1,2,3};

	int fd[2];
	pipe(fd);

	pid_t pids[p];		

	for(int i = 0; i<p; i++){
		printf("loop nr %d\n",i );
		pids[i] = fork();
		if(pids[i] == 0){
			printf("Child jobbar...\n");
			close(fd[0]);
			printf("Child: %d Parent: %d\n",(int)getpid(), (int)getppid());
			func(&data[i]);
			write(fd[1], &data[i], sizeof(data[i]));
			exit(0);
		}
		else{

			printf("Parent jobbar...\n");
		/*	close(fd[1]);
			func(&data[i]);
			read(fd[0], (char*)&data[i], sizeof(data[i]));
			close(fd[0]);
			*/
			waitpid(pids[i], NULL, 0);

		}
	}


}