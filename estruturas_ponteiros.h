#ifndef _ESTRUTURAS_PONTEIROS_H
#define _ESTRUTURAS_PONTEIROS_H

typedef struct /* Estrutura usada para armazenar informacoes das pontuacoes dos jogadores. */
{
    int count;
    float soma;
    float media;

} Jogadores;

typedef struct Ponteiro1 /* Estrutura referente a cada nodo da lista de usuarios. */
{
    User usuario; /* Estrutura contendo informacoes de cada nodo da lista. */
    struct Ponteiro1 *prox; /* Ponteiro para o proximo nodo da lista encadeada. */

} PonteiroUser;

typedef struct /* Estrutura contendo informacoes de cada jogador. */
{
    char sofifa_id[DIMENSAO_GERAL];
    char playername[DIMENSAO_GERAL];
    char positions[DIMENSAO_GERAL];

} Player;

typedef struct Ponteiro2 /* Estrutura referente a cada nodo da lista de jogadores. */
{
    Player jogador; /* Estrutura contendo informacoes de cada nodo da lista. */
    struct Ponteiro2 *prox; /* Ponteiro para o proximo nodo da lista encadeada. */

} PonteiroPlayer;

typedef struct /* Estrutura contendo informacoes do usuario, do jogador e da sua tag associada. */
{
    char user_id[TAMANHOPEQUENO];
    char sofifa_id[DIMENSAO_GERAL];
    char tag[DIMENSAO_GERAL];

} Info;

typedef struct Ponteiro3 /* Estrutura referente a cada nodo da lista contendo usuarios, tags e jogadores. */
{
    Info infos; /* Estrutura contendo informacoes de cada nodo da lista. */
    struct Ponteiro3 *prox; /* Ponteiro para o proximo nodo da lista encadeada. */

} PonteiroTag;

typedef struct Ponteiro4 /* Estrutura auxliar usada nas operacaoes da arvore trie, para obter nomes. */
{
    struct Ponteiro4 *prox;
    struct Ponteiro4 *down;
    char letter;
	int end;

} PonteiroLetra;

#endif