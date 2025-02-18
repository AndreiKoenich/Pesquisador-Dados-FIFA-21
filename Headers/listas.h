#ifndef _LISTAS_H_
#define _LISTAS_H_

PonteiroPlayer* insereInicioPlayer (PonteiroPlayer *ptLista, Player dados); /* Funcao para inserir nodos no inicio de uma lista de jogadores. */
PonteiroUser* insereInicioUser (PonteiroUser *ptLista, User dados); /* Funcao para inserir nodos no inicio de uma lista de usuarios. */
PonteiroTag* insereInicioTag (PonteiroTag *ptLista, Info dados); /* Funcao para inserir nodos no inicio de uma lista de tags. */
void* destroiListaPlayer (PonteiroPlayer *ptLista); /* Funcao para destruir uma lista de jogadores. */
void* destroiListaUser (PonteiroUser *ptLista); /* Funcao para destruir uma lista de usuarios. */
void* destroiListaTags (PonteiroTag *ptLista); /* Funcao para destruir uma lista de tags. */

#endif