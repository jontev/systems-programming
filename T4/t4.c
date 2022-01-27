#include <stdio.h>
#include "integral.h"
#include <pthread.h>
#include <math.h>

typedef struct my_params_struct{
	double sum;
	Funcion f;
	void *ptr;
	double xi, xf;
	int n;

} My_Params;

void *aux_integral_par(void *arg){
	My_Params *mp = (My_Params*) arg;
	(mp->sum) += integral(mp->f, mp->ptr, mp->xi, mp->xf, mp->n);
	pthread_exit(0);
}

double integral_par(Funcion f, void *ptr, double xi, double xf, int n, int p) {
	

	pthread_t threads[p];
	My_Params params[p];
	double step = (double)(fabs(xi)+fabs(xf))/p;
	double res = 0;
	int i;
	for(i = 0; i<p; i++){
		params[i].sum = 0;
		params[i].f = f;
		params[i].ptr = ptr;
		params[i].xi = xi+step*i;
		params[i].xf = xi+step*(i+1);
		params[i].n = n/p;
	}
	for(i = 0; i<p; i++){
		printf("Creating thread %d\n", i);
		pthread_create(&threads[i], NULL, aux_integral_par, &params[i]);
	}
	for(i= 0; i<p; i++){
		pthread_join(threads[i], NULL);
	}
	for(i = 0; i<p; i++){
		res += params[i].sum;
	}
	
  return res;   
}


