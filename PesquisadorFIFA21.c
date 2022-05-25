/* Nome: Andrei Pochmann Koenich    Matricula: 00308680
   Nome: Pedro Company Beck         Matricula: 00324055 */

/* O programa a seguir explora o dataset FIFA21 - Players, por meio de operacoes de indexacao e de consulta dos arquivos
de texto players.csv, rating.csv e tags.csv. Apos as indexacoes de todas as informacoes contidas nesses arquivos, o usuario
pode fazer consultas aos dados desses arquivos com comandos especificos, listados no menu de ajuda do programa. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio2.h>
#include <ctype.h>

#define TOTALUSERS 138494
#define TOTALTAGS 1000
#define TOTALJOGADORES 18944
#define DIMENSAO 70
#define TOTALSOFIFAID 300000
#define TOTALPOSITIONS 50
#define USERJOGADORESMAX 20
#define DIMENSAO_POSITION 5

#define TAMANHOPEQUENO 10
#define PEQUENOIMPRESSAO 8
#define TAMANHOAUX 20
#define TAMANHOGRANDE 45
#define TAMANHONUMERO 6

#define MAXTAGS 15000
#define MINIMOAVALIACOES 1000

#define ESC 27
#define APOSTROFE 39

typedef struct /* Estrutura usada para armazenar informacoes mostradas com os comandos player, top, tags e down. */
{
    int sofifa_id;
    char name[DIMENSAO];
    char player_positions[DIMENSAO];
    float global_rating;
    int count;

} COMANDOS134;

typedef struct /* Estrutura usada para armazenar informacoes mostradas com o comando user. */
{
    int sofifa_id;
    char name[DIMENSAO];
    float global_rating;
    int count;
    float rating;

} COMANDO2;

typedef struct /* Estrutura usada para armazenar informacoes mostradas com o comando playerid. */
{
    int userID;
    char tag[DIMENSAO];

} COMANDO6;

typedef struct /* Estrutura usada para armazenar informacoes das pontuacoes dos jogadores. */
{
    int count;
    float soma;
    float media;

} JOGADORES;

typedef struct /* Estrutura usada para armazenar informacoes mostradas com o comando 2. */
{
    int user_id;
    int sofifa_id;
    float rating;

} USER;

typedef struct PONT1 /* Estrutura referente a cada nodo da lista de usuarios. */
{
    USER usuario; /* Estrutura contendo informacoes de cada nodo da lista. */
    struct PONT1 *prox; /* Ponteiro para o proximo nodo da lista encadeada. */

} PONT_USER;

typedef struct /* Estrutura contendo informacoes de cada jogador. */
{
    char sofifa_id[DIMENSAO];
    char playername[DIMENSAO];
    char positions[DIMENSAO];

} PLAYER;

typedef struct PONT2 /* Estrutura referente a cada nodo da lista de jogadores. */
{
    PLAYER jogador; /* Estrutura contendo informacoes de cada nodo da lista. */
    struct PONT2 *prox; /* Ponteiro para o proximo nodo da lista encadeada. */

} PONT_PLAYER;

typedef struct /* Estrutura contendo informacoes do usuario, do jogador e da sua tag associada. */
{
    char user_id[TAMANHOPEQUENO];
    char sofifa_id[DIMENSAO];
    char tag[DIMENSAO];

} INFO;

typedef struct PONT3 /* Estrutura referente a cada nodo da lista contendo usuarios, tags e jogadores. */
{
    INFO infos; /* Estrutura contendo informacoes de cada nodo da lista. */
    struct PONT3 *prox; /* Ponteiro para o proximo nodo da lista encadeada. */

} PONT_TAG;

typedef struct PONT4 /* Estrutura auxliar usada nas operacaoes da arvore trie, para obter nomes. */
{
    struct PONT4 *prox;
    struct PONT4 *down;
    char letter;
	int end;

} PONT_LETRA;

void* inicializa() /* Funcao para inicializar uma lista encadeada. */
{
    return NULL; /* Retorna um ponteiro nulo. */
}

PONT_PLAYER* insereInicioPlayer (PONT_PLAYER *ptLista, PLAYER dados) /* Funcao para inserir nodos no inicio de uma lista de jogadores. */
{
    PONT_PLAYER *novo;
    novo = (PONT_PLAYER*) malloc (sizeof(PONT_PLAYER)); /* Aloca espaco de memoria para o novo nodo da lista, que sera o primeiro. */
    novo->jogador = dados;
    novo->prox = ptLista; /* Atualiza o novo primeiro nodo da lista. */
    ptLista = novo;

    return novo; /* Retorna o ponteiro para o novo primeiro nodo da lista. */
}

PONT_USER* insereInicioUser (PONT_USER *ptLista, USER dados) /* Funcao para inserir nodos no inicio de uma lista de usuarios. */
{
    PONT_USER *novo;
    novo = (PONT_USER*) malloc (sizeof(PONT_USER)); /* Aloca espaco de memoria para o novo nodo da lista, que sera o primeiro. */
    novo->usuario = dados;
    novo->prox = ptLista; /* Atualiza o novo primeiro nodo da lista. */
    ptLista = novo;

    return novo; /* Retorna o ponteiro para o novo primeiro nodo da lista. */
}

PONT_TAG* insereInicioTag (PONT_TAG *ptLista, INFO dados) /* Funcao para inserir nodos no inicio de uma lista de tags. */
{
    PONT_TAG *novo;
    novo = (PONT_TAG*) malloc (sizeof(PONT_TAG)); /* Aloca espaco de memoria para o novo nodo da lista, que sera o primeiro. */
    novo->infos = dados;
    novo->prox = ptLista; /* Atualiza o novo primeiro nodo da lista. */
    ptLista = novo;

    return novo; /* Retorna o ponteiro para o novo primeiro nodo da lista. */
}

