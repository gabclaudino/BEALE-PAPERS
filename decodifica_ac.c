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

void Decodifica_usando_ac(FILE *chaves, FILE *mensagemcod, FILE *mensagemdecod){

    /*cria um vetor de filas para guarda as chaves, o caractere eh o indice do vetor*/
    int i;
    struct fila *vetorchaves[MAXCHAR];
    for(i=0;i<MAXCHAR;i++)
        vetorchaves[i] = iniciaFila();
    
    /*percorre a linha inteira*/
    char linhas[MAXLINHA+1];
    while(fgets(linhas, MAXLINHA, chaves))
    {
        /*letra que vira indice*/
        char letra = linhas[0];

        /*pula o : e o espaco entre a letra e as chaves*/
        int pos = 2;

        /*enquando nao for o final da linha ou do arquivo*/
        while((linhas[pos] != '\n') && (linhas[pos] != '\0'))
        {
            /*veririca se o ponteiro aponta para um numero*/
            if(isdigit(linhas[pos]))
            {
                /*se sim utuliza a func atoi para tranformar*/
                /*uma string em um inteiro */
                int num = atoi(&linhas[pos]);

                /*enfilera esse numero*/
                queue(vetorchaves[letra], num);

                /*enquando ainda por numero, vai passando a posicao no arquivo*/
                while(isdigit(linhas[pos]))
                    pos++;
            }

            /*se nao so pula de posicao ate encontrar um numero*/
            else
                pos++;
        }
    }

    /*cria um vetor para armazenar os numeros da mensagem codificada*/   
    int *vetorcod = malloc(sizeof(int));
    int num;
    int sizev = 2;
    i=0;

    /*le o numero da mensagem codificada*/
    fscanf(mensagemcod, "%d", &num);

    /*guarda no vetor*/
    vetorcod[i] = num;
    i++;

    /*vao dando realoc no vetor e salvando seus numeros*/
    while(!feof(mensagemcod))
    {
        vetorcod = realloc(vetorcod, sizev * sizeof(int));
        sizev++;
        fscanf(mensagemcod, "%d", &num);
        vetorcod[i] = num;
        i++;
    }

    /*faz a busca do valor no vetor de chaves*/
    int reg = i;
    int j;
    int achou;
    for(i=0;i<reg-1;i++)
    {
        /*se o numero codificado for -1, escre um espaco em branco*/
        if(vetorcod[i] == -1)
            fprintf(mensagemdecod, " ");
        else if(vetorcod[i] == -2)
            fprintf(mensagemdecod, "?");
        else if(vetorcod[i] == -3)
            fprintf(mensagemdecod, "!");
        else
        {
            j=0;
            achou=0;

            /*verifica todas as filas de chaves ate encontrar o numero desejado*/
            while((j<MAXCHAR) && (achou == 0))
            {
                struct NoFila *atual;
                atual = vetorchaves[j]->ini;

                /*percorre a fila*/
                while((atual != NULL) && (achou == 0))
                {
                    /*se encontrar o valor passa para o proximo numero a ser decodificado*/
                    /*se nao encontrar na fila, passa para a proxima*/
                    if(vetorcod[i] == atual->valor)
                    {
                        fprintf(mensagemdecod, "%c", j);
                        achou = 1;
                    }
                    atual = atual->prox;
                }
                j++;
            }
        }
    }
    free(vetorcod);

}