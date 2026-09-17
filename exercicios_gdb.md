# Laboratório de Depuração com GDB

## Objetivo

Utilizar o **GDB (GNU Debugger)** para investigar a execução de programas em C, com ênfase em:

- chamadas de funções recursivas;
- pilha de execução (*stack*);
- parâmetros e variáveis locais;
- endereços de memória;
- vetores;
- ponteiros;
- alocação dinâmica;
- estruturas encadeadas;
- inspeção direta da memória.

Os exercícios utiliza os programas `algoritmos_recursivos.c` e `bst.c`.

## Preparação

Compile os programas com informaçõs de depuração e sem otimizações:

```bash
gcc -Wall -Wextra -g -O0 algoritmos_recursivos.c -o algoritmos_recursivos
gcc -Wall -Wextra -g -O0 bst.c -o bst
```

Para iniciar o GDB sem a mensagem inicial:

```bash
gdb -q ./algoritmos_recursivos
```

ou:

```bash
gdb -q ./bst
```

## Examinando a memória com `x`

O comando `x` (*examine*) lê o conteudo da memória a partir de um endereço. Use-o quando quiser observar diretamente bytes, elementos de um vetor ou campos de uma estrutura, além dos valor mostrados por `print`.

```gdb
x/<quantidade><formato><unidade> <endereço>
```

- **Quantidade:** número de unidades a mostrar.
- **Formato:** como apresentar os dados; por exemplo, `x` (hexadecimal), `d` (decimal com sinal), `u` (decimal sem sinal) ou `c` (caractere).
- **Unidade:** tamanho de cada item lido: `b` (1 byte), `h` (2 bytes), `w` (4 bytes) ou `g` (8 bytes).
- **Endereço:** expressão que aponta para a região a examinar, como `&vetorMerge[0]`, `v` ou `novo`.

Exemplos para usar quando a execução estiver parada em um ponto onde as variáveis estejam disponíveis:

```gdb
x/7dw &vetorMerge[0]
x/16xb novo
print sizeof(No)
```

O primeiro comando mostra sete unidade de 4 bytes em decimal a partir do vetor; o segundo mostra 16 bytes do nó em hexadecimal. Em `x/7dw`, o `7` é a quantidade, `d` é o formato e `w` é a unidade de 4 bytes. Confirme o tamanho real do tipo com `print sizeof(...)` antes de escolher a unidade: ler a memória com um tamanho incorreto pode agrupar os bytes de forma inesperada.

---

## Questão 1 — Pilha de execução do fatorial

Execute o programa `algoritmos_recursivos.c` utilizando o GDB. Coloque um *breakpoint* na função `fatorial` e interrompa a execução quando o parâmetro `n` possuir valor `1`.

Utilizando apenas informações obtidas através do GDB, responda:

1. Quanto *stack frames* da função `fatorial` existem nesse instante?
2. Qual é o valor de `n` em cada um desses frames?
3. Qual comando do GDB permite visualizar toda a sequência de chamadas?
4. Selecione o frame correspondente a `fatorial(4)` e informe o endereço de memória do parâmetro `n`.
5. Compare esse endereço com o endereço de `n` em `fatorial(3)`. Eles são iguais?
6. Explique o que essa observação demonstra sobre as variáveis locais e os parâmetros em chamadas recursivas.

---

## Questão 2 — Investigando o Fibonacci

A função `fibonacci` realiza chamadas recursiva para calcular o resultado.

Coloque um *breakpoint* na função:

```gdb
break fibonacci
```

Execute o programa e acompanhe suas chamdas.

Determine através do GDB:

1. Quantas vezes a função `fibonacci` é chamada para calcular `fibonacci(6)`?
2. Quantas dessas chamadas possuem `n == 2`?
3. Crie um **breakpoint condicional** que interrompa a execução somente quando `n == 2`.
4. Quando esse breakpoint for atingido, utilize o GDB para registrar a sequência de chamadas que levou até uma das ocorrências de `fibonacci(2)`.
5. A partir da depuração, explique por que essa implementação realiza cálculos repetidos.

---

## Questão 3 — Depurando a busca binária

O programa possui o seguinte vetor:

