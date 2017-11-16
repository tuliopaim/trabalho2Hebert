#include <stdio.h>
#include <stdlib.h>
#include "T3D.h"

#define DEBUG

int main (){
	FILE * arq;
	Mat4x1 * teste;
	teste = AlocaMat4x1();
	arq = fopen("entradas.txt","r");
	Cria(teste,"entradas.txt");

	//ESCALONAMENTO
	double deltaX,deltaY,deltaZ;
	printf("Coordenadas de escalonamento:");
	scanf("%lf %lf %lf", &deltaX, &deltaY, &deltaZ);

	Mat4x4 M;// AlocaMat4x4();
	M = Trans(M, deltaX, deltaY, deltaZ);

	imprimeMat4x4(&M);

	//TRANSLAÇÃO
	double FX, FY, FZ;
	printf("Coordenadas de escala:");
	scanf("%lf %lf %lf", &FX, &FY, &FZ);

	Mat4x4 S; //= AlocaMat4x4();
	S = Escala(S, FX, FY, FZ);

	imprimeMat4x4(&S);

	imprimeMat4x1(teste);
	return 0;
}