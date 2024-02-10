#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "definicoes.h"
#include "estruturas_comandos.h"
#include "estruturas_ponteiros.h"
#include "arvore_trie.h"
#include "listas.h"
#include "auxiliares.h"

/* Funcao para armazenar os dados do arquivo players.csv em tres tabelas hash, cada uma com informacoes diferentes usadas no hashing. */
void analisa_arquivo_players(PonteiroPlayer **tabela_players1,PonteiroPlayer **tabela_players2,PonteiroPlayer **tabela_players3, PonteiroLetra **raiz)
{
    int i,j,indice;

    FILE *arq1;

    char linha[DIMENSAO_GERAL];
    char aux[DIMENSAO_GERAL];
    char posicoes[DIMENSAO_POSITION];

    Player jogador;

    for (i = 0; i < TOTALJOGADORES; i++) /* Inicializacao de uma lista simplesmente encadeada em cada posicao da tabela. */
        tabela_players1[i] = inicializa();

    for (i = 0; i < TOTALJOGADORES; i++) /* Inicializacao de uma lista simplesmente encadeada em cada posicao da tabela. */
        tabela_players2[i] = inicializa();

    for (i = 0; i < TOTALPOSITIONS; i++) /* Inicializacao de uma lista simplesmente encadeada em cada posicao da tabela. */
        tabela_players3[i] = inicializa();

    if (!(arq1 = fopen(ARQUIVOPLAYER,"r"))) /* Abertura do arquivo players.csv, com controle dos casos em que nao e possivel abri-lo. */
    {
        printf("\nErro na abertura do arquivo %s. Fim do programa.\n", ARQUIVOPLAYER);
        getch();
        exit(1); /* Encerra a execucao do programa, retornando 1. */
    }

    fgets(linha,DIMENSAO_GERAL,arq1); /* Pula a primeira linha do arquivo texto. */

    while (!feof(arq1)) /* Iteracao para percorrer o arquivo texto do inicio ao fim. */
    {
        i = 0;
        j = 0;

        memset(linha, 0, sizeof(linha));
        memset(aux, 0, sizeof(aux));

        fgets(linha,DIMENSAO_GERAL,arq1);

        while (linha[i] != ',') /* Obtem a informacao do id do jogador. */
        {
            aux[j] = linha[i];
            i++;
            j++;
        }

        strcpy(jogador.sofifa_id, aux);
        memset(aux, 0, sizeof(aux));
        i++;
        j = 0;

        while (linha[i] != ',') /* Obtem a informacao do nome do jogador. */
        {
            aux[j] = linha[i];
            i++;
            j++;
        }

        strcpy(jogador.playername, aux);
		*raiz = insereTrie(*raiz, jogador.playername);
        memset(aux, 0, sizeof(aux));
        i++;
        j = 0;

        while (linha[i] != '\n' && linha[i] != '\0') /* Obtem a informacao das posicoes do jogador. */
        {
            if (linha[i] != '"')
            {
                aux[j] = linha[i];
                j++;
            }

            i++;
        }

        strcpy(jogador.positions,aux);

        indice = hash(jogador.playername,TOTALJOGADORES);
        tabela_players1[indice] = insereInicioPlayer(tabela_players1[indice],jogador); /* Insere as informacoes do jogador na tabela hash, usando o seu nome como indice. */

        indice = hash(jogador.sofifa_id,TOTALJOGADORES);
        tabela_players2[indice] = insereInicioPlayer(tabela_players2[indice],jogador); /* Insere as informacoes do jogador na tabela hash, usando o seu ID como indice. */

        j = 0;

        for (int i = 0; jogador.positions[i] != '\0'; i++) /* Iteracao para obter cada posicao do jogador separadamente. */
        {
            if (jogador.positions[i] != ',' && jogador.positions[i] != ' ')
            {
                posicoes[j] = jogador.positions[i];
                j++;
            }

            else if (jogador.positions[i] == ',')
            {
                posicoes[j] = '\0';
                j = 0;
                indice = hash(posicoes,TOTALPOSITIONS);
                tabela_players3[indice] = insereInicioPlayer(tabela_players3[indice], jogador); /* Insere as informacoes do jogador na tabela hash, usando uma de suas posicoes como indice. */
            }
        }

        posicoes[j] = '\0';
        indice = hash(posicoes,TOTALPOSITIONS);
        tabela_players3[indice] = insereInicioPlayer(tabela_players3[indice], jogador); /* Insere as informacoes do jogador na tabela hash, usando uma de suas posicoes como indice. */
    }


    fclose(arq1); /* Fechamento do arquivo players.csv. */

}

