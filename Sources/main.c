/* Nome: Andrei Pochmann Koenich    Matricula: 00308680 */

/* O programa a seguir explora o dataset FIFA21 - Players, por meio de operacoes de indexacao e de consulta dos arquivos
de texto players.csv, rating.csv e tags.csv. Apos as indexacoes de todas as informacoes contidas nesses arquivos, o usuario
pode fazer consultas aos dados desses arquivos com comandos especificos, listados no menu de ajuda do programa. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../Headers/auxiliares.h"
#include "../Headers/constantes.h"
#include "../Headers/analiseArquivos.h"
#include "../Headers/estruturasPonteiros.h"
#include "../Headers/listas.h"
#include "../Headers/arvoreTrie.h"
#include "../Headers/execucaoComandos.h"
#include "../Headers/menu.h"

int analisaComando(char *comando) /* Analisa qual comando sera utilizado pelo programa, com base no que foi digitado pelo usuario. */
{
    int i = 0;
    char comandoLower[DIMENSAOGERAL];

    for(i = 0; comando[i] != '\0'; i++)
        comandoLower[i] = tolower(comando[i]);

    comandoLower[i] = '\0';

    if (strncmp(comandoLower,"player ",7) == 0)
        return 1; 

    else if (strncmp(comandoLower,"user ",5) == 0)
    {
        if (!isdigit(comando[5]))
            return 0; 

        else
            return 2; 
    }

    else if (strncmp(comandoLower,"top",3) == 0)
    {
        if (!isdigit(comando[3]))
            return 0;
        else
            return 3;
    }

    else if (strncmp(comandoLower,"tags ",5) == 0)
        return 4; 

    else if (strncmp(comandoLower,"down",4) == 0)
    {
        if (!isdigit(comando[4]))
            return 0;
        else
            return 5; 
    }

    else if (strncmp(comandoLower,"id ",3) == 0)
        return 6; 

    else if (strcmp(comandoLower,"help") == 0)
        return 7; 

    else if (strcmp(comandoLower,"info")==0)
        return 8;

    else if (strcmp(comandoLower,"exit") == 0)
        return 9; 

    else
        return 0;
}

void iniciaPrograma() /* Funcao para carregar as estruturas de pesquisa do programa e iniciar a sua execucao. */
{
    int numero_comando = 0;

    char tecla;
    char comando[DIMENSAOGERAL];
    
    PonteiroLetra *raizArvoreTrie = createNode();

    PonteiroPlayer **tabelaHashPlayers1 = calloc(TOTALJOGADORES,sizeof(PonteiroPlayer*)); /* Tabela hash para indexacao do arquivo players.csv usando o nome do jogador como referencia de indice. */
    PonteiroPlayer **tabelaHashPlayers2 = calloc(TOTALJOGADORES,sizeof(PonteiroPlayer*)); /* Tabela hash para indexacao do arquivo players.csv usando o ID do jogador como referencia de indice. */
    PonteiroPlayer **tabelaHashPlayers3 = calloc(TOTALPOSICOES,sizeof(PonteiroPlayer*));  /* Tabela hash para indexacao do arquivo players.csv usando a posicao do jogador como referencia de indice. */

    PonteiroUser **tabelaHashRating = calloc(TOTALUSERS,sizeof(PonteiroUser*)); /* Tabela hash para indexacao do arquivo rating.csv usando o ID do usuario como referencia de indice. */

    Jogadores *vetorMedias = calloc(TOTALSOFIFAID,sizeof(Jogadores)); /* Vetor auxiliar contendo as pontuacoes dos jogadores (avaliacoes parciais, total de avaliacoes e media de avaliacoes). */

    PonteiroTag **tabelaHashTags1 = calloc(TOTALTAGS,sizeof(PonteiroTag*)); /* Tabela hash para indexacao do arquivo tags.csv usando a tag do jogador como referencia de indice. */
    PonteiroTag **tabelaHashTags2 = calloc(TOTALJOGADORES,sizeof(PonteiroTag*)); /* Tabela hash para indexacao do arquivo tags.csv usando o ID do jogador como referencia de indice. */

    analisaArquivoPlayers(tabelaHashPlayers1,tabelaHashPlayers2,tabelaHashPlayers3, raizArvoreTrie); 
    analisaArquivoRating(tabelaHashRating, vetorMedias); 
    analisaArquivoTags(tabelaHashTags1,tabelaHashTags2); 

    system("clear");

    do 
    {
        menu();
        gotoxy(2,10);
        obtemComando(comando);

        numero_comando = analisaComando(comando); 

        system("clear");

        printf("Pressione ESC para encerrar a execucao do programa, ou qualquer outra tecla para continuar as consultas.\n");

        if (numero_comando != 7 && numero_comando != 8)
            printf("\nCOMANDO INSERIDO:\n%s\n",comando);

        switch(numero_comando)
        {
            case 0:
                printf("\nComando invalido.\n");
                break;

            case 1:
                analisaPlayer(comando,raizArvoreTrie,tabelaHashPlayers1,vetorMedias);
                break;

            case 2:
                comandoUserID(comando,tabelaHashPlayers2,tabelaHashRating,vetorMedias);
                break;

            case 3:
                controlaTop(comando,tabelaHashPlayers3,tabelaHashPlayers2,vetorMedias);
                break;

            case 4:
                controlaTags(comando,tabelaHashPlayers2,tabelaHashTags1,vetorMedias);
                break;

            case 5:
                controlaDown(comando,tabelaHashPlayers3,tabelaHashPlayers2,vetorMedias); 
                break;

            case 6:
                comandoID(comando,tabelaHashPlayers2,tabelaHashTags2,vetorMedias);
                break;

            case 7:
                menuHelp();
                break;

            case 8:
                menuPositions(); 
                break;

            case 9:
                system("clear");
                goto finalizaExecucao;
                break;
        }

        gotoxy(105,1);

        tecla = _getch(); 
        system("clear");

    } while (tecla != ESC);

    finalizaExecucao:

    system("clear");

    destroiTrie(raizArvoreTrie);

    destroiTabelaHashPlayers_1_2(tabelaHashPlayers1);
    destroiTabelaHashPlayers_1_2(tabelaHashPlayers2);
    destroiTabelaHashPlayers_3(tabelaHashPlayers3);

    destroiTabelaHashRating(tabelaHashRating);

    destroiTabelaHashTags_1(tabelaHashTags1);
    destroiTabelaHashTags_2(tabelaHashTags2);

    free(vetorMedias);
}

int main ()
{
    iniciaPrograma();
    return 0; 
}