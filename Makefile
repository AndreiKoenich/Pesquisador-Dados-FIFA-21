# CLASSIFICAÇÃO E PESQUISA DE DADOS

# Autor: Andrei Pochmann Koenich

# Makefile

# Variáveis de flags de compilação e de diretórios
FLAGS := -g -fsanitize=address -o

FILES :=	Sources/main.c \
			Sources/analiseArquivos.c \
			Sources/execucaoComandos.c \
			Sources/arvoreTrie.c \
			Sources/auxiliares.c \
			Sources/listas.c \
			Sources/menu.c 

# Comando para linkar os arquivos compilados e gerar o executável
link: 
	gcc $(FLAGS) PesquisadorFIFA21 $(FILES)

# Comando padrão do Makefile
.DEFAULT_GOAL := link