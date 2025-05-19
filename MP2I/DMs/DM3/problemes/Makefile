# Liste des exécutables
EXEC = n_dames maisons calendrier calendrier_n_pieces print_tab

# Compilateur et flags de compilation
CC = gcc
CFLAGS = -Wextra -Wall
CDEBUG = -g3 -Og
LDLIBS = -lm

debug ?= 0
ifeq ($(debug),1)
	ALLFLAGS = $(CDEBUG) $(CFLAGS) $(LDLIBS)
else
	ALLFLAGS = $(CFLAGS) $(LDLIBS)
endif

# Règle pour tout compiler
.PHONY: all
all: $(EXEC)

# Règle spécifique pour chaque exécutable
n_dames: utils.c utils.h
maisons: utils.c utils.h
calendrier: utils.c utils.h piece.c piece.h
calendrier_n_pieces: utils.c utils.h piece.c piece.h

# Règle globale pour chaque exécutable
$(EXEC): %: %.c
	$(CC) $^ $(ALLFLAGS) -o $@

# Règle pour la suppression des exécutables
.PHONY: mrproper
mrproper:
	rm -f $(EXEC)
