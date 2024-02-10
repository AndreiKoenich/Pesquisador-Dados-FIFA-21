/* Nome: Andrei Pochmann Koenich    Matricula: 00308680
   Nome: Pedro Company Beck         Matricula: 00324055 */

/* O programa a seguir explora o dataset FIFA21 - Players, por meio de operacoes de indexacao e de consulta dos arquivos
de texto players.csv, rating.csv e tags.csv. Apos as indexacoes de todas as informacoes contidas nesses arquivos, o usuario
pode fazer consultas aos dados desses arquivos com comandos especificos, listados no menu de ajuda do programa. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

#include "definicoes.h"
#include "auxiliares.h"
#include "estruturas_ponteiros.h"
#include "estruturas_comandos.h"
#include "arvore_trie.h"
#include "execucao_comandos.h"
#include "analise_arquivos.h"
#include "menu.h"

int analisa_comando(char *comando) /* Analisa qual comando sera utilizado pelo programa, com base no que foi digitado pelo usuario. */
{
    int i = 0;
    char comando_lower[DIMENSAO_GERAL];

    for(i = 0; comando[i] != '\0'; i++)
        comando_lower[i] = tolower(comando[i]);

    comando_lower[i] = '\0';

    if (strncmp(comando_lower,"player ",7) == 0)
        return 1; /* Retorna o numero correspondente ao comando player. */

    else if (strncmp(comando_lower,"user ",5) == 0)
    {
        if (!isdigit(comando[5]))
            return 0; /* Retorna o numero que representa um comando invalido. */

        else
            return 2; /* Retorna o numero correspondente ao comando user. */
    }

    else if (strncmp(comando_lower,"top",3) == 0)
    {
        if (!isdigit(comando[3]))
            return 0; /* Retorna o numero que representa um comando invalido. */

        else
            return 3; /* Retorna o numero correspondente ao comando top. */
    }

    else if (strncmp(comando_lower,"tags ",5) == 0)
        return 4; /* Retorna o numero correspondente ao comando tags. */

    else if (strncmp(comando_lower,"down",4) == 0)
    {
        if (!isdigit(comando[4]))
            return 0; /* Retorna o numero que representa um comando invalido. */

        else
            return 5; /* Retorna o numero correspondente ao comando down. */
    }

    else if (strncmp(comando_lower,"id ",3) == 0)
        return 6; /* Retorna o numero correspondente ao comando id. */

    else if (strcmp(comando_lower,"help") == 0)
        return 7; /* Retorna o numero correspondente ao comando help. */

    else if (strcmp(comando_lower,"info")==0)
        return 8; /* Retorna o numero correspondente ao comando positions. */

    else if (strcmp(comando_lower,"exit") == 0)
        return 9; /* Retorna o numero correspondente ao comando exit. */

    else
        return 0; /* Retorna o numero que representa um comando invalido. */
}

