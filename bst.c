#include <stdio.h>
#include <stdlib.h>

typedef struct No {
  int valor;
  struct No *esq;
  struct No *dir;
} No;

No *inserir(No *raiz, int valor);

int main() {
  No *nos[6];
  nos[0] = malloc(sizeof(struct No));
  nos[0]->esq = 0;
  nos[0]->dir = 0;
  nos[0]->valor = 10;

  nos[0]->dir = malloc(sizeof(struct No));
  nos[1] = nos[0]->dir;
  nos[1]->dir = 0;
  nos[1]->esq = 0;
  nos[1]->valor = 30;

  nos[1]->dir = malloc(sizeof(struct No));
  nos[2] = nos[1]->dir;
  nos[2]->dir = 0;
  nos[2]->esq = 0;
  nos[2]->valor = 40;
}
//Atenção: Não estou utilizando o cast para o mallocs
No *inserir(No *raiz, int valor) {
  if (raiz == 0) {
    No *novo = malloc(sizeof(No));
    if(novo == 0){
        printf("Erro: Não foi possível crirar No");
        exit(1);
    }
    novo->dir = 0;
    novo->esq = 0;
    novo->valor = valor;
    return novo;
  }
  if(valor < raiz->valor){
    raiz->esq = inserir(raiz->esq, valor);
  }else if(valor > raiz->valor){
    raiz->dir = inserir(raiz->dir, valor);
  }
  return raiz;
}

/*
Inserir manualmente:
10 - 30 - 40 - 8 - 25 - 14
*/