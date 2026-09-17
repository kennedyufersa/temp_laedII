### Comandos do GDB

- `run (r)` - Executa o programa.
- `break (b)` - Define um ponto de interrupção.
- `continue (c)` - Continua a execução do programa até o próximo ponto de interrupção.
- `step (s)` - Executa a próxima instrução, entrando em funções chamadas.
- `next (n)` - Executa a próxima instrução, pulando funções chamadas.
- `finish (fin)` - Executa até o final da função atual.
- `print (p)` - Exibe o valor de uma variável ou expressão.
- `info (i)` - Fornece informações sobre o estado do programa.
- `backtrace (bt)` - Exibe o rastreamento de pilha (stack trace).
- `quit (q)` - Sai do GDB.
- `continue (c)` - Continua a execução do programa.
- `list (l)` - Exibe o código-fonte ao redor da linha atual ou de um ponto de interrupção.
- `delete (d)` - Remove um ou mais pontos de interrupção.
- `info breakpoints` - Exibe informações sobre todos os pontos de interrupção.
- `display` - Exibe o valor de uma variável automaticamente a cada parada.
- `watch` - Define uma expressão para ser monitorada e parar quando seu valor mudar.
- `set` - Modifica o valor de uma variável durante a depuração.
- `info registers (i r)` - Exibe o conteúdo dos registradores.
- `x` - Exibe o conteúdo da memória em um endereço específico.
- `layout` - Escolhe o layout da janela de exibição durante a depuração.
- `help (h)` - Exibe ajuda sobre comandos e opções disponíveis no GDB.
- `run args` - Executa o programa com argumentos especificados.
- `start` - Inicia o programa e interrompe antes do main() ser chamado.
- `attach pid` - Anexa o GDB a um processo em execução com o PID especificado.
- `detach` - Desanexa o GDB de um processo anexado.
- `info functions` - Lista todas as funções definidas no programa.
- `info locals` - Exibe informações sobre variáveis locais.
- `info breakpoints` - Exibe informações sobre os pontos de interrupção definidos.
- `set breakpoint pending on` - Permite definir pontos de interrupção em funções ainda não carregadas.

### Diferença entre display e whatchpoints
+ display:
  O comando display é usado para configurar variáveis que você deseja monitorar automaticamente durante a execução do programa. Ele permite que você exiba os valores das variáveis em cada parada (stop) ou a cada passo (step) do programa. Essa funcionalidade é útil quando você quer acompanhar o comportamento de uma variável específica ao longo da execução do programa sem ter que digitá-la manualmente em cada parada.

Exemplo:
Suponha que você tenha uma variável chamada contador que controla a iteração de um loop importante em seu programa. Você pode usar o comando display contador para monitorar automaticamente o valor de contador a cada parada ou passo do programa.

+ watchpoints:
  Os watchpoints, por outro lado, são pontos de parada especiais que são acionados quando o valor de uma variável é alterado. Eles permitem que você detecte quando uma variável específica é modificada e pare a execução do programa nesse ponto para examinar o que está acontecendo. Isso é útil quando você deseja identificar o momento exato em que uma variável crítica muda de valor.

Exemplo:
Suponha que você tenha um programa que está causando um comportamento inesperado e suspeita que uma variável chamada flag esteja sendo alterada de forma incorreta. Você pode definir um watchpoint usando o comando watch flag para que o GDB interrompa a execução sempre que o valor de flag mudar, permitindo que você investigue a causa da mudança indesejada.

Em resumo, a principal diferença entre display e watchpoints é que display é usado para exibir automaticamente valores de variáveis em cada parada ou passo, enquanto watchpoints é usado para interromper a execução do programa quando o valor de uma variável específica muda. Ambos os recursos são valiosos na depuração de programas complexos e podem ajudar a encontrar problemas e entender melhor o comportamento do código durante a execução.