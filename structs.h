  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <time.h>

  #define MAX_PARAGRAPH_SIZE 2048
  #define MAX_NODES 100

  // Estrutura para representar o jogador
  typedef struct {
      int vida;
      char nome[50];
  } Jogador;

  // Estrutura para representar um nó da árvore
  typedef struct Node {
      int numero;                     // Número do quadro
      char texto[MAX_PARAGRAPH_SIZE]; // Texto do quadro
      struct Node* esquerda;          // Caminho para a escolha 1
      struct Node* direita;           // Caminho para a escolha 2
  } Node;