int hash(char *nome, int M) /* Funcao de hashing CRC32 modificada. */
{
	unsigned int crc32 = 0xFFFFFFFFu;

	static int Table[256] = {0};
	static int ini = 0;

	if (!ini) /* Gerar tabela CRC32 "aleatoriamente" apenas uma vez na execucao. */
    	{
		srand(0xdeadbeef); /* Usa sempre a mesma seed. */

		for (int j = 0; j < 256; j++)
			Table[j] = rand();

		ini = 1;
	}

	for (int i = 0; i < strlen(nome); i++) {
		unsigned int lookup = (crc32 ^ nome[i]) & 0xff;
		crc32 = (crc32 >> 8) ^ Table[lookup];
	}

	crc32 ^= 0xFFFFFFFFu;

	return crc32 % M; /* Retornar o resto do crc32 por M. */
}

void insere_down(PONT_LETRA **pont, char c) /* Funcao para inserir um nodo em um nivel abaixo na arvore trie. */
{
	PONT_LETRA *novo;

	novo = (PONT_LETRA*) malloc(sizeof(PONT_LETRA));
	novo->letter = c;
	novo->prox = NULL;
	novo->down = NULL;
	novo->end = 0;

	(*pont)->down = novo;
}

void insere_prox(PONT_LETRA **pont, char c) /* Funcao para inserir um nodo no mesmo nivel na arvore trie. */
{
	PONT_LETRA *novo;

	novo = (PONT_LETRA*) malloc(sizeof(PONT_LETRA));
	novo->letter = c;
	novo->prox = NULL;
	novo->down = NULL;
	novo->end = 0;

	(*pont)->prox = novo;
}

int testa_repetida(PONT_LETRA *pont, char c) /* Testa se uma letra da arvore trie e repetida. */
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

PONT_LETRA* insereTrie(PONT_LETRA *raiz, const char *palavra) /* Insere nomes na arvore trie. */
{
    PONT_LETRA *ptaux = raiz;
    int achou = 0, root = 0, i = 0;

	if (!raiz) { /* Se a raiz esta vazia, criar raiz */
		raiz = (PONT_LETRA*) malloc (sizeof(PONT_LETRA));
		raiz->prox = NULL;
		raiz->down = NULL;
		raiz->letter = palavra[i];
        if (palavra[1]) { /* Se a palavra tem mais de 1 caractere */
            raiz->end = 0;
        } else { /* Se a palavra tem apenas 1 caractere */
            raiz->end = 1;
        }
		ptaux = raiz;
		root = 1; /* Ativar flag de root */
	}

    while (palavra[i])
    {
		while (ptaux->prox) { /* Procurar a letra no nivel */
			if (palavra[i] == ptaux->letter) {
                if (palavra[i] != palavra[i+1] && !testa_repetida(ptaux, palavra[i])) {
                    ptaux = ptaux->down; /* Se achou, ir um nivel abaixo */
                }
				achou = 1;
				if (!palavra[i+1]) { /* Se e a ultima letra da palavra */
					return raiz; /* Palavra duplicada */
				}
				break;
			}
			else {
				ptaux = ptaux->prox;
			}
		}
		if (root && (palavra[i] == ptaux->letter)) { /* Se e a primeira palavra a ser inserida */
			i++;
			/* Insere a palavra inteira para baixo */
			while (palavra[i]) {
				insere_down(&ptaux, palavra[i]);
				ptaux = ptaux->down;
				i++;
			}
			ptaux->end = 1;
			return raiz;
		} /* Se a letra esta na arvore */
		else if (palavra[i] == ptaux->letter) {
            if (palavra[i] == palavra[i+1]) { /* Se ha duas letras iguais repetidas */
                if (testa_repetida(ptaux, palavra[i])) {
                    i++;
                    ptaux = ptaux->down;
                    while (ptaux->letter != palavra[i]) {
                        ptaux = ptaux->prox;
                    }
                }
            }
            /* Se chegou no fim de uma palavra que ja estava na arvore */
			else if (palavra[i+1] && ptaux->end) {
				/* Inserir o resto da palavra inteira para baixo */
				i++;
				while (palavra[i]) {
					insere_down(&ptaux, palavra[i]);
					ptaux = ptaux->down;
					i++;
				}
				ptaux->end = 1;
				return raiz;
			}
			else if (ptaux->end) { /* Se chegou no fim da arvore */
				/* Palavra ja estava na lista */
				return raiz;
			}
			else if (!palavra[i+1]) { /* Se chegou no fim da palavra */
				ptaux->end = 1;
				return raiz;
			}
			ptaux = ptaux->down;
		} /* Se nao achou a letra no nivel e a palavra continua */
        else if (!achou && palavra[i+1]) {
			insere_prox(&ptaux, palavra[i]); /* Cria proximo nodo */
			/* Insere a palavra inteira para baixo */
			ptaux = ptaux->prox;
			i++;
			while (palavra[i]) {
				insere_down(&ptaux, palavra[i]);
				ptaux = ptaux->down;
				i++;
			}
			ptaux->end = 1;
			return raiz;
		} /* Se nao achou a letra no nivel e for a ultima letra da palavra */
        else if (!achou && palavra[i] && !palavra[i+1]) {
            insere_prox(&ptaux, palavra[i]);
            ptaux = ptaux->prox;
            ptaux->end = 1;
            return raiz;
        }
		i++;
		achou = 0;
    }
	if (ptaux) {
		ptaux->end = 1;
	}
	return raiz;
}

