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

	Mat4x4 MatT;
	MatT = Trans(MatT, 7.5, 7.5, 0);

	imprimeMat4x4(&MatT);

	Mat4x4 MatR;
	MatR = Rot(MatR, 'Z', 30);

	imprimeMat4x4(&MatR);

	Mat4x4 MatT2;
	MatT2 = Trans(MatT2, -7.5, -7.5, 0);

	imprimeMat4x4(&MatT2);

	Mat4x4 Fim;
	Fim = MatComp(MatT, MatR);
	imprimeMat4x4(&Fim);
	Fim = MatComp(Fim, MatT2);
	imprimeMat4x4(&Fim);

	Mat4x1 vet;
	vet.matriz[0][0] = 0;
	vet.matriz[1][0] = 15;
	vet.matriz[2][0] = 15;
	vet.matriz[3][0] = 1;

	Mat4x1 Final;
	Final = MatTransf(Fim, vet);

	imprimeMat4x1(&Final);
	

	return 0;
}