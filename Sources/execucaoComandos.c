#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../Headers/constantes.h"
#include "../Headers/estruturasComandos.h"
#include "../Headers/estruturasPonteiros.h"
#include "../Headers/arvoreTrie.h"
#include "../Headers/auxiliares.h"
#include "../Headers/execucaoComandos.h"

/* Funcao para analisar o comando digitado pelo usuario, para utilizar o comando player. */
void analisaPlayer(char *comando, PonteiroLetra *raiz, PonteiroPlayer **tabelaHashPlayers1, Jogadores *vetorMedias)
{
    printf("\nsofifa_id\tpositions\t\trating\t\tcount\t\tname\n\n");

    char prefixo[DIMENSAOGERAL];
    int j = 0;

    for (int i = 7; comando[i] != '\0'; i++) /* Obtem o prefixo digitado pelo usuario a partir do comando. */
    {
        prefixo[j] = comando[i];
        j++;
    }

    prefixo[j] = '\0';

    imprimePrefixo(raiz, prefixo, tabelaHashPlayers1, vetorMedias); /* Impressao dos jogadores que correspondem ao prefixo. */
}

void mostraUserID(Comando2 *informacoes, int dimensao_vetor) /* Impressao dos dados relacionados ao uso do comando user na tela. */
{
    printf("\nsofifa_id\tglobal_rating\t\tcount\t\trating\t\tname\n\n");

    for (int i = 0; i < USERJOGADORESMAX && i < dimensao_vetor; i++)
    {
        printf("%9d\t%13.6f\t\t%5d",informacoes[i].sofifa_id,informacoes[i].global_rating,informacoes[i].count);
        printf("\t\t%6.1f\t\t%s\n",informacoes[i].rating,informacoes[i].name);
    }
}

int controleUserID(char *comando) /* Funcao para analisar o comando digitado pelo usuario, para utilizar o comando user. */
{
    char aux[TAMANHONUMERO];
    int count = 0;
    int user_id;

    for (int i = 0; comando[i] != '\0'; i++) 
    {
        if (count > TAMANHONUMERO-1)
        {
            printf("\nID de usuario mal inserido.\n");
            return 0;
        }

        if (isdigit(comando[i]))
        {
            aux[count] = comando[i];
            count++;
        }
    }

    aux[count] = '\0';
    user_id = atoi(aux);

    if (user_id >= TOTALUSERS || user_id <= 0) 
    {
        printf("\nID de usuario mal inserido. Os ID's dos usuarios variam entre 1 e 138493.\n");
        return 0;
    }

    return user_id; /* Retorna o id do usuario. */
}

/* Realiza a adequacao das informacoes a serem impressas com o comando user. */
void comandoUserID(char *comando, PonteiroPlayer **tabela_players2,PonteiroUser **tabela_rating, Jogadores *vetorMedias)
{
    Comando2 *informacoes;

    PonteiroUser *ptaux;
    PonteiroPlayer *ptaux2;

    int indice, i, aux_sofifaid = 0, dimensao_vetor = 0;

    char indice_aux[TAMANHOAUX];

    int user_id = controleUserID(comando);

    if (user_id == 0) 
        return;

    for (ptaux = tabela_rating[user_id]; ptaux != NULL; ptaux = ptaux->prox) 
        dimensao_vetor++;

    informacoes = calloc(dimensao_vetor,sizeof(Comando2));

    for (ptaux = tabela_rating[user_id],i = 0; ptaux != NULL; ptaux = ptaux->prox, i++) 
    {
        informacoes[i].sofifa_id = ptaux->usuario.sofifa_id; 
        informacoes[i].rating = ptaux->usuario.rating; 

        informacoes[i].global_rating = vetorMedias[ptaux->usuario.sofifa_id].media; 
        informacoes[i].count = vetorMedias[ptaux->usuario.sofifa_id].count;

        snprintf(indice_aux, sizeof(indice_aux), "%d", informacoes[i].sofifa_id);

        indice = hash(indice_aux,TOTALJOGADORES);

        for (ptaux2 = tabela_players2[indice]; ptaux2 != NULL; ptaux2 = ptaux2->prox) 
        {
            aux_sofifaid = atoi(ptaux2->jogador.sofifa_id);

            if (informacoes[i].sofifa_id == aux_sofifaid)
            {
                strcpy(informacoes[i].name,ptaux2->jogador.playername);
                break;
            }
        }
    }

    bubblesortStruct(informacoes,dimensao_vetor);
    mostraUserID(informacoes, dimensao_vetor); 
    free(informacoes);
}

