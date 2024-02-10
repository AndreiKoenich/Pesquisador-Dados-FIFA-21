#ifndef _EXECUCAO_COMANDOS_H_
#define _EXECUCAO_COMANDOS_H_

void analisa_player(char *comando, PonteiroLetra *raiz, PonteiroPlayer **tabela_players1, Jogadores *vetor_medias); /* Funcao para analisar o comando digitado pelo usuario, para utilizar o comando player. */
void mostra_userID(Comando2 *informacoes, int dimensao_vetor); /* Impressao dos dados relacionados ao uso do comando user na tela. */
int controle_userID(char *comando); /* Funcao para analisar o comando digitado pelo usuario, para utilizar o comando user. */
void comando_userID(char *comando, PonteiroPlayer **tabela_players2,PonteiroUser **tabela_rating, Jogadores *vetor_medias); /* Realiza a adequacao das informacoes a serem impressas com o comando user. */
void mostra_topdown(Comandos_1_3_4 *informacoes, int dimensao_vetor, int N); /* Impressao dos dados relacionados ao uso do comando top e do comando down na tela. */
void comando_top(char *position, int N, PonteiroPlayer **tabela_players3, PonteiroPlayer **tabela_players2, Jogadores *vetor_medias); /* Realiza a adequacao das informacoes a serem impressas com o comando top. */
void controla_top (char *comando,PonteiroPlayer **tabela_players3, PonteiroPlayer **tabela_players2, Jogadores *vetor_medias); /* Funcao para analisar o comando digitado pelo usuario, para utilizar o comando top. */
void mostra_tags(Comandos_1_3_4 *informacoes, int intersecoes); /* Impressao dos dados relacionados ao uso do comando tags na tela. */
void comando_tags(PonteiroPlayer **tabela_players2,Jogadores *vetor_medias,int **vetor_sofifas,int intersecoes, int quantidade_tags); /* Realiza a adequacao das informacoes a serem impressas com o comando tags. */
int calcula_interseccao(int **vetor_sofifas,int *quantidades,int indice_menor, int quantidade_tags); /* Determina quantos jogadores estao associados a uma mesma tag simultaneamente. */
void controla_tags(char *comando,PonteiroPlayer **tabela_players2, PonteiroTag **tabela_tags, Jogadores *vetor_medias); /* Funcao para analisar o comando digitado pelo usuario, para utilizar o comando tags. */
void comando_down(char *position, int N, PonteiroPlayer **tabela_players3, PonteiroPlayer **tabela_players2, Jogadores *vetor_medias); /* Realiza a adequacao das informacoes a serem impressas com o comando down. */
void controla_down (char *comando,PonteiroPlayer **tabela_players3, PonteiroPlayer **tabela_players2, Jogadores *vetor_medias); /* Funcao para analisar o comando digitado pelo usuario, para utilizar o comando down. */
void mostra_playerID(char *playerid, Comando6 *informacoes_users, PonteiroPlayer **tabela_players2, Jogadores *vetor_medias); /* Funcao para obter e imprimir as informacoes do jogador da tabela hash. */
void mostra_playerID2(char *playerid, Comando6 *informacoes_users, PonteiroTag **tabela_tags2, int dimensao_vetor); /* Funcao para obter e imprimir as informacoes dos usuarios da tabela hash. */
void comando_id(char *comando,PonteiroPlayer **tabela_players2,PonteiroTag **tabela_tags2,Jogadores *vetor_medias); /* Funcao para mostrar as informacoes do jogador do ID inserido, alem dos usuarios que o avaliaram e das avaliacoes com tags. */

#endif