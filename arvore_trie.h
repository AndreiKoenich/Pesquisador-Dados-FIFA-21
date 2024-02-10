#ifndef _ARVORE_TRIE_H_
#define _ARVORE_TRIE_H_

void insere_down(PonteiroLetra **pont, char c); /* Funcao para inserir um nodo em um nivel abaixo na arvore trie. */
void insere_prox(PonteiroLetra **pont, char c); /* Funcao para inserir um nodo no mesmo nivel na arvore trie. */
int testa_repetida(PonteiroLetra *pont, char c); /* Testa se uma letra da arvore trie e repetida. */
PonteiroLetra *insereTrie(PonteiroLetra *raiz, const char *palavra); /* Insere nomes na arvore trie. */
void copia_down(PonteiroLetra *raiz, char *str, int i); /* Funcao para copiar os caracteres a partir de uma raiz para uma string. */
void imprime_recursiva(PonteiroLetra *raiz, char *pref, char *str, int root, char *nome, PonteiroPlayer **tabela_players1, Jogadores *vetor_medias); /* Funcao auxiliar recursiva para imprimir os nomes inseridos na arvore trie, com busca por prefixo. */
void imprime_prefixo(PonteiroLetra *raiz, char *pref, PonteiroPlayer **tabela_players1, Jogadores *vetor_medias); /* Imprime nomes inseridos na arvore trie, a partir de busca por prefixo. */

#endif