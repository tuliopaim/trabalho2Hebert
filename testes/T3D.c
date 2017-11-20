
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "T3D.h"

/*
IMPLEMENTAÇÃO DAS FUNÇÕES
*/

void Cria(Mat4x1 *Obj, char* fName){
	int i,qtdPontos;
	double valores[3];
	FILE * arq;
	//abre o arquivo para a leitura das coordenadas
	arq = fopen(fName,"r");
	//lê a quantidade de pontos a serem atribuidos
	fscanf(arq,"%d",&qtdPontos);
	//atribui os valores aos pontos
	for(i = 0; i < qtdPontos;i++){
		fscanf(arq,"%lf %lf %lf",&valores[0],&valores[1],&valores[2]);
		addNode(Obj,valores);
	}
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

Mat4x4 Rot(Mat4x4 M, int eixo, double ang){
	int i, j;
	double angulo = (PI*ang)/180;
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

void Imprime(Mat4x1 *Obj, char* fName){
	FILE * arq;
	Mat4x1 * temp;
	//abre o arquivo fName para a impressão das coordenadas
	arq = fopen(fName,"w");
	temp = Obj->next;
	//imprimindo no arquivo fName as coordenadas
	while(temp != NULL){
		fprintf(arq, "%.3lf %.3lf %.3lf\n",temp->matriz[0][0],temp->matriz[1][0],temp->matriz[2][0]);
		temp = temp->next;
	}
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
	printf("Coordenadas (x,y,z,t) : (%.2lf,%.2lf,%.2lf,%.2lf)\n",elemento->matriz[0][0],elemento->matriz[1][0],elemento->matriz[2][0], elemento->matriz[3][0]);
}

void imprimeMat4x4(Mat4x4 * M){
	int i, j;
	printf("\tMATRIZ\n");
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			printf((j==3) ? "%lf\n" : "%lf ", M->matriz[i][j]);
		}
	}
}

Mat4x1 * createNode(){
	int i;
	Mat4x1 * new;
	//aloca o nó zerando seus valores
	new = malloc(sizeof(Mat4x1));
	if (new != NULL){
		for (i = 0; i < 3;i++){
			new->matriz[i][0];
		}
		new->matriz[3][0] = 1;
		new->next = NULL;
		return new;
	}
	printf ("Erro ao tentar criar o nó\n");
	return NULL;
}

void addNode(Mat4x1 * head,double * valores){
	Mat4x1 * temp, *new;
	int i;
	//chega ao ultimo valor da lista
	temp = head;
	while(temp->next != NULL){
		temp = temp->next;
	}
	//atribui os valores ao nó "new"
	new = createNode();
	for (i = 0;i < 3;i++){
		new->matriz[i][0] = valores[i];
	}
	//coloca new como ultimo elemento da lista
	temp->next = new;	

}

void aplicaTrans(Mat4x1 * Objeto,Mat4x4 M){
	Mat4x1 * temp;
	Mat4x1 a;
	for (temp = Objeto->next;temp != NULL;temp = temp->next){
		a = *temp;
		a = MatTransf(M,a);
		alteraNode(temp,a);
	}
}

void alteraNode(Mat4x1 * elemento,Mat4x1 a){
	int i;
	for(i = 0; i < 3;i++){
		elemento->matriz[i][0] = a.matriz[i][0];
	}
}

void imprimeObjeto(Mat4x1 * Obj){
	int i = 1;
	Mat4x1 * temp;
	for (temp = Obj->next; temp != NULL; temp = temp->next){
		printf("Coordenadas do ponto %d : (%.2lf ,%.2lf ,%.2lf)\n",i,temp->matriz[0][0],temp->matriz[1][0],temp->matriz[2][0]);
		i++;
	}
}
