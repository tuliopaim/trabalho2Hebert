#include <stdio.h>
#include <stdlib.h>
#include "T3D.h"

#define DEBUG

int main (){
	int qtdpontos,i,lixo;
	char opt,eixoRot;
	double deltaX,deltaY,deltaZ,angulos,FX,FY,FZ;
	Mat4x1 * Objeto, * temp;
	Mat4x4 transfor;
	FILE * arq;
	//cria objeto a ser transformado
	Objeto = createNode();
	Cria(Objeto,"entradas.txt");
	//abre o arquivo para a leitura das transformações
	arq = fopen("entradas.txt","r");
	//move o cursor para a primeira tranformação
	fscanf(arq,"%d",&qtdpontos);
	for(i = 0; i < qtdpontos;i++){
		fscanf(arq,"%d %d %d",&lixo,&lixo,&lixo);
	}
	//realiza as tranformações do arquivo
	i = 1;
	while(fgetc(arq) != EOF){
		//lê a opção desejada
		fscanf(arq,"%c",&opt);
		//Transalação
		if (opt == 't' || opt == 'T'){
			fscanf(arq,"%lf %lf %lf",&deltaX,&deltaY,&deltaZ);
			//preenche a matriz "transfor"
			transfor = Trans(transfor,deltaX,deltaY,deltaZ);
			//aplica a transformação para todos os pontos
			aplicaTrans(Objeto,transfor);
		}
		//Rotação
		if (opt == 'r' || opt == 'R'){
			fseek(arq,1,SEEK_CUR);
			fscanf(arq,"%c %lf",&eixoRot,&angulos);
			transfor = Rot(transfor,eixoRot,angulos);
			aplicaTrans(Objeto,transfor);
		}
		//Escalonamento
		if(opt == 'e' || opt == 'E'){
			fscanf(arq,"%lf %lf %lf",&FX,&FY,&FZ);
			transfor = Escala(transfor,FX,FY,FZ);
			aplicaTrans(Objeto,transfor);
		}
		i++;
	}
	Imprime(Objeto,"saidas.txt");
	fclose(arq);
	return 0;
}