#include <stdio.h>

#include "TST.h"

void printMenu() {
  printf("[1] - Consultar palavra\n");
  printf("[2] - Imprimir dicionario\n");
  printf("[3] - Carregar arquivo de stopwords\n");
  printf("[4] - Consultar semelhante\n");
  printf("[0] - Fechar\n");
}

int main() {
  char wordsFileName[50];
  printf("Entre com o arquivo de palavras para ser criado o dicionario: ");
  gets(wordsFileName);

  TSTNode *root = loadTxtFile(NULL, wordsFileName);

  system("cls");
  printMenu();
  int entry;
  printf(">>> ");
  scanf("%d", &entry);

  while (entry) {
    system("cls");
    switch (entry) {
      case 1: {
        char prefix[50];
        printf("Entre com o prefixo: ");
        scanf("%s", prefix);

        printPrefix(root, prefix);
        break;
      }

      case 2:
        printTST(root);
        break;

      case 3: {
        char fileName[50];
        printf("Entre com o nome do arquivo: ");
        scanf("%s", fileName);

        removeWords(root, fileName);
        break;
      }

      case 4: {
        char word[50];
        int n;
        printf("Entre com a palavra a ser consultada: ");
        scanf("%s", word);
        printf("Entre com o grau de semelhanca (n): ");
        scanf("%d", &n);

        findSimilar(root, word, n);
        printf("\n");
      }

      default:
        break;
    }

    printf("\nPressione qualquer tecla para voltar ao menu...\n");
    getchar();
    getchar();
    system("cls");

    printMenu();
    printf(">>> ");
    scanf("%d", &entry);
  }
}
