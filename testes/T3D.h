#ifndef T3D
#define T3D

//Definição dos tipos de dados
typedef struct mat4x1 Mat4x1;
typedef struct mat4x4 Mat4x4;


/**Cria o objeto a transformar: lê o arquivo de entrada e preenche o vetor de coordenadas.
*
*
*/
void Cria(Mat4x1 *Obj, char* fName);

/**Preenche uma matriz 4x4 com os parâmetros de translação.
*
*/

Mat4x4 Trans(Mat4x4 M, double deltaX, double deltaY, double deltaZ);
/**Preenche uma matriz 4x4 com os parˆametros de mudança de escala.
*
*/

Mat4x4 Escala(Mat4x4 M, double FX, double FY, double FZ);

/**Preenche uma matriz 4x4 com os parˆametros de rota¸c˜ao
*/
Mat4x4 Rot(Mat4x4 M, int eixo, double angulo);

/**Multiplica duas matrizes 4x4, para composiçao de transformações
*/
Mat4x4 MatComp(Mat4x4 M1, Mat4x4 M2);

/**Multiplica uma matriz 4x4 por um vetor de coordenadas, efetuando a transformação.
*/
Mat4x1 MatTransf(Mat4x4 M, Mat4x1 P);

/** Imprime as coordenadas de um objeto no arquivo de nome FName
*/
void Imprime(Mat4x1 *Obj, char* fName);

/**Aloca o espaço para a struct Mat4x1
*/
Mat4x1 * AlocaMat4x1();

/**Imprime uma Objeto Matrix 4x1
*/

void imprimeMat4x1(Mat4x1 * elemento);
#endif