/* Impressao dos dados relacionados ao uso do comando top e do comando down na tela. */
void mostraTopDown(Comandos_1_3_4 *informacoes, int dimensao_vetor, int N)
{
    int count = 0;

    printf("\nsofifa_id\tplayer_positions\t  rating\tcount\t\tname\n\n");

    for (int i = 0; i < dimensao_vetor; i++)
    {
        if (count >= N)
            break;

        if (informacoes[i].count >= MINIMOAVALIACOES) 
        {
            printf("%9d\t%s",informacoes[i].sofifa_id,informacoes[i].player_positions);

            if (strlen(informacoes[i].player_positions) < PEQUENOIMPRESSAO)
                printf("\t");

            printf("\t\t%f\t%5d\t\t%s\n",informacoes[i].global_rating,informacoes[i].count,informacoes[i].name);

            count++;
        }
    }
}

/* Realiza a adequacao das informacoes a serem impressas com o comando top. */
void comandoTop(char *position, int N, PonteiroPlayer **tabela_players3, PonteiroPlayer **tabela_players2, Jogadores *vetorMedias)
{
    Comandos_1_3_4 *informacoes;
    int indice = hash(position,TOTALPOSICOES);
    int indice2;
    int dimensao_vetor = 0;

    int i = 0;

    PonteiroPlayer *ptaux;
    PonteiroPlayer *ptaux2;

    for (ptaux = tabela_players3[indice]; ptaux != NULL; ptaux = ptaux->prox) 
        if (strstr(ptaux->jogador.positions,position))
            dimensao_vetor++;

    if (dimensao_vetor == 0) 
    {
        printf("\nPosicao de jogador invalida.\n");
        return;
    }

    else if (N > dimensao_vetor)
    {
        printf("\nNumero de jogadores invalido.\n");
        return;
    }

    informacoes = calloc(dimensao_vetor,sizeof(Comandos_1_3_4));

    for (ptaux = tabela_players3[indice]; ptaux != NULL; ptaux = ptaux->prox)
    {
        if (strstr(ptaux->jogador.positions,position))
        {
            informacoes[i].sofifa_id = atoi(ptaux->jogador.sofifa_id);
            strcpy(informacoes[i].player_positions,ptaux->jogador.positions); 

            indice2 = atoi(ptaux->jogador.sofifa_id);

            informacoes[i].global_rating = vetorMedias[indice2].media; 
            informacoes[i].count = vetorMedias[indice2].count;  

            indice2 = hash(ptaux->jogador.sofifa_id,TOTALJOGADORES);

            for (ptaux2 = tabela_players2[indice2]; ptaux2 != NULL; ptaux2 = ptaux2->prox)
            {
                if (strcmp (ptaux->jogador.sofifa_id,ptaux2->jogador.sofifa_id) == 0)
                {
                    strcpy(informacoes[i].name,ptaux2->jogador.playername);
                    break;
                }
            }

            i++;
        }
    }

    quickSortStructDec(informacoes,0,dimensao_vetor-1);
    mostraTopDown(informacoes,dimensao_vetor,N);
    free(informacoes);
}

