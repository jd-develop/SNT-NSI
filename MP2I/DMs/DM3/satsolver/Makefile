# Liste des exécutables
EXEC = satsolver fnc_solver

# Règle pour tout compiler
.PHONY: all
all: $(EXEC)

# Règle globale pour chaque exécutable
$(EXEC): %: %.ml
	ocamlopt $^ -o $@

# Règle pour la suppression des fichiers temporaires
.PHONY: clean
clean:
	rm -f $(EXEC:%=%.o)
	rm -f $(EXEC:%=%.cmi)
	rm -f $(EXEC:%=%.cmx)

# Règle pour la suppression des exécutables
.PHONY: mrproper
mrproper: clean
	rm -f $(EXEC)
