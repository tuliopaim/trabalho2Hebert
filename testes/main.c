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


	Mat4x1 vet;
	vet.matriz[0][0] = 0;
	vet.matriz[1][0] = 0;
	vet.matriz[2][0] = 0;
	vet.matriz[3][0] = 1;

	imprimeMat4x1(&vet);

	Mat4x4 fim;

	//TRANSPOSTA 1
	Mat4x4 MatT;
	MatT = Trans(MatT, 7.5, 7.5, 0);
	printf("Matriz Trans\n");
	imprimeMat4x4(&MatT);

	//ROTACIONAR
	Mat4x4 MatRot;
	MatRot = Rot(MatRot, 'Z', 30);
	printf("Matriz Rot\n");
	imprimeMat4x4(&MatRot);

	fim = MatComp(MatT, MatRot); // MULTIPLICA AS DUAS

	//TRANS 2
	Mat4x4 MatT2;
	MatT2 = Trans(MatT2, -7.5, -7.5, 0);
	printf("Matriz Trans2\n");
	imprimeMat4x4(&MatT2);

	fim = MatComp(fim, MatT2); // MULTIPLICA AS DUAS
	
	//APLICA NO PONTO
	Mat4x1 final;
	final = MatTransf(fim, vet);
	imprimeMat4x1(&final);



	return 0;
}