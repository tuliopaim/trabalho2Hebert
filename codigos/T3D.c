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


//GERA A MATRIZ TRANSLAÇÃO
Mat4x4 Trans(Mat4x4 M, double deltaX, double deltaY, double deltaZ){
	int i, j;

	//CRIA MATRIZ TRANSLAÇÃO
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


//GERA A MATRIZ ESCALA
Mat4x4 Escala(Mat4x4 M, double FX, double FY, double FZ){
	int i, j;
	//CRIA MATRIZ ESCALA
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


//GERA A MATRIZ DE ROTAÇÃO
Mat4x4 Rot(Mat4x4 M, int eixo, double ang){
	int i, j;
	//TRANSFORMA O ANGULO DADO EM RADIANO
	double angulo = (PI*ang)/180;
	//PARA A ROTAÇÃO NO EIXO X, PREENCHE A MATRIZ
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
	//PARA A ROTAÇÃO NO EIXO Y, PREENCHE A MATRIZ
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
	//PARA A ROTAÇÃO NO EIXO z, PREENCHE A MATRIZ
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


//REALIZA A MULTIPLICAÇÃO DE MATRIZES 4X4 * 4X4
Mat4x4 MatComp(Mat4x4 M1, Mat4x4 M2){
	int x, i, j;
	Mat4x4 F; ////MATRIZ ONDE SERÁ REALIZADA A MULTIPLICAÇÃO
	for(x=0;x<4;x++){
		for(i=0;i<4;i++){
			F.matriz[x][i] = 0; //PREENCHE A POSIÇÃO COM ZERO
			for(j=0;j<4;j++){ //MULTIPLICA
				F.matriz[x][i] += M1.matriz[x][j] * M2.matriz[j][i];
			}
		}
	}
	return F;
}

//REALIZA A MULTIPLICAÇÃO DE MATRIZES 4X4 * 4X1
Mat4x1 MatTransf(Mat4x4 M, Mat4x1 P){
	int i, j;
	double temp;
	Mat4x1 v; //MATRIZ ONDE SERÁ REALIZADA A MULTIPLICAÇÃO

	for(i=0;i<4;i++){
		v.matriz[i][0] = 0; //PREENCHE A POSIÇÃO COM ZERO
		for(j=0;j<4;j++){ //MULTIPLICA
			v.matriz[i][0] += P.matriz[j][0] * M.matriz[i][j];
		}
	}
	return v;
}

//IMPRME OS VALORES DA LISTA NO ARQUIVO DE TEXTO
void Imprime(Mat4x1 *Obj, char* fName){
	int i;
	//ABRE O ARQUIVO
	FILE * out;
	out = fopen(fName,"a+");
	if(out == NULL){
		printf("Erro ao abrir o arquivo\n");
	}

	Mat4x1 * percorre = Obj->prox; // PONTEIRO QUE IRÁ PERCORRER A LISTA
	while(percorre!=NULL){
		for (i=0;i<3;i++){
			if(*percorre->matriz[i]==(int)*percorre->matriz[i]){
				//SE O NUMERO FOR INTEIRO, IMPRIME SEU VALOR INTEIRO
				fprintf(out, (i==2) ? "%d\n" : "%d ", (int)*percorre->matriz[i]);
			}
			else{
				//SE FOR FRACIONADO IMPRIME COM PRECISÃO DE 3 CASAS DECIMAIS
			 	fprintf(out,(i==2) ? "%.3lf\n" : "%.3lf ", *percorre->matriz[i]);
			}
		}
		percorre = percorre->prox;
	}
	fclose(out);
}


//IMPRIME UMA MATRIZ 4X1 PARA DEBUG
void imprimeMat4x1(Mat4x1 * elemento){
	int i;
	for(i=0;i<3;i++) printf((i==2) ? "%lf\n" :" %lf ", elemento->matriz[i]);
}


//IMPRIME UMA MATRIZ 4X4 PARA DEBUG
void imprimeMat4x4(Mat4x4 * M){
	int i, j;
	printf("\tMATRIZ\n");
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			printf((j==3) ? "%lf\n" : "%lf ", M->matriz[i][j]);
		}
	}
}


//LÊ LINHA POR LINHA DO ARQUIVO E ARMAZENA NA LISTA
void Cria(Mat4x1 *Obj, char * fName){
	int n, i, j;
	//ABRE O ARQUIVO
	FILE * arq;
	arq = fopen(fName,"a+");
	if (arq == NULL){
		printf("Erro ao abrir o aquivo para a leitura dos dados\n");
		return ;
	}

	//VETOR TEMPORARIO
	double * coordenadas;
	coordenadas = malloc(sizeof(double)*3);
	fscanf(arq, "%d ", &n); // LÊ OS CASOS DE TESTE
	for(i=0;i<n;i++){
		// ARMAZENA CADA LINHA NO VETOR coordenadas
		coordenadas = ler(arq, coordenadas);
		//INSERE O VETOR NA LISTA
		lista_insere(Obj, coordenadas[0], coordenadas[1], coordenadas[2]);
	}
}

//LE UMA LINHA DO ARQUIVO E ARMAZENA AS COORDENADAS EM UM VETOR
double * ler(FILE * p, double * vetor){
	int j=0, i;
	double temp;
	//PERCORRE A LINHA E LE CADA COORDENADA EM temp  E ARMAZENA NO VETOR
	for(i=0;i<3;i++){
		fscanf(p, "%lf ", &temp);
		vetor[j++] = temp;
	}
	//RETORNA O VETOR
	return vetor;
}

//INICIA UM NOVO NÓ PARA A LISTA
Mat4x1 * lista_inicia(){
		//ALOCA A MEMORIA NECESSARIA
    Mat4x1 * LISTA = (Mat4x1*)malloc(sizeof(Mat4x1));
		//CASO NÃO SEJA POSSIVEL ALOCAR EXIBE A MENSAGEM
		if(!LISTA){
        printf("Não alocada!\n");
        exit(1);
    }
		//O NÓ APONTA PARA NULL
    LISTA->prox = NULL;
    return LISTA;
}

//RECEBE AS COORDENADAS E INSERE EM UM NÓ DA LISTA ENCADEADA
void lista_insere(Mat4x1 * COORD, double x, double y, double z){
  	int i;
		Mat4x1 * percorre = COORD;
		//DECLARAÇÃO DO NOVO NÓ  MAT4X1
		Mat4x1 * novo = lista_inicia();
		//PERCORRE A LISTA ATÉ O FINAL
  	while(percorre->prox!=NULL) percorre = percorre->prox;
		//CONECTA O NOVO NÓ AO FINAL DA LISTA
  	percorre->prox = novo;
		//PASSA AS COORDENADAS PARA O NÓ
  	novo->matriz[0][0] = x;
  	novo->matriz[1][0] = y;
  	novo->matriz[2][0] = z;
  	novo->matriz[3][0] = 1;
}


//LE O ARQUIVO, GERA AS MATRIZES E ÀS MULTIPLICA
Mat4x4 pegaMatrizes(char * fName){
	//ABRE O ARQUIVO
	FILE * in;
	in = fopen(fName, "r");

	//CRIA UMA MATRIZ DE TEMPORARIA PARA AVANÇAR NO ARQUIVO
	double * cache;
	cache = malloc(sizeof(double)*3);

	//PASSAR PELAS COORDENADAS
	int i, j, n;
	fscanf(in, "%d ", &n);
	for(i=0;i<n;i++){
		cache = ler(in, cache);
	}
	free(cache);

	//CRIA A MATRIZ FINAL QUE MULTIPLICARA TODAS AS OUTRAS
	Mat4x4 final;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++){
			if(i==j) final.matriz[i][j] = 1;
			else final.matriz[i][j] = 0;
		}
	/*
		MATRIZ FINAL CRIADA
					1 0 0 0
					0 1 0 0
					0 0 1 0
					0 0 0 1
	*/

	char op;
	while(!feof(in)){ //LOOP SE REPETE ATÉ O FINAL DO ARQUIVO
		//LÊ QUAL MATRIZ SERÁ CRIADA
		fscanf(in, "%c ", &op);

		//MATRIZ TRANSLAÇÃO
		if(op == 'T'){
			double dX, dY, dZ;
			//LÊ OS PARAMETROS
			fscanf(in, "%lf %lf %lf ", &dX, &dY, &dZ);
			//GERA A MATRIZ TRANSLAÇÃO COM OS PARAMETROS
			Mat4x4 trans = Trans(trans, dX, dY, dZ);
			//MULTIPLICA PELA MATRIZ FINAL
			final = MatComp(final, trans);
		}

		//MATRIZ ROTAÇÃO
		else if(op == 'R'){
			char eixo;
			double ang;
			//LÊ OS PARAMETROS
			fscanf(in, "%c %lf ", &eixo, &ang);
			//GERA A MATRIZ ROTAÇÃO COM OS PARAMETROS
			Mat4x4 rota = Rot(rota, eixo, ang);
			//MULTIPLICA PELA MATRIZ FINAL
			final = MatComp(final, rota);
		}

		//MATRIZ ESCALA
		else if(op == 'S'){
			double Fx, Fy, Fz;
			//LÊ OS PARAMETROS
			fscanf(in, "%lf %lf %lf ", &Fx, &Fy, &Fz);
			//GERA A MATRIZ ESCALA COM OS PARAMETROS
			Mat4x4 escala = Escala(escala, Fx, Fy, Fz);
			//MULTIPLICA PELA MATRIZ FINAL
			final = MatComp(final, escala);
		}
	}

	//RETORNA A MATRIZ FINAL
	return final;
}

