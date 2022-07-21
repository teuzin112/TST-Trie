#include "TST.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * funcao para criar novo no inicializando com valores padrao
 * @param info caractere a ser armazenado no no
 * @return novo no inicializado e alocado
 * @precondition nenhuma
 * @postcondition nenhuma
 */
TSTNode* createNode(char info) {
  TSTNode* newNode = (TSTNode*)malloc(sizeof(TSTNode));
  newNode->left = newNode->middle = newNode->right = NULL;
  newNode->isEnd = 0;
  newNode->ch = info;
  return newNode;
}

/**
 * funcao para inserir uma palavra na arvore TST
 * @param r raiz da arvore
 * @param word palavra a ser inserida
 * @return raiz da arvore ou nova raiz caso tenha alterado
 * @precondition palavra nao contem caracteres especiais e apenas letras minusculas
 * @postcondition palavra inserida na arvore
 */
TSTNode* insert(TSTNode* r, char* word) {
  // Arvore vazia apenas cria novo no
  if (r == NULL)
    r = createNode(*word);

  // Menor insere na esquerda
  if (*word < r->ch)
    r->left = insert(r->left, word);
  // Maior insere na direita
  else if (*word > r->ch)
    r->right = insert(r->right, word);
  else {                      // Igual insere no meio (*word == r->ch)
    if (*(word + 1) != '\0')  // Testa se nao eh o fim da palavra
      r->middle = insert(r->middle, word + 1);

    // Se for o fim atualiza o no
    else
      r->isEnd = 1;
  }
  return r;
}

/**
 * funcao principal para imprimir todas as palavras da arvore na tela
 * @param r no atual da arvore
 * @param aux variavel auxiliar que armazena a palavra a ser impressa
 * @param i variavel auxiliar indexadora para armazenar a palavra a ser impressa
 * @precondition nenhuma
 * @postcondition todas as palavras impressas na tela
 */
void printTSTaux(TSTNode* r, char* aux, int i) {
  if (r != NULL) {
    // Imprime esquerda
    printTSTaux(r->left, aux, i);

    // Armazena o dado do no atual
    aux[i] = r->ch;
    if (r->isEnd) {
      aux[i + 1] = '\0';
      printf("%s\n", aux);
    }

    // Imprime meio
    printTSTaux(r->middle, aux, i + 1);
    // Imprime direita
    printTSTaux(r->right, aux, i);
  }
}

/**
 * funcao para imprimir todas as palavras da arvore em ordem alfabetica
 * @param r raiz da arvore
 * @precondition nenhuma
 * @postcondition arovore impressa na tela
 */
void printTST(TSTNode* r) {
  char aux[50];
  printTSTaux(r, aux, 0);
}

/**
 * funcao que imprime as 10 primeiras palavras a partir de um no da arvore
 * @param r no atual da arvore
 * @param aux variavel auxiliar que armazena a palavra a ser impressa
 * @param i variavel auxiliar indexadora para armazenar a palavra a ser impressa
 * @param j variavel auxiliar para contar quantas palavras ja foram impressas
 * @precondition nenhuma
 * @postcondition 10 primeiras palavras impressas na tela
 */
void printPrefixAux(TSTNode* r, char* aux, int i, int* j) {
  if (r != NULL && *j != 10) {
    // Imprime esquerda
    printPrefixAux(r->left, aux, i, j);

    // Armazena o dado do no atual
    aux[i] = r->ch;
    if (r->isEnd) {
      aux[i + 1] = '\0';

      if (*j == 0)
        printf("%s", aux);
      else
        printf(", %s", aux);
      (*j)++;
    }

    // Imprime meio
    printPrefixAux(r->middle, aux, i + 1, j);
    // Imprime direita
    printPrefixAux(r->right, aux, i, j);
  }
}

/**
 * funcao que busca o no da ultima letra de uma string caso ela pertenca a arvore
 * @param r raiz da arvore
 * @param str string a ser procurada na arvore
 * @return retorna o no da ultima letra de str
 * @precondition nenhuma
 * @postcondition nenhuma
 */
TSTNode* search(TSTNode* r, char* str) {
  if (r != NULL) {
    if (*(str + 1) != '\0' || *str != r->ch) {
      if (*str < r->ch)
        r = search(r->left, str);

      else if (*str > r->ch)
        r = search(r->right, str);

      else
        r = search(r->middle, str + 1);
    }
  }
  return r;
}

/**
 * funcao para imprimir todas as palavras com o prefixo
 * @param r raiz da arvore
 * @param prefix prefixo das palavras
 * @precondition nenhuma
 * @postcondition todas palavras com o prefixo impressas
 */
