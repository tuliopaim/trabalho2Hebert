#include <stdio.h>
#include <stdlib.h>
#include "T3D.h"

/*
TIPOS DE DADOS
*/
struct mat4x1{
	int x,y,z,t;
};

struct mat4x4{
	
};


/*
IMPLEMENTAÇÃO DAS FUNÇÕES
*/
void Cria(Mat4x1 *Obj, char* fName){

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

}