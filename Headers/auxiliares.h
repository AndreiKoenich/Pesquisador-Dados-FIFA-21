#ifndef _AUXILIARES_H
#define _AUXILIARES_H

#include "../Headers/estruturasComandos.h"
#include "../Headers/estruturasPonteiros.h"

void obtemComando(char* comando); /* Funcao para obter a string do comando digitada pelo usuario. */
void* inicializaEstrutura();; /* Funcao para inicializar uma lista encadeada. */
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
void mostraPlayer(char *nome, PonteiroPlayer **tabelaHashPlayers1, Jogadores *vetorMedias); /* Funcao para imprimir os nomes dos jogadores pesquisados, junto com suas informacoes. */
char _getch(); /* Aguarda o pressionamento de tecla pelo usuario. */
void destroiTabelaHashPlayers_1_2(PonteiroPlayer **tabelaHashPlayers); /* Funcao para destruir toda as posicoes das tabelas hash 1 e 2 de jogadores. */
void destroiTabelaHashPlayers_3(PonteiroPlayer **tabelaHashPlayers3); /* Funcao para destruir toda as posicoes da tabela hash 3 de jogadores. */
void destroiTabelaHashRating(PonteiroUser **tabelaHashRating); /* Funcao para destruir toda as posicoes de uma tabela hash de avaliacoes. */
void destroiTabelaHashTags_1(PonteiroTag **tabelaHashTags); /* Funcao para destruir toda as posicoes da tabela hash de tags 1. */
void destroiTabelaHashTags_2(PonteiroTag **tabelaHashTags_2); /* Funcao para destruir toda as posicoes da tabela hash de tags 2. */

#endif