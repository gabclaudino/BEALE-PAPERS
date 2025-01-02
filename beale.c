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

void main(int argc, char **argv){

    /*ponteiros para os arquivos*/
    FILE *livrocifra;
    FILE *chaves;
    FILE *mensagemcod;
    FILE *mensagemdecod;

    /*ponteiros para serem lidos pelos argumentos
    da funcao main*/
    char *LIVROCIFRA = NULL;
    char *CHAVES = NULL;
    char *MENSAGEMCOD = NULL;
    char *MENSAGEMORI = NULL;
    char *RESULT = NULL;

    /*flags para realizar as comparacoes mais para frente*/
    int option;
    int flag_e = 0;
    int flag_d = 0;
    int flag_c = 0;
    int flag_b = 0;

    /*ler o paramentro de entrada ao executar o programa*/
    while ((option = getopt (argc, argv, "edb:m:o:c:i:")) != -1)
    {
        switch (option)
        {
            case 'e':      
                flag_e = 1;
                break;
            case 'd':      
                flag_d = 1;
                break;
            case 'b':
                flag_b = 1;      
                LIVROCIFRA = optarg;
                break;
            case 'm':
                MENSAGEMORI = optarg;
                break;
            case 'o':
                RESULT = optarg;                
                break;
            case 'c':
                flag_c = 1;
                CHAVES = optarg;            
                break;
            case 'i':
                MENSAGEMCOD = optarg;
                break;
            default:
                printf("Argumento invalido! \n");
                exit(1);
        }
    }


    /*verifica se a opcao -e foi inserida*/
    if(flag_e == 1)
    {
        /*abre os aquivos necessarios em seus formatos necessarios*/
        livrocifra = fopen(LIVROCIFRA, "r");
        mensagemdecod = fopen(MENSAGEMORI, "r");
        mensagemcod = fopen(RESULT, "w");
        chaves = fopen(CHAVES, "w");

        /*chama a funcao para criar o Arquivo de Chaves*/
        cria_chaves(livrocifra, chaves);
        /*retorna o Ponteiro para o inicio dos arquivos*/
        rewind(livrocifra);
        rewind(chaves);

        /*chama afuncao para codificar uma mensagem usando o livro cifra*/
        Codifica_usando_lc(livrocifra, mensagemcod, mensagemdecod);
        /*retorna o ponteiro para o inicio do arquivo*/
        rewind(livrocifra);
        rewind(mensagemcod);
        rewind(mensagemdecod);

        /*fecha os arquivos*/
        fclose(livrocifra);
        fclose(chaves);
        fclose(mensagemdecod);
        fclose(mensagemcod);

        return;

    }
    /*verifica se a opcao -d foi colocada*/
    else if(flag_d == 1);
    {
        /*verifica se a opcao -c foi colocada(usar Arquivo de Chaves)*/
        if(flag_c == 1)
        {
            /*abre os aquivos necessarios*/
            mensagemcod = fopen(MENSAGEMCOD, "r");
            chaves = fopen(CHAVES, "r");
            mensagemdecod = fopen(RESULT, "w");

            /*chama a funcao de decodificar uma mensagem usando o Arquivo de Chaves*/
            Decodifica_usando_ac(chaves, mensagemcod, mensagemdecod);

            /*retorna o ponteiro para o inicio dos arquivos*/
            rewind(chaves);
            rewind(mensagemdecod);
            rewind(mensagemcod);

            /*fecha os arquivos*/
            fclose(chaves);
            fclose(mensagemcod);
            fclose(mensagemdecod);

            return;
        }
        /*veririca se a opcao -b foi usada (usar livro cifra)*/
        else if(flag_b == 1)
        {
            /*abre os arquivos necessarios*/
            mensagemcod = fopen(MENSAGEMCOD, "r");
            livrocifra = fopen(LIVROCIFRA, "r");
            mensagemdecod = fopen(RESULT, "w");

            /*chama a funcao para decodificar usando o livro cifra*/
            Decodifica_usando_lc(livrocifra, mensagemcod, mensagemdecod);

            /*retorna o ponteiro para o inicio do arquivo*/
            rewind(livrocifra);
            rewind(mensagemcod);
            rewind(mensagemdecod);

            /*fecha o arquivo*/
            fclose(livrocifra);
            fclose(mensagemcod);
            fclose(mensagemdecod);

            return;
        }
    }
}