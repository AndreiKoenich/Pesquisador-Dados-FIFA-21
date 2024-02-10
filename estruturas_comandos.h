#ifndef _ESTRUTURAS_COMANDOS_H_
#define _ESTRUTURAS_COMANDOS_H_

typedef struct /* Estrutura usada para armazenar informacoes mostradas com os comandos player, top, tags e down. */
{
    int sofifa_id;
    char name[DIMENSAO_GERAL];
    char player_positions[DIMENSAO_GERAL];
    float global_rating;
    int count;

} Comandos_1_3_4;

typedef struct /* Estrutura usada para armazenar informacoes mostradas com o comando user. */
{
    int sofifa_id;
    char name[DIMENSAO_GERAL];
    float global_rating;
    int count;
    float rating;

} Comando2;

typedef struct /* Estrutura usada para armazenar informacoes mostradas com o comando playerid. */
{
    int userID;
    char tag[DIMENSAO_GERAL];

} Comando6;

typedef struct /* Estrutura usada para armazenar informacoes mostradas com o comando 2. */
{
    int user_id;
    int sofifa_id;
    float rating;

} User;

#endif