```c
int vetorBusca[] = {10, 20, 30, 40, 50, 60, 70, 80};
```

e procura pelo valor `60`.

Coloque um *breakpoint* na função `buscaBinaria`.

Para cada chamada recursiva, utillize o GDB para preencher a tabela:

| Chamada | `inicio` | `fim` | `meio` | `v[meio]` |
|---|---:|---:|---:|---:|
| 1 | | | | |
| 2 | | | | |
| 3 | | | | |
| 4 | | | | |

Em seguida, responda:

1. Quantas chamadas foram necessárias para encontrar `60`?
2. Qual índice foi retornado?
3. Qual é o endereço inicial do vetor `v`?
4. Qual é o endereço de `v[5]`?
5. Utilize `sizeof` no GDB para descobrir o tamanho de cada elemento do vetor.
6. Explique a relação entre o tamanho de um elemento e a diferença entre os endereços de `v[0]` e `v[5]`.

---

## Questão 4 — Stack e Heap na árvore binária

No programa `bst.c`, a função `criarNo` utiliza alocação dinâmica:

```c
No *novo = malloc(sizeof(No));
```

Coloque um *breakpoint* na função `criarNo` e acompanhe a criação do primeiro nó.

Utilizando o GDB, determine:

1. Qual é o valor de `sizeof(No)`?
2. Qual é o endereço da variável local `novo`?
3. Após a execução do `malloc`, qual endereço está armazenado dentro de `novo`?
4. O endereço de `novo` e o endereço armazenado em `novo` são iguais? Explique a diferença entre eles.
5. Utilize o comando `x` para visualizar os bytes correspondentes ao nó alocado.
6. Investigue os campos da estrutura e identifique os valores armazenados em:
   - `valor`;
   - `esq`;
   - `dir`.
7. Explique quais informações estão associadas à variável local `novo` e quais pertencem ao objeto criado dinamicamente.

---

## Questão 5 — Reconstruindo a árvore somente pelo GDB

O programa `bst.c` cria uma arvore binária de busca inserindo, nessa ordem:

```text
10, 30, 40, 8, 14
```

Coloque um *breakpoint* imediatamente após todas as inserções.

**Não utilize as funções de percurso da árvore para descobrir sua estrutura.**

Utilizando comandos do GDB como `print`, `ptype`, `sizeof` e `x`, além dos ponteiros `esq` e `dir`:

1. Descubra o endereço de memória de cada um dos cinco nó.
2. Preencha a tabela:

| Valor | Endereço do nó | Filho esquerdo | Filho direito |
|---:|---|---|---|
| 10 | | | |
| 8 | | | |
| 30 | | | |
| 14 | | | |
| 40 | | | |

3. A partir exclusivamente das informações obtidas através dos ponteiros, desenhe a árvore resultante.
4. Identifique quais nós são folhas apenas observando os valores dos ponteiros `esq` e `dir`.
5. Identifique o nó raiz sem utilizar as funções de percurso.
6. Explique como os endereço armazenados nos campos `esq` e `dir` permitem representar uma árvore na memória.

## Questão 6 — Alterando um valor durante a depuração

No `bst.c`, interrompa a execução na primeira chamada de `busca`, que ocorre após as cinco inserções. Nesse momento, `raiz` aponta para a árvore já construída. Altere o valor do nó esquerdo da raiz de `8` para `9`, sem editar o código-fonte:

```bash
gcc -Wall -Wextra -g -O0 bst.c -o bst
gdb -q ./bst
```

```gdb
break busca
run
print raiz->esq->valor
set var raiz->esq->valor = 9
print raiz->esq->valor
disable 1
continue
```

O primeiro `print` deve mostrar `8` e o segundo, `9`. O `disable 1` desativa o breakpoint criado nesse exemplo para que `continue` prossiga sem parar nas chamadas recursivas de `busca`. Na saída do programa, o percurso em pré-ordem passa a começar com `10 9 30`, confirmando que a alteração afetou o nó em memória durante essa execução. Ao executar o programa novamente, a árvore volta a ser criada com o valor original `8`.

---

## Questão 7 — Acompanhando a recursão do MDC

