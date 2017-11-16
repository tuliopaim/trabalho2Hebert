#include <stdio.h>
#include <stdlib.h>
#include "T3D.h"


int main (){
	FILE * arq;
	Mat4x1 * teste;
	teste = AlocaMat4x1();
	arq = fopen("entradas.txt","r");
	Cria(teste,"entradas.txt");
	imprimeMat4x1(teste);
	return 0;
}