//MULTIPLICA CADA COORDENADA DA LISTA PELA MATRIZ TRANSFORMAÇÃO
//ARMAZENA AS NOVAS COORDENADAS DE VOLTA NA LISTA
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

//FUNÇÃO QUE DESALOCA A LISTA DINAMICA
void lista_libera(Mat4x1 * lista){
	Mat4x1 * atual = lista;
	Mat4x1 * prox = atual;
	while(atual!=NULL){
		prox = atual ->prox;
		free(atual);
		atual = prox;
	}

}

void MakeItHappen(char * in, char * out){
	int i, j,n;

	//LISTA DE COORDENADAS
	//DECLARA O INICIO DE UMA LISTA DE MAT4X1
	Mat4x1 * cord = lista_inicia();
	//FUNÇÃO CRIA LÊ AS COORDENADAS DO ARQUIVO E CRIA UMA LISTA
	//DINAMICA ENCADEADA
	Cria(cord, in);

	//MATRIZ TRANSFORMAÇÃO
	//CRIA UMA STRUCT MAT4X4 PARA ARMAZENAR A MATRIZ TRANSFORMAÇÃO
	Mat4x4 transforma;
	//FUNÇÃO pegaMatrizes LÊ AS TRANSFORMAÇÕES NO ARQUIVO, GERA E MULTIPLICA
	//TODAS AS MATRIZES, RETORNA A RESULTANTE
	transforma = pegaMatrizes(in);

	//PERCORRER E MULTIPLICAR
	//PERCORRE A LISTA DE COORDENADAS E AS TRANSFORMA
	perMult(cord, transforma);

	//IMPRIME O NUMERO DE CASOS NO INICIO DO ARQUIVO
	FILE * entrada = fopen(in, "r");
	FILE * saida = fopen(out, "a+");
	fscanf(entrada, "%d", &n);
	fprintf(saida, "%d\n", n);
	fclose(entrada);
	fclose(saida);

	//BURN
	//IMPRIME AS COORDENADAS TRANSFORMADAS NO ARQUIVO DE SAIDA
	Imprime(cord, out);

	//Clear the mess, go home
	//DESALOCA A LISTA CRIADA
	lista_libera(cord);
}
