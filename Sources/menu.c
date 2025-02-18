#include <stdio.h>
#include <stdlib.h>

#include "../Headers/menu.h"
#include "../Headers/auxiliares.h"

void menu() /* Funcao para realizar a impressao do menu principal do programa na tela. */
{
    printf("\t\t\t\t   CLASSIFICACAO E PESQUISA DE DADOS\n");

    printf("\t\t\t\t\tTRABALHO FINAL - 2021/1\n\n");

    printf("AUTOR: Andrei Pochmann Koenich\n");

    printf("\n----------------------------------------------------------------------------------------------------\n");

    printf("\nInsira o comando de pesquisa e pressione ENTER para iniciar a busca:\n");

    printf("\n>");

    printf("\n\nDigite 'help' para ver uma lista de comandos de busca.\n");
    printf("Digite 'info' para ver uma lista de posicoes de jogo.\n");
    printf("Digite 'exit' para encerrar a execucao do programa.\n");
}

void menuHelp() /* Funcao para realizar a impressao do menu de ajuda do programa na tela. */
{
    printf("\nLISTA DE COMANDOS:\n");

    printf("\n----------------------------------------------------------------------------------------------------\n");

    printf("\nCOMANDO 1:\nplayer");

    printf("\n\nSINTAXE:\nplayer <nome ou prefixo>");

    printf("\n\nDESCRICAO:\n");

    printf("Esta pesquisa tem por objetivo retornar a lista de jogadores cujo nome comeca com um texto,\n");
    printf("que pode ser o prefixo ou o texto completo do nome de um jogador. Todos os jogadores que\n");
    printf("satisfizerem o texto de consulta serao retornados, junto com a lista de posicoes dos\n");
    printf("jogadores, avaliacao media e numero de avaliacoes.\n");

    printf("\nEXEMPLOS:\n");
    printf("player Fer\n");
    printf("player Aaron\n");
    printf("player Kevin\n");

    printf("\n----------------------------------------------------------------------------------------------------\n");

    printf("\nCOMANDO 2:\nuser");

    printf("\n\nSINTAXE:\nuser <ID do usuario>");

    printf("\n\nDESCRICAO:\n");

    printf("Esta pesquisa retorna uma lista com no maximo 20 jogadores revisados pelo usuario e, para\n");
    printf("cada jogador, mostra a nota dada pelo usuario, a media global e a contagem de avaliacoes.\n");
    printf("A lista sera ordenada pela nota dada pelo usuario de maneira decrescente (maiores notas primeiro).\n");
    printf("Os valores numericos dos ID's dos usuarios variam entre 1 e 138493.\n");

    printf("\nEXEMPLOS:\n");

    printf("user 77\n");
    printf("user 1337\n");
    printf("user 3301\n");

    printf("\n----------------------------------------------------------------------------------------------------\n");

    printf("\nCOMANDO 3:\ntop");

    printf("\n\nSINTAXE:\ntop<N> '<posicao>'");

    printf("\n\nDESCRICAO:\n");

    printf("Esta pesquisa tem por objetivo retornar a lista de jogadores com melhores notas de uma dada\n");
    printf("posicao. Para evitar que um jogador seja retornando com uma boa media mas com poucas avaliacoes,\n");
    printf("esta consulta deve retornar somente os melhores jogadores com no minimo 1000 avaliacoes. Para\n");
    printf("gerenciar o numero de jogadores a serem retornados, a consulta deve receber como parametro um\n");
    printf("numero N que corresponde ao numero maximo de jogadores a serem retornados. O resultado da consulta\n");
    printf("estara ordenado da maior para a menor avaliacao.\n");

    printf("\nEXEMPLOS:\n");
    printf("top10 'ST'\n");
    printf("top15 'CM'\n");
    printf("top20 'RW'\n");

    printf("\n----------------------------------------------------------------------------------------------------\n");

    printf("\nCOMANDO 4:\ntags");

    printf("\n\nSINTAXE:\ntags <lista de tags>");

    printf("\n\nDESCRICAO:\n");

    printf("Esta pesquisa tem por objetivo explorar a lista de tags adicionadas por cada usuario em cada\n");
    printf("revisao. Para uma lista de tags dada como entrada, a pesquisa deve retornar a lista de jogadores\n");
    printf("que estao associados a esse conjunto de tags. Como as tags podem ser termos com espaco, a tag\n");
    printf("passada na consulta deve ser escrita entre apostrofes.\n");

    printf("\nEXEMPLOS:\n");
    printf("tags 'Brazil'\n");
    printf("tags 'France''China PR'\n");
    printf("tags 'Aerial Threat'\n");

    printf("\n----------------------------------------------------------------------------------------------------\n");

    printf("\nCOMANDO 5:\ndown");

    printf("\n\nSINTAXE:\ndown<N> '<posicao>'");

    printf("\n\nDESCRICAO:\n");

    printf("Esta pesquisa tem por objetivo retornar a lista de jogadores com piores notas de uma dada\n");
    printf("posicao. Para evitar que um jogador seja retornando com uma boa media mas com poucas avaliacoes,\n");
    printf("esta consulta deve retornar somente os piores jogadores com no minimo 1000 avaliacoes. Para\n");
    printf("gerenciar o numero de jogadores a serem retornados, a consulta deve receber como parametro um\n");
    printf("numero N que corresponde ao numero maximo de jogadores a serem retornados. O resultado da consulta\n");
    printf("estara ordenado da menor para a maior avaliacao.\n");

    printf("\nEXEMPLOS:\n");
    printf("down10 'GK'\n");
    printf("down15 'CB'\n");
    printf("down20 'LW'\n");

    printf("\n----------------------------------------------------------------------------------------------------\n");

    printf("\nCOMANDO 6:\nid");

    printf("\n\nSINTAXE:\nid <ID do jogador>");

    printf("\n\nDESCRICAO:\n");

    printf("Esta pesquisa tem por objetivo retornar as informacoes do jogador que corresponde ao ID inserido,\n");
    printf("alem de todos os ID's dos usuarios que o avaliaram, com a respectiva tag atribuida por cada um deles\n");
    printf("ao jogador pesquisado.\n");

    printf("\nEXEMPLOS:\n");
    printf("id 20801\n");
    printf("id 158023\n");
    printf("id 190871\n");

    printf("\n----------------------------------------------------------------------------------------------------\n");

    printf("\nPressione ESC para encerrar a execucao do programa, ou qualquer outra tecla para continuar as consultas.\n");
}

