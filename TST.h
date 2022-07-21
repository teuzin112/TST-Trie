#ifndef TST_H_INCLUDED
#define TST_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TSTNode {
  struct TSTNode* left;    // Ponteiro para caractere menor que nao pertence a palavra
  struct TSTNode* middle;  // Ponteiro para caractere que faz parte da palavra
  struct TSTNode* right;   // Ponteiro para caractere maior que nao pertence a palavra
  int isEnd;               // Tipo bool para dizer se eh ou nao fim da palavra
  char ch;                 // Caractere armazenado
} TSTNode;

/**
 * funcao para criar novo no inicializando com valores padrao
 * @param info caractere a ser armazenado no no
 * @return novo no inicializado e alocado
 * @precondition nenhuma
 * @postcondition nenhuma
 */
TSTNode* createNode(char info);

/**
 * funcao para inserir uma palavra na arvore TST
 * @param r raiz da arvore
 * @param word palavra a ser inserida
 * @return raiz da arvore ou nova raiz caso tenha alterado
 * @precondition palavra nao contem caracteres especiais e apenas letras minusculas
 * @postcondition palavra inserida na arvore
 */
TSTNode* insert(TSTNode* r, char* word);

/**
 * funcao principal para imprimir todas as palavras da arvore na tela
 * @param r no atual da arvore
 * @param aux variavel auxiliar que armazena a palavra a ser impressa
 * @param i variavel auxiliar indexadora para armazenar a palavra a ser impressa
 * @precondition nenhuma
 * @postcondition todas as palavras impressas na tela
 */
void printTSTaux(TSTNode* r, char* aux, int i);

/**
 * funcao para imprimir todas as palavras da arvore em ordem alfabetica
 * @param r raiz da arvore
 * @precondition nenhuma
 * @postcondition arovore impressa na tela
 */
void printTST(TSTNode* r);

/**
 * funcao que imprime as 10 primeiras palavras a partir de um no da arvore
 * @param r no atual da arvore
 * @param aux variavel auxiliar que armazena a palavra a ser impressa
 * @param i variavel auxiliar indexadora para armazenar a palavra a ser impressa
 * @param j variavel auxiliar para contar quantas palavras ja foram impressas
 * @precondition nenhuma
 * @postcondition 10 primeiras palavras impressas na tela
 */
void printPrefixAux(TSTNode* r, char* aux, int i, int* j);

/**
 * funcao que busca o no da ultima letra de uma string caso ela pertenca a arvore
 * @param r raiz da arvore
 * @param str string a ser procurada na arvore
 * @return retorna o no da ultima letra de str
 * @precondition nenhuma
 * @postcondition nenhuma
 */
TSTNode* search(TSTNode* r, char* str);

/**
 * funcao para imprimir todas as palavras com o prefixo
 * @param r raiz da arvore
 * @param prefix prefixo das palavras
 * @precondition nenhuma
 * @postcondition todas palavras com o prefixo impressas
 */
void printPrefix(TSTNode* r, char* prefix);

/**
 * funcao para verificar se um no eh folha ou nao
 * @param r no a ser verificado
 * @return 1 para sim e 0 para nao
 * @precondition no diferente de nulo
 * @postcondition nenhuma
 */
int isLeaf(TSTNode* r);

/**
 * funcao auxiliar que retorna o maior no a partir de um determinado no
 * @param r no a ser buscado
 * @return o penultimo maior no
 * @precondition no diferente de NULL
 * @postcondition desencadeia o penultimo no do no que sera retornado
 */
TSTNode* searchDel(TSTNode* r);

/**
 * funcao auxiliar que deleta um no tratando todas as possibilidades de rotacao
 * @param r no a ser deletado
 * @return novo no devidamente encadeado no lugar do no que foi deletado
 * @precondition no a ser deletado deve ser diferente de NULL
 * @postcondition nenhuma
 */
TSTNode* deleteAux(TSTNode* r);

/**
 * funcao para deletar uma palavra da arvore TST
 * @param r raiz da arvore
 * @param word palavra a ser deletada
 * @param aux variavel auxiliar passada por referencia inicialmente com o valor 0
 * @return raiz da arvore ou nova raiz caso tenho alterado
 * @precondition palavra a ser deletada nao pode ser NULL
 * @postcondition arvore alterada
 */
TSTNode* delete (TSTNode* r, char* word, int* aux);

/**
 * funcao para calcular o menor valor entre tres inteiros
 * @param a
 * @param b
 * @param c
 * @return o maior valor dentre os tres
 * @precondition nenhuma
 * @postcondition nenhuma
 */
int min(int a, int b, int c);

/**
 * funcao para calcular a distancia de edicao entre duas strings
 * @param str1
 * @param str2
 * @return o numero minimo de operacoes para transformar str1 em str2
 * @precondition nenhuma
 * @postcondition nenhuma
 */
int minEditDistance(char* str1, char* str2);

/**
 * funcao auxiliar para imprimir todas as palavras semelhantes de uma arvore trie
 * @param r raiz da arvore
 * @param aux variavel auxiliar que armazena a palavra a ser impressa
 * @param i variavel auxiliar indexadora para armazenar a palavra a ser impressa
 * @param word palavra semelhante a ser procurada
 * @param n grau de semelhanca
 * @param j variavel auxiliar para contar quantas palavras ja foram impressas
 * @precondition word deve ser diferente de NULL
 * @postcondition todas as palavras com grau menor ou igual a n de semelhanca sao impressas
 */
void findSimilarAux(TSTNode* r, char* aux, int i, char* word, int n, int* j);

/**
 * funcao para encontrar todas as palavras semelhantes de uma arvore trie
 * @param r raiz da arvore
 * @param word palavra a ser procurada
 * @param n grau de semelhanca entre as duas palavras
 * @precondition word diferente de NULL
 * @postcondition todas as palavras com grau menor ou igual a n de semelhanca sao impressas
 */
void findSimilar(TSTNode* r, char* word, int n);

/**
 * funcao para carregar todas as palavras de um arquivo txt na arvore
 * @param r raiz da arovre
 * @param fileName nome do arquivo a ser carregado
 * @return nova raiz da arvore
 * @precondition arquivo deve existir
 * @postcondition nenhuma
 */
TSTNode* loadTxtFile(TSTNode* r, char* fileName);

/**
 * funcao para carregar remover as palavras de um arquivo txt da arvore
 * @param r raiz da arovre
 * @param fileName nome do arquivo a ser carregado
 * @return nova raiz da arvore
 * @precondition arquivo deve existir
 * @postcondition nenhuma
 */
TSTNode* removeWords(TSTNode* r, char* fileName);

#endif