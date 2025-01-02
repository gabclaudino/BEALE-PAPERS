#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>
#include <getopt.h>
#include "funcs.h"

#define MAXCHAR 128
#define MAXLINHA 10000

void cria_chaves(FILE *livrocifra, FILE *chaves){
    /*cria um vetor de listas(fila) do livro cifra*/ 
    char letra;
    char aux;

    /*ve qual o tamanho do livro cifra*/
    int tamarq;
    fseek(livrocifra, 0, SEEK_END);
    tamarq = ftell(livrocifra);
    fseek(livrocifra, 0, SEEK_SET);
    tamarq = tamarq/sizeof(char);

    /*aloca um vetor para guardar os caracteres do livro cifra*/
    char *textobase = malloc(tamarq * (sizeof(char)));
    fread(textobase,sizeof(char),tamarq,livrocifra);

    /*faz um vetor de filas para guardar as chaves*/
    struct fila *vetorfila[MAXCHAR];
    int i;
    for(i=0; i<MAXCHAR; i++)
        vetorfila[i] = iniciaFila();

    /*verifica se o primeiro caractere eh uma letra/numero*/
    int indice=0;
    letra = textobase[0];
    letra = tolower(letra);
    if((isalpha(letra) != 0) || (isdigit(letra) != 0))
    {
        queue(vetorfila[letra], indice);
        indice++;
    }
    /*verifica se eh a primeira letra/numero da palavra*/
    for(i=1;i<tamarq;i++)
    {
        letra = textobase[i];
        letra = tolower(letra);
        if((isalpha(letra) != 0) || (isdigit(letra) != 0))
            if((textobase[i-1] == ' ') || (textobase[i-1] == '"') || (textobase[i-1] == '\n'))
            {
                queue(vetorfila[letra], indice);
                indice++;
            }
    }


    /*cria arquivo de chaves usando livro cifra*/

    /*verifica qual o primeiro caractere que nao esta com a fila vazia*/
    i=0;
    int temp;
    while(filaVazia(vetorfila[i]) == 1)
        i++;
    temp = i;

    /*printa o primeiro valor no arquivo de Chaves*/
    /*fiz isso para nao "bugar" o \n ao final do laco*/
    if((filaVazia(vetorfila[i]) != 1))
    {
        aux = i;
        fprintf(chaves, "%c: ", aux);
        struct NoFila *atual;
        atual = vetorfila[i]->ini;

        /*percorre a fila inteira para, escrevendo seus valores*/
        /*na respectiva chave, ate acabar a fila*/
        while(atual != NULL)
        {
            fprintf(chaves, "%d ", atual->valor);
            atual = atual->prox;
        }
    }

    /*faz mesma coisa que acima, porem coloca um \n entre*/
    /*cada inicio das chaves*/
    for(i=temp+1; i<MAXCHAR; i++)
    {
        if((filaVazia(vetorfila[i]) != 1))
        {
            fprintf(chaves, "\n");
            aux = i;
            fprintf(chaves, "%c: ", aux);
            struct NoFila *atual;
            atual = vetorfila[i]->ini;
            while(atual != NULL)
            {
                fprintf(chaves, "%d ", atual->valor);
                atual = atual->prox;
            }
        }
    }
    

}