void printPrefix(TSTNode* r, char* prefix) {
  int j = 0;
  char aux[50];
  strcpy(aux, prefix);

  r = search(r, prefix);
  if (r != NULL)
    printPrefixAux(r->middle, aux, strlen(prefix), &j);

  printf("\n");
}

/**
 * funcao para verificar se um no eh folha ou nao
 * @param r no a ser verificado
 * @return 1 para sim e 0 para nao
 * @precondition no diferente de nulo
 * @postcondition nenhuma
 */
int isLeaf(TSTNode* r) {
  return (!r->left && !r->middle && !r->right);
}

/**
 * funcao auxiliar que retorna o maior no a partir de um determinado no
 * @param r no a ser buscado
 * @return o penultimo maior no
 * @precondition no diferente de NULL
 * @postcondition desencadeia o penultimo no do no que sera retornado
 */
TSTNode* searchDel(TSTNode* r) {
  if (r->right == NULL) return r;  // Se o primeiro no ja for o ultimo apenas retorna ele mesmo

  while (r->right->right != NULL)  // Anda para direita ate chegar no penultimo no
    r = r->right;

  TSTNode* aux = r->right;  // Armazena o ultimo no da direita
  r->right = NULL;          // Desencadeia o penultimo no do ultimo

  return aux;
}

/**
 * funcao auxiliar que delete um no tratando todas as possibilidades de rotacao
 * @param r no a ser deletado
 * @return novo no devidamente encadeado no lugar do no que foi deletado
 * @precondition no a ser deletado deve ser diferente de NULL
 * @postcondition nenhuma
 */
TSTNode* deleteAux(TSTNode* r) {
  TSTNode* del = r;
  if (r->middle != NULL) {  // Se tem meio apenas atualiza o no
    r->isEnd = 0;
  } else {
    if (r->left != NULL && r->right != NULL) {
      r = searchDel(r->left);  // Retorna o maior dos menores nos

      if (del->left == r)  // Se for o primeiro no da esquerda apenas sobe ele
        r->right = del->right;

      else {  // Se nao for o primeiro no realiza toda a rotacao
        TSTNode* left = r->left;

        r->left = del->left;
        r->right = del->right;

        TSTNode* Aux = r->left;

        while (Aux->right != NULL)
          Aux = Aux->right;

        Aux->right = left;
      }

    } else if (r->left != NULL) {  // Se tem apenas esquerda, copia a esquerda no lugar do no que foi deletado
      r = r->left;

    } else {  // Se tem apenas direita, copia a direita no lugar do no que foi deletado
      r = r->right;
    }
    free(del);
  }
  return r;
}

/**
 * funcao para deletar uma palavra da arvore TST
 * @param r raiz da arvore
 * @param word palavra a ser deletada
 * @param aux variavel auxiliar passada por referencia inicialmente com o valor 0
 * @return raiz da arvore ou nova raiz caso tenho alterado
 * @precondition palavra a ser deletada nao pode ser NULL
 * @postcondition arvore alterada
 */
TSTNode* delete (TSTNode* r, char* word, int* aux) {
  if (r != NULL) {
    if (r->isEnd && *(word + 1) != '\0') (*aux)++;  // Se percorreu algum no que eh fim de palavra incrementa

    if (*(word + 1) != '\0' || *word != r->ch) {  // Percorre a arvore ate chegar no no a ser removido
      if (*word < r->ch)
        r->left = delete (r->left, word, aux);

      else if (*word > r->ch)
        r->right = delete (r->right, word, aux);

      else
        r->middle = delete (r->middle, word + 1, aux);
    }
    if (r->isEnd) {
      if (isLeaf(r) && *(word + 1) == '\0') {  // Se for folha e o fim da palavra libera o no e decrementa aux
        free(r);
        r = NULL;
        (*aux)--;
      } else if (*(word + 1) == '\0' && *word == r->ch) {  // Se for o fim da palavra e for o caracter correspondente ao fim
        r = deleteAux(r);
      }

    } else if (*aux == 0) {  // Na chamada recursiva se nao foi percorrida nenhuma palavra remove todos os nos ate
                             // chegar em um no que tenha uma palavra.
      if (isLeaf(r)) {       // Se for folha apenas deleta o no
        free(r);
        r = NULL;
      } else {  // Se nao realiza rotacao se necessario
        r = deleteAux(r);
      }
    }
  }
  return r;
}

