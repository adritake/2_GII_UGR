// Orden de compilacion: gcc -m32 bomba.c -o bomba


#include <stdio.h>	// para printf()
#include <stdlib.h>	// para exit()
#include <string.h>	// para strncmp()/strlen()
#include <sys/time.h>	// para gettimeofday(), struct timeval

/*

Voy a codificar la contraseña de tal manera que los indices que son primos corresponden a un caracter de la contraseña ( explosion )

char codigo[]={'a','t','e','x','u','p','s','l','s','o','w','o','y','s','g','h','z','i','q','o','l','k','k','n','q','w','f','r','h','\n'};
			 // 0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28   29
			 //         *   *       *       *              *       *               *       *               *                        *

*/

char codigo[]="atexupslsowoysghziqolkknqwfrh\n";


char password[10];
int  passcode  = 1234;

void boom(){
	printf("***************\n");
	printf("*** BOOM!!! ***\n");
	printf("***************\n");
	exit(-1);
}

void defused(){
	printf("·······························\n");
	printf("·······Bomba desactivada·······\n");
	printf("·······························\n");
	exit(0);
}

int es_primo( int n ){

	int primo = 0;
	int i;
	int lista_primos[]={2,3,5,7,11,13,17,19,23,29};

	for( i = 0; i < 10; i++)

		if( lista_primos[i] == n)
			primo = 1;

	return primo;

}


void decodifica(){

	int i,j=0;
	for( i = 0; i <= 29; i++){
		if( es_primo(i) ){
			password[j] = codigo[i];
			j++;
		}
	}
}


int main(){
#define SIZE 100
	char pass[SIZE];
	int  pasv;
#define TLIM 60
	struct timeval tv1,tv2;	// gettimeofday() secs-usecs

	gettimeofday(&tv1,NULL);


	printf("Introduce la contraseña: ");
	fgets(pass,SIZE,stdin);

	decodifica();
	if (strncmp(pass,password,strlen(password)))
	    boom();

	gettimeofday(&tv2,NULL);
	if (tv2.tv_sec - tv1.tv_sec > TLIM)
	    boom();

	printf("Introduce el código: ");
	scanf("%i",&pasv);
	decodifica();
	if (pasv!=passcode) boom();

	gettimeofday(&tv1,NULL);
	if (tv1.tv_sec - tv2.tv_sec > TLIM)
	    boom();

	defused();
}
