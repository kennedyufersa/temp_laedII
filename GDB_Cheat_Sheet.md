# GDB — guia rápido de comandos

Explicação em português dos comandos de [GDB_Cheat_Sheet.pdf](GDB_Cheat_Sheet.pdf). Nos exemplos, substitua os valores entre `< >` pelos seus próprios valores. Compile com informações de depuração, por exemplo: `gcc -g programa.c -o programa`.

## Iniciar e executar

| Comando | O que faz | Exemplo |
| --- | --- | --- |
| `gdb <programa> [core]` | Abre o executável no GDB; opcionalmente carrega um arquivo de core dump. É um comando do terminal. | `gdb ./programa` ou `gdb ./programa core` |
| `gdb --args <programa> <argumentos...>` | Abre o executável já com argumentos definidos. É um comando do terminal. | `gdb --args ./programa entrada.txt` |
| `gdb --pid <pid>` | Anexa o GDB a um processo em execução. É um comando do terminal. | `gdb --pid 1234` |
| `set args <argumentos...>` | Define os argumentos para a próxima execução pelo GDB. | `set args entrada.txt` |
| `run` | Inicia o programa ou o reinicia após uma execução anterior. | `run` |
| `kill` | Encerra o programa que está sendo depurado, sem fechar o GDB. | `kill` |

## Pontos de parada e de observação

| Comando | O que faz | Exemplo |
| --- | --- | --- |
| `break <local>` | Para a execução ao chegar a uma função, linha ou endereço. | `break main` |
| `delete <número>` | Remove o breakpoint ou watchpoint com esse número. `delete` sem número remove todos, após confirmação. | `delete 1` |
| `clear [local]` | Remove breakpoints no local indicado; sem argumento, usa a linha atual. | `clear programa.c:42` |
| `enable <número>` / `disable <número>` | Ativa ou desativa um breakpoint ou watchpoint sem removê-lo. | `disable 1` / `enable 1` |
| `watch <expressão>` | Para quando o valor da expressão muda. | `watch contador` |
| `break <local> if <condição>` | Cria um breakpoint que só para quando a condição é verdadeira. | `break programa.c:42 if contador > 10` |
| `watch <expressão> if <condição>` | Cria um watchpoint condicional. | `watch contador if contador > 10` |
| `condition <número> <condição>` | Define ou altera a condição de um breakpoint ou watchpoint existente. | `condition 1 contador > 10` |

Em `break`, o `<local>` pode ser uma função (`break main`), uma linha do arquivo atual (`break 42`) ou arquivo e linha (`break programa.c:42`). Para `watch`, use uma expressão que possa ser observada, como `watch contador`. Exemplo condicional: `break programa.c:42 if contador > 10`.

## Pilha e controle da execução

| Comando | O que faz | Exemplo |
| --- | --- | --- |
| `backtrace` ou `where` | Mostra a pilha de chamadas. | `backtrace` |
| `backtrace full` ou `where full` | Mostra a pilha e também as variáveis locais disponíveis em cada quadro. | `backtrace full` |
| `frame <número>` | Seleciona um quadro da pilha para examinar suas variáveis. | `frame 1` |
| `step` | Executa a próxima linha, entrando em funções chamadas. | `step` |
| `next` | Executa a próxima linha, passando pela chamada de função sem entrar nela. | `next` |
| `finish` | Executa até a função atual retornar. | `finish` |
| `continue` | Retoma a execução até a próxima parada ou o fim do programa. | `continue` |

`step` e `next` avançam por **linhas de código-fonte**, quando essa informação está disponível. `display` mostra valores a cada parada; `watch` provoca uma parada quando o valor observado muda.

## Variáveis e memória

