#ifndef LuanBib_h
#define LuanBib_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *NER_TokenDados(FILE*,int *);
void AchaeTroca(FILE *AR,FILE *ofp,FILE *token_word,char *tokenid,int tam);

#endif

char *NER_TokenDados(FILE *token,int *tam){

    int tamanho;
    char *tokenid;

    tokenid = (char*)malloc(10*sizeof(char));

    fscanf(token,"%d %s\n",&tamanho,tokenid);

    //printf("%d\n%s\n",tamanho,tokenid);

    *tam = tamanho;

    return tokenid;
}

// ctype tolower

// verifica se a palavra tem , . \n : e tira.
char TemCaracterEspecial(char palavra[100])
{
    char caracteres[4] = {'\n',',','.','\r'};
    int aux = 0;
    while(palavra[aux] != 0){
        for(int i = 0;i<4; i++){
            if(palavra[aux] == caracteres[i]){
                return caracteres[i];
            }
        }
        aux++;
    }
    return ' ';
}

// normaliza palavra : traz tudo pra minúsculo
//void Normaliza_Palavra()



void AchaeTroca(FILE *AR,FILE *ofp,FILE *token_word,char *tokenid,int tam){

    char palavra_lida[100];
    char palavra_token[tam];
    char final_palavra;

    // voltar o ponteiro de cada arquivo para o ínicio
    rewind(AR);
    rewind(ofp);
    rewind(token_word);


    // loop para percorrer o AR e comparar com as palavras do arquivo token
    while(!feof(AR)){

        // usar o fscanf para ler uma string no AR e salvar na variavel palavra_referencia
        fscanf(AR,"%s",palavra_lida);

        final_palavra = TemCaracterEspecial(palavra_lida);

        if(final_palavra != ' '){
            palavra_lida[strlen(palavra_lida) - 1] = palavra_lida[strlen(palavra_lida)];
        }
        // usar um loop para percorrer o o arquivo token para achar as palavras.
        rewind(token_word);
        while(!feof(token_word)){
            // ler a palavra do token e comparar com a palavra_lida

            fscanf(token_word,"%s",palavra_token);

            // usando a string.h, faz a comparação de 2 strings
            if(strcmp(palavra_lida,palavra_token) == 0){
                strcpy(palavra_lida,tokenid);
            }
        }

        // se for igual, já fez a copia, se não for, a palavra é passada para o output do mesmo jeito
        fprintf(ofp,"%s",palavra_lida);
        fputc(final_palavra,ofp);
    }

}