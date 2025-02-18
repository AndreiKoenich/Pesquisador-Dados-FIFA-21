#ifndef _ANALISEARQUIVOS_H_
#define _ANALISEARQUIVOS_H

#include "../Headers/estruturasComandos.h"
#include "../Headers/estruturasPonteiros.h"

void analisaArquivoPlayers(PonteiroPlayer **tabelaHashPlayers1,PonteiroPlayer **tabelaHashPlayers2,PonteiroPlayer **tabelaHashPlayers3, PonteiroLetra *raizArvoreTrie); /* Funcao para armazenar os dados do arquivo players.csv em tres tabelas hash, cada uma com informacoes diferentes usadas no hashing. */
void analisaArquivoRating(PonteiroUser **tabelaHashRating, Jogadores *vetorMedias); /* Funcao para armazenar os dados do arquivo rating.csv em uma tabela hash e em um vetor auxiliar. */
void analisaArquivoTags(PonteiroTag **tabelaHashTags1, PonteiroTag **tabelaHashTags2); /* Funcao para armazenar os dados do arquivo tags.csv em uma tabela hash. */

#endif