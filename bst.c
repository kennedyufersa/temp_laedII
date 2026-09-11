#include <stdio.h>
#include <stdlib.h>

typedef struct No {
  int valor;
  struct No *esq;
  struct No *dir;
} No;


int main(){
    No *novo = malloc(sizeof(struct No));
    novo->esq = 0;
    novo->dir = 0;
    novo->valor = 10;

    novo->dir = malloc(sizeof(struct No));
    novo->dir->dir = 0;
    novo->dir->esq = 0;
    novo->dir->valor = 30;
}

/*
Inserir manualmente:
10 - 30 - 40 - 8 - 25 - 14
*/