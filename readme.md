# Naive::Morph

## Sobre

Esta é uma biblioteca experimental e didática de Processamendo Digital de
Imagens e Visão Computacional, desenvolvida em C++23. 

O projeto nasceu como objeto de estudo para a disciplina PDI-VC 2026.2,
ministrada pelo Prof. Francisco Zampitolli.

Tem por objetivo consolidar os conceitos matemáticos e algorítimos de forma
pura, sem otimizações complexas e sem auxilio de frameworks de terceiros, para
uma maior clareza dos estudos. 

## Uso
**Naive::Morph** é uma *Single-Header Library*, tendo todo seu conteúdo
organizado no arquivo `naivemorph.hpp`. Para utilizar faça download biblioteca,
matenha-a no mesmo diretório de seu arquivo que será compilado (ex: main.cpp). 

É necessário definir a flag `NAIVE_MORPH_IMPLEMENTATION` como no snippet abaixo: 

```cpp
#define NAIVE_MORPH_IMPLEMENTATION
#include  "naivemorph.hpp" 

namespace mm = Naive::Morph;
```