/* Funcao para indexar os dados do arquivo players.csv em tres tabelas hash, cada uma com informacoes diferentes usadas no hashing. */
void analisa_arquivo_players(PONT_PLAYER **tabela_players1,PONT_PLAYER **tabela_players2,PONT_PLAYER **tabela_players3, PONT_LETRA **raiz)
{
    int i,j,indice;

    FILE *arq1;

    char linha[DIMENSAO];
    char aux[DIMENSAO];
    char posicoes[DIMENSAO_POSITION];

    PLAYER jogador;

    for (i = 0; i < TOTALJOGADORES; i++) /* Inicializacao de uma lista simplesmente encadeada em cada posicao da tabela. */
        tabela_players1[i] = inicializa();

    for (i = 0; i < TOTALJOGADORES; i++) /* Inicializacao de uma lista simplesmente encadeada em cada posicao da tabela. */
        tabela_players2[i] = inicializa();

    for (i = 0; i < TOTALPOSITIONS; i++) /* Inicializacao de uma lista simplesmente encadeada em cada posicao da tabela. */
        tabela_players3[i] = inicializa();

    if (!(arq1 = fopen("players.csv","r"))) /* Abertura do arquivo players.csv, com controle dos casos em que nao e possivel abri-lo. */
    {
        printf("\nErro na abertura do arquivo players.csv. Fim do programa.\n");
        getch();
        exit(1); /* Encerra a execucao do programa, retornando 1. */
    }

    fgets(linha,DIMENSAO,arq1); /* Pula a primeira linha do arquivo texto. */

    while (!feof(arq1)) /* Iteracao para percorrer o arquivo texto do inicio ao fim. */
    {
        i = 0;
        j = 0;

        memset(linha, 0, sizeof(linha));
        memset(aux, 0, sizeof(aux));

        fgets(linha,DIMENSAO,arq1);

        while (linha[i] != ',') /* Obtem a informacao do id do jogador. */
        {
            aux[j] = linha[i];
            i++;
            j++;
        }

        strcpy(jogador.sofifa_id, aux);
        memset(aux, 0, sizeof(aux));
        i++;
        j = 0;

        while (linha[i] != ',') /* Obtem a informacao do nome do jogador. */
        {
            aux[j] = linha[i];
            i++;
            j++;
        }

        strcpy(jogador.playername, aux);
		*raiz = insereTrie(*raiz, jogador.playername);
        memset(aux, 0, sizeof(aux));
        i++;
        j = 0;

        while (linha[i] != '\n' && linha[i] != '\0') /* Obtem a informacao das posicoes do jogador. */
        {
            if (linha[i] != '"')
            {
                aux[j] = linha[i];
                j++;
            }

            i++;
        }

        strcpy(jogador.positions,aux);

        indice = hash(jogador.playername,TOTALJOGADORES);
        tabela_players1[indice] = insereInicioPlayer(tabela_players1[indice],jogador); /* Insere as informacoes do jogador na tabela hash, usando o seu nome como indice. */

        indice = hash(jogador.sofifa_id,TOTALJOGADORES);
        tabela_players2[indice] = insereInicioPlayer(tabela_players2[indice],jogador); /* Insere as informacoes do jogador na tabela hash, usando o seu ID como indice. */

        j = 0;

        for (int i = 0; jogador.positions[i] != '\0'; i++) /* Iteracao para obter cada posicao do jogador separadamente. */
        {
            if (jogador.positions[i] != ',' && jogador.positions[i] != ' ')
            {
                posicoes[j] = jogador.positions[i];
                j++;
            }

            else if (jogador.positions[i] == ',')
            {
                posicoes[j] = '\0';
                j = 0;
                indice = hash(posicoes,TOTALPOSITIONS);
                tabela_players3[indice] = insereInicioPlayer(tabela_players3[indice], jogador); /* Insere as informacoes do jogador na tabela hash, usando uma de suas posicoes como indice. */
            }
        }

        posicoes[j] = '\0';
        indice = hash(posicoes,TOTALPOSITIONS);
        tabela_players3[indice] = insereInicioPlayer(tabela_players3[indice], jogador); /* Insere as informacoes do jogador na tabela hash, usando uma de suas posicoes como indice. */
    }

    fclose(arq1); /* Fechamento do arquivo players.csv. */
}

/* Funcao para indexar os dados do arquivo rating.csv em uma tabela hash e em um vetor auxiliar. */
void analisa_arquivo_rating(PONT_USER **tabela_rating, JOGADORES *vetor_medias)
{
    int indice;

    FILE *arq2;

    char linha[DIMENSAO];
    char c;

    USER usuario;

    for (int i = 0; i < TOTALUSERS; i++)
        tabela_rating[i] = inicializa(); /* Inicializacao de uma lista simplesmente encadeada em cada posicao da tabela. */

    for (int i = 0; i < TOTALSOFIFAID; i++) /* Inicializa o vetor contendo informacoes das pontuacoes dos jogadores. */
    {
        vetor_medias[i].count = 0;
        vetor_medias[i].soma = 0;
        vetor_medias[i].media = 0;
    }

    if (!(arq2 = fopen("rating.csv","r"))) /* Abertura do arquivo rating.csv, com controle dos casos em que nao e possivel abri-lo. */
    {
        printf("\nErro na abertura do arquivo rating.csv. Fim do programa.\n");
        getch();
        exit(1); /* Encerra a execucao do programa, retornando 1. */
    }

    fgets(linha,DIMENSAO,arq2); /* Pula a primeira linha do arquivo texto. */

    while (!feof(arq2)) /* Iteracao para percorrer o arquivo texto do inicio ao fim. */
    {
        fscanf(arq2,"%d %c %d %c %f",&usuario.user_id,&c,&usuario.sofifa_id,&c,&usuario.rating); /* Obtem as informacoes da linha do arquivo. */
        indice = usuario.user_id;
        tabela_rating[indice] = insereInicioUser(tabela_rating[indice],usuario); /* Insere as informacoes do usuario e do jogador na tabela hash, usando o ID do usuario como indice. */

        indice = usuario.sofifa_id;
        vetor_medias[indice].count += 1;
        vetor_medias[indice].soma += usuario.rating; /* Insere as notas dos jogadores no vetor auxiliar. */
    }

    for (int i = 0; i < TOTALSOFIFAID; i++) /* Atualiza o vetor auxiliar, calculando todas as medias de pontuacoes dos jogadores. */
        if (vetor_medias[i].count != 0)
            vetor_medias[i].media = (vetor_medias[i].soma) / (vetor_medias[i].count);

    fclose(arq2); /* Fechamento do arquivo rating.csv. */
}

