#ifndef _ESTRUTURASCOMANDOS_H_
#define _ESTRUTURASCOMANDOS_H_

#include "constantes.h"

typedef struct /* Estrutura usada para armazenar informacoes mostradas com os comandos player, top, tags e down. */
{
    int sofifa_id;
    char name[DIMENSAOGERAL];
    char player_positions[DIMENSAOGERAL];
    float global_rating;
    int count;

} Comandos_1_3_4;

typedef struct /* Estrutura usada para armazenar informacoes mostradas com o comando user. */
{
    int sofifa_id;
    char name[DIMENSAOGERAL];
    float global_rating;
    int count;
    float rating;

} Comando2;

typedef struct /* Estrutura usada para armazenar informacoes mostradas com o comando playerid. */
{
    int userID;
    char tag[DIMENSAOGERAL];

} Comando6;

#endif