/* Funcao para analisar o comando digitado pelo usuario, para utilizar o comando top. */
void controlaTop (char *comando,PonteiroPlayer **tabela_players3, PonteiroPlayer **tabela_players2, Jogadores *vetorMedias)
{
    char numero[TAMANHONUMERO];
    int N;
    char posicao[DIMENSAO_POSITION];
    int i,j = 0;
    int apostrofe = 0;

    for (i = 0; comando[i] != '\0'; i++)
    {
        if (j >= TAMANHONUMERO-1)
        {
            printf("\nNumero de jogadores invalido.\n");
            return;
        }

        if (isdigit(comando[i]))
        {
            numero[j] = comando[i];
            j++;
        }
    }

    numero[j] = '\0';

    N = atoi(numero);

    if (N >= TOTALJOGADORES || N == 0)
    {
        printf("\nNumero de jogadores invalido.\n");
        return;
    }

    j = 0;

    for (i = 0; comando[i] != '\0'; i++)
    {
        if (j > 3)
        {
            printf("\nPosicao de jogador invalida.\n");
            return;
        }

        if (comando[i] == APOSTROFE)
            apostrofe++;

        else if (apostrofe == 1)
        {
            posicao[j] = comando[i];
            j++;
        }
    }

    posicao[j] = '\0';

    if (apostrofe != 2 || j == 0)
    {
        printf("\nPosicao de jogador invalida.\n");
        return;
    }

    comandoTop(posicao, N, tabela_players3, tabela_players2, vetorMedias);
}

void mostraTags(Comandos_1_3_4 *informacoes, int intersecoes) 
{
    printf("\nsofifa_id\tplayer_positions\t  rating\tcount\t\tname\n\n");

    for (int i = 0; i < intersecoes; i++)
    {
        printf("%9d\t%s",informacoes[i].sofifa_id,informacoes[i].player_positions);

        if (strlen(informacoes[i].player_positions) < PEQUENOIMPRESSAO)
            printf("\t");

        printf("\t\t%f\t%5d\t\t%s\n",informacoes[i].global_rating,informacoes[i].count,informacoes[i].name);
    }
}

/* Realiza a adequacao das informacoes a serem impressas com o comando tags. */
void comandoTags(PonteiroPlayer **tabela_players2,Jogadores *vetorMedias,int **vetor_sofifas,int intersecoes, int quantidade_tags)
{
    Comandos_1_3_4 *informacoes;
    PonteiroPlayer *ptaux;

    char indice_aux[TAMANHOAUX];
    int indice ,i=0,j=0, aux_sofifaid = 0;

    informacoes = calloc(intersecoes,sizeof(Comandos_1_3_4));

    while (i < intersecoes)
    {
        snprintf(indice_aux, sizeof(indice_aux), "%d", vetor_sofifas[quantidade_tags][i]);

        indice = hash(indice_aux,TOTALJOGADORES);

        for (ptaux = tabela_players2[indice]; ptaux != NULL; ptaux = ptaux->prox) /* Iteracao para armazenar os dados a serem impressos na tela. */
        {
            aux_sofifaid = atoi(ptaux->jogador.sofifa_id);

            if (vetor_sofifas[quantidade_tags][i] == aux_sofifaid)
            {
                informacoes[j].sofifa_id = atoi(ptaux->jogador.sofifa_id); /* Armazena a informacao referente ao ID do jogador. */
                strcpy(informacoes[j].name,ptaux->jogador.playername); /* Armazena a informacao referente ao nome do jogador. */
                strcpy(informacoes[j].player_positions,ptaux->jogador.positions); /* Armazena a informacao referente a posicao do jogador. */
                informacoes[j].global_rating = vetorMedias[aux_sofifaid].media; /* Armazena a informacao referente ao rating global do jogador. */
                informacoes[j].count = vetorMedias[aux_sofifaid].count; /* Armazena a informacao referente a quantidade de avaliacoes do jogador. */
                j++;
            }
        }

        i++;
    }

    mostraTags(informacoes, intersecoes); /* Impressao dos dados relacionados ao uso do comando tags na tela. */
    free(informacoes);
}

