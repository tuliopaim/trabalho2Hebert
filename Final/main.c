#include "T3D.h"

int main(){
  int i, j,n;

  //DECLARA O INICIO DE UMA LISTA DE MAT4X1
  Mat4x1 * cord = lista_inicia();
  /*FUNÇÃO CRIA LÊ AS COORDENADAS DO ARQUIVO E CRIA UMA LISTA
  DINAMICA ENCADEADA */
  Cria(cord, "entradas.txt");

  /*MATRIZ TRANSFORMAÇÃO
  CRIA UMA STRUCT MAT4X4 PARA ARMAZENAR A MATRIZ TRANSFORMAÇÃO*/
  Mat4x4 transforma;
  /*FUNÇÃO pegaMatrizes LÊ AS TRANSFORMAÇÕES NO ARQUIVO, GERA E MULTIPLICA
  TODAS AS MATRIZES, RETORNA A RESULTANTE*/
  transforma = pegaMatrizes("entradas.txt");

  //PERCORRE A LISTA DE COORDENADAS E AS MULTIPLICA PELA MATRIZ TRANSFORMAÇÃO
  perMult(cord, transforma);

  //IMPRIME O NUMERO DE COORDENADAS NO INICIO DO ARQUIVO
  FILE * entrada = fopen("entradas.txt", "r");
  FILE * saida = fopen("saidas.txt", "w");
  fscanf(entrada, "%d", &n);
  fprintf(saida, "%d\n", n);
  fclose(entrada);
  fclose(saida);

  //BURN
  //IMPRIME AS COORDENADAS TRANSFORMADAS NO ARQUIVO DE SAIDA
  Imprime(cord,"saidas.txt");

  //Clear the mess, go home
  //DESALOCA A LISTA CRIADA
  lista_libera(cord);
  return 0;
}
