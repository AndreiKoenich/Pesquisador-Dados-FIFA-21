#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Headers/constantes.h"
#include "../Headers/estruturasComandos.h"
#include "../Headers/estruturasPonteiros.h"
#include "../Headers/arvoreTrie.h"
#include "../Headers/auxiliares.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

/* Funcao para criar um novo no da trie */
PonteiroLetra *createNode() {
    PonteiroLetra *nodo = (PonteiroLetra *)malloc(sizeof(PonteiroLetra));
    nodo->isEndOfWord = false;

    for (int i = 0; i < TOTALCARACTERESASCII; i++)
        nodo->filho[i] = NULL;

    return nodo;
}

/* Funcao para converter um caractere para um indice (0-255) */
int charToIndex(unsigned char c) {
    return (int)c; 
}

/* Funcao para inserir uma palavra na trie */
void insereTrie(PonteiroLetra *raiz, char *palavra) {
    PonteiroLetra *current = raiz;

    for (int i = 0; i < strlen(palavra); i++) {
        int indice = charToIndex((unsigned char)palavra[i]); 

        if (current->filho[indice] == NULL) {
            current->filho[indice] = createNode();
        }

        current = current->filho[indice];
    }

    current->isEndOfWord = true;
}

/* Funcao para buscar uma palavra na trie */
bool procuraTrie(PonteiroLetra *raiz, char *palavra) {
    PonteiroLetra *current = raiz;

    for (int i = 0; i < strlen(palavra); i++) {
        int indice = charToIndex((unsigned char)palavra[i]); 

        if (current->filho[indice] == NULL) {
            return false;
        }

        current = current->filho[indice];
    }

    return (current != NULL && current->isEndOfWord);
}

/* Função para destruir a trie recursivamente */
void destroiTrie(PonteiroLetra *raiz) {
    if (raiz == NULL) {
        return; 
    }

    for (int i = 0; i < 256; i++) { 
        if (raiz->filho[i] != NULL) {
            destroiTrie(raiz->filho[i]); 
        }
    }
    free(raiz);
}

/* Funcao auxiliar para realizar a travessia DFS e imprimir palavras */
void dfsPrint(PonteiroLetra *nodo, char *prefixo, int nivel, PonteiroPlayer **tabelaHashPlayers1, Jogadores *vetorMedias) {
    if (nodo == NULL) {
        return;
    }

    if (nodo->isEndOfWord) {
        prefixo[nivel] = '\0';
        mostraPlayer(prefixo,tabelaHashPlayers1,vetorMedias);
    }

    for (int i = 0; i < TOTALCARACTERESASCII; i++) { 
        if (nodo->filho[i] != NULL) {
            prefixo[nivel] = (char)i; 
            dfsPrint(nodo->filho[i], prefixo, nivel + 1, tabelaHashPlayers1, vetorMedias); 
        }
    }
}

/* Funcao para imprimir todas as palavras que começam com um prefixo */
void imprimePrefixo(PonteiroLetra *raiz, char *prefixo, PonteiroPlayer **tabelaHashPlayers1, Jogadores *vetorMedias) {
    PonteiroLetra *current = raiz;

    for (int i = 0; i < strlen(prefixo); i++) {
        int indice = charToIndex((unsigned char)prefixo[i]);

        if (current->filho[indice] == NULL) {
            printf("\nNenhum jogador corresponde a esse prefixo.\n");
            return;
        }

        current = current->filho[indice];
    }

    char buffer[100];
    strcpy(buffer, prefixo); 

    dfsPrint(current, buffer, strlen(prefixo), tabelaHashPlayers1, vetorMedias);
}