/* Determina quantos jogadores estao associados a uma mesma tag simultaneamente. */
int calculaInterseccao(int **vetor_sofifas,int *quantidades,int indice_menor, int quantidade_tags)
{
    int indices_busca[quantidade_tags]; /* Registra em qual posicao de busca de ID's cada um dos vetores esta. */
    int achou = 0;
    int count = 0;
    int i = 0, j = 0, k = 0, n = 0;

    for (i = 0; i < quantidade_tags; i++) /* Inicializa os indices de busca de cada vetor com zero. */
        indices_busca[i] = 0;

    i = 0;

    if (j == indice_menor) /* Evita que o menor vetor seja considerado como um vetor maior a ser percorrido. */
        j++;

    while (i < quantidades[indice_menor]) /* Usa o menor vetor como referencia, para calcular as intersecoes de valores entre todos os vetores. */
    {
        count = 0;
        j = 0;

        if (j == indice_menor) /* Evita que o menor vetor seja considerado como um vetor maior a ser percorrido. */
            j++;

        while (j < quantidade_tags) /* Percorre um vetor a ser analisado, e identifica os numeros da interseccao com o vetor menor usado como referencia. */
        {
            for (k = indices_busca[j]; k < quantidades[j]; k++)
                if (vetor_sofifas[indice_menor][i] == vetor_sofifas[j][k])
                {
                    achou = 1;
                    count++;
                    indices_busca[j] = k;
                    break;
                }

            j++;

            if (j == indice_menor)
                j++;

            if (achou != 1) /* Descarta o numero e interrompe o laco, caso nao exista intersecao. */
            {
                j = 0;
                achou = 0;
                count = 0;
                break;
            }
        }

        if (count == quantidade_tags-1) /* Armazena o numero, caso haja intersecao envolvendo todos os vetores de ID's de jogadores. */
        {
            vetor_sofifas[quantidade_tags][n] = vetor_sofifas[indice_menor][i]; /* Atualiza o vetor contendo todas as intersecoes de ID's de jogadores. */
            n++;
        }

        i++;
    }

    if (n == 0) /* Retorna zero, caso nao hajam intersecoes. */
        return 0;

    else /* Retorna o numero de intersecoes. */
        return n;
}

