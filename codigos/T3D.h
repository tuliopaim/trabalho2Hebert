#ifndef T3D
#define T3D
#define PI 3.14159265

//Tipos de dados
typedef struct mat4x1 Mat4x1;
typedef struct mat4x4 Mat4x4;

/**Função que lê todas as coordendas no arquivo de nome fNamee, e passa pra uma lista de *Obj
**/
void Cria(Mat4x1 *Obj, char * fName);

/*Função que inicia
*/

Mat4x1 * lista_inicia();

/**Insere coordenadas na lista
**/
void lista_insere(Mat4x1 * COORD, double x, double y, double z);

/*Função que le uma linha de coordendas e passa os valores para um vetor
*/
double * ler(FILE * p, double * vetor);

/**Cria o objeto a transformar: lê o arquivo de entrada e preenche o vetor de coordenadas.
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

/**Multiplica uma matriz 4x4 por um vetor de coordenadas, efetuando a transformação.
*/
Mat4x1 MatTransf(Mat4x4 M, Mat4x1 P);

/** Imprime as coordenadas de um objeto no arquivo de nome FName
*/
void ImprimeNoArquivo(Mat4x1 *Obj, char* fName);

/**Aloca o espaço para a struct Mat4x1
*/
Mat4x1 * AlocaMat4x1();

/**Aloca o espaço para a struct Mat4x1
*/
Mat4x4 * AlocaMat4x4();

/**Imprime uma Objeto Matrix 4x1
*/
void imprimeMat4x1(Mat4x1 * elemento);

/**Imprime uma Objeto Matrix 4x4
*/
void imprimeMat4x4(Mat4x4 * M);

//~~ MAKES SHIT HAPPENS
// A MAGIA ACONTECE
//Rebe a string nome do arquivo de entrada dos dados
void MakeItHappen(char * in, char * out);

//MULTIPLICA AS MATRIZES DE TRANSFORMAÇÃO
Mat4x4 pegaMatrizes(char * fName);

//PERCORRE E MULTIPLICA
void perMult(Mat4x1 * cord, Mat4x4 transforma);

//limpa a memoria da lista
void lista_libera(Mat4x1 * lista);

#endif
