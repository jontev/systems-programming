#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#include "impr.h"

static int PRINTING;

struct orden {
	int finished;
	Doc* doc;
};


ColaFifo* cola;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

pthread_t *threads;
int N_threads;
void *f(void* arg);



void init_impr(Impr **imprs, int n_impr) {
	PRINTING = 1;
	N_threads = n_impr;
	cola = nuevaColaFifo();
	threads = malloc(n_impr*sizeof(*threads));
	for(int i=0; i<n_impr; i++){
		pthread_create(&threads[i], NULL, f, imprs[i]);
	}
	
}

void terminar_impr() {
  /* no olvide invocar pthread_join para enterrar los threads */
	PRINTING = 0;
	pthread_mutex_unlock(&mutex);
	pthread_cond_signal(&cond);
	for(int i = 0; i<N_threads; i++){	
		pthread_join(threads[i]	, NULL);
	}
	free(threads);
	free(cola);
 }

Orden *imprimir_asinc(Doc *doc) {
	Orden* ord = malloc(sizeof(*ord));
	ord->doc = doc;
	ord->finished = 0;

	pthread_mutex_lock(&mutex);
	while(!vacia(cola)) pthread_cond_wait(&cond, &mutex);
	agregar(cola, ord);
	pthread_cond_broadcast(&cond);
	pthread_mutex_unlock(&mutex);
	return ord;
}

void confirmar(Orden *ord) {
	while(!ord->finished) pthread_cond_wait(&cond, &mutex);
	free(ord);
	pthread_cond_signal(&cond);
 
}


void *f(void* arg){

	Impr* impr = (Impr*)arg;
	while(PRINTING){
		pthread_mutex_lock(&mutex);
		while(vacia(cola)) {
			if(!PRINTING){
				pthread_mutex_unlock(&mutex);
				pthread_cond_signal(&cond);
				return NULL;
			}
			pthread_cond_wait(&cond, &mutex);
		}
		Orden* ord = (Orden*) extraer(cola);
		pthread_mutex_unlock(&mutex);
		imprimir(ord->doc, impr);
		ord->finished = 1;
		pthread_cond_broadcast(&cond);	
	}
	pthread_mutex_unlock(&mutex);
	pthread_cond_signal(&cond);
	return NULL;
}

