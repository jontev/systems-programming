#include <stdio.h>
#include <stdlib.h>
#include "integral.h"
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

double integral_par(Funcion f, void *ptr, double xi, double xf, int n, int p) {
	double step = (double)(fabs(xi)+fabs(xf))/p;
	int fd[2];
	pipe(fd);
	pid_t pids[p];		
	double vals[p];

	for(int i = 0; i<p; i++){
		pids[i] = fork();
		if(pids[i] == 0){
			close(fd[0]);
			vals[i] = integral(f, ptr, xi+step*i, xi+step*(i+1), n/p);
			write(fd[1], &vals[i], sizeof(double));
			exit(0);
		}
	}
	double res = 0;

	for(int i=0; i<p; i++){
		wait(NULL);
		close(fd[1]);
		read(fd[0], &vals[i], sizeof(double));
		res+= vals[i];
	}

  return res;   
}