void menuPositions() /* Funcao para realizar a impressao do menu da lista de posicoes do programa na tela. */
{
    printf("\nLISTA DE POSICOES DE JOGO:\n");

    printf("\n----------------------------------------------------------------------------------------------------\n");

    printf("\nATACANTES:\n");
    printf("\nRW = Right Winger   - Ala Direito\nLW = Left Winger    - Ala Esquerdo\nST = Striker        - Atacante");
    printf("\nCF = Center Forward - Centroavante\n");

    printf("\n----------------------------------------------------------------------------------------------------\n");

    printf("\nMEIO-CAMPISTAS:\n");
    printf("\nCM  = Central Midfielder \t   - Meia Central");
    printf("\nLM  = Left Midfielder \t\t   - Meia Esquerda\nRM  = Right Midfielder \t\t   - Meia Direita");
    printf("\nCAM = Central Attacking Midfielder - Meio-Campo Ofensivo / Armador");
    printf("\nCDM = Central Defensive Midfielder - Meio-Campo Defensivo / Volante\n");

    printf("\n----------------------------------------------------------------------------------------------------\n");

    printf("\nDEFENSORES:\n");
    printf("\nGK  = Goalkeeper      - Goleiro\nRB  = Right Back      - Zagueiro Direito\nCB  = Central Back    - Zagueiro Central");
    printf("\nLB  = Left Back       - Zagueiro Esquerdo\nRWB = Right Wing Back - Lateral Direito\nLWB = Left Wing Back  - Lateral Esquerdo\n");

    printf("\n----------------------------------------------------------------------------------------------------\n");

    printf("\nPressione ESC para encerrar a execucao do programa, ou qualquer outra tecla para continuar as consultas.\n");
}