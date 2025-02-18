#include <stdio.h>
#include <stdlib.h>

#include "../Headers/constantes.h"
#include "../Headers/estruturasComandos.h"
#include "../Headers/estruturasPonteiros.h"
#include "../Headers/listas.h"

PonteiroPlayer* insereInicioPlayer (PonteiroPlayer *ptLista, Player dados) /* Funcao para destruir nodos no inicio de uma lista de jogadores. */
{
    PonteiroPlayer *novo;
    novo = (PonteiroPlayer*) malloc (sizeof(PonteiroPlayer));
    novo->jogador = dados;
    novo->prox = ptLista; 
    ptLista = novo;

    return novo; 
}

PonteiroUser* insereInicioUser (PonteiroUser *ptLista, User dados) /* Funcao para destruir nodos no inicio de uma lista de usuarios. */
{
    PonteiroUser *novo;
    novo = (PonteiroUser*) malloc (sizeof(PonteiroUser)); 
    novo->usuario = dados;
    novo->prox = ptLista; 
    ptLista = novo;

    return novo; 
}

PonteiroTag* insereInicioTag (PonteiroTag *ptLista, Info dados) /* Funcao para destruir nodos no inicio de uma lista de tags. */
{
    PonteiroTag *novo;
    novo = (PonteiroTag*) malloc (sizeof(PonteiroTag)); 
    novo->infos = dados;
    novo->prox = ptLista; 
    ptLista = novo;

    return novo; 
}

void* destroiListaPlayer (PonteiroPlayer *ptLista) /* Funcao para destruir uma lista de jogadores. */
{
    PonteiroPlayer *ptaux;

    while (ptLista != NULL) {
        ptaux = ptLista;
        ptLista = ptLista->prox;
        free(ptaux);
    }

    free(ptLista);
    return NULL;
}

void* destroiListaUser (PonteiroUser *ptLista) /* Funcao para destruir uma lista de usuarios. */
{
    PonteiroUser *ptaux;

    while (ptLista != NULL) {
        ptaux = ptLista;
        ptLista = ptLista->prox;
        free(ptaux);
    }

    free(ptLista);
    return NULL;
}

void* destroiListaTags (PonteiroTag *ptLista) /* Funcao para destruir uma lista de tags. */
{
    PonteiroTag *ptaux;

    while (ptLista != NULL) {
        ptaux = ptLista;
        ptLista = ptLista->prox;
        free(ptaux);
    }

    free(ptLista);
    return NULL;
}