/* Funcao para analisar o comando digitado pelo usuario, para utilizar o comando tags. */
void controlaTags(char *comando,PonteiroPlayer **tabela_players2, PonteiroTag **tabela_tags, Jogadores *vetorMedias)
{
    char tag[DIMENSAOGERAL];

    int apostrofos = 0;
    int quantidade_tags;
    int i = 0, j = 0, m = 0, n = 0;
    int *quantidades;
    int **vetor_sofifas;
    int indice, total_IDS;
    char aux[TAMANHOPEQUENO];
    int intersecoes = 0, menor_quantidade = 0, indice_menor = 0;

    PonteiroTag *ptaux;

    for (i = 0; comando[i] != '\0'; i++) /* Calcula a quantidade de apostrofos presentes no comando. */
        if (comando[i] == APOSTROFE)
            apostrofos++;

    if (apostrofos == 0 || apostrofos % 2 != 0) /* Controle dos casos em que uma ou mais tags sao mal inseridas. */
    {
        printf ("\nUma ou mais tags foram mal inseridas.\n");
        return;
    }

    quantidade_tags = apostrofos/2;
    apostrofos = 0;

    quantidades = calloc(quantidade_tags,sizeof(int));
    vetor_sofifas = calloc(quantidade_tags+1,sizeof(int));

    for (i = 0; i < quantidade_tags+1; i++)
        vetor_sofifas[i] = calloc(MAXTAGS,sizeof(int));

    for (i = 0; comando[i] != '\0'; i++) /* Iteracao para separar as tags digitadas e fazer a pesquisa uma por uma; */
    {
        if (comando[i] == APOSTROFE)
            apostrofos++;

        if (apostrofos == 1 && comando[i] != APOSTROFE) /* Armazena cada caractere de cada tag. */
        {
            tag[j] = comando[i];
            j++;
        }

        if (apostrofos == 2) /* Realiza a leitura de uma tag por vez. */
        {
            tag[j] = '\0';
            apostrofos = 0;
            j = 0;
            n = 0;
            total_IDS = 0;

            indice = hash(tag,TOTALTAGS);

            for (ptaux = tabela_tags[indice]; ptaux != NULL; ptaux = ptaux->prox) /* Iteracao para percorrer a lista da tabela e armazenas as informacoes. */
            {
                if (strcmp(ptaux->infos.tag,tag) == 0 && strcmp(aux,ptaux->infos.sofifa_id) != 0)
                {
                    vetor_sofifas[m][n] = atoi(ptaux->infos.sofifa_id); /* Armazena os ID's dos jogadores que correspondem as tags do comando. */
                    n++;
                    total_IDS++;
                    strcpy(aux,ptaux->infos.sofifa_id);
                }
            }

            quantidades[m] = total_IDS; /* Armazena a quantidade de ID's que correspondem a cada uma das tags. */

            if (m == 0)
                menor_quantidade = quantidades[0];

            if (quantidades[m] < menor_quantidade) /* Identifica qual o vetor com o menor numero de ID's. */
            {
                menor_quantidade = quantidades[m];
                indice_menor = m;
            }

            m++;
            memset(aux,0,sizeof(aux));
        }
    }

    if (quantidades[0] == 0) /* Controle dos casos em que a tag inserida nao corresponde a nenhum jogador. */
        printf("\nNenhum jogador corresponde a essa(s) tag(s).\n");

    else
    {

        if (quantidade_tags == 1) /* Controle dos casos em que existe somente uma tag, portanto nao ha intersecoes a serem determinadas. */
            comandoTags(tabela_players2,vetorMedias,vetor_sofifas,quantidades[0],0);

        else
        {
            for (i = 0; i < quantidade_tags; i++) /* Ordenada cada um dos vetores de ID's em ordem crescente, para otimizar a operacao de intersecao dos vetores. */
                quickSortInt(vetor_sofifas[i], 0, quantidades[i]-1);

            intersecoes = calculaInterseccao(vetor_sofifas,quantidades,indice_menor,quantidade_tags); /* Obtem o vetor com os ID's da intersecao, alem do numero total de intersecoes. */

            if (intersecoes == 0) /* Controle dos casos em que nenhum jogador corresponde a todas as tags simultaneamente. */
                printf("\nNenhum jogador corresponde a essas tags simultaneamente.\n");

            else
                comandoTags(tabela_players2,vetorMedias,vetor_sofifas,intersecoes,quantidade_tags); /* Realiza a adequacao das informacoes a serem impressas com o comando tags. */
        }
    }

    free(quantidades);

    for (i = 0; i < quantidade_tags+1; i++)
        free(vetor_sofifas[i]);

    free(vetor_sofifas);
}

