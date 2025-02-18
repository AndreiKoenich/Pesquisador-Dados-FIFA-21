#ifndef _ESTRUTURASPONTEIROS_H
#define _ESTRUTURASPONTEIROS_H

#include "constantes.h"
#include <stdbool.h>

typedef struct /* Estrutura usada para armazenar informacoes mostradas com o comando 2. */
{
    int user_id;
    int sofifa_id;
    float rating;

} User;

typedef struct /* Estrutura usada para armazenar informacoes das pontuacoes dos jogadores. */
{
    int count;
    float soma;
    float media;

} Jogadores;

typedef struct Ponteiro1 /* Estrutura referente a cada nodo da lista de usuarios. */
{
    User usuario; 
    struct Ponteiro1 *prox; 

} PonteiroUser;

typedef struct /* Estrutura contendo informacoes de cada jogador. */
{
    char sofifa_id[DIMENSAOGERAL];
    char playername[DIMENSAOGERAL];
    char positions[DIMENSAOGERAL];

} Player;

typedef struct Ponteiro2 /* Estrutura referente a cada nodo da lista de jogadores. */
{
    Player jogador; 
    struct Ponteiro2 *prox; 

} PonteiroPlayer;

typedef struct /* Estrutura contendo informacoes do usuario, do jogador e da sua tag associada. */
{
    char user_id[TAMANHOPEQUENO];
    char sofifa_id[DIMENSAOGERAL];
    char tag[DIMENSAOGERAL];

} Info;

typedef struct Ponteiro3 /* Estrutura referente a cada nodo da lista contendo usuarios, tags e jogadores. */
{
    Info infos; 
    struct Ponteiro3 *prox; 

} PonteiroTag;

typedef struct Ponteiro4 /* Estrutura auxliar usada nas operacaoes da arvore trie, para obter nomes. */
{
    struct Ponteiro4 *filho[TOTALCARACTERESASCII];
    bool isEndOfWord; // Indica se este nó é o fim de uma palavra

} PonteiroLetra;

#endif