#ifndef _EXECUCAO_COMANDOS_H_
#define _EXECUCAO_COMANDOS_H_

#include "../Headers/estruturasComandos.h"
#include "../Headers/estruturasPonteiros.h"


void analisaPlayer(char *comando, PonteiroLetra *raiz, PonteiroPlayer **tabelaHashPlayers1, Jogadores *vetorMedias); /* Funcao para analisar o comando digitado pelo usuario, para utilizar o comando player. */
void mostraUserID(Comando2 *informacoes, int dimensao_vetor); /* Impressao dos dados relacionados ao uso do comando user na tela. */
int controleUserID(char *comando); /* Funcao para analisar o comando digitado pelo usuario, para utilizar o comando user. */
void comandoUserID(char *comando, PonteiroPlayer **tabela_players2,PonteiroUser **tabela_rating, Jogadores *vetorMedias); /* Realiza a adequacao das informacoes a serem impressas com o comando user. */
void mostraTopDown(Comandos_1_3_4 *informacoes, int dimensao_vetor, int N); /* Impressao dos dados relacionados ao uso do comando top e do comando down na tela. */
void comandoTop(char *position, int N, PonteiroPlayer **tabela_players3, PonteiroPlayer **tabela_players2, Jogadores *vetorMedias); /* Realiza a adequacao das informacoes a serem impressas com o comando top. */
void controlaTop (char *comando,PonteiroPlayer **tabela_players3, PonteiroPlayer **tabela_players2, Jogadores *vetorMedias); /* Funcao para analisar o comando digitado pelo usuario, para utilizar o comando top. */
void mostraTags(Comandos_1_3_4 *informacoes, int intersecoes); /* Impressao dos dados relacionados ao uso do comando tags na tela. */
void comandoTags(PonteiroPlayer **tabela_players2,Jogadores *vetorMedias,int **vetor_sofifas,int intersecoes, int quantidade_tags); /* Realiza a adequacao das informacoes a serem impressas com o comando tags. */
int calculaInterseccao(int **vetor_sofifas,int *quantidades,int indice_menor, int quantidade_tags); /* Determina quantos jogadores estao associados a uma mesma tag simultaneamente. */
void controlaTags(char *comando,PonteiroPlayer **tabela_players2, PonteiroTag **tabela_tags, Jogadores *vetorMedias); /* Funcao para analisar o comando digitado pelo usuario, para utilizar o comando tags. */
void comandoDown(char *position, int N, PonteiroPlayer **tabela_players3, PonteiroPlayer **tabela_players2, Jogadores *vetorMedias); /* Realiza a adequacao das informacoes a serem impressas com o comando down. */
void controlaDown (char *comando,PonteiroPlayer **tabela_players3, PonteiroPlayer **tabela_players2, Jogadores *vetorMedias); /* Funcao para analisar o comando digitado pelo usuario, para utilizar o comando down. */
void mostraPlayerID(char *playerid, Comando6 *informacoes_users, PonteiroPlayer **tabela_players2, Jogadores *vetorMedias); /* Funcao para obter e imprimir as informacoes do jogador da tabela hash. */
void mostraPlayerID2(char *playerid, Comando6 *informacoes_users, PonteiroTag **tabela_tags2, int dimensao_vetor); /* Funcao para obter e imprimir as informacoes dos usuarios da tabela hash. */
void comandoID(char *comando,PonteiroPlayer **tabela_players2,PonteiroTag **tabela_tags2,Jogadores *vetorMedias); /* Funcao para mostrar as informacoes do jogador do ID inserido, alem dos usuarios que o avaliaram e das avaliacoes com tags. */

#endif