/* Funcao para armazenar os dados do arquivo rating.csv em uma tabela hash e em um vetor auxiliar. */
void analisa_arquivo_rating(PonteiroUser **tabela_rating, Jogadores *vetor_medias)
{
    int indice;

    FILE *arq2;

    char linha[DIMENSAO_GERAL];
    char c;

    User usuario;

    for (int i = 0; i < TOTALUSERS; i++)
        tabela_rating[i] = inicializa(); /* Inicializacao de uma lista simplesmente encadeada em cada posicao da tabela. */

    for (int i = 0; i < TOTALSOFIFAID; i++) /* Inicializa o vetor contendo informacoes das pontuacoes dos jogadores. */
    {
        vetor_medias[i].count = 0;
        vetor_medias[i].soma = 0;
        vetor_medias[i].media = 0;
    }

    if (!(arq2 = fopen(ARQUIVORATING,"r"))) /* Abertura do arquivo rating.csv, com controle dos casos em que nao e possivel abri-lo. */
    {
        printf("\nErro na abertura do arquivo %s. Fim do programa.\n", ARQUIVORATING);
        getch();
        exit(1); /* Encerra a execucao do programa, retornando 1. */
    }

    fgets(linha,DIMENSAO_GERAL,arq2); /* Pula a primeira linha do arquivo texto. */

    while (!feof(arq2)) /* Iteracao para percorrer o arquivo texto do inicio ao fim. */
    {
        fscanf(arq2,"%d %c %d %c %f",&usuario.user_id,&c,&usuario.sofifa_id,&c,&usuario.rating); /* Obtem as informacoes da linha do arquivo. */
        indice = usuario.user_id;
        tabela_rating[indice] = insereInicioUser(tabela_rating[indice],usuario); /* Insere as informacoes do usuario e do jogador na tabela hash, usando o ID do usuario como indice. */

        indice = usuario.sofifa_id;
        vetor_medias[indice].count += 1;
        vetor_medias[indice].soma += usuario.rating; /* Insere as notas dos jogadores no vetor auxiliar. */
    }

    for (int i = 0; i < TOTALSOFIFAID; i++) /* Atualiza o vetor auxiliar, calculando todas as medias de pontuacoes dos jogadores. */
        if (vetor_medias[i].count != 0)
            vetor_medias[i].media = (vetor_medias[i].soma) / (vetor_medias[i].count);

    fclose(arq2); /* Fechamento do arquivo rating.csv. */
}

/* Funcao para armazenar os dados do arquivo tags.csv em uma tabela hash. */
void analisa_arquivo_tags(PonteiroTag **tabela_tags, PonteiroTag **tabela_tags2)
{
    int i,j,indice;

    FILE *arq3;

    char linha[DIMENSAO_GERAL];
    char aux[DIMENSAO_GERAL];

    Info dados;

    for (int i = 0; i < TOTALTAGS; i++)
        tabela_tags[i] = inicializa();

    for (int i = 0; i < TOTALJOGADORES; i++)
        tabela_tags2[i] = inicializa();

    if (!(arq3 = fopen(ARQUIVOTAGS,"r"))) /* Abertura do arquivo tags.csv, com controle dos casos em que nao e possivel abri-lo. */
    {
        printf("\nErro na abertura do arquivo %s. Fim do programa.\n", ARQUIVOTAGS);
        getch();
        exit(1); /* Encerra a execucao do programa, retornando 1. */
    }

    fgets(linha,DIMENSAO_GERAL,arq3); /* Pula a primeira linha do arquivo texto. */

    while (!feof(arq3)) /* Iteracao para percorrer o arquivo texto do inicio ao fim. */
    {
        i = 0;
        j = 0;

        memset(linha, 0, sizeof(linha));
        memset(aux, 0, sizeof(aux));

        fgets(linha,DIMENSAO_GERAL,arq3);

        while (linha[i] != ',') /* Obtem a informacao do ID do usuario. */
        {
            aux[j] = linha[i];
            i++;
            j++;
        }

        strcpy(dados.user_id,aux);
        memset(aux, 0, sizeof(aux));
        i++;
        j = 0;

        while (linha[i] != ',') /* Obtem a informacao do ID do jogador. */
        {
            aux[j] = linha[i];
            i++;
            j++;
        }

        strcpy(dados.sofifa_id, aux);
        memset(aux, 0, sizeof(aux));
        i++;
        j = 0;

        while (linha[i] != '\0' && linha[i] != '\n') /* Obtem a informacao da tag atribuida pelo usuario ao jogador. */
        {
            aux[j] = linha[i];
            i++;
            j++;
        }

        strcpy(dados.tag,aux);

        indice = hash(dados.tag,TOTALTAGS);
        tabela_tags[indice] = insereInicioTag(tabela_tags[indice],dados); /* Insere os dados obtidos na tabela hash. */
        indice = hash(dados.sofifa_id,TOTALJOGADORES);
        tabela_tags2[indice] = insereInicioTag(tabela_tags2[indice],dados); /* Insere os dados obtidos na tabela hash. */
    }

    fclose(arq3); /* Fechamento do arquivo tags.csv. */
}