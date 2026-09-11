#include <stdio.h>
#include <stdlib.h>

typedef struct No {
  int valor;
  struct No *esq;
  struct No *dir;
} No;

No *inserir(No *raiz, int valor);
No *criarNo(int);

int main() {
  No *raiz = 0;
  raiz = inserir(raiz, 10);
  raiz = inserir(raiz, 30);
  raiz = inserir(raiz, 40);
  raiz = inserir(raiz, 8);
  raiz = inserir(raiz, 14);
}
// Atenção: Não estou utilizando o cast para o mallocs
No *inserir(No *raiz, int valor) {
  if (raiz == 0) {
    return criarNo(valor);
  }
  if (valor < raiz->valor) {
    raiz->esq = inserir(raiz->esq, valor);
  } else if (valor > raiz->valor) {
    raiz->dir = inserir(raiz->dir, valor);
  }
  return raiz;
}

No *criarNo(int valor) {
  No *novo = malloc(sizeof(No));
  if (novo == 0) {
    printf("Erro: Não foi possível crirar No");
    exit(1);
  }
  novo->dir = 0;
  novo->esq = 0;
  novo->valor = valor;
  return novo;
}