#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "definicoes.h"
#include "estruturas_comandos.h"
#include "estruturas_ponteiros.h"
#include "arvore_trie.h"
#include "auxiliares.h"

void insere_down(PonteiroLetra **pont, char c) /* Funcao para inserir um nodo em um nivel abaixo na arvore trie. */
{
	PonteiroLetra *novo;

	novo = (PonteiroLetra*) malloc(sizeof(PonteiroLetra));
	novo->letter = c;
	novo->prox = NULL;
	novo->down = NULL;
	novo->end = 0;

	(*pont)->down = novo;
}

void insere_prox(PonteiroLetra **pont, char c) /* Funcao para inserir um nodo no mesmo nivel na arvore trie. */
{
	PonteiroLetra *novo;

	novo = (PonteiroLetra*) malloc(sizeof(PonteiroLetra));
	novo->letter = c;
	novo->prox = NULL;
	novo->down = NULL;
	novo->end = 0;

	(*pont)->prox = novo;
}

int testa_repetida(PonteiroLetra *pont, char c) /* Testa se uma letra da arvore trie e repetida. */
{
    if (pont)
    {
        if (pont->down)
        {
            pont = pont->down;

            if (c == pont->letter)
                return 1;

            while (pont->prox) /* Procura a letra no nivel. */
            {
                if (c == pont->letter)
                    return 1;

                else
                    pont = pont->prox;
            }
        }
    }

    return 0;
}

PonteiroLetra *insereTrie(PonteiroLetra *raiz, const char *palavra) /* Insere nomes na arvore trie. */
{
    PonteiroLetra *ptaux = raiz;
    int achou = 0, root = 0, i = 0;

	if (!raiz) /* Se a raiz esta vazia, criar raiz */
    { 
		raiz = (PonteiroLetra*) malloc (sizeof(PonteiroLetra));
		raiz->prox = NULL;
		raiz->down = NULL;
		raiz->letter = palavra[i];
        if (palavra[1]) /* Se a palavra tem mais de 1 caractere */
            raiz->end = 0;
        
        else /* Se a palavra tem apenas 1 caractere */
            raiz->end = 1;
		ptaux = raiz;
		root = 1; /* Ativar flag de root */
	}

    while (palavra[i])
    {
		while (ptaux->prox) /* Procurar a letra no nivel */
        { 
			if (palavra[i] == ptaux->letter) 
            {
                if (palavra[i] != palavra[i+1] && !testa_repetida(ptaux, palavra[i])) 
                    ptaux = ptaux->down; /* Se achou, ir um nivel abaixo */
				achou = 1;
				if (!palavra[i+1]) /* Se e a ultima letra da palavra */
					return raiz; /* Palavra duplicada */
				break;
			}

			else 
				ptaux = ptaux->prox;
		}

		if (root && (palavra[i] == ptaux->letter)) /* Se e a primeira palavra a ser inserida */
        {
			i++;
			/* Insere a palavra inteira para baixo */
			while (palavra[i]) 
            {
				insere_down(&ptaux, palavra[i]);
				ptaux = ptaux->down;
				i++;
			}
			ptaux->end = 1;
			return raiz;
		} 
        
		else if (palavra[i] == ptaux->letter) /* Se a letra esta na arvore */
        {
            if (palavra[i] == palavra[i+1]) /* Se ha duas letras iguais repetidas */
            { 
                if (testa_repetida(ptaux, palavra[i])) 
                {
                    i++;
                    ptaux = ptaux->down;
                    while (ptaux->letter != palavra[i]) 
                        ptaux = ptaux->prox;
                    
                }
            }

            /* Se chegou no fim de uma palavra que ja estava na arvore */
			else if (palavra[i+1] && ptaux->end) 
            {
				/* Inserir o resto da palavra inteira para baixo */
				i++;
				while (palavra[i]) 
                {
					insere_down(&ptaux, palavra[i]);
					ptaux = ptaux->down;
					i++;
				}
				ptaux->end = 1;
				return raiz;
			}

			else if (ptaux->end) /* Se chegou no fim da arvore */
            { 
				/* Palavra ja estava na lista */
				return raiz;
			}

			else if (!palavra[i+1]) /* Se chegou no fim da palavra */
            { 
				ptaux->end = 1;
				return raiz;
			}
			ptaux = ptaux->down;
		} /* Se nao achou a letra no nivel e a palavra continua */

        else if (!achou && palavra[i+1]) 
        {
			insere_prox(&ptaux, palavra[i]); /* Cria proximo nodo */
			/* Insere a palavra inteira para baixo */
			ptaux = ptaux->prox;
			i++;
			while (palavra[i]) 
            {
				insere_down(&ptaux, palavra[i]);
				ptaux = ptaux->down;
				i++;
			}
			ptaux->end = 1;
			return raiz;
		} 

        else if (!achou && palavra[i] && !palavra[i+1])  /* Se nao achou a letra no nivel e for a ultima letra da palavra */
        {
            insere_prox(&ptaux, palavra[i]);
            ptaux = ptaux->prox;
            ptaux->end = 1;
            return raiz;
        }
		i++;
		achou = 0;
    }

	if (ptaux) 
		ptaux->end = 1;

	return raiz;
}