/* Funcao para indexar os dados do arquivo tags.csv em uma tabela hash. */
void analisa_arquivo_tags(PONT_TAG **tabela_tags, PONT_TAG **tabela_tags2)
{
    int i,j,indice;

    FILE *arq3;

    char linha[DIMENSAO];
    char aux[DIMENSAO];

    INFO dados;

    for (int i = 0; i < TOTALTAGS; i++)
        tabela_tags[i] = inicializa();

    for (int i = 0; i < TOTALJOGADORES; i++)
        tabela_tags2[i] = inicializa();

    if (!(arq3 = fopen("tags.csv","r"))) /* Abertura do arquivo tags.csv, com controle dos casos em que nao e possivel abri-lo. */
    {
        printf("\nErro na abertura do arquivo tags.csv. Fim do programa.\n");
        getch();
        exit(1); /* Encerra a execucao do programa, retornando 1. */
    }

    fgets(linha,DIMENSAO,arq3); /* Pula a primeira linha do arquivo texto. */

    while (!feof(arq3)) /* Iteracao para percorrer o arquivo texto do inicio ao fim. */
    {
        i = 0;
        j = 0;

        memset(linha, 0, sizeof(linha));
        memset(aux, 0, sizeof(aux));

        fgets(linha,DIMENSAO,arq3);

        while (linha[i] != ',') /* Obtem a informacao do ID do usuario. */
        {
            aux[j] = linha[i];
            i++;
            j++;
        }

        strcpy(dados.user_id,aux);
        memset(aux, 0, sizeof(aux));
        i++;
        j = 0;

        while (linha[i] != ',') /* Obtem a informacao do ID do jogador. */
        {
            aux[j] = linha[i];
            i++;
            j++;
        }

        strcpy(dados.sofifa_id, aux);
        memset(aux, 0, sizeof(aux));
        i++;
        j = 0;

        while (linha[i] != '\0' && linha[i] != '\n') /* Obtem a informacao da tag atribuida pelo usuario ao jogador. */
        {
            aux[j] = linha[i];
            i++;
            j++;
        }

        strcpy(dados.tag,aux);

        indice = hash(dados.tag,TOTALTAGS);
        tabela_tags[indice] = insereInicioTag(tabela_tags[indice],dados); /* Insere os dados obtidos na tabela hash. */
        indice = hash(dados.sofifa_id,TOTALJOGADORES);
        tabela_tags2[indice] = insereInicioTag(tabela_tags2[indice],dados); /* Insere os dados obtidos na tabela hash. */
    }

    fclose(arq3); /* Fechamento do arquivo tags.csv. */
}

void bubblesortStruct(COMANDO2 v[], int dimensao) /* Realiza a ordenacao de jogadores com base no seu rating em ordem decrescente. */
{
    int i, j;

    COMANDO2 aux;

    for (i = 0; i < dimensao; i++)
        for (j = 0; j < dimensao-i-1; j++)
        {
            if (v[j].rating < v[j+1].rating)
            {
                aux = v[j];
                v[j] = v[j+1];
                v[j+1] = aux;
            }
        }
}

void swapStruct (COMANDOS134 v[], int i, int j) /* Funcao auxiliar da ordenacao decrescente com base no rating global dos jogadores, com quick sort. */
{
    COMANDOS134 aux = v[i];
    v[i] = v[j];
    v[j] = aux;
}

int pHoareStructDec(COMANDOS134 v[], int p, int r) /* Funcao auxiliar da ordenacao decrescente com base no rating global dos jogadores, com quick sort. */
{
    COMANDOS134 pivot = v[p]; /* Seleciona o primeiro elemento do vetor como pivo da ordenacao. */
    int i = p - 1, j = r + 1;

    while (1)
    {
        do
        {
            i++;

        } while (v[i].global_rating > pivot.global_rating);

        do
        {
            j--;

        } while (v[j].global_rating < pivot.global_rating);

        if (i >= j)
            return j;

        swapStruct(v, i, j);
    }
}

void quickSortStructDec(COMANDOS134 v[], int p, int r)  /* Realiza a ordenacao de jogadores com base no seu rating em ordem decrescente. */
{
    if (p < r)
    {
        int posicao = pHoareStructDec(v, p, r);
        quickSortStructDec(v, p, posicao);
        quickSortStructDec(v, posicao+1, r);
    }
}

int pHoareStructCresc(COMANDOS134 v[], int p, int r) /* Funcao auxiliar da ordenacao decrescente com base no rating global dos jogadores, com quick sort. */
{
    COMANDOS134 pivot = v[p]; /* Seleciona o primeiro elemento do vetor como pivo da ordenacao. */
    int i = p - 1, j = r + 1;

    while (1)
    {
        do
        {
            i++;

        } while (v[i].global_rating < pivot.global_rating);

        do
        {
            j--;

        } while (v[j].global_rating > pivot.global_rating);

        if (i >= j)
            return j;

        swapStruct(v, i, j);
    }
}

void quickSortStructCresc(COMANDOS134 v[], int p, int r)  /* Realiza a ordenacao de jogadores com base no seu rating em ordem decrescente. */
{
    if (p < r)
    {
        int posicao = pHoareStructCresc(v, p, r);
        quickSortStructCresc(v, p, posicao);
        quickSortStructCresc(v, posicao+1, r);
    }
}

void swapInt (int v[], int i, int j) /* Funcao auxiliar da ordenacao crescente com base no ID dos jogadores, com quick sort. */
{
    int aux = v[i];
    v[i] = v[j];
    v[j] = aux;
}

int pHoareInt(int v[], int p, int r) /* Funcao auxiliar da ordenacao crescente com base no ID dos jogadores, com quick sort. */
{
    int pivot = v[p]; /* Seleciona o primeiro elemento do vetor como pivo da ordenacao. */
    int i = p - 1, j = r + 1;

    while (1)
    {
        do
        {
            i++;

        } while (v[i] < pivot);

        do
        {
            j--;

        } while (v[j] > pivot);

        if (i >= j)
            return j;

        swapInt(v, i, j);
    }
}

void quickSortInt(int v[], int p, int r) /* Realiza a ordenacao de jogadores com base no seu ID em ordem crescente. */
{
    if (p < r)
    {
        int posicao = pHoareInt(v, p, r);
        quickSortInt(v, p, posicao);
        quickSortInt(v, posicao+1, r);
    }
}

