#ifndef FUNCS_H
#define FUNCS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>
#include <getopt.h>

#define MAXCHAR 128
#define MAXLINHA 10000

/*no da fila*/
struct NoFila{
    int valor;
    struct NoFila *prox;
    struct NoFila *ant;
};

/*struct da fila a base de uma lista duplamente encadeada*/
struct fila{
    struct NoFila *ini;
    struct NoFila *fim;
    int tam;
};

struct fila *iniciaFila();

int filaVazia(struct fila *f);

void queue(struct fila *f, int x);

void dequeue(struct fila *f);

void imprimeCabeca(struct fila *f);

void destroiFila(struct fila *f);

void cria_chaves(FILE *livrocifra, FILE *chaves);

void Codifica_usando_lc(FILE *livrocifra, FILE *mensagemcod, FILE *mensagemdecod);

void Decodifica_usando_ac(FILE *chaves, FILE *mensagemcod, FILE *mensagemdecod);

void Decodifica_usando_lc(FILE *livrocifra, FILE *mensagemcod, FILE *mensagemdecod);

#endif