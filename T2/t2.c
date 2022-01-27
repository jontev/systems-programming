 
#include <stdlib.h>
#include <stdio.h>

typedef struct nodo{
	int x;
	struct nodo *izq, *der;

} Nodo;
	

int calzar(Nodo *a, Nodo **ppat){

	Nodo *p = *ppat;
	
	//base case 1
	if(p == NULL){
		if (a->x != 0){
			*ppat = a;

			return 1;
		}
	}
	//base case 2
	if(a == NULL){
		if (p->x != 0){
			return 0;
		}
	}
	//base case 3
	if(a->x !=0 && p->x !=0 && a->x != p->x){ 
		return 0;
	}
	
	//recursion
	if (a->x == p->x){
			
			if(calzar(a->izq, &((*ppat)->izq))){

				if(!calzar(a->der, &((*ppat)->der))){
					return 0;
				}

			}
		return 1;

	}
	return 1;
}