/* Realiza a adequacao das informacoes a serem impressas com o comando down. */
void comandoDown(char *position, int N, PonteiroPlayer **tabela_players3, PonteiroPlayer **tabela_players2, Jogadores *vetorMedias)
{
    Comandos_1_3_4 *informacoes;
    int indice = hash(position,TOTALPOSICOES);
    int indice2;
    int dimensao_vetor = 0;

    int i = 0;

    PonteiroPlayer *ptaux;
    PonteiroPlayer *ptaux2;

    for (ptaux = tabela_players3[indice]; ptaux != NULL; ptaux = ptaux->prox) /* Determina quantas posicoes o vetor de informacoes devera ter. */
        if (strstr(ptaux->jogador.positions,position))
            dimensao_vetor++;

    if (dimensao_vetor == 0) /* Controle dos casos em que a posicao do jogador e mal inserida. */
    {
        printf("\nPosicao de jogador invalida.\n");
        return;
    }

    else if (N > dimensao_vetor) /* Controle dos casos em que o numero dos jogadores e mal inserido. */
    {
        printf("\nNumero de jogadores invalido.\n");
        return;
    }

    informacoes = calloc(dimensao_vetor,sizeof(Comandos_1_3_4));

    for (ptaux = tabela_players3[indice]; ptaux != NULL; ptaux = ptaux->prox) /* Iteracao para percorrer as tabelas e obter as informacoes a serem impressas. */
    {
        if (strstr(ptaux->jogador.positions,position))
        {
            informacoes[i].sofifa_id = atoi(ptaux->jogador.sofifa_id); /* Armazena a informacao do ID do jogador a ser impresso. */
            strcpy(informacoes[i].player_positions,ptaux->jogador.positions); /* Armazena das posicoes do jogador a serem impressas. */

            indice2 = atoi(ptaux->jogador.sofifa_id);

            informacoes[i].global_rating = vetorMedias[indice2].media; /* Armazena a informacao do rating global do jogador a ser impresso. */
            informacoes[i].count = vetorMedias[indice2].count;  /* Armazena a informacao da quantidade de avaliacoes do jogadore a ser impressa. */

            indice2 = hash(ptaux->jogador.sofifa_id,TOTALJOGADORES);

            for (ptaux2 = tabela_players2[indice2]; ptaux2 != NULL; ptaux2 = ptaux2->prox) /* Realiza uma busca intermediaria pelo nome do jogador na outra tabela hash. */
            {
                if (strcmp (ptaux->jogador.sofifa_id,ptaux2->jogador.sofifa_id) == 0)
                {
                    strcpy(informacoes[i].name,ptaux2->jogador.playername);
                    break;
                }
            }

            i++;
        }
    }

    quickSortStructCresc(informacoes,0,dimensao_vetor-1); /* Realiza a ordenacao dos jogadores em ordem decrescente, com base nos seus ratings globais. */
    mostraTopDown(informacoes,dimensao_vetor,N); /* Imprime as informacoes na tela, apos a ordenacao. */
    free(informacoes);
}

/* Funcao para analisar o comando digitado pelo usuario, para utilizar o comando down. */
void controlaDown (char *comando,PonteiroPlayer **tabela_players3, PonteiroPlayer **tabela_players2, Jogadores *vetorMedias)
{
    char numero[TAMANHONUMERO];
    int N;
    char posicao[DIMENSAO_POSITION];
    int i,j = 0;
    int apostrofe = 0;

    for (i = 0; comando[i] != '\0'; i++)
    {
        if (j >= TAMANHONUMERO-1) /* Controle dos casos em que o numero de jogadores e mal inserido. */
        {
            printf("\nNumero de jogadores invalido.\n");
            return;
        }

        if (isdigit(comando[i]))
        {
            numero[j] = comando[i];
            j++;
        }
    }

    numero[j] = '\0';

    N = atoi(numero);

    if (N >= TOTALJOGADORES || N == 0) /* Controle dos casos em que o numero de jogadores e mal inserido. */
    {
        printf("\nNumero de jogadores invalido.\n");
        return;
    }

    j = 0;

    for (i = 0; comando[i] != '\0'; i++) /* Controle dos casos em que a posicao do jogador e mal inserida. */
    {
        if (j > 3)
        {
            printf("\nPosicao de jogador invalida.\n");
            return;
        }

        if (comando[i] == APOSTROFE)
            apostrofe++;

        else if (apostrofe == 1)
        {
            posicao[j] = comando[i];
            j++;
        }
    }

    posicao[j] = '\0';

    if (apostrofe != 2 || j == 0) /* Controle dos casos em que a posicao do jogador e mal inserida. */
    {
        printf("\nPosicao de jogador invalida.\n");
        return;
    }

    comandoDown(posicao, N, tabela_players3, tabela_players2, vetorMedias); /* Realiza a adequacao das informacoes a serem impressas com o comando top. */
}

