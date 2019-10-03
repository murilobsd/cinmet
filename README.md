# CINMET
> Rápida biblioteca para consumir e interpretar dados meteorológicos da rede INMET.

<p align="center">
  <img src="https://m0x.ru/logo-cinmet.png" alt="Logo CINMET" width="280px"/>
</p>

[![license](https://img.shields.io/badge/License-BSD-blue.svg?style=for-the-badge)](LICENSE)

> A meteorologia vem tomando conta dos noticiários nas últimas décadas. A crecente imprevisibilidade
do meio ambiente torna os fenômenos naturais cada vez mais difíceis de se previnir, prejudicando
não somente a natureza mas todos que dependem dela, incluindo a NÓS.
É certo que as atitudes dos seres humanos vêm contribuindo com a crescente instabilidade
dos efeitos naturais fazendo com que certas alterações tragam danos irreversíveis para a humanidade.

## CINMET?

CINMET é uma biblioteca simples escrita em C, para obter dados e
tratá-los do website do Instituto Nacional de Meteorologia (INMET).
Hoje existem inúmeros serviços fornecidos pelo INMET, os quais servem cientistas,
estudantes, agricultores, indústria e comércio, porêm não existe nenhuma
API disponível para o consumo por outros softwares!
Ai que o CINMET entra com uma simples interface você pode adicionar funcionalidades
extras ao seu software de meteorologia ou mesmo aos seus estudos de meteorologia.

**O CINMET apesar de utilizar a fonte de dados do INMET, não tem nenhum
vínculo com a instituição.**

> Todos os esforços, são frutos de finais de semana sem NETFLIX e acredite
alguns sem :coffee: :sleeping:

## Índice

- [Instalação](#instalação)
    - [Dependências](#dependências)
    - [Compilando](#Compilando)
- [Uso](#uso)

## Instalação

Os passos abaixo serão conduzidos no sistema operacional
[OpenBSD](https://openbsd.org), alguns comando devem divergir do seu
sistema operacional.

### Dependências

Para as chamadas http a biblioteca CINMET utiliza a biblioteca CURL,
para instalar via package:

```
doas pkg_add curl
```

### Compilando

```
make
```

## Uso

No código fonte você deve ter percebido que existe um _main_, ele só é
utilizado para fins de teste e não deve ser usado. Abaixo um exemplo de
como obter as estações do estado de São Paulo.

```c
#include <stdio.h>
#include <stdlib.h>

#include "inmet.h"

int
main(int argc, char *argv[])
{
        Stations *ss, *sts_sp;
        size_t num_sta_sp = 0;

        /* init sts_sp */
        sts_sp = init_stations();

        /* get list of stations */
        ss = get_stations();
        //dump_stations(ss);

        /* search stations by federative unit (UF) */
        if ((num_sta_sp = search_sta_uf("SP", ss, sts_sp)) == 0)
                printf("Not found stations on SP\n");
        else
                dump_stations(sts_sp);

        //clean_stations(sts_sp);
        if (sts_sp != NULL) free(sts_sp);
        /* clean list stations */
        clean_stations(ss);

        return (0);
}
```

Agora basta compilar:

```
cc -o myprogram -I./ -linmet myprogram.c
```
