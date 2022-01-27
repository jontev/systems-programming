
#include <stdlib.h>
#include <string.h>

typedef unsigned int uint;

uint comprimir(uint *a, int nbits){
	
	uint mask = ((1<<nbits)-1);
	uint result = 0;
	int k = (int) sizeof(uint)*8/nbits;

	for(int i = 0; i < k; i++){
		a[i] = a[i] & mask;
		a[i] = a[i] << nbits*(k-i-1);
		result = result | a[i];
	}	
	return result;
}

char *insercion(char *d, char *s){

	char *concatenated = malloc(sizeof(char)*(strlen(d) + strlen(s) + 1)); 

	
	strcpy(concatenated, s);	
	
	strcat(concatenated, d);

return concatenated;
}

void insertar(char *d, char *s) {
	
	int sizeOfD = strlen(d);
	int sizeOfS = strlen(s);
	char *pointerD;
	char *pointerLastD;
	char *pointerLastConcatenated;
	pointerD = d;
	*pointerD = *d; 

	pointerLastD = d;
	*pointerLastD = *d;
	pointerLastD += sizeOfD-1;

	pointerLastConcatenated = d;
	*pointerLastConcatenated = *d;
	pointerLastConcatenated+= (sizeOfD + sizeOfS-1); 

	while(*pointerLastD){
		*pointerLastConcatenated = *pointerLastD;
		pointerLastConcatenated--;
		pointerLastD--;
	} 

	while(*s){
		*pointerD = *s;
		pointerD++;
		s++;
	}

}
