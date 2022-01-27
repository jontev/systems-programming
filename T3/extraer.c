#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void extraer(char *filename);

int main(int argc, char *argv[]){

  	char *filename = argv[1];

  	extraer(filename);

	return 0;
}

void extraer(char *filename){

	FILE *fp;
	fp = fopen(filename, "r+");

	char firstline[5];
	fread(firstline, sizeof(firstline), 1, fp);
	int n = atoi(firstline);
	int m = n;
	if(n==0){
		printf("%s\n", "error: cola.txt esta vacía");
		exit(1);
	}

	size_t readcount;
	char currentline[17];
	char *t;
	char prioline[17];
	int prio = 9090909; 
	int currprio;
	long int pos;

	while( (readcount = fread(currentline, sizeof(currentline), 1, fp)) ==1){
		n--;			
		t = currentline;

		t+=10;

		currprio = atoi(t);
		if(currprio < prio){
			pos = ftell(fp) -17;
			prio = currprio;
			strcpy(prioline, currentline);

		}
		if(n == 0){
			
			prioline[10] = 0;
			printf("%s\n", prioline );
			m--;
			fseek(fp, pos, SEEK_SET);
			fwrite(currentline, sizeof(char), sizeof(currentline), fp);

			fseek(fp, 0, SEEK_SET);
			char s[6], d[5];
			sprintf(s, "%-4d\n", m);
			memcpy(d,s, 5);

			fwrite(d, sizeof(char), sizeof(d), fp);
			
			break;
		}
	}
	fclose(fp);
}



 