void inicia_programa() /* Funcao para carregar as estruturas de pesquisa do programa e iniciar a sua execucao. */
{
    int numero_comando = 0;

    char tecla;
    char comando[DIMENSAO_GERAL];

    printf("Carregando...");

    PonteiroLetra *raiz = inicializa(); /* Inicializa a raiz da arvore trie, para receber os nomes dos jogadores. */

    PonteiroPlayer **tabela_players1 = calloc(TOTALJOGADORES,sizeof(PonteiroPlayer*));  /* Tabela hash para indexacao do arquivo players.csv usando o nome do jogador como referencia de indice. */
    PonteiroPlayer **tabela_players2 = calloc(TOTALJOGADORES,sizeof(PonteiroPlayer*));  /* Tabela hash para indexacao do arquivo players.csv usando o ID do jogador como referencia de indice. */
    PonteiroPlayer **tabela_players3 = calloc(TOTALPOSITIONS,sizeof(PonteiroPlayer*));  /* Tabela hash para indexacao do arquivo players.csv usando a posicao do jogador como referencia de indice. */

    PonteiroUser **tabela_rating = calloc(TOTALUSERS,sizeof(PonteiroUser*)); /* Tabela hash para indexacao do arquivo rating.csv usando o ID do usuario como referencia de indice. */

    Jogadores *vetor_medias = calloc(TOTALSOFIFAID,sizeof(Jogadores)); /* Vetor auxiliar contendo as pontuacoes dos jogadores (avaliacoes parciais, total de avaliacoes e media de avaliacoes). */

    PonteiroTag **tabela_tags = calloc(TOTALTAGS,sizeof(PonteiroTag*)); /* Tabela hash para indexacao do arquivo tags.csv usando a tag do jogador como referencia de indice. */
    PonteiroTag **tabela_tags2 = calloc(TOTALJOGADORES,sizeof(PonteiroTag*)); /* Tabela hash para indexacao do arquivo tags.csv usando o ID do jogador como referencia de indice. */

    analisa_arquivo_players(tabela_players1,tabela_players2,tabela_players3, &raiz); /* Indexacao do arquivo players.csv nas tabelas hash. */
    analisa_arquivo_rating(tabela_rating, vetor_medias); /* Indexacao do arquivo players.csv na tabela hash e no vetor de pontuacoes dos jogadores. */
    analisa_arquivo_tags(tabela_tags,tabela_tags2); /* Indexacao do arquivo tags.csv nas tabelas hash. */

    system("cls");

    do /* Executa o programa enquanto o usuario nao digitar 'exit' ou pressionar a tecla ESC. */
    {
        menu(); /* Impressao do menu principal da tela. */

        gotoxy(2,11); /* Atualiza a posicao do cursor para facilitar a visualizacao da tela. */

        gets(comando);

        numero_comando = analisa_comando(comando); /* Determina o numero do comando a ser utilizado pelo programa. */

        system("cls");

        printf("Pressione ESC para encerrar a execucao do programa, ou qualquer outra tecla para continuar as consultas.\n");

        if (numero_comando != 7 && numero_comando != 8)
            printf("\nCOMANDO INSERIDO:\n%s\n",comando);

        switch(numero_comando) /* Faz a chamada da funcao correspondente ao comando, dependendo do que foi digitado pelo usuario. */
        {
            case 0:
                printf("\nComando invalido.\n"); /* Informa ao usuario que o comando digitado e invalido. */
                break;

            case 1:
                analisa_player(comando,raiz,tabela_players1,vetor_medias); /* Executa o comando player. */
                break;

            case 2:
                comando_userID(comando,tabela_players2,tabela_rating,vetor_medias); /* Executa o comando user. */
                break;

            case 3:
                controla_top(comando,tabela_players3,tabela_players2,vetor_medias); /* Executa o comando top. */
                break;

            case 4:
                controla_tags(comando,tabela_players2,tabela_tags,vetor_medias); /* Executa o comando tags */
                break;

            case 5:
                controla_down(comando,tabela_players3,tabela_players2,vetor_medias); /* Executa o comando down. */
                break;

            case 6:
                comando_id(comando,tabela_players2,tabela_tags2,vetor_medias); /* Executa o comando id. */
                break;

            case 7:
                menu_help(); /* Mostra o menu de ajuda ao usuario. */
                break;

            case 8:
                menu_positions(); /* Mostra a lista de posicoes de jogo ao usuario. */
                break;

            case 9:
                system("cls");
                exit(0); /* Encerra a execucao do programa, retornando zero. */
                break;
        }

        gotoxy(105,1); /* Atualiza a posicao do cursor para facilitar a visualizacao da tela. */

        tecla = getch(); /* Armazena a tecla digitada pelo usuario, para decidir entre continuar ou terminar o programa. */
        system("cls");

    } while (tecla != ESC);
}

int main ()
{
    inicia_programa(); /* Inicia as operacoes de indexacao e de consulta do programa. */
    return 0; /* Retorna zero, indicando que a execucao do programa foi bem-sucedida. */
}
