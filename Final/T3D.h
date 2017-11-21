#ifndef T3D
#define T3D

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265

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

//Tipos de dados
typedef struct mat4x1 Mat4x1;
typedef struct mat4x4 Mat4x4;

/**Função que lê todas as coordendas no arquivo de nome fName, e passa pra uma lista de *Obj
**/
void Cria(Mat4x1 *Obj, char * fName);

/*Função que inicia e aloca um nó da lista dinamica
*/

Mat4x1 * lista_inicia();

/**Insere coordenadas na lista
**/
void lista_insere(Mat4x1 * COORD, double x, double y, double z);

/*Função que le uma linha de coordendas e passa os valores para um vetor
*/
double * ler(FILE * p, double * vetor);

/**Lê linha por linha do arquivo e armazena todas as coordenadas em
uma lista dinamica
**/
void Cria(Mat4x1 *Obj, char* fName);

/**Preenche uma matriz 4x4 com os parâmetros de translação.
**/
Mat4x4 Trans(Mat4x4 M, double deltaX, double deltaY, double deltaZ);

/**Preenche uma matriz 4x4 com os parˆametros de mudança de escala.
**/
Mat4x4 Escala(Mat4x4 M, double FX, double FY, double FZ);

/**Preenche uma matriz 4x4 com os parâmetros de rotacão, recebe o eixo de rotação e o angulo em graus
*/
Mat4x4 Rot(Mat4x4 M, int eixo, double ang);

/**Multiplica duas matrizes 4x4
*/
Mat4x4 MatComp(Mat4x4 M1, Mat4x4 M2);

/**Multiplica uma matriz 4x4 por uma matriz 4x1
*/
Mat4x1 MatTransf(Mat4x4 M, Mat4x1 P);

/** Imprime as coordenadas de um objeto no arquivo de nome fName
*/
void Imprime(Mat4x1 *Obj, char* fName);

/*Gera todas as matrizes de transformação do arquivo, as multiplica
e retorna a matriz resultante
*/
Mat4x4 pegaMatrizes(char * fName);

/*percorre a lista de coordenadas e multiplica cada
ponto pela matriz transformação, inserindo as novas
coordenadas na mesma lista
*/
void perMult(Mat4x1 * cord, Mat4x4 transforma);

//limpa a memoria da lista
void lista_libera(Mat4x1 * lista);

#endif
