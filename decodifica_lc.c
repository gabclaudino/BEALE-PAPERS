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

void Decodifica_usando_lc(FILE *livrocifra, FILE *mensagemcod, FILE *mensagemdecod){

    /*cria um vetor de listas(fila) do livro cifra*/
     
    char letra;
    char aux;

    /*veirifica o tamanho do livro cifra*/
    int tamarq;
    fseek(livrocifra, 0, SEEK_END);
    tamarq = ftell(livrocifra);
    fseek(livrocifra, 0, SEEK_SET);
    tamarq = tamarq/sizeof(char);

    /*cria e aloca um vetor para guardar os caracteres do livro cifra*/
    char *textobase = malloc(tamarq * (sizeof(char)));
    fread(textobase,sizeof(char),tamarq,livrocifra);

    /*cria um vetor de filas para armazenar as chaves*/
    struct fila *vetorfila[MAXCHAR];
    int i;
    for(i=0; i<MAXCHAR; i++)
        vetorfila[i] = iniciaFila();

    /*verifica se o primeiro caractere do texto eh um numero ou letra */
    int indice=0;
    letra = textobase[0];
    letra = tolower(letra);
    if((isalpha(letra) != 0) || (isdigit(letra) != 0))
    {
        /*se sim enfilera a chave no indice da letra/numero*/
        queue(vetorfila[letra], indice);
        indice++;
    }
    /*faz isso para as posicoes do livro crifra*/
    for(i=0;i<tamarq;i++)
    {
        letra = textobase[i];
        letra = tolower(letra);
        if((isalpha(letra) != 0) || (isdigit(letra) != 0))

            /*verifica se eh a primeira letra/numero da palavra*/
            if((textobase[i-1] == ' ') || (textobase[i-1] == '"') || (textobase[i-1] == '\n'))
            {
                queue(vetorfila[letra], indice);
                indice++;
            }
    }

    /*aloca um vetor com os numeros codificados*/
    int *vetorcod = malloc(sizeof(int));
    int num;
    int sizev = 2;
    i=0;

    /*vai realocando ate o fim da mensagem codificada*/
    fscanf(mensagemcod, "%d", &num);
    vetorcod[i] = num;
    i++;
    while(!feof(mensagemcod))
    {
        vetorcod = realloc(vetorcod, sizev * sizeof(int));
        sizev++;
        fscanf(mensagemcod, "%d", &num);
        /*salva o numero codificado no vetor de codificados*/
        vetorcod[i] = num;
        i++;
    }
    int reg = i;
    
    int j;

    /*percorre o vetor de numeros codificados e verifica qual letra*/
    /*ele eh com base na chave gerada pelo livro cifra*/
    for(i=0;i<reg-1;i++)
    {
        /*se o numero codificado for -1, escreve um espaco*/
        if(vetorcod[i] == -1)
            fprintf(mensagemdecod, " ");
        else if(vetorcod[i] == -2)
            fprintf(mensagemdecod, "?");
        else if(vetorcod[i] == -3)
            fprintf(mensagemdecod, "!");
        else
        {
            /*busca em todas as filas*/
            for(j=0;j<MAXCHAR;j++)
            {
                /*percore a fila de todas as letras ate encontrar*/
                /*a letra/numero correspondente*/
                struct NoFila *atual;
                atual = vetorfila[j]->ini;

                /*percorre a fila da letra procurando o numero correspondente*/
                while(atual != NULL)
                {
                    /*faz a comparacao do numero codificado
                     com a chave do livro cira*/
                    if(vetorcod[i] == atual->valor)
                        fprintf(mensagemdecod, "%c", j);
                    atual = atual->prox;
                }
            }
        }
    }
    free(textobase);
    free(vetorcod);

}