| Comando | O que faz | Exemplo |
| --- | --- | --- |
| `print[/formato] <expressão>` | Mostra o valor de uma expressão, variável, endereço ou registrador. | `print/x contador` |
| `display[/formato] <expressão>` | Mostra automaticamente a expressão a cada parada. | `display contador` |
| `undisplay <número>` | Remove um `display` pelo número mostrado ao criá-lo. | `undisplay 1` |
| `enable display <número>` / `disable display <número>` | Ativa ou desativa uma exibição automática. | `disable display 1` / `enable display 1` |
| `x/<n><f><u> <endereço>` | Examina a memória: quantidade `n`, formato `f` e tamanho de unidade `u`. | `x/16xb ponteiro` |

Formatos usuais para `print`, `display` e `x`: `a` (endereço), `c` (caractere), `d` (decimal com sinal), `f` (ponto flutuante), `o` (octal), `s` (string), `t` (binário), `u` (decimal sem sinal) e `x` (hexadecimal). Em `x`, os tamanhos de unidade são `b` (1 byte), `h` (2 bytes), `w` (4 bytes) e `g` (8 bytes).

Em `<expressão>`, você pode usar expressões de C, `arquivo.c::variavel` para uma variável estática do arquivo, `funcao::variavel` para uma variável da função, `{tipo}endereco` para interpretar memória como um tipo e `$registrador` para consultar um registrador. Os registradores `$eip`, `$esp` e `$ebp` citados no PDF são da arquitetura x86 de 32 bits; seus nomes variam conforme a arquitetura.

## Threads, alterações e código-fonte

| Comando | O que faz | Exemplo |
| --- | --- | --- |
| `thread <número>` | Seleciona uma thread para inspeção. | `thread 2` |
| `set var <variável>=<valor>` | Altera o valor de uma variável durante a depuração. | `set var contador=0` |
| `return <expressão>` | Faz a função selecionada retornar imediatamente com o valor indicado. | `return 0` |
| `directory <diretório>` | Acrescenta um diretório à busca por arquivos-fonte. | `directory ./src` |
| `list` | Mostra linhas de código-fonte próximas da posição atual. | `list` |
| `list <arquivo>:<função>` | Mostra o código da função no arquivo indicado. | `list programa.c:main` |
| `list <arquivo>:<linha>` | Mostra o código próximo dessa linha. | `list programa.c:42` |
| `list <primeira>,<última>` | Mostra o intervalo de linhas indicado. | `list 40,50` |
| `set listsize <quantidade>` | Define quantas linhas `list` mostra por padrão. | `set listsize 20` |

## Sinais e informações

| Comando | O que faz | Exemplo |
| --- | --- | --- |
| `handle <sinal> <opções>` | Configura como o GDB trata um sinal. As opções incluem `print`/`noprint`, `stop`/`nostop` e `pass`/`nopass`. | `handle SIGSEGV stop print` |
| `disassemble [local]` | Mostra as instruções de máquina da função atual ou do local indicado. | `disassemble main` |
| `info args` | Mostra os argumentos da função do quadro selecionado. | `info args` |
| `info breakpoints` | Lista breakpoints e watchpoints. | `info breakpoints` |
| `info display` | Lista as expressões configuradas com `display`. | `info display` |
| `info locals` | Mostra as variáveis locais do quadro selecionado. | `info locals` |
| `info sharedlibrary` | Lista as bibliotecas compartilhadas carregadas. | `info sharedlibrary` |
| `info signals` | Lista os sinais e o tratamento configurado para cada um. | `info signals` |
| `info threads` | Lista as threads do processo. | `info threads` |
| `show directories` | Mostra os diretórios de busca por arquivos-fonte. | `show directories` |
| `show listsize` | Mostra quantas linhas `list` exibe por padrão. | `show listsize` |
| `whatis <variável>` | Mostra o tipo de uma variável ou expressão. | `whatis contador` |

**Nota sobre o PDF:** a descrição de `clear` nele diz que o comando apaga todos os breakpoints. No GDB, `clear` remove os breakpoints de um **local**; para remover todos, use `delete` sem número.