/* Funcao para obter e imprimir as informacoes do jogador da tabela hash. */
void mostraPlayerID(char *playerid, Comando6 *informacoes_users, PonteiroPlayer **tabela_players2, Jogadores *vetorMedias)
{
    int indice,indice2;
    PonteiroPlayer *ptaux;

    indice = hash(playerid,TOTALJOGADORES);

    for (ptaux = tabela_players2[indice]; ptaux != NULL; ptaux = ptaux->prox) /* Obtem e imprime as informacoes do jogador na tabela hash. */
    {
        if (strcmp(playerid,ptaux->jogador.sofifa_id)==0)
        {
            indice2 = atoi(ptaux->jogador.sofifa_id);

            printf("\nsofifa_id\tplayer_positions\t  rating\tcount\t\tname\n\n");
            printf("%9d\t%s",atoi(ptaux->jogador.sofifa_id),ptaux->jogador.positions);

            if (strlen(ptaux->jogador.positions) < TAMANHOPEQUENO)
                printf("\t");

            printf("\t\t%f\t%5d\t\t%s\n",vetorMedias[indice2].media,vetorMedias[indice2].count,ptaux->jogador.playername);

            break;
        }
    }
}

/* Funcao para obter e imprimir as informacoes dos usuarios da tabela hash. */
void mostraPlayerID2(char *playerid, Comando6 *informacoes_users, PonteiroTag **tabela_tags2, int dimensao_vetor)
{
    PonteiroTag *ptaux;
    int indice = hash(playerid,TOTALJOGADORES);
    int j = 0;
    int aux_userid;

    for (ptaux = tabela_tags2[indice]; ptaux != NULL; ptaux = ptaux->prox) /* Obtem as informacoes dos usuarios que avaliaram o jogador na tabela hash. */
    {
        if (strcmp(playerid,ptaux->infos.sofifa_id)==0)
        {
            strcpy(informacoes_users[j].tag,ptaux->infos.tag);

            aux_userid = atoi(ptaux->infos.user_id);
            informacoes_users[j].userID = aux_userid;

            j++;
        }
    }

    if (j == 0)
    {
        printf("\nEsse jogador nao foi avaliado por nenhum usuario.\n");
        return;
    }

    printf("\n----------------------------------------------------------------------------------------------------\n");

    printf("\nuser_id\t\ttag\n\n"); /* Impressao das informacoes dos usuarios que avaliaram o jogador. */

    for (int i = 0; i < dimensao_vetor; i++)
        printf("%7d\t\t%s\n", informacoes_users[i].userID, informacoes_users[i].tag);
}

/* Funcao para mostrar as informacoes do jogador do ID inserido, alem dos usuarios que o avaliaram e das avaliacoes com tags. */
void comandoID(char *comando,PonteiroPlayer **tabela_players2,PonteiroTag **tabela_tags2,Jogadores *vetorMedias)
{
    char playerid[TAMANHOPEQUENO];
    int i = 0, j = 0, indice;
    PonteiroTag *ptaux2;
    int dimensao_vetor = 0;
    Comando6 *informacoes_users;

    for (i = 3; comando[i] != '\0'; i++) /* Obtem o ID do jogador. */
    {
        playerid[j] = comando[i];
        j++;
    }

    playerid[j] = '\0';
    j = 0;

    indice = hash(playerid,TOTALJOGADORES);

    for (ptaux2 = tabela_tags2[indice]; ptaux2 != NULL; ptaux2 = ptaux2->prox)
        if (strcmp(playerid,ptaux2->infos.sofifa_id)==0)
            dimensao_vetor++;

    if (dimensao_vetor == 0) /* Controle dos casos em que o ID do jogador e mal inserido. */
    {
        printf("\nNenhum jogador corresponde a esse ID.\n");
        return;
    }

    informacoes_users = calloc(dimensao_vetor,sizeof(Comando6));

    mostraPlayerID(playerid,informacoes_users,tabela_players2,vetorMedias); /* Obtem e imprime as informacoes do jogador da tabela hash. */
    mostraPlayerID2(playerid,informacoes_users,tabela_tags2,dimensao_vetor); /* Obtem e imprime as informacoes dos usuarios da tabela hash. */

    free(informacoes_users);
}