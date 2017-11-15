# trabalho2Hebert
    O objetivo desse trabalho é rever conceitos básicos de programação bem como ex-
plorar os conceitos de Tipos Abstratos de Dados (TADs) e análise de complexidade.
Você deverá programar um tipo abstrato de dados T3D, que será usado para realizar
transformações geométricas e projeções a partir de objetos tridimensionais. A base
do TAD é a representação de conjuntos de coordenadas homogêneas, em que cada
vértice geométrico é representado por um vetor 4x1, que contém as coordenadas x,
y, z e t, com t = 1 para as finalidades deste trabalho. Portanto, você deverá definir
um tipo estruturado para matriz 4x4 e outro para matriz 4x1. As transformações
são obtidas a partir da combinação de transformações primitivas, listadas abaixo. As
transformações primitivas são representadas por matrizes 4 x 4, e a combinação de duas
transformações se faz por pré-multiplicação de matrizes. As transformações primitivas
que serão implementadas no TAD são as seguintes:

(a) translação

(b) Mudança de escala

(c) Rotação (em torno dos eixos x, y e z, a partir da origem do sistema de coordenadas)

    A composição de operações é feita por pré-multiplicação, da seguinte forma. A matriz
da primeira transformação a ser realizada é o ponto de partida. A matriz da segunda
transformação deve ser multiplicada pela da primeira transformação, formando uma nova
matriz. A matriz da terceira transformação deve ser multiplicada pela matriz resultante
anterior, formando nova matriz, e assim por diante. Ao final, tem-se uma matriz 4x4 que
condensa os efeitos de todas as transformações. Esta matriz final deve ser multiplicada pelos
vetores 4x1 correspondentes a cada vértice da geometria de entrada. A matriz 4x1 resultante
contém as novas coordenadas do vértice, após a transformação. Por exemplo, a sequência
abaixo faz o deslocamento dos vértices por 30 unidades em x e em y, realiza uma rotação
de 30 graus ao redor da origem em torno do eixo z e desloca os vértices novamente por -30
unidades em x e y. O efeito esperado é a rotação de 30 graus em torno do eixo z ao redor
do ponto de coordenadas (30, 30, 0).

Para cada vértice de entrada P = [x P , y P , z P , 1] T , o vértice resultante é P 0 = M · P .

As operações que devem ser realizadas em seu TAD T3D são:

1. Cria o objeto a transformar: lê o arquivo de entrada e preenche o vetor de coordenadas.
O espaço de memória necessário para o vetor deverá ser alocado dinamicamente por
esta função.

void Cria(Mat4x1 *Obj, char* fName);


2. Preenche uma matriz 4x4 com os parâmetros de translação:

Mat4x4 Trans(Mat4x4 M, double deltaX, double deltaY, double deltaZ);


3. Preenche uma matriz 4x4 com os parâmetros de mudança de escala:

Mat4x4 Escala(Mat4x4 M, double FX, double FY, double FZ);


4. Preenche uma matriz 4x4 com os parâmetros de rotação:

Mat4x4 Rot(Mat4x4 M, int eixo, double angulo);


5. Multiplica duas matrizes 4x4, para composição de transformações:

Mat4x4 MatComp(Mat4x4 M1, Mat4x4 M2);

6. Multiplica uma matriz 4x4 por um vetor de coordenad as, efetuando a transformação:

Mat4x1 MatTransf(Mat4x4 M, Mat4x1 P);


7. Imprime as coordenadas de um objeto no arquivo de nome FName.

void Imprime(Mat4x1 *Obj, char* fName);


    Programe o seu TAD em arquivos separados do program a principal (TD3D.c e T3D.h).
Se necessário você pode criar outras funções auxiliares em seu TAD, mas programe as funções
solicitadas com a interface descrita na página anterior de forma que seu TAD possa ser
testado automaticamente.
    Uma vez criado, o seu TAD deverá ser utilizado em um programa, que lê um arquivo
de texto contendo os dados de entrada (numero de coordenadas, coordenadas geométricas
de um objeto tridimensional e uma sequencia de transformações) e grava outro arquivo de
texto chamado entrada.txt, contendo as coordenadas geométricas do objeto transformado.
