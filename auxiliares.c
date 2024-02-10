#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <windows.h>

#include "estruturas_comandos.h"
#include "estruturas_ponteiros.h"
#include "definicoes.h"
#include "auxiliares.h"

void* inicializa() /* Funcao para inicializar uma lista encadeada. */
{
    return NULL; /* Retorna um ponteiro nulo. */
}

void gotoxy(int x, int y) /* Funcao para alterar a posicao do cursor do usuario no terminal, durante a execucao do programa. */
{
    static HANDLE h = NULL;  
    if(!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x-1, y-1 };  
    SetConsoleCursorPosition(h,c);
}

int hash(char *nome, int M) /* Funcao de hashing CRC32 modificada. */
{
	unsigned int crc32 = 0xFFFFFFFFu;

	static int Table[256] = {0};
	static int ini = 0;

	if (!ini) /* Gerar tabela CRC32 "aleatoriamente" apenas uma vez na execucao. */
    {
		srand(0xdeadbeef); /* Usa sempre a mesma seed. */

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

	return crc32 % M; /* Retornar o resto do crc32 por M. */
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

void swapInt (int v[], int i, int j) /* Funcao auxiliar da ordenacao crescente com base no ID dos jogadores, com quick sort. */
{
    int aux = v[i];
    v[i] = v[j];
    v[j] = aux;
}

int pHoareInt(int v[], int p, int r) /* Funcao auxiliar da ordenacao crescente com base no ID dos jogadores, com quick sort. */
{
    int pivot = v[p]; /* Seleciona o primeiro elemento do vetor como pivo da ordenacao. */
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
void mostra_player(char *nome, PonteiroPlayer **tabela_players1, Jogadores *vetor_medias)
{
    PonteiroPlayer *ptaux;
    int indice = hash(nome,TOTALJOGADORES), indice2;

    for (ptaux = tabela_players1[indice]; ptaux != NULL; ptaux = ptaux->prox) /* Iteracao para procurar o nome na tabela hash. */
    {
        if (strcmp(ptaux->jogador.playername,nome)==0)
        {
            indice2 = atoi(ptaux->jogador.sofifa_id);

            printf("%9d\t%s",atoi(ptaux->jogador.sofifa_id),ptaux->jogador.positions);

            if (strlen(ptaux->jogador.positions) < PEQUENOIMPRESSAO)
                printf("\t");

            printf("\t\t%6.6f\t%5d\t\t%s\n",vetor_medias[indice2].media,vetor_medias[indice2].count,ptaux->jogador.playername);

            break;
        }
    }
}