/**
 * funcao para calcular o menor valor entre tres inteiros
 * @param a
 * @param b
 * @param c
 * @return o maior valor dentre os tres
 * @precondition nenhuma
 * @postcondition nenhuma
 */
int min(int a, int b, int c) {
  if (a <= b && a <= c) {
    return a;
  } else if (b <= a && b <= c) {
    return b;
  } else if (c <= a && c <= b) {
    return c;
  }
}

/**
 * funcao para calcular a distancia de edicao entre duas strings
 * @param str1
 * @param str2
 * @return o numero minimo de operacoes para transformar str1 em str2
 * @precondition nenhuma
 * @postcondition nenhuma
 */
int minEditDistance(char* str1, char* str2) {
  int i, j, strlen1, strlen2;
  strlen1 = strlen(str1);
  strlen2 = strlen(str2);

  int mat[strlen2 + 1][strlen1 + 1];
  mat[0][0] = 0;

  for (j = 1; j <= strlen1; j++)
    mat[0][j] = mat[0][j - 1] + 1;  // Iniciliza primeira linha com 0, 1, 2, 3, ...

  for (i = 1; i <= strlen2; i++)
    mat[i][0] = mat[i - 1][0] + 1;  // Iniciliza primeira coluna com 0, 1, 2, 3, ...

  for (i = 1; i <= strlen2; i++)
    for (j = 1; j <= strlen1; j++)
      mat[i][j] = min(mat[i - 1][j] + 1, mat[i][j - 1] + 1, mat[i - 1][j - 1] + (str1[j - 1] == str2[i - 1] ? 0 : 1));

  return (mat[strlen2][strlen1]);
}

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
void findSimilarAux(TSTNode* r, char* aux, int i, char* word, int n, int* j) {
  if (r != NULL) {
    // Imprime esquerda
    findSimilarAux(r->left, aux, i, word, n, j);

    // Armazena o dado do no atual
    aux[i] = r->ch;
    if (r->isEnd) {
      aux[i + 1] = '\0';
      if (minEditDistance(word, aux) <= n) {
        if (*j == 0)
          printf("%s", aux);
        else
          printf(", %s", aux);
        (*j)++;
      }
    }

    // Imprime meio
    findSimilarAux(r->middle, aux, i + 1, word, n, j);
    // Imprime direita
    findSimilarAux(r->right, aux, i, word, n, j);
  }
}

/**
 * funcao para encontrar todas as palavras semelhantes de uma arvore trie
 * @param r raiz da arvore
 * @param word palavra a ser procurada
 * @param n grau de semelhanca entre as duas palavras
 * @precondition word diferente de NULL
 * @postcondition todas as palavras com grau menor ou igual a n de semelhanca sao impressas
 */
void findSimilar(TSTNode* r, char* word, int n) {
  char aux[50];
  int j = 0;
  findSimilarAux(r, aux, 0, word, n, &j);
}

/**
 * funcao para carregar todas as palavras de um arquivo txt na arvore
 * @param r raiz da arovre
 * @param fileName nome do arquivo a ser carregado
 * @return nova raiz da arvore
 * @precondition arquivo deve existir
 * @postcondition nenhuma
 */
TSTNode* loadTxtFile(TSTNode* r, char* fileName) {
  FILE* f = fopen(fileName, "r");

  while (!feof(f)) {
    char word[50];
    int i, skip = 0;
    fscanf(f, "%s ", word);

    for (i = 0; i <= strlen(word) - 1; i++) {
      if (word[i] >= 'A' && word[i] <= 'Z')
        word[i] = word[i] + 32;

      if (!(word[i] >= 'a' && word[i] <= 'z'))
        skip = 1;
    }

    if (skip) continue;

    r = insert(r, word);
  }
  fclose(f);
  return r;
}

/**
 * funcao para carregar remover as palavras de um arquivo txt da arvore
 * @param r raiz da arovre
 * @param fileName nome do arquivo a ser carregado
 * @return nova raiz da arvore
 * @precondition arquivo deve existir
 * @postcondition nenhuma
 */
TSTNode* removeWords(TSTNode* r, char* fileName) {
  FILE* f = fopen(fileName, "r");

  while (!feof(f)) {
    char word[50];
    int i, skip = 0;
    fscanf(f, "%s ", word);

    for (i = 0; i <= strlen(word) - 1; i++) {
      if (word[i] >= 'A' && word[i] <= 'Z')
        word[i] = word[i] + 32;

      if (!(word[i] >= 'a' && word[i] <= 'z'))
        skip = 1;
    }

    if (skip) continue;

    int aux = 0;
    r = delete (r, word, &aux);
  }
  fclose(f);
  return r;
}
