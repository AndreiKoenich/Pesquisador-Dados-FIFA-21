#ifndef _AUXILIARES_H
#define _AUXILIARES_H

#include "estruturas_comandos.h"
#include "estruturas_ponteiros.h"

void* inicializa();; /* Funcao para inicializar uma lista encadeada. */
void gotoxy(int x, int y); /* Funcao para alterar a posicao do cursor do usuario no terminal, durante a execucao do programa. */
int hash(char *nome, int M); /* Funcao de hashing CRC32 modificada. */
void bubblesortStruct(Comando2 v[], int dimensao); /* Realiza a ordenacao de jogadores com base no seu rating em ordem decrescente. */
void swapStruct (Comandos_1_3_4 v[], int i, int j); /* Funcao auxiliar da ordenacao decrescente com base no rating global dos jogadores, com quick sort. */
int pHoareStructDec(Comandos_1_3_4 v[], int p, int r); /* Funcao auxiliar da ordenacao decrescente com base no rating global dos jogadores, com quick sort. */
void quickSortStructDec(Comandos_1_3_4 v[], int p, int r);  /* Realiza a ordenacao de jogadores com base no seu rating em ordem decrescente. */
int pHoareStructCresc(Comandos_1_3_4 v[], int p, int r); /* Funcao auxiliar da ordenacao decrescente com base no rating global dos jogadores, com quick sort. */
void quickSortStructCresc(Comandos_1_3_4 v[], int p, int r);  /* Realiza a ordenacao de jogadores com base no seu rating em ordem decrescente. */
void swapInt (int v[], int i, int j); /* Funcao auxiliar da ordenacao crescente com base no ID dos jogadores, com quick sort. */
int pHoareInt(int v[], int p, int r); /* Funcao auxiliar da ordenacao crescente com base no ID dos jogadores, com quick sort. */
void quickSortInt(int v[], int p, int r); /* Realiza a ordenacao de jogadores com base no seu ID em ordem crescente. */
void mostra_player(char *nome, PonteiroPlayer **tabela_players1, Jogadores *vetor_medias); /* Funcao para imprimir os nomes dos jogadores pesquisados, junto com suas informacoes. */
#endif