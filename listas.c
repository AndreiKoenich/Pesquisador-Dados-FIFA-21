#include <stdio.h>
#include <stdlib.h>

#include "definicoes.h"
#include "estruturas_comandos.h"
#include "estruturas_ponteiros.h"
#include "listas.h"

PonteiroPlayer* insereInicioPlayer (PonteiroPlayer *ptLista, Player dados) /* Funcao para inserir nodos no inicio de uma lista de jogadores. */
{
    PonteiroPlayer *novo;
    novo = (PonteiroPlayer*) malloc (sizeof(PonteiroPlayer)); /* Aloca espaco de memoria para o novo nodo da lista, que sera o primeiro. */
    novo->jogador = dados;
    novo->prox = ptLista; /* Atualiza o novo primeiro nodo da lista. */
    ptLista = novo;

    return novo; /* Retorna o ponteiro para o novo primeiro nodo da lista. */
}

PonteiroUser* insereInicioUser (PonteiroUser *ptLista, User dados) /* Funcao para inserir nodos no inicio de uma lista de usuarios. */
{
    PonteiroUser *novo;
    novo = (PonteiroUser*) malloc (sizeof(PonteiroUser)); /* Aloca espaco de memoria para o novo nodo da lista, que sera o primeiro. */
    novo->usuario = dados;
    novo->prox = ptLista; /* Atualiza o novo primeiro nodo da lista. */
    ptLista = novo;

    return novo; /* Retorna o ponteiro para o novo primeiro nodo da lista. */
}

PonteiroTag* insereInicioTag (PonteiroTag *ptLista, Info dados) /* Funcao para inserir nodos no inicio de uma lista de tags. */
{
    PonteiroTag *novo;
    novo = (PonteiroTag*) malloc (sizeof(PonteiroTag)); /* Aloca espaco de memoria para o novo nodo da lista, que sera o primeiro. */
    novo->infos = dados;
    novo->prox = ptLista; /* Atualiza o novo primeiro nodo da lista. */
    ptLista = novo;

    return novo; /* Retorna o ponteiro para o novo primeiro nodo da lista. */
}