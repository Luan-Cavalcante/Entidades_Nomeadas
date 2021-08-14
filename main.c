//
//  main.c
//  Arquivos
//
//  Created by Nilton Correia da Silva on 27/02/21.
//

#include <stdio.h>
#include "BibArquivos.h"
#include "filem.h"
//#include ???? //AQUI VAI O NOME DA BIBLIOTECA QUE VC VAI CRIAR.
#include <stdlib.h> //Necessário para free()
#include <string.h>

int main(int argc, const char * argv[]) {
    char NomeArq[30] = "";

    FILE *AR = NULL;      //Arquivo de texto de referência
    FILE *Token= NULL;    //Arquivo com informações dos tokens
    FILE *Saida= NULL;    //Arquivo contendo resultado
    char popc = '0';

//Informações contidas no arquivo de Token:
    char *TokenID = NULL;
    int TamanhoTermos;

    while(popc != 'S'){
        printf("\n################## ENTIDADES NOMEADAS ##################");
        printf("\n");
        printf("\nR - Abrir Arquivo de Referência");
        printf("\nT - Abrir Arquivo de Especificação de Token");
        printf("\nA - Aplicar Tokenização");
        printf("\nr - Exibir Arquivo de Referência");
        printf("\nt - Exibir Arquivo de Especificação de Token");
        printf("\nS - Sair");
        printf("\nOpção: ");
        scanf("\n%c", &popc);
        switch (popc) {
            case 'R':
                printf("Arquivo de Referência: ");
                scanf("%s",NomeArq);
                if(AR != NULL)
                    fclose(AR);
                AR = Arquivo_AbreLeitura(NomeArq);
                if(AR == NULL){
                    printf("Erro 1: Arquivo de Referência não pode ser aberto\n");
                }
                else
                    printf("%s aberto!!!\n", NomeArq);
                //system("cls");
                break;
            case 'T':
                printf("Arquivo de Especificação de Token: ");
                scanf("%s",NomeArq);
                if(Token != NULL)
                    fclose(Token);
                Token = Arquivo_AbreLeitura(NomeArq);
                if(Token == NULL){
                    printf("Erro 2: Arquivo de Especificação de Token não pode ser aberto\n");
                    TamanhoTermos = 0;
                    if(TokenID != NULL)
                       free(TokenID);
                }
                else{
                    //TokenID = NER_TokenDados(Token, &TamanhoTermos);
                    TokenID = NER_TokenDados(Token, &TamanhoTermos);
                    printf("tamanho : %d\nID : %s",TamanhoTermos,TokenID);
                    //printf("%d %s %lu\n", TamanhoTermos, TokenID, sizeof(TokenID));
                    //printf("Tá esquisito isso\n");
                }
                //system("cls");
                break;
            case 'r':
                if(!Arquivo_MostraConteudo(AR)){
                    printf("Arquivo de Referência não está carregado\n");
                }
                break;
            case 't':
                if(!Arquivo_MostraConteudo(Token)){
                    printf("Arquivo de Especificação de Token não está carregado\n");
                }
                //system("cls");
                break;

                // ----------------------------------------------------------------------------------

            case 'A':
                if((AR == NULL) || (Token == NULL)){
                    printf("Carregue os arquivo de Texto de Referência e de Especificação de Token!!!\n");
                    break;
                }

                printf("Arquivo de Saída: ");
                scanf("%s",NomeArq);
                if(Saida != NULL)
                    fclose(Saida);

                /*
                Saida = Arquivo_AbreLeitura(NomeArq);
                if(Saida == NULL){
                    printf("Erro 2: Arquivo de Saida para ser tokenizado não pode ser aberto\n");
                }

                if(!Arquivo_Novo(NomeArq)){
                    printf("Erro 3: Arquivo de Saída não pode ser criado\n");
                }
                else
                    printf("\n%s gerado!!!\n", NomeArq);
                */
                Saida = fopen(NomeArq,"w");

                AchaeTroca(AR,Saida,Token,TokenID,TamanhoTermos);


                //Faça a chamada às funções que vc criou para aplicar a Tokenização aqui.
                //Ao final: Feche o arquivo de saída. Abra-o em modo de leitura e mostre seu
                //conteúdo.
                //Ao final, o Ponteiro Saida deve conter seu arquivo de saída.

                // ARQUIVO DE ENTRADA - AR
                // ARQUIVO DE SAÍDA - Saida

                //fscanf(AR,"%s",);

                //system("cls");
                break;

            case 'S':
                //system("cls");
                break;
        }
        if(popc == 'S')
            break;
    }

    free(TokenID);
    fclose(AR);
    fclose(Token);
    fclose(Saida);
    printf("\n\n ----- Sistema Encerrado ----- \n\n");

    return 0;
}
