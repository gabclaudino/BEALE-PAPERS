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

int verifica(char letra){
    letra = tolower(letra);
    if((letra == 'a') || (letra == 'b') || (letra == 'c') || (letra == 'd') || (letra == 'e') || (letra == 'f') || (letra == 'g') || (letra == 'h') || (letra == 'i') || (letra == 'j') || (letra == 'k') || (letra == 'l') || (letra == 'm') || (letra == 'n') || (letra == 'o') || (letra == 'p') || (letra == 'q') || (letra == 'r') || (letra == 's') || (letra == 't') || (letra == 'u') || (letra == 'v') || (letra == 'w') || (letra == 'x') || (letra == 'y') || (letra == 'z') || (letra == '1') || (letra == '2') || (letra == '3') || (letra == '4') || (letra == '5') || (letra == '6') || (letra == '7') || (letra == '8') || (letra == '9') || (letra == '0'))
        return 1;
    else
        return 0;
}


void Codifica_usando_lc(FILE *livrocifra, FILE *mensagemcod, FILE *mensagemdecod){

    /*cria um vetor de listas(fila) do livro cifra*/
      
    char letra;
    char aux;
    /*ve qual o tamanho do livro cifra*/
    int tamarq;
    fseek(livrocifra, 0, SEEK_END);
    tamarq = ftell(livrocifra);
    fseek(livrocifra, 0, SEEK_SET);
    tamarq = tamarq/sizeof(char);

    /*aloca um vetor para guarda o livro cifra*/
    char *textobase = malloc(tamarq * (sizeof(char)));
    fread(textobase,sizeof(char),tamarq,livrocifra);

    /*cria um vetor de filas para armazenar as chaves das palavras*/
    struct fila *vetorfila[MAXCHAR];
    int i;
    for(i=0; i<MAXCHAR; i++)
        vetorfila[i] = iniciaFila();

    /*verifica se o primeiro caractere eh uma letra ou numero*/
    /*se sim enfilera no indice da letra/numero na tabela ASCII*/
    int indice=0;
    letra = textobase[0];

    /*transforma a letra em minuscula*/
    letra = tolower(letra);
    if((isalpha(letra) != 0) || (isdigit(letra) != 0))
    {
        queue(vetorfila[letra], indice);
        indice++;
    }

    /*verifica se eh a primeira letra/numero de uma palavra*/
    /*se sim enfilera*/
    for(i=1;i<tamarq;i++)
    {
        /*le o caractere do salvo no vetor textobase*/
        letra = textobase[i];

        /*trasforma a letra em minuscula*/
        letra = tolower(letra);

        /*faz a veriricacao se eh numero ou letra*/
        if((isalpha(letra) != 0) || (isdigit(letra) != 0))

            /*ve se eh a primeira letra/numero da palavra*/
            if((textobase[i-1] == ' ') || (textobase[i-1] == '"') || (textobase[i-1] == '\n'))
            {
                queue(vetorfila[letra], indice);
                indice++;
            }
    }
    
    /*verifica o tamanho do arquivo com a mensagem original*/
    int tamcod;
    fseek(mensagemdecod, 0, SEEK_END);
    tamcod = ftell(mensagemdecod);
    rewind(mensagemdecod);

    /*aloca um vetor para guardar a mensagem original*/
    char *vetordecod = malloc(sizeof(char) * tamcod);
    fread(vetordecod, sizeof(char), tamcod, mensagemdecod);


    /*verifica cada caractere decodificado*/
    for(i=0; i<tamcod; i++)
    {
        /*se eh um espaco, codifica como -1*/
        if(vetordecod[i] == ' ')
            fprintf(mensagemcod, "-1 ");
        else
        {
            /*verifica se a fila de chaves da letra eh vazia*/
            /*se estivar vazia, na ha chaves referentes aquela letra*/
            /*codifica como (sem chave)*/
            if(verifica(vetordecod[i]) == 1)
            {
                vetordecod[i] = tolower(vetordecod[i]);
                if(filaVazia(vetorfila[vetordecod[i]]) == 1)
                    fprintf(mensagemcod, "-2 ");

                /*se ha valor na fila, entao codifica o primeiro que aparecer*/
                else
                    fprintf(mensagemcod, "%d ", vetorfila[vetordecod[i]]->ini->valor);
            }
            else
                fprintf(mensagemcod, "-3 ");
        }
    }

    /*da free nos vetores alocados*/
    free(textobase);
    free(vetordecod);

}