#include <stdio.h>
#include <stdlib.h>
#include "T3D.h"

#define DEBUG

void test(int inteiro){
	if(inteiro == 'c') printf("deu!\n");
	else printf("Não deu n\n");
}


int main (){
	FILE * arq;
	Mat4x1 * teste;
	teste = AlocaMat4x1();
	arq = fopen("entradas.txt","r");
	Cria(teste,"entradas.txt");

	imprimeMat4x1(teste);

	//TESTE MatComp
	Mat4x4 m1;
	Mat4x4 m2;

	for (int i = 0; i < 4; ++i){
		for(int j=0;j<4;j++){
			m1.matriz[i][j] = 1;
			m2.matriz[i][j] = 1;
		}
	}

	m2 = MatComp(m1, m2);
	imprimeMat4x4(&m2);

	//TESTE MatTransf
	Mat4x4 mat;
	Mat4x1 vet;

	for (int i = 0; i < 4; ++i) vet.vetor[i] = 1;

	for (int i = 0; i < 4; ++i){
		for(int j=0;j<4;j++){
			mat.matriz[i][j] = 1;
		}
	}

	vet = MatTransf(mat, vet);

	imprimeMat4x1(&vet);



	//TESTE ESCALONAMENTO
	double deltaX,deltaY,deltaZ;
	printf("Coordenadas de escalonamento:");
	scanf("%lf %lf %lf", &deltaX, &deltaY, &deltaZ);

	Mat4x4 M = Trans(M, deltaX, deltaY, deltaZ);

	imprimeMat4x4(&M);

	//TESTE TRANSLAÇÃO
	double FX, FY, FZ;
	printf("Coordenadas de escala:");
	scanf("%lf %lf %lf", &FX, &FY, &FZ);

	Mat4x4 S = Escala(S, FX, FY, FZ);

	imprimeMat4x4(&S);


	//TESTE ROTAÇÃO
	char type;
	double ang, val = PI / 180;
	scanf(" %c %lf", &type, &ang);

	Mat4x4 R = Rot(R, type, val*ang);

	imprimeMat4x4(&R);
	

	return 0;
}