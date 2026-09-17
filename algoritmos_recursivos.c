#include <stdio.h>

/* 1. Fatorial */
long long fatorial(int n) {
    if (n <= 1)
        return 1;

    return n * fatorial(n - 1);
}

/* 2. Fibonacci */
long long fibonacci(int n) {
    if (n <= 1)
        return n;

    return fibonacci(n - 1) + fibonacci(n - 2);
}

/* 3. Soma dos elementos de um vetor */
int somaVetor(int v[], int n) {
    if (n == 0)
        return 0;

    return v[n - 1] + somaVetor(v, n - 1);
}

/* 4. Busca binaria recursiva */
int buscaBinaria(int v[], int inicio, int fim, int valor) {
    if (inicio > fim)
        return -1;

    int meio = inicio + (fim - inicio) / 2;

    if (v[meio] == valor)
        return meio;

    if (valor < v[meio])
        return buscaBinaria(v, inicio, meio - 1, valor);

    return buscaBinaria(v, meio + 1, fim, valor);
}

/* 5. Maximo divisor comum - Algoritmo de Euclides */
int mdc(int a, int b) {
    if (b == 0)
        return a;

    return mdc(b, a % b);
}

/* 6. Potenciacao rapida */
long long potencia(long long base, unsigned int exp) {
    if (exp == 0)
        return 1;

    long long metade = potencia(base, exp / 2);

    if (exp % 2 == 0)
        return metade * metade;

    return base * metade * metade;
}

/* Funcao auxiliar do Merge Sort */
void merge(int v[], int inicio, int meio, int fim) {
    int tamanho = fim - inicio + 1;
    int temp[tamanho];

    int i = inicio;
    int j = meio + 1;
    int k = 0;

    while (i <= meio && j <= fim) {
        if (v[i] <= v[j])
            temp[k++] = v[i++];
        else
            temp[k++] = v[j++];
    }

    while (i <= meio)
        temp[k++] = v[i++];

    while (j <= fim)
        temp[k++] = v[j++];

    for (i = inicio, k = 0; i <= fim; i++, k++)
        v[i] = temp[k];
}

/* 7. Merge Sort */
void mergeSort(int v[], int inicio, int fim) {
    if (inicio >= fim)
        return;

    int meio = inicio + (fim - inicio) / 2;

    mergeSort(v, inicio, meio);
    mergeSort(v, meio + 1, fim);

    merge(v, inicio, meio, fim);
}

void imprimirVetor(int v[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", v[i]);

    printf("\n");
}

int main(void) {
    /* 1. Fatorial */
    int nFatorial = 5;
    printf("1. Fatorial\n");
    printf("%d! = %lld\n\n", nFatorial, fatorial(nFatorial));

    /* 2. Fibonacci */
    int nFibonacci = 6;
    printf("2. Fibonacci\n");
    printf("Fibonacci(%d) = %lld\n\n",
           nFibonacci, fibonacci(nFibonacci));

    /* 3. Soma recursiva de vetor */
    int vetorSoma[] = {10, 20, 30, 40, 50};
    int tamanhoSoma = sizeof(vetorSoma) / sizeof(vetorSoma[0]);

    printf("3. Soma recursiva de vetor\n");
    printf("Soma = %d\n\n", somaVetor(vetorSoma, tamanhoSoma));

    /* 4. Busca binaria */
    int vetorBusca[] = {10, 20, 30, 40, 50, 60, 70, 80};
    int tamanhoBusca = sizeof(vetorBusca) / sizeof(vetorBusca[0]);
    int procurado = 60;

    printf("4. Busca binaria recursiva\n");

    int posicao = buscaBinaria(
        vetorBusca,
        0,
        tamanhoBusca - 1,
        procurado
    );

    if (posicao != -1)
        printf("%d encontrado na posicao %d.\n\n",
               procurado, posicao);
    else
        printf("%d nao encontrado.\n\n", procurado);

    /* 5. MDC */
    int a = 48;
    int b = 18;

    printf("5. Maximo divisor comum\n");
    printf("MDC(%d, %d) = %d\n\n", a, b, mdc(a, b));

    /* 6. Potenciacao rapida */
    long long base = 2;
    unsigned int expoente = 10;

    printf("6. Potenciacao rapida\n");
    printf("%lld^%u = %lld\n\n",
           base, expoente, potencia(base, expoente));

    /* 7. Merge Sort */
    int vetorMerge[] = {38, 27, 43, 3, 9, 82, 10};
    int tamanhoMerge = sizeof(vetorMerge) / sizeof(vetorMerge[0]);

    printf("7. Merge Sort\n");
    printf("Antes:  ");
    imprimirVetor(vetorMerge, tamanhoMerge);

    mergeSort(vetorMerge, 0, tamanhoMerge - 1);

    printf("Depois: ");
    imprimirVetor(vetorMerge, tamanhoMerge);

    return 0;
}