/* Funcao para imprimir os nomes dos jogadores pesquisados, junto com suas informacoes. */
void mostra_player(char *nome, PONT_PLAYER **tabela_players1, JOGADORES *vetor_medias)
{
    PONT_PLAYER *ptaux;
    int indice = hash(nome,TOTALJOGADORES), indice2;

    for (ptaux = tabela_players1[indice]; ptaux != NULL; ptaux = ptaux->prox) /* Iteracao para procurar o nome na tabela hash. */
    {
        if (strcmp(ptaux->jogador.playername,nome)==0)
        {
            indice2 = atoi(ptaux->jogador.sofifa_id);

            printf("%9d\t%s",atoi(ptaux->jogador.sofifa_id),ptaux->jogador.positions);

            if (strlen(ptaux->jogador.positions) < PEQUENOIMPRESSAO)
                printf("\t");

            printf("\t\t%6.6f\t%5d\t\t%s\n",vetor_medias[indice2].media,vetor_medias[indice2].count,ptaux->jogador.playername);

            break;
        }
    }
}

void copia_down(PONT_LETRA *raiz, char *str, int i) /* Funcao para copiar os caracteres a partir de uma raiz para uma string. */
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
void imprime_recursiva(PONT_LETRA *raiz, char *pref, char *str, int root, char *nome, PONT_PLAYER **tabela_players1, JOGADORES *vetor_medias)
{
	PONT_LETRA *ptaux = raiz;
    PONT_LETRA *ptaux2; /* Ponteiros auxiliares para percorrer a arvore trie. */
	char straux[2] = {0}; /* String auxiliar com um caractere. */
	char str2[DIMENSAO] = {0}; /* String para chamar nas recursoes. */
    char nome2[DIMENSAO] = {0};
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
void imprime_prefixo(PONT_LETRA *raiz, char *pref, PONT_PLAYER **tabela_players1, JOGADORES *vetor_medias)
{
	PONT_LETRA *ptaux = raiz;
	int i = 0;
	int achou = 0;
	char empty[DIMENSAO] = {0}; /* Strings vazias para chamar na recursao */
    char nome[DIMENSAO] = {0};

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

/* Funcao para analisar o comando digitado pelo usuario, para utilizar o comando player. */
void analisa_player(char *comando, PONT_LETRA *raiz, PONT_PLAYER **tabela_players1, JOGADORES *vetor_medias)
{
    char prefixo[DIMENSAO];
    int j = 0;

    for (int i = 7; comando[i] != '\0'; i++) /* Obtem o prefixo digitado pelo usuario a partir do comando. */
    {
        prefixo[j] = comando[i];
        j++;
    }

    prefixo[j] = '\0';

    imprime_prefixo(raiz, prefixo, tabela_players1,vetor_medias); /* Impressao dos jogadores que correspondem ao prefixo. */
}

void mostra_userID(COMANDO2 *informacoes, int dimensao_vetor) /* Impressao dos dados relacionados ao uso do comando user na tela. */
{
    printf("\nsofifa_id\tglobal_rating\t\tcount\t\trating\t\tname\n\n");

    for (int i = 0; i < USERJOGADORESMAX && i < dimensao_vetor; i++)
    {
        printf("%9d\t%13.6f\t\t%5d",informacoes[i].sofifa_id,informacoes[i].global_rating,informacoes[i].count);
        printf("\t\t%6.1f\t\t%s\n",informacoes[i].rating,informacoes[i].name);
    }
}

int controle_userID(char *comando) /* Funcao para analisar o comando digitado pelo usuario, para utilizar o comando user. */
{
    char aux[TAMANHONUMERO];
    int count = 0;
    int user_id;

    for (int i = 0; comando[i] != '\0'; i++) /* Obtem o ID do usuario. */
    {
        if (count > TAMANHONUMERO-1) /* Controle dos casos em que o ID do usuario e inserido incorretamente. */
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

    if (user_id >= TOTALUSERS || user_id <= 0) /* Controle dos casos em que o ID do usuario e inserido incorretamente. */
    {
        printf("\nID de usuario mal inserido.\n");
        return 0;
    }

    return user_id; /* Retorna o id do usuario. */
}

/* Realiza a adequacao das informacoes a serem impressas com o comando user. */
void comando_userID(char *comando, PONT_PLAYER **tabela_players2,PONT_USER **tabela_rating, JOGADORES *vetor_medias)
{
    COMANDO2 *informacoes;

    PONT_USER *ptaux;
    PONT_PLAYER *ptaux2;

    int indice, i, aux_sofifaid = 0, dimensao_vetor = 0;

    char indice_aux[TAMANHOAUX];

    int user_id = controle_userID(comando);

    if (user_id == 0) /* Controle dos casos em que o ID do usuario e mal inserido. */
        return;

    for (ptaux = tabela_rating[user_id]; ptaux != NULL; ptaux = ptaux->prox) /* Determina quantas posicoes o vetor de informacoes devera ter. */
        dimensao_vetor++;

    informacoes = calloc(dimensao_vetor,sizeof(COMANDO2));

    for (ptaux = tabela_rating[user_id],i = 0; ptaux != NULL; ptaux = ptaux->prox, i++) /* Iteracao para percorrer as tabelas e obter as informacoes a serem impressas. */
    {
        informacoes[i].sofifa_id = ptaux->usuario.sofifa_id; /* Armazena a informacao do ID do jogador a ser impresso. */
        informacoes[i].rating = ptaux->usuario.rating; /* Armazena a informacao do rating do jogador a ser impresso. */

        informacoes[i].global_rating = vetor_medias[ptaux->usuario.sofifa_id].media; /* Armazena a informacao do rating global do jogador a ser impresso. */
        informacoes[i].count = vetor_medias[ptaux->usuario.sofifa_id].count; /* Armazena a informacao da quantidade de avaliacoes do jogadore a ser impressa. */

        itoa(informacoes[i].sofifa_id,indice_aux,10);

        indice = hash(indice_aux,TOTALJOGADORES);

        for (ptaux2 = tabela_players2[indice]; ptaux2 != NULL; ptaux2 = ptaux2->prox) /* Realiza uma busca intermediaria pelo nome do jogador na outra tabela hash. */
        {
            aux_sofifaid = atoi(ptaux2->jogador.sofifa_id);

            if (informacoes[i].sofifa_id == aux_sofifaid)
            {
                strcpy(informacoes[i].name,ptaux2->jogador.playername);
                break;
            }
        }
    }

    bubblesortStruct(informacoes,dimensao_vetor); /* Ordena os ratings dos jogadores em ordem decrescente. */
    mostra_userID(informacoes, dimensao_vetor); /* Imprime as informacoes na tela, apos a ordenacao. */
    free(informacoes);
}

/* Impressao dos dados relacionados ao uso do comando top e do comando down na tela. */
void mostra_topdown(COMANDOS134 *informacoes, int dimensao_vetor, int N)
{
    int count = 0;

    printf("\nsofifa_id\tplayer_positions\t  rating\tcount\t\tname\n\n");

    for (int i = 0; i < dimensao_vetor; i++)
    {
        if (count >= N)
            break;

        if (informacoes[i].count >= MINIMOAVALIACOES) /* Verifica se o jogador tem pelo menos mil avaliacoes computadas, para ser impresso na tela. */
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
void comando_top(char *position, int N, PONT_PLAYER **tabela_players3, PONT_PLAYER **tabela_players2, JOGADORES *vetor_medias)
{
    COMANDOS134 *informacoes;
    int indice = hash(position,TOTALPOSITIONS);
    int indice2;
    int dimensao_vetor = 0;

    int i = 0;

    PONT_PLAYER *ptaux;
    PONT_PLAYER *ptaux2;

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

    informacoes = calloc(dimensao_vetor,sizeof(COMANDOS134));

    for (ptaux = tabela_players3[indice]; ptaux != NULL; ptaux = ptaux->prox) /* Iteracao para percorrer as tabelas e obter as informacoes a serem impressas. */
    {
        if (strstr(ptaux->jogador.positions,position))
        {
            informacoes[i].sofifa_id = atoi(ptaux->jogador.sofifa_id); /* Armazena a informacao do ID do jogador a ser impresso. */
            strcpy(informacoes[i].player_positions,ptaux->jogador.positions); /* Armazena das posicoes do jogador a serem impressas. */

            indice2 = atoi(ptaux->jogador.sofifa_id);

            informacoes[i].global_rating = vetor_medias[indice2].media; /* Armazena a informacao do rating global do jogador a ser impresso. */
            informacoes[i].count = vetor_medias[indice2].count;  /* Armazena a informacao da quantidade de avaliacoes do jogadore a ser impressa. */

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

    quickSortStructDec(informacoes,0,dimensao_vetor-1); /* Realiza a ordenacao dos jogadores em ordem decrescente, com base nos seus ratings globais. */
    mostra_topdown(informacoes,dimensao_vetor,N); /* Imprime as informacoes na tela, apos a ordenacao. */
    free(informacoes);
}

/* Funcao para analisar o comando digitado pelo usuario, para utilizar o comando top. */
void controla_top (char *comando,PONT_PLAYER **tabela_players3, PONT_PLAYER **tabela_players2, JOGADORES *vetor_medias)
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

    comando_top(posicao, N, tabela_players3, tabela_players2, vetor_medias); /* Realiza a adequacao das informacoes a serem impressas com o comando top. */
}

void mostra_tags(COMANDOS134 *informacoes, int intersecoes) /* Impressao dos dados relacionados ao uso do comando tags na tela. */
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
void comando_tags(PONT_PLAYER **tabela_players2,JOGADORES *vetor_medias,int **vetor_sofifas,int intersecoes, int quantidade_tags)
{
    COMANDOS134 *informacoes;
    PONT_PLAYER *ptaux;

    char indice_aux[TAMANHOAUX];
    int indice ,i=0,j=0, aux_sofifaid = 0;

    informacoes = calloc(intersecoes,sizeof(COMANDOS134));

    while (i < intersecoes)
    {
        itoa(vetor_sofifas[quantidade_tags][i],indice_aux,10);

        indice = hash(indice_aux,TOTALJOGADORES);

        for (ptaux = tabela_players2[indice]; ptaux != NULL; ptaux = ptaux->prox) /* Iteracao para armazenar os dados a serem impressos na tela. */
        {
            aux_sofifaid = atoi(ptaux->jogador.sofifa_id);

            if (vetor_sofifas[quantidade_tags][i] == aux_sofifaid)
            {
                informacoes[j].sofifa_id = atoi(ptaux->jogador.sofifa_id); /* Armazena a informacao referente ao ID do jogador. */
                strcpy(informacoes[j].name,ptaux->jogador.playername); /* Armazena a informacao referente ao nome do jogador. */
                strcpy(informacoes[j].player_positions,ptaux->jogador.positions); /* Armazena a informacao referente a posicao do jogador. */
                informacoes[j].global_rating = vetor_medias[aux_sofifaid].media; /* Armazena a informacao referente ao rating global do jogador. */
                informacoes[j].count = vetor_medias[aux_sofifaid].count; /* Armazena a informacao referente a quantidade de avaliacoes do jogador. */
                j++;
            }
        }

        i++;
    }

    mostra_tags(informacoes, intersecoes); /* Impressao dos dados relacionados ao uso do comando tags na tela. */
    free(informacoes);
}

/* Determina quantos jogadores estao associados a uma mesma tag simultaneamente. */
int calcula_interseccao(int **vetor_sofifas,int *quantidades,int indice_menor, int quantidade_tags)
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
void controla_tags(char *comando,PONT_PLAYER **tabela_players2, PONT_TAG **tabela_tags, JOGADORES *vetor_medias)
{
    char tag[DIMENSAO];

    int apostrofos = 0;
    int quantidade_tags;
    int i = 0, j = 0, m = 0, n = 0;
    int *quantidades;
    int **vetor_sofifas;
    int indice, total_IDS;
    char aux[TAMANHOPEQUENO];
    int intersecoes = 0, menor_quantidade = 0, indice_menor = 0;

    PONT_TAG *ptaux;

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
            comando_tags(tabela_players2,vetor_medias,vetor_sofifas,quantidades[0],0);

        else
        {
            for (i = 0; i < quantidade_tags; i++) /* Ordenada cada um dos vetores de ID's em ordem crescente, para otimizar a operacao de intersecao dos vetores. */
                quickSortInt(vetor_sofifas[i], 0, quantidades[i]-1);

            intersecoes = calcula_interseccao(vetor_sofifas,quantidades,indice_menor,quantidade_tags); /* Obtem o vetor com os ID's da intersecao, alem do numero total de intersecoes. */

            if (intersecoes == 0) /* Controle dos casos em que nenhum jogador corresponde a todas as tags simultaneamente. */
                printf("\nNenhum jogador corresponde a essas tags simultaneamente.\n");

            else
                comando_tags(tabela_players2,vetor_medias,vetor_sofifas,intersecoes,quantidade_tags); /* Realiza a adequacao das informacoes a serem impressas com o comando tags. */
        }
    }

    free(quantidades);

    for (i = 0; i < quantidade_tags+1; i++)
        free(vetor_sofifas[i]);

    free(vetor_sofifas);
}

/* Realiza a adequacao das informacoes a serem impressas com o comando down. */
void comando_down(char *position, int N, PONT_PLAYER **tabela_players3, PONT_PLAYER **tabela_players2, JOGADORES *vetor_medias)
{
    COMANDOS134 *informacoes;
    int indice = hash(position,TOTALPOSITIONS);
    int indice2;
    int dimensao_vetor = 0;

    int i = 0;

    PONT_PLAYER *ptaux;
    PONT_PLAYER *ptaux2;

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

    informacoes = calloc(dimensao_vetor,sizeof(COMANDOS134));

    for (ptaux = tabela_players3[indice]; ptaux != NULL; ptaux = ptaux->prox) /* Iteracao para percorrer as tabelas e obter as informacoes a serem impressas. */
    {
        if (strstr(ptaux->jogador.positions,position))
        {
            informacoes[i].sofifa_id = atoi(ptaux->jogador.sofifa_id); /* Armazena a informacao do ID do jogador a ser impresso. */
            strcpy(informacoes[i].player_positions,ptaux->jogador.positions); /* Armazena das posicoes do jogador a serem impressas. */

            indice2 = atoi(ptaux->jogador.sofifa_id);

            informacoes[i].global_rating = vetor_medias[indice2].media; /* Armazena a informacao do rating global do jogador a ser impresso. */
            informacoes[i].count = vetor_medias[indice2].count;  /* Armazena a informacao da quantidade de avaliacoes do jogadore a ser impressa. */

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
    mostra_topdown(informacoes,dimensao_vetor,N); /* Imprime as informacoes na tela, apos a ordenacao. */
    free(informacoes);
}

/* Funcao para analisar o comando digitado pelo usuario, para utilizar o comando down. */
void controla_down (char *comando,PONT_PLAYER **tabela_players3, PONT_PLAYER **tabela_players2, JOGADORES *vetor_medias)
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

    comando_down(posicao, N, tabela_players3, tabela_players2, vetor_medias); /* Realiza a adequacao das informacoes a serem impressas com o comando top. */
}

/* Funcao para obter e imprimir as informacoes do jogador da tabela hash. */
void mostra_playerID(char *playerid, COMANDO6 *informacoes_users, PONT_PLAYER **tabela_players2, JOGADORES *vetor_medias)
{
    int indice,indice2;
    PONT_PLAYER *ptaux;

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

            printf("\t\t%f\t%5d\t\t%s\n",vetor_medias[indice2].media,vetor_medias[indice2].count,ptaux->jogador.playername);

            break;
        }
    }
}

/* Funcao para obter e imprimir as informacoes dos usuarios da tabela hash. */
void mostra_playerID2(char *playerid, COMANDO6 *informacoes_users, PONT_TAG **tabela_tags2, int dimensao_vetor)
{
    PONT_TAG *ptaux;
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
void comando_id(char *comando,PONT_PLAYER **tabela_players2,PONT_TAG **tabela_tags2,JOGADORES *vetor_medias)
{
    char playerid[TAMANHOPEQUENO];
    int i = 0, j = 0, indice, indice2;
    PONT_PLAYER *ptaux;
    PONT_TAG *ptaux2;
    int dimensao_vetor = 0, aux_userid = 0;
    COMANDO6 *informacoes_users;

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

    informacoes_users = calloc(dimensao_vetor,sizeof(COMANDO6));

    mostra_playerID(playerid,informacoes_users,tabela_players2,vetor_medias); /* Obtem e imprime as informacoes do jogador da tabela hash. */
    mostra_playerID2(playerid,informacoes_users,tabela_tags2,dimensao_vetor); /* Obtem e imprime as informacoes dos usuarios da tabela hash. */

    free(informacoes_users);
}

int analisa_comando(char *comando) /* Analisa qual comando sera utilizado pelo programa, com base no que foi digitado pelo usuario. */
{
    int i = 0;
    char comando_lower[DIMENSAO];

    for(i = 0; comando[i] != '\0'; i++)
        comando_lower[i] = tolower(comando[i]);

    comando_lower[i] = '\0';

    if (strncmp(comando_lower,"player ",7) == 0)
        return 1; /* Retorna o numero correspondente ao comando player. */

    else if (strncmp(comando_lower,"user ",5) == 0)
    {
        if (!isdigit(comando[5]))
            return 0; /* Retorna o numero que representa um comando invalido. */

        else
            return 2; /* Retorna o numero correspondente ao comando user. */
    }

    else if (strncmp(comando_lower,"top",3) == 0)
    {
        if (!isdigit(comando[3]))
            return 0; /* Retorna o numero que representa um comando invalido. */

        else
            return 3; /* Retorna o numero correspondente ao comando top. */
    }

    else if (strncmp(comando_lower,"tags ",5) == 0)
        return 4; /* Retorna o numero correspondente ao comando tags. */

    else if (strncmp(comando_lower,"down",4) == 0)
    {
        if (!isdigit(comando[4]))
            return 0; /* Retorna o numero que representa um comando invalido. */

        else
            return 5; /* Retorna o numero correspondente ao comando down. */
    }

    else if (strncmp(comando_lower,"id ",3) == 0)
        return 6; /* Retorna o numero correspondente ao comando id. */

    else if (strcmp(comando_lower,"help") == 0)
        return 7; /* Retorna o numero correspondente ao comando help. */

    else if (strcmp(comando_lower,"info")==0)
        return 8; /* Retorna o numero correspondente ao comando positions. */

    else if (strcmp(comando_lower,"exit") == 0)
        return 9; /* Retorna o numero correspondente ao comando exit. */

    else
        return 0; /* Retorna o numero que representa um comando invalido. */
}

void menu() /* Funcao para realizar a impressao do menu principal do programa na tela. */
{
    printf("\t\t\t\t   CLASSIFICACAO E PESQUISA DE DADOS\n");

    printf("\t\t\t\t\tTRABALHO FINAL - 2021/1\n\n");

    printf("Andrei Pochmann Koenich - 00308680\n");

    printf("Pedro Company Beck      - 00324055\n");

    printf("\n----------------------------------------------------------------------------------------------------\n");

    printf("\nInsira o comando de pesquisa e pressione ENTER para iniciar a busca:\n");

    printf("\n>");

    printf("\n\nDigite 'help' para ver uma lista de comandos de busca.\n");
    printf("Digite 'info' para ver uma lista de posicoes de jogo.\n");
    printf("Digite 'exit' para encerrar a execucao do programa.\n");
}

void menu_help() /* Funcao para realizar a impressao do menu de ajuda do programa na tela. */
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

void menu_positions() /* Funcao para realizar a impressao do menu da lista de posicoes do programa na tela. */
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

void inicia_programa() /* Funcao para carregar as estruturas de pesquisa do programa e iniciar a sua execucao. */
{
    int numero_comando = 0;

    char tecla;
    char comando[DIMENSAO];

    printf("Carregando...");

    PONT_LETRA *raiz = inicializa(); /* Inicializa a raiz da arvore trie, para receber os nomes dos jogadores. */

    PONT_PLAYER **tabela_players1 = calloc(TOTALJOGADORES,sizeof(PONT_PLAYER*));  /* Tabela hash para indexacao do arquivo players.csv usando o nome do jogador como referencia de indice. */
    PONT_PLAYER **tabela_players2 = calloc(TOTALJOGADORES,sizeof(PONT_PLAYER*));  /* Tabela hash para indexacao do arquivo players.csv usando o ID do jogador como referencia de indice. */
    PONT_PLAYER **tabela_players3 = calloc(TOTALPOSITIONS,sizeof(PONT_PLAYER*));  /* Tabela hash para indexacao do arquivo players.csv usando a posicao do jogador como referencia de indice. */

    PONT_USER **tabela_rating = calloc(TOTALUSERS,sizeof(PONT_USER*)); /* Tabela hash para indexacao do arquivo rating.csv usando o ID do usuario como referencia de indice. */

    JOGADORES *vetor_medias = calloc(TOTALSOFIFAID,sizeof(JOGADORES)); /* Vetor auxiliar contendo as pontuacoes dos jogadores (avaliacoes parciais, total de avaliacoes e media de avaliacoes). */

    PONT_TAG **tabela_tags = calloc(TOTALTAGS,sizeof(PONT_TAG*)); /* Tabela hash para indexacao do arquivo tags.csv usando a tag do jogador como referencia de indice. */
    PONT_TAG **tabela_tags2 = calloc(TOTALJOGADORES,sizeof(PONT_TAG*)); /* Tabela hash para indexacao do arquivo tags.csv usando o ID do jogador como referencia de indice. */

    analisa_arquivo_players(tabela_players1,tabela_players2,tabela_players3, &raiz); /* Indexacao do arquivo players.csv nas tabelas hash. */
    analisa_arquivo_rating(tabela_rating, vetor_medias); /* Indexacao do arquivo players.csv na tabela hash e no vetor de pontuacoes dos jogadores. */
    analisa_arquivo_tags(tabela_tags,tabela_tags2); /* Indexacao do arquivo tags.csv nas tabelas hash. */

    system("cls");

    do /* Executa o programa enquanto o usuario nao digitar 'exit' ou pressionar a tecla ESC. */
    {
        menu(); /* Impressao do menu principal da tela. */

        gotoxy(2,11); /* Atualiza a posicao do cursor para facilitar a visualizacao da tela. */

        gets(comando);

        numero_comando = analisa_comando(comando); /* Determina o numero do comando a ser utilizado pelo programa. */

        system("cls");

        printf("Pressione ESC para encerrar a execucao do programa, ou qualquer outra tecla para continuar as consultas.\n");

        if (numero_comando != 7 && numero_comando != 8)
            printf("\nCOMANDO INSERIDO:\n%s\n",comando);

        switch(numero_comando) /* Faz a chamada da funcao correspondente ao comando, dependendo do que foi digitado pelo usuario. */
        {
            case 0:
                printf("\nComando invalido.\n"); /* Informa ao usuario que o comando digitado e invalido. */
                break;

            case 1:
                analisa_player(comando,raiz,tabela_players1,vetor_medias); /* Executa o comando player. */
                break;

            case 2:
                comando_userID(comando,tabela_players2,tabela_rating,vetor_medias); /* Executa o comando user. */
                break;

            case 3:
                controla_top(comando,tabela_players3,tabela_players2,vetor_medias); /* Executa o comando top. */
                break;

            case 4:
                controla_tags(comando,tabela_players2,tabela_tags,vetor_medias); /* Executa o comando tags */
                break;

            case 5:
                controla_down(comando,tabela_players3,tabela_players2,vetor_medias); /* Executa o comando down. */
                break;

            case 6:
                comando_id(comando,tabela_players2,tabela_tags2,vetor_medias); /* Executa o comando id. */
                break;

            case 7:
                menu_help(); /* Mostra o menu de ajuda ao usuario. */
                break;

            case 8:
                menu_positions(); /* Mostra a lista de posicoes de jogo ao usuario. */
                break;

            case 9:
                system("cls");
                exit(0); /* Encerra a execucao do programa, retornando zero. */
                break;
        }

        gotoxy(105,1); /* Atualiza a posicao do cursor para facilitar a visualizacao da tela. */

        tecla = getch(); /* Armazena a tecla digitada pelo usuario, para decidir entre continuar ou terminar o programa. */
        system("cls");

    } while (tecla != ESC);
}

int main ()
{
    inicia_programa(); /* Inicia as operacoes de indexacao e de consulta do programa. */

    return 0; /* Retorna zero, indicando que a execucao do programa foi bem-sucedida. */
}
