FuzzyTruck
==========

Dependências
------------

- JDK e JRE para Java 10+;
- Compilador `g++` com suporte a C++17;
- Python 3;
- Um compilador LaTeX (para geração do relatório).

Como utilizar
-------------

Há um `makefile` que disponibiliza as seguintes operações:

- `run-server`: Executa o servidor com a interface gráfica do simulador.
- `run-client`: Executa o cliente socket para cálculo do sistema Fuzzy e envio
  das informações para o servidor. A porta é especificada com `PORT=<valor>`. O
  _host_ é fixo em `localhost`.
- `show-chart`: Mostra gráficos dos intervalos dos conjuntos Fuzzy. O arquivo
  FCL e seu _"Function Block"_ a serem analisados devem ser especificados com
  `FILE=<arquivo>` e `FUNCTIONBLOCK=<function block>`.

Por exemplo, para se rodar o cliente socket na porta 4321, pode-se executar:

```bash
$ make run-client PORT=4321
```

Ferramentas
---------

As seguintes ferramentas já vem disponíveis e não necessitam compilação:

- Uma biblioteca e software de Lógica Fuzzy em Java, `jFuzzyLogic`. É utilizada
  para geração de código C++ a partir de FCL para execução do sistema, bem como
  exibição de gráficos.
- O código C++ gerado é apenas um .cpp (que inclui um ponto de entrada `main`),
  então para separar as definições em um header e eliminar o ponto de entrada é
  utilizado o script [C++ Fixer](/tools/cppfixer.py).

As ferramentas que precisam ser compiladas são:

- `lib/socket.a`: Uma biblioteca de Sockets escrita em C++. O código fonte está
  em [tools/socket](/tools/socket);
- `lib/truck.a`: Uma biblioteca com comandos para o Fuzzy Truck escrita em C++
  a partir do código gerado com `jFuzzyLogic` e consertado com o
  [C++ Fixer](/tools/cppfixer.py);
- [Charter](tools/Charter.java): Um pequeno bytecode Java que mostra gráficos
  dos intervalos dos conjuntos Fuzzy;
- [Cliente Socket](/src): O cliente socket específico para o Fuzzy Truck,
  escrito em C++ utilizando o `lib/truck.a` e `lib/socket.a`.
