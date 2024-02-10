#ifndef _ANALISE_ARQUIVOS_H_
#define _ANALISE_ARQUIVOS_H_

/* Funcao para armazenar os dados do arquivo players.csv em tres tabelas hash, cada uma com informacoes diferentes usadas no hashing. */
void analisa_arquivo_players(PonteiroPlayer **tabela_players1,PonteiroPlayer **tabela_players2,PonteiroPlayer **tabela_players3, PonteiroLetra **raiz);

/* Funcao para armazenar os dados do arquivo rating.csv em uma tabela hash e em um vetor auxiliar. */
void analisa_arquivo_rating(PonteiroUser **tabela_rating, Jogadores *vetor_medias);

/* Funcao para armazenar os dados do arquivo tags.csv em uma tabela hash. */
void analisa_arquivo_tags(PonteiroTag **tabela_tags, PonteiroTag **tabela_tags2);

#endif