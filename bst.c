#include <stdio.h>
#include <stdlib.h>

typedef struct No {
  int valor;
  struct No *esq;
  struct No *dir;
} No;

No *inserir(No *raiz, int valor);
No *criarNo(int);
No *busca(No *, int);
No *encontrarMin(No *);
No *encontrarMax(No *);

//Percursos

void preOrdem(No*);
void inOrdem(No*);
void posOrdem(No*);

int altura(No *);
/*

      10                   <-raiz
  8          30
         14       40

*/

// Pre-Ordem = 10 - 8 - 30 - 14 - 40
// In-Ordem  = 8 - 10 - 14 - 30 - 40
// Pos-Ordem = 8 - 14 - 40 - 30 - 10


int main() {
  No *raiz = 0;
  raiz = inserir(raiz, 10);
  raiz = inserir(raiz, 30);
  raiz = inserir(raiz, 40);
  raiz = inserir(raiz, 8);
  raiz = inserir(raiz, 14);

  No *procura = busca(raiz, 30);
  No *min = encontrarMin(raiz);
  No *max = encontrarMax(raiz);
  int h = altura(procura);

  printf("Min: %d\n", min->valor);
  printf("Max: %d\n", max->valor);
  printf("Altura(30): %d\n", h);
  preOrdem(raiz);
  printf("\n");
  inOrdem(raiz);
  printf("\n");
  posOrdem(raiz);
  printf("\n");
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

No *busca(No *raiz, int valor) {
  if (raiz == 0 || raiz->valor == valor) {
    return raiz;
  }
  if (valor < raiz->valor) {
    return busca(raiz->esq, valor);
  }
  return busca(raiz->dir, valor);
}

No *encontrarMin(No *raiz) {
  if (raiz == 0) {
    return 0;
  }

  while (raiz->esq != 0) {
    raiz = raiz->esq;
  }
  return raiz;
}

No *encontrarMax(No *raiz) {
  if (raiz == 0) {
    return 0;
  }

  while (raiz->dir != 0) {
    raiz = raiz->dir;
  }
  return raiz;
}

int altura(No *raiz) {
  if (raiz == 0) {
    return -1;
  }
  int esq = altura(raiz->esq);
  int dir = altura(raiz->dir);

  if (esq < dir) {
    return dir + 1;
  }
  return esq + 1;
}

void preOrdem(No* raiz){
    if(raiz != 0){
        printf("%d ", raiz->valor);
        preOrdem(raiz->esq);
        preOrdem(raiz->dir);
    }
}
void posOrdem(No* raiz){
    if(raiz != 0){
        posOrdem(raiz->esq);
        posOrdem(raiz->dir);
        printf("%d ", raiz->valor);
    }
}
void inOrdem(No* raiz){
    if(raiz != 0){
        inOrdem(raiz->esq);
        printf("%d ", raiz->valor);
        inOrdem(raiz->dir);
    }
}