#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "T3D.h"

/*
TIPOS DE DADOS
*/
struct mat4x1{
	double matriz[4][1];
	struct mat4x1 * prox;
};

struct mat4x4{
	double matriz[4][4];
};

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
	FILE * out;
	//abrindo o arquivo
	out = fopen(fName,"a+");
	if(out == NULL){
		printf("Erro ao abrir o arquivo\n");
	}
	//coloca as coordenadas x, y e z no arquivo "Arq"
	int i;
	Mat4x1 * percorre = Obj->prox;
	while(percorre!=NULL){
		for (i=0;i<3;i++){
			if(*percorre->matriz[i]==(int)*percorre->matriz[i])
				fprintf(out, (i==2) ? "%d\n" : "%d ", (int)*percorre->matriz[i]);
			else fprintf(out,(i==2) ? "%.3lf\n" : "%.3lf ", *percorre->matriz[i]);
		}
		percorre = percorre->prox;
	}
	fclose(out);
}

void imprimeMat4x1(Mat4x1 * elemento){
	int i;
	for(i=0;i<3;i++) printf((i==2) ? "%lf\n" :" %lf ", elemento->matriz[i]);
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

void Cria(Mat4x1 *Obj, char * fName){
	FILE * arq;

	//abrindo arquivo "arq"
	arq = fopen(fName,"a+");
	if (arq == NULL){
		printf("Erro ao abrir o aquivo para a leitura dos dados\n");
		return ;
	}

	int n, i, j;
	double * coordenadas;
	coordenadas = malloc(sizeof(double)*3);
	fscanf(arq, "%d ", &n);
	for(i=0;i<n;i++){
		coordenadas = ler(arq, coordenadas);
		lista_insere(Obj, coordenadas[0], coordenadas[1], coordenadas[2]);
	}

}

double * ler(FILE * p, double * vetor){
	int j=0, i;
	double temp;
	//LER VETORES DE ARQUIVO E ARMAZENAR
	for(i=0;i<3;i++){
		fscanf(p, "%lf ", &temp);
		vetor[j++] = temp;
	}
	return vetor;
}

Mat4x1 * lista_inicia(){
    Mat4x1 * LISTA = (Mat4x1*)malloc(sizeof(Mat4x1));
    if(!LISTA){
        printf("Não alocada!\n");
        exit(1);
    }
    LISTA->prox = NULL;
    return LISTA;
}

void lista_insere(Mat4x1 * COORD, double x, double y, double z){
  	int i;
	Mat4x1 * percorre = COORD;
	Mat4x1 * novo = lista_inicia();
  	while(percorre->prox!=NULL) percorre = percorre->prox;
  	percorre->prox = novo;
  	novo->matriz[0][0] = x;
  	novo->matriz[1][0] = y;
  	novo->matriz[2][0] = z;
  	novo->matriz[3][0] = 1;
  	/*
  	for(i=0;i<4;i++) printf("%lf ", novo->matriz[i][0]);
  	printf("\n");*/
}

Mat4x4 pegaMatrizes(char * fName){
	FILE * in;
	double * cache;
	cache = malloc(sizeof(double)*3);
	in = fopen(fName, "r");
	//PASSAR PELAS COORDENADAS
	int i, j, n;
	fscanf(in, "%d ", &n);
	for(i=0;i<n;i++){
		cache = ler(in, cache);
	}

	Mat4x4 final;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++){
			if(i==j) final.matriz[i][j] = 1;
			else final.matriz[i][j] = 0;
		}

	char op;
	while(!feof(in)){
		fscanf(in, "%c ", &op);
		if(op == 'T'){
			double dX, dY, dZ;
			fscanf(in, "%lf %lf %lf ", &dX, &dY, &dZ); //LÊ OS VALORES
			Mat4x4 trans = Trans(trans, dX, dY, dZ); //MATRIZ TRANS
			final = MatComp(final, trans);
			//imprimeMat4x4(&final);
		}else if(op == 'R'){
			char eixo;
			double ang;
			fscanf(in, "%c %lf ", &eixo, &ang);
			Mat4x4 rota = Rot(rota, eixo, ang);
			final = MatComp(final, rota);
			//imprimeMat4x4(&final);
		}else if(op == 'S'){
			double Fx, Fy, Fz;
			fscanf(in, "%lf %lf %lf ", &Fx, &Fy, &Fz);
			Mat4x4 escala = Escala(escala, Fx, Fy, Fz);
			final = MatComp(final, escala);
			//imprimeMat4x4(&final);
		}
	}
	return final;
}

void perMult(Mat4x1 * cord, Mat4x4 transforma){
	Mat4x1 * percorre = cord->prox;
	Mat4x1 temp, pontos;
	int i;
	while(percorre!=NULL){
		for(i=0;i<4;i++) pontos.matriz[i][0] = percorre->matriz[i][0];
		temp = MatTransf(transforma, pontos);
		for(i=0;i<4;i++) percorre->matriz[i][0] = temp.matriz[i][0];
		percorre = percorre->prox;
	}
}

void MakeItHappen(char * in, char * out){
	int i, j,n;

	//LISTA DE COORDENADAS
	Mat4x1 * cord = lista_inicia();
	Cria(cord, in);

	//MATRIZ TRANSFORMAÇÃO
	Mat4x4 transforma;
	transforma = pegaMatrizes(in);

	//PERCORRER E MULTIPLICAR
	perMult(cord, transforma);

	//ABRIR ARQUIVOS E IMPRIMIR O Nº DE CASOS
	FILE * entrada = fopen(in, "r");
	FILE * saida = fopen(out, "a+");
	fscanf(entrada, "%d", &n);
	fprintf(saida, "%d\n", n);
	fclose(entrada);
	fclose(saida);

	//BURN
	Imprime(cord, out);
}
