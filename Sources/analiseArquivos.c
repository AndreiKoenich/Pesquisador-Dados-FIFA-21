#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "../Headers/constantes.h"
#include "../Headers/estruturasComandos.h"
#include "../Headers/estruturasPonteiros.h"
#include "../Headers/arvoreTrie.h"
#include "../Headers/listas.h"
#include "../Headers/auxiliares.h"
#include "../Headers/analiseArquivos.h"

/* Funcao para armazenar os dados do arquivo players.csv em tres tabelas hash, cada uma com informacoes diferentes usadas no hashing. */
void analisaArquivoPlayers(PonteiroPlayer **tabelaHashPlayers1,PonteiroPlayer **tabelaHashPlayers2,PonteiroPlayer **tabelaHashPlayers3, PonteiroLetra *raizArvoreTrie)
{
    int i,j,indice;

    FILE *arquivoPlayers;

    char linha[DIMENSAOGERAL];
    char aux[DIMENSAOGERAL];
    char posicoes[DIMENSAO_POSITION];

    Player jogador;

    for (i = 0; i < TOTALJOGADORES; i++) 
        tabelaHashPlayers1[i] = inicializaEstrutura();

    for (i = 0; i < TOTALJOGADORES; i++) 
        tabelaHashPlayers2[i] = inicializaEstrutura();

    for (i = 0; i < TOTALPOSICOES; i++) 
        tabelaHashPlayers3[i] = inicializaEstrutura();

    if (!(arquivoPlayers = fopen(ARQUIVOPLAYER,"r"))) 
    {
        printf("\nErro na abertura do arquivo %s. Fim do programa.\n", ARQUIVOPLAYER);
        exit(1); 
    }

    fgets(linha,DIMENSAOGERAL,arquivoPlayers); 

    while (!feof(arquivoPlayers)) 
    {
        i = 0;
        j = 0;

        memset(linha, 0, sizeof(linha));
        memset(aux, 0, sizeof(aux));

        fgets(linha,DIMENSAOGERAL,arquivoPlayers);

        while (linha[i] != ',')
        {
            aux[j] = linha[i];
            i++;
            j++;
        }

        strcpy(jogador.sofifa_id, aux);
        memset(aux, 0, sizeof(aux));
        i++;
        j = 0;

        while (linha[i] != ',') 
        {
            aux[j] = linha[i];
            i++;
            j++;
        }

        strcpy(jogador.playername, aux);
		insereTrie(raizArvoreTrie, jogador.playername);
        memset(aux, 0, sizeof(aux));
        i++;
        j = 0;

        while (linha[i] != '\n' && linha[i] != '\0') 
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
        tabelaHashPlayers1[indice] = insereInicioPlayer(tabelaHashPlayers1[indice],jogador);

        indice = hash(jogador.sofifa_id,TOTALJOGADORES);
        tabelaHashPlayers2[indice] = insereInicioPlayer(tabelaHashPlayers2[indice],jogador);

        j = 0;

        for (int i = 0; jogador.positions[i] != '\0'; i++) 
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
                indice = hash(posicoes,TOTALPOSICOES);
                tabelaHashPlayers3[indice] = insereInicioPlayer(tabelaHashPlayers3[indice], jogador); 
            }
        }

        posicoes[j] = '\0';
        indice = hash(posicoes,TOTALPOSICOES);
        tabelaHashPlayers3[indice] = insereInicioPlayer(tabelaHashPlayers3[indice], jogador);
    }

    fclose(arquivoPlayers);
}

/* Funcao para armazenar os dados do arquivo rating.csv em uma tabela hash e em um vetor auxiliar. */
void analisaArquivoRating(PonteiroUser **tabelaHashRating, Jogadores *vetorMedias)
{
    int indice;

    FILE *arquivoRating;

    char linha[DIMENSAOGERAL];
    char c;

    User usuario;

    for (int i = 0; i < TOTALUSERS; i++)
        tabelaHashRating[i] = inicializaEstrutura();

    for (int i = 0; i < TOTALSOFIFAID; i++)
    {
        vetorMedias[i].count = 0;
        vetorMedias[i].soma = 0;
        vetorMedias[i].media = 0;
    }

    if (!(arquivoRating = fopen(ARQUIVORATING,"r"))) 
    {
        printf("\nErro na abertura do arquivo %s. Fim do programa.\n", ARQUIVORATING);
        exit(1); 
    }

    fgets(linha,DIMENSAOGERAL,arquivoRating);

    while (!feof(arquivoRating)) 
    {
        fscanf(arquivoRating,"%d %c %d %c %f",&usuario.user_id,&c,&usuario.sofifa_id,&c,&usuario.rating); 
        indice = usuario.user_id;
        tabelaHashRating[indice] = insereInicioUser(tabelaHashRating[indice],usuario);

        indice = usuario.sofifa_id;
        vetorMedias[indice].count += 1;
        vetorMedias[indice].soma += usuario.rating; 
    }

    for (int i = 0; i < TOTALSOFIFAID; i++) 
        if (vetorMedias[i].count != 0)
            vetorMedias[i].media = (vetorMedias[i].soma) / (vetorMedias[i].count);

    fclose(arquivoRating); 
}

/* Funcao para armazenar os dados do arquivo tags.csv em uma tabela hash. */
void analisaArquivoTags(PonteiroTag **tabelaHashTags1, PonteiroTag **tabelaHashTags2)
{
    int i,j,indice;

    FILE *arquivoTags;

    char linha[DIMENSAOGERAL];
    char aux[DIMENSAOGERAL];

    Info dados;

    for (int i = 0; i < TOTALTAGS; i++)
        tabelaHashTags1[i] = inicializaEstrutura();

    for (int i = 0; i < TOTALJOGADORES; i++)
        tabelaHashTags2[i] = inicializaEstrutura();

    if (!(arquivoTags = fopen(ARQUIVOTAGS,"r"))) 
    {
        printf("\nErro na abertura do arquivo %s. Fim do programa.\n", ARQUIVOTAGS);
        exit(1); 
    }

    fgets(linha,DIMENSAOGERAL,arquivoTags); 

    while (!feof(arquivoTags))
    {
        i = 0;
        j = 0;

        memset(linha, 0, sizeof(linha));
        memset(aux, 0, sizeof(aux));

        fgets(linha,DIMENSAOGERAL,arquivoTags);

        while (linha[i] != ',')
        {            
            
            aux[j] = linha[i];
            i++;
            j++;
        }

        strcpy(dados.user_id,aux);
        memset(aux, 0, sizeof(aux));
        i++;
        j = 0;

        while (linha[i] != ',') 
        {
            aux[j] = linha[i];
            i++;
            j++;
        }

        strcpy(dados.sofifa_id, aux);
        memset(aux, 0, sizeof(aux));
        i++;
        j = 0;

        while (linha[i] != '\0' && linha[i] != '\n')
        {
            aux[j] = linha[i];
            i++;
            j++;
        }

        strcpy(dados.tag,aux);

        indice = hash(dados.tag,TOTALTAGS);
        tabelaHashTags1[indice] = insereInicioTag(tabelaHashTags1[indice],dados);
        indice = hash(dados.sofifa_id,TOTALJOGADORES);
        tabelaHashTags2[indice] = insereInicioTag(tabelaHashTags2[indice],dados);
    }

    fclose(arquivoTags);
}
