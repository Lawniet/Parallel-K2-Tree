# Sobre este diretório

Repositório utilizado para compartilhar o Trabalho de Conclusão de Curso acerca da paralelização da estrutura de dados compactas K²-Tree.

# Base de conhecimento

Para a realização dos estudos utilizamos preferencialmento os livros referência de estrutura de dados [Introdução a Estruturas de Dados: com técnicas de programação em C](), artigos cietíficos (Nieves R. Brisaboa, Susana Ladra, Gonzalo Navarro e etc), tutoriais, guias e forúns de desenvolvimento algorítmico ([SoloLearn](https://www.sololearn.com/Course/CPlusPlus/), [Algoritmos para Grafos - via Sedgewick](https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/graphdatastructs.html), [it-swarm.dev](https://www.it-swarm.dev/search/?q=c%2B%2B#gsc.tab=0&gsc.q=c%2B%2B&gsc.page=1), [stackoverflow.com](https://pt.stackoverflow.com/questions/tagged/c%2b%2b), [GeeksforGeeks](https://www.geeksforgeeks.org/c-plus-plus/?ref=leftbar) e etc). 

Além disto foi utilizada na base de conhecimento as reuniões realizadas pela ferramenta Google Meet, as quais foram períodicas a fim de esclarecer a pesquisa e abordar novos tópicos. As reuniões foram gravadas, sob autorização, pelo prof. Daniel Saad. 

## Requisitos

Para complilar os códigos aqui disponíveis será necessário:

* Um compilador moderno pronto para C ++ 11, como `g ++` versão 4.9 ou superior ou `clang` versão 3.2 ou superior.
* Biblioteca SDSL-Lite ou uma similar que fornce suporte à vetores de bits
* OpenMP na versão 4.5 ou supoerior.
* O sistema de compilação [cmake] [cmake].
* Um sistema operacional de 64 bits. Tanto o Mac OS X quanto o Linux são atualmente suportados.
* Para maior desempenho, o processador do sistema deve suportar operações de bit rápido disponíveis em `SSE4.2`

## Utilização

Para baixar e utilizar os módulos de teste, favor usar os seguintes comandos:

```sh
git clone https://github.com/Lawniet/Parallel-K2-Tree.git
cd Parallel-K2-Tree-main
Make all
```
## Bugs e demais problemas técnicos

Embora tenhamos realizado testes de validação de unidade, em caso de bugs nós encorajamos você a relatar quaisquer problemas por meio do [sistema de rastreamento de problemas do github] (https://github.com/Lawniet/Parallel-Trees/issues) desse projeto. 

## Recursos externos utilizados no projeto

* Biblioteca [SDSL-Lite](https://github.com/simongog/sdsl-lite), módulo de vetor de bits e o algoritmo de construção K²-Tree.

## Licenciamento

Este é um software livre fornecido sob a GNU General Public License
(GPLv3). Para mais informações veja [COPYING file] [CF] na biblioteca
diretório.

# Referências

[CELES, W.; CERQUEIRA, R.; RANGEL, J.Introdução a Estruturas de Dados: com técnicas de programação em c. Elsevier Brasil, 2017.](https://www.elsevier.com/books/introducao-a-estruturas-de-dados/celes/978-85-352-8345-7)

[Graph data structs](https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/graphdatastructs.html)

[CPP Reference](cppreference.com)

[C plus plus](cplusplus.com)

