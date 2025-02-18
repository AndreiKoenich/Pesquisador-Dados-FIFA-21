#ifndef _ARVORE_TRIE_H_
#define _ARVORE_TRIE_H_

PonteiroLetra *createNode(); /* Funcao para criar um novo no da trie */
int charToIndex(unsigned char c); /* Funcao para converter um caractere para um indice (0-25) */
void insereTrie(PonteiroLetra *raiz, char *palavra); /* Funcao para inserir uma palavra na trie */
bool procuraTrie(PonteiroLetra *raiz, char *palavra); /* Funcao para buscar uma palavra na trie */
void destroiTrie(PonteiroLetra *raiz); /* Função para destruir a trie recursivamente */
void dfsPrint(PonteiroLetra *nodo, char *prefixo, int nivel, PonteiroPlayer **tabelaHashPlayers1, Jogadores *vetorMedias); /* Funcao auxiliar para realizar a travessia DFS e imprimir palavras */
void imprimePrefixo(PonteiroLetra *raiz, char *prefixo, PonteiroPlayer **tabelaHashPlayers1, Jogadores *vetorMedias); /* Funcao para imprimir todas as palavras que começam com um prefixo */

#endif