No programa `algoritmos_recursivos.c`, a função `mdc` utiliza o algoritmo de Euclides de forma recursiva. O programa calcula:

```c
mdc(48, 18)
```

Coloque um *breakpoint* na função `mdc`.

Utilizando o GDB:

1. Registre os valores de `a` e `b` em cada chamada.
2. Preencha a tabela:

| Chamada | `a` | `b` | `a % b` |
|---|---:|---:|---:|
| 1 | | | |
| 2 | | | |
| 3 | | | |
| 4 | | | |

3. Em qual chamada o caso-base é atingido?
4. Qual é o valor de retorno dessa chamada?
5. Quando estiver no caso-base, visualize a pilha de chamadas.
6. Navegue entre os diferentes frames e consulte os valore de `a` e `b` em cada um deles.
7. Explique como o valor encontrado no caso-base retorna pelas chamadas anteriores.

---

## Questão 8 — Investigando a potenciação rápida

O programa calcula:

```c
potencia(2, 10)
```

A função reduz o expoente pela metade em cada chamada recursiva.

Coloque um *breakpoint* na função `potencia` e acompanhe sua execução.

1. Registre o valor de `base` e `exp` em cada chamada recursiva.
2. Qual é a sequência de valores assumidos por `exp`?
3. Quantos frames da função `potencia` existem quando `exp == 0`?
4. Utilize o GDB para visualizar todas as chamadas ativas nesse momento.
5. Selecione cada frame e determine o endereço do parâmetro `exp`.
6. Os diferentes frames compartilham a mesma variável `exp`? Justifique utilizando os endereços encontrados.
7. Acompanhe o retorno das funções e observe o valor da variável `metade`.
8. Explique como a depuração evidencia que essa estratégia reduz a profundidade da recursão em comparação com uma implementação que calculasse `base^(exp-1)` recursivamente.

---

## Questão 9 — Investigando o Merge Sort e o vetor na memória

Utilize a função `mergeSort` do programa `algoritmos_recursivos.c`.

O vetor inicial é:

```c
int vetorMerge[] = {38, 27, 43, 3, 9, 82, 10};
```

Coloque um *breakpoint* em `mergeSort`.

### Parte A — Divisão recursiva

1. Para cada chamada inicial, registre os valores de:
   - `inicio`;
   - `fim`;
   - `meio`.

2. Quando uma chamada atingir o caso-base (`inicio >= fim`), visualize a pilha de execução.

3. Determine quantas chamadas de `mergeSort` estão ativas nesse momento.

4. Navegue entre os frames e identifique qual intervalo do vetor cada frame representa.

### Parte B — Memória do vetor

Antes da ordenação, descubra:

1. O endereço de `vetorMerge[0]`.
2. O endereço de `vetorMerge[1]`.
3. O endereço de `vetorMerge[6]`.
4. O tamanho de cada elemento do vetor.

Utilize o comando `x` para visualizar diretamente na memória os sete valores do vetor.

### Parte C — Alterações durante a ordenação

Coloque um *breakpoint* na função `merge`.

Durante as chamadas dessa função:

1. Observe os valores de `inicio`, `meio` e `fim`.
2. Examine o conteúdo de `v` antes e depois de uma operação de intercalação.
3. Observe o vetor temporário `temp`.
4. Descubra o tamanho de `temp` em uma das chamadas.
5. Determine o endereço de `temp` e compare-o com o endereço do vetor original.
6. Explique por que diferentes chamadas de `merge` pode possuir vetores temporários distintos.

Ao final, utilize o GDB para confirmar que o vetor contém:

```text
3 9 10 27 38 43 82
```

---

## Comandos úteis

Durante os exercícios, alguns comandos do GDB podem ser úteis:

```gdb
break funcao
break arquivo.c:linha
condition N expressao
run
continue
next
step
finish
backtrace
bt full
frame N
up
down
info args
info locals
print variavel
print &variavel
print sizeof(variavel)
ptype tipo
x/10dw endereco
x/20gx endereco
display variavel
undisplay N
```

> O objetivo do laboratório não é apenas obter as respostas, mas utilizar o depurador para relacionar a execução do código C com funções, *stack frames*, variáveis, ponteiros e regiões de memória.
