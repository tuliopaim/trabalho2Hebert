/*
----------------------------------------------------------------------------
As funções implementadas por Matheus fecham o arquivo depois que elas acabam
----------------------------------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "T3D.h"

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
	fscanf(arq,"%lf %lf %lf",&Obj->matriz[0][0],&Obj->matriz[1][0],&Obj->matriz[2][0]);
	fclose(arq);
}

Mat4x4 Trans(Mat4x4 M, double deltaX, double deltaY, double deltaZ){
	int i, j;
	
	//CRIA MATRIZ TRANS A SER MULTIPLICADA PELA COORDENADA
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(i==j) M.matriz[i][j] = 1;
			else if(i==0 && j==3) M.matriz[i][j] = deltaX;
			else if(i==1 && j==3) M.matriz[i][j] = deltaY;
			else if(i==2 && j==3) M.matriz[i][j] = deltaZ;
			else M.matriz[i][j] = 0;
		}
	}

	//mat4x4 * result = multiplicaMatriz(T);

	return M;

}

Mat4x4 Escala(Mat4x4 M, double FX, double FY, double FZ){
	int i, j;
	//CRIA MATRIZ ESCALA A SER MULTIPLICADA PELA COORDENADA
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(i==0 && j==0) M.matriz[i][j] = FX;
			else if(i==1 && j==1) M.matriz[i][j] = FY;
			else if(i==2 && j==2) M.matriz[i][j] = FZ;
			else if(i==3 && j==3) M.matriz[i][j] = 1;
			else M.matriz[i][j] = 0;
		}
	}

	//mat4x4 * result = multiplicaMatriz(T);

	return M;

}

Mat4x4 Rot(Mat4x4 M, int eixo, double angulo){
	int i, j;
	if(eixo == 'X' || eixo == 'x'){
		for(i=0;i<4;i++){
			for(j=0;j<4;j++){
				if((i==0 && j==0) || (i==3 && j==3)) M.matriz[i][j] = 1;
				else if((i==1 && j==1) || (i==2 && j==2)) M.matriz[i][j] = cos(angulo);
				else if(i==1 && j==2) M.matriz[i][j] = -1 * sin(angulo);
				else if(i==2 && j==1) M.matriz[i][j] = sin(angulo);
				else M.matriz[i][j] = 0;
			}
		}
	}
	else if(eixo == 'Y' || eixo == 'y'){
		for(i=0;i<4;i++){
			for(j=0;j<4;j++){
				if((i==1 && j==1) || (i==3 && j==3)) M.matriz[i][j] = 1;
				else if((i==0 && j==0) || (i==2 && j==2)) M.matriz[i][j] = cos(angulo);
				else if(i==0 && j==2) M.matriz[i][j] = -1 * sin(angulo);
				else if(i==2 && j==0) M.matriz[i][j] = sin(angulo);
				else M.matriz[i][j] = 0;
			}
		}
	}
	else if(eixo == 'Z' || eixo == 'z'){
		for(i=0;i<4;i++){
			for(j=0;j<4;j++){
				if((i==2 && j==2) || (i==3 && j==3)) M.matriz[i][j] = 1;
				else if((i==0 && j==0) || (i==1 && j==1)) M.matriz[i][j] = cos(angulo);
				else if(i==0 && j==1) M.matriz[i][j] = -1 * sin(angulo);
				else if(i==1 && j==0) M.matriz[i][j] = sin(angulo);
				else M.matriz[i][j] = 0;
			}
		}
	}
	return M;
}

Mat4x4 MatComp(Mat4x4 M1, Mat4x4 M2){
	int x, i, j;
	Mat4x4 F;
	for(x=0;x<4;x++){
		for(i=0;i<4;i++){
			F.matriz[x][i] = 0;
			for(j=0;j<4;j++){
				F.matriz[x][i] += M1.matriz[x][j] * M2.matriz[j][i];
			}
		}
	}
	return F;
}

Mat4x1 MatTransf(Mat4x4 M, Mat4x1 P){
	int i, j;
	double temp;
	Mat4x1 v;
	for(i=0;i<4;i++){
		v.matriz[i][0] = 0;
		for(j=0;j<4;j++){
			v.matriz[i][0] += P.matriz[j][0] * M.matriz[i][j];
			#ifdef DEBUG
			printf("%.2lf * %.2lf = %.2lf\n", P.matriz[j][0], M.matriz[i][j], v.matriz[i][0]);
			#endif
		}
	}
	return v;
}

void ImprimeNoArquivo(Mat4x1 *Obj, char* fName){
	FILE * arq;
	//abrindo o arquivo
	arq = fopen(fName,"a+");
	if(arq == NULL){
		printf("Erro ao abrir o arquivo\n");
	}
	//coloca as coordenadas x, y e z no arquivo "Arq"
	fprintf(arq, "%lf %lf %lf\n",Obj->matriz[0][0],Obj->matriz[1][0],Obj->matriz[2][0]);
	fclose(arq);
}

Mat4x1 * AlocaMat4x1(){
	Mat4x1 * new;
	//alocando
	new = malloc(sizeof(Mat4x1));
	//conferindo se não foi alocado
	if (new == NULL){
		printf("Erro ao alocar uma nova matriz 4x1\n");
		return NULL;
	}
	new->matriz[3][0] = 1;
	return new;
}

Mat4x4 * AlocaMat4x4(){
	Mat4x4 * new;
	//alocando
	new = malloc(sizeof(Mat4x4));
	//conferindo se não foi alocado
	if (new == NULL){
		printf("Erro ao alocar uma nova matriz 4x4\n");
		return NULL;
	}
	return new;
}

void imprimeMat4x1(Mat4x1 * elemento){
	printf("Coordenadas (x,y,z,t) : (%.2lf,%.2lf,%.2lf,%.2lf)\n",elemento->matriz[0][0],elemento->matriz[0][1],elemento->matriz[0][2], elemento->matriz[0][3]);
}

void imprimeMat4x4(Mat4x4 * M){
	int i, j;
	printf("\tMATRIZ\n");
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			printf((j==3) ? "%.2lf\n" : "%.2lf ", M->matriz[i][j]);
		}
	}
}