void copia_down(PonteiroLetra *raiz, char *str, int i) /* Funcao para copiar os caracteres a partir de uma raiz para uma string. */
{
	while (raiz)
	{
        str[i] = raiz->letter;
        i++;
		raiz = raiz->down;
	}

	str[i] = 0;
}

/* Funcao auxiliar recursiva para imprimir os nomes inseridos na arvore trie, com busca por prefixo. */
void imprime_recursiva(PonteiroLetra *raiz, char *pref, char *str, int root, char *nome, PonteiroPlayer **tabela_players1, Jogadores *vetor_medias)
{
	PonteiroLetra *ptaux = raiz;
    PonteiroLetra *ptaux2; /* Ponteiros auxiliares para percorrer a arvore trie. */
	char straux[2] = {0}; /* String auxiliar com um caractere. */
	char str2[DIMENSAO_GERAL] = {0}; /* String para chamar nas recursoes. */
    char nome2[DIMENSAO_GERAL] = {0};
	int i = 0, j = 0;

	if (root) /* Primeira vez que a funcao e chamada. */
    {
		for (i = 0; i < strlen(pref)-1; i++)
		{
            nome[i] = pref[i]; /* Montar o nome com o prefixo. */
            j++;
		}
	}

	else  /* Proximas vezes que a funcao e chamada. */
        j = strlen(nome); /* Prefixo ja esta em *nome. */

    straux[0] = ptaux->letter;
    strcat(str, straux); /* Montar a string com os caracteres do primeiro nome que se repetem. */
    copia_down(ptaux, nome, j); /* Copiar o resto do primeiro nome. */

    mostra_player(nome,tabela_players1,vetor_medias); /* Impressao do nome e das informacoes do jogador na tela. */

    ptaux = ptaux->down; /* Ir para o nivel de baixo na arvore. */
    ptaux2 = ptaux;

	while (ptaux)
    {
		while (ptaux2->prox) /* Percorrer ate acabar o nivel da arvore trie. */
		{
			for (i = 0; i < strlen(pref)-1; i++)
                nome2[i] = pref[i];

            for (j = 0; j < strlen(str); j++)
            {
                nome2[i] = str[j];
                i++;
            }

            nome2[i] = 0;
            strcpy(str2, str);
            imprime_recursiva(ptaux2->prox, pref, str2, 0, nome2, tabela_players1, vetor_medias); /* Chamar recursivamente com o nome e a string montados. */
            ptaux2 = ptaux2->prox; /* Ir para o proximo elemento do nivel. */
		}


		if (ptaux->end && ptaux->down) /* Se encontrar um nome que esta contido em outro nome. */
        {
            i = 0;
			for (j = 0; j < strlen(pref); j++) /* Montar o segundo nome. */
			{
                nome2[i] = pref[j];
                i++;
			}
            for (j = 1; j < strlen(str); j++)
            {
                nome2[i] = str[j];
                i++;
            }

            nome2[i] = ptaux->letter;
            nome2[i+1] = 0;

            mostra_player(nome2,tabela_players1,vetor_medias); /* Impressao do nome e das informacoes do jogador na tela.. */
			return;
		}

		straux[0] = ptaux->letter;
		strcat(str, straux);
        ptaux = ptaux->down; /* Ir para um nivel abaixo na arvore. */
        ptaux2 = ptaux;
	}
}

/* Imprime nomes inseridos na arvore trie, a partir de busca por prefixo. */
void imprime_prefixo(PonteiroLetra *raiz, char *pref, PonteiroPlayer **tabela_players1, Jogadores *vetor_medias)
{
	PonteiroLetra *ptaux = raiz;
	int i = 0;
	int achou = 0;
	char empty[DIMENSAO_GERAL] = {0}; /* Strings vazias para chamar na recursao */
    char nome[DIMENSAO_GERAL] = {0};

	while (pref[i])
	{
        if (!ptaux)
            break;  /* Nao achou o prefixo */

        if (ptaux->letter == pref[i]) /* Verificar se esta na letra */
        {
            if (pref[i+1]) /* Verificar se nao chegou no final do prefixo */
            {
                ptaux = ptaux->down; /* Ir um nivel abaixo na arvore */
                i++;
            }

            else
                break; /* Se chegou, achou o prefixo */
		}

		else /* Procurar no proximo elemento do nivel */
            ptaux = ptaux->prox;
	}

	if (ptaux) /* Se o prefixo foi encontrado. */
    {
        printf("\nsofifa_id\tplayer_positions\t  rating\tcount\t\tname\n\n");
		imprime_recursiva(ptaux, pref, empty, 1, nome, tabela_players1, vetor_medias);
	}

	else /* Se o prefixo nao foi encontrado. */
        printf("\nNenhum jogador corresponde a esse prefixo.\n", pref);
}