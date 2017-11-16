/*
----------------------------------------------------------------------------
As funções implementadas por Matheus fecham o arquivo depois que elas acabam
----------------------------------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include "T3D.h"

/*
TIPOS DE DADOS
*/
struct mat4x1{
	double x,y,z;
};

struct mat4x4{
	double matrix[4][4];
};


/*
IMPLEMENTAÇÃO DAS FUNÇÕES
*/

void Cria(Mat4x1 *Obj, char* fName){
	FILE * arq;
	//abrindo arquivo "arq"
	arq = fopen(fName,"r");
	if (arq == NULL){
		printf("Erro ao abrir o aquivo para a leitura dos dados\n");
		return ;
	}
	//lendo e preenchendo a matriz 4x1
	fscanf(arq,"%lf %lf %lf",&Obj->x,&Obj->y,&Obj->z);
	fclose(arq);
}

Mat4x4 Trans(Mat4x4 M, double deltaX, double deltaY, double deltaZ){

}

Mat4x4 Escala(Mat4x4 M, double FX, double FY, double FZ){

}

Mat4x4 Rot(Mat4x4 M, int eixo, double angulo){

}

Mat4x4 MatComp(Mat4x4 M1, Mat4x4 M2){

}

Mat4x1 MatTransf(Mat4x4 M, Mat4x1 P){

}

void Imprime(Mat4x1 *Obj, char* fName){
	FILE * arq;
	//abrindo o arquivo
	arq = fopen(fName,"a+");
	if(arq == NULL){
		printf("Erro ao abrir o arquivo\n");
	}
	//coloca as coordenadas x, y e z no arquivo "Arq"
	fprintf(arq, "%lf %lf %lf %lf\n",Obj->x,Obj->y,Obj->z);
	fclose(arq);
}