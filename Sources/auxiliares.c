#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <termios.h>
#include "../Headers/estruturasComandos.h"
#include "../Headers/estruturasPonteiros.h"
#include "../Headers/constantes.h"
#include "../Headers/listas.h"
#include "../Headers/auxiliares.h"

void obtemComando(char* comando) { /* Funcao para obter a string do comando digitada pelo usuario. */
    fgets(comando, DIMENSAOGERAL, stdin);

    size_t len = strlen(comando);
    if (len > 0 && comando[len - 1] == '\n') {
        comando[len - 1] = '\0';
    }
}

char _getch() /* Aguarda o pressionamento de tecla pelo usuario. */
{
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if(tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if(tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if(read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if(tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return buf;
 }

void* inicializaEstrutura() /* Funcao para inicializar uma lista encadeada. */
{
    return NULL;
}

void gotoxy(int x, int y) /* Funcao para alterar a posicao do cursor do usuario no terminal, durante a execucao do programa. */
{
    printf("%c[%d;%df", 0x1B, y, x);
    fflush(stdout);
}

int hash(char *nome, int M) /* Funcao de hashing CRC32 modificada. */
{
	unsigned int crc32 = 0xFFFFFFFFu;

	static int Table[256] = {0};
	static int ini = 0;

	if (!ini) 
    {
		srand(0xdeadbeef); 

		for (int j = 0; j < 256; j++)
        {
			Table[j] = rand();
		}
		ini = 1;
	}

	for (int i = 0; i < strlen(nome); i++) {
		unsigned int lookup = (crc32 ^ nome[i]) & 0xff;
		crc32 = (crc32 >> 8) ^ Table[lookup];
	}

	crc32 ^= 0xFFFFFFFFu;

	return crc32 % M; 
}

void bubblesortStruct(Comando2 v[], int dimensao) /* Realiza a ordenacao de jogadores com base no seu rating em ordem decrescente. */
{
    int i, j;

    Comando2 aux;

    for (i = 0; i < dimensao; i++)
        for (j = 0; j < dimensao-i-1; j++)
        {
            if (v[j].rating < v[j+1].rating)
            {
                aux = v[j];
                v[j] = v[j+1];
                v[j+1] = aux;
            }
        }
}

void swapStruct (Comandos_1_3_4 v[], int i, int j) /* Funcao auxiliar da ordenacao decrescente com base no rating global dos jogadores, com quick sort. */
{
    Comandos_1_3_4 aux = v[i];
    v[i] = v[j];
    v[j] = aux;
}

int pHoareStructDec(Comandos_1_3_4 v[], int p, int r) /* Funcao auxiliar da ordenacao decrescente com base no rating global dos jogadores, com quick sort. */
{
    Comandos_1_3_4 pivot = v[p]; /* Seleciona o primeiro elemento do vetor como pivo da ordenacao. */
    int i = p - 1, j = r + 1;

    while (1)
    {
        do
        {
            i++;

        } while (v[i].global_rating > pivot.global_rating);

        do
        {
            j--;

        } while (v[j].global_rating < pivot.global_rating);

        if (i >= j)
            return j;

        swapStruct(v, i, j);
    }
}

void quickSortStructDec(Comandos_1_3_4 v[], int p, int r)  /* Realiza a ordenacao de jogadores com base no seu rating em ordem decrescente. */
{
    if (p < r)
    {
        int posicao = pHoareStructDec(v, p, r);
        quickSortStructDec(v, p, posicao);
        quickSortStructDec(v, posicao+1, r);
    }
}

int pHoareStructCresc(Comandos_1_3_4 v[], int p, int r) /* Funcao auxiliar da ordenacao decrescente com base no rating global dos jogadores, com quick sort. */
{
    Comandos_1_3_4 pivot = v[p]; /* Seleciona o primeiro elemento do vetor como pivo da ordenacao. */
    int i = p - 1, j = r + 1;

    while (1)
    {
        do
        {
            i++;

        } while (v[i].global_rating < pivot.global_rating);

        do
        {
            j--;

        } while (v[j].global_rating > pivot.global_rating);

        if (i >= j)
            return j;

        swapStruct(v, i, j);
    }
}

void quickSortStructCresc(Comandos_1_3_4 v[], int p, int r)  /* Realiza a ordenacao de jogadores com base no seu rating em ordem decrescente. */
{
    if (p < r)
    {
        int posicao = pHoareStructCresc(v, p, r);
        quickSortStructCresc(v, p, posicao);
        quickSortStructCresc(v, posicao+1, r);
    }
}

void swapInt (int v[], int i, int j) 
{
    int aux = v[i];
    v[i] = v[j];
    v[j] = aux;
}

int pHoareInt(int v[], int p, int r) /* Funcao auxiliar da ordenacao crescente com base no ID dos jogadores, com quick sort. */
{
    int pivot = v[p];
    int i = p - 1, j = r + 1;

    while (1)
    {
        do
        {
            i++;

        } while (v[i] < pivot);

        do
        {
            j--;

        } while (v[j] > pivot);

        if (i >= j)
            return j;

        swapInt(v, i, j);
    }
}

void quickSortInt(int v[], int p, int r) /* Realiza a ordenacao de jogadores com base no seu ID em ordem crescente. */
{
    if (p < r)
    {
        int posicao = pHoareInt(v, p, r);
        quickSortInt(v, p, posicao);
        quickSortInt(v, posicao+1, r);
    }
}

/* Funcao para imprimir os nomes dos jogadores pesquisados, junto com suas informacoes. */
void mostraPlayer(char *nome, PonteiroPlayer **tabelaHashPlayers1, Jogadores *vetorMedias)
{
    PonteiroPlayer *ptaux;
    int indice = hash(nome,TOTALJOGADORES), indice2;

    for (ptaux = tabelaHashPlayers1[indice]; ptaux != NULL; ptaux = ptaux->prox)
    {
        if (strcmp(ptaux->jogador.playername,nome)==0)
        {
            indice2 = atoi(ptaux->jogador.sofifa_id);

            printf("%9d\t%s",atoi(ptaux->jogador.sofifa_id),ptaux->jogador.positions);

            if (strlen(ptaux->jogador.positions) < PEQUENOIMPRESSAO)
                printf("\t");

            printf("\t\t%6.6f\t%5d\t\t%s\n",vetorMedias[indice2].media,vetorMedias[indice2].count,ptaux->jogador.playername);

            break;
        }
    }
}

/* Funcao para destruir toda as posicoes das tabelas hash 1 e 2 de jogadores. */
void destroiTabelaHashPlayers_1_2(PonteiroPlayer **tabelaHashPlayers) {
    for (int i = 0; i < TOTALJOGADORES; i++) 
        if (tabelaHashPlayers[i] != NULL) {
            destroiListaPlayer(tabelaHashPlayers[i]);
        }
    free(tabelaHashPlayers);
}

/* Funcao para destruir toda as posicoes da tabela hash 3 de jogadores. */
void destroiTabelaHashPlayers_3(PonteiroPlayer **tabelaHashPlayers3) {
    for (int i = 0; i < TOTALPOSICOES; i++) 
        if (tabelaHashPlayers3[i] != NULL) {
            destroiListaPlayer(tabelaHashPlayers3[i]);
        }
    free(tabelaHashPlayers3);
}

/* Funcao para destruir toda as posicoes de uma tabela hash de avaliacoes. */
void destroiTabelaHashRating(PonteiroUser **tabelaHashRating) {
    for (int i = 0; i < TOTALUSERS; i++) 
        if (tabelaHashRating[i] != NULL) {
            destroiListaUser(tabelaHashRating[i]);
        }
    free(tabelaHashRating);
}

/* Funcao para destruir toda as posicoes da tabela hash de tags 1. */
void destroiTabelaHashTags_1(PonteiroTag **tabelaHashTags_1) {
    for (int i = 0; i < TOTALTAGS; i++) 
        if (tabelaHashTags_1[i] != NULL) {
            destroiListaTags(tabelaHashTags_1[i]);
        }
    free(tabelaHashTags_1);
}

/* Funcao para destruir toda as posicoes da tabela hash de tags 2. */
void destroiTabelaHashTags_2(PonteiroTag **tabelaHashTags_2) {
    for (int i = 0; i < TOTALJOGADORES; i++) 
        if (tabelaHashTags_2[i] != NULL) {
            destroiListaTags(tabelaHashTags_2[i]);
        }
    free(tabelaHashTags_2);
}