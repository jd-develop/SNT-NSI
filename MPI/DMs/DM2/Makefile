all : uf_exemple tests_uf tests_laby 

uf.o : uf.c uf.h
	gcc -Wall -c uf.c -o uf.o

uf_exemple : uf_exemple.c uf.o
	gcc -Wall -g uf.o uf_exemple.c -o uf_exemple

tests_uf : tests_uf.c uf.o
	gcc -Wall -g tests_uf.c uf.o -o tests_uf
	
laby.o : laby.c laby.h uf.h
	gcc -Wall -g -c laby.c -o laby.o

tests_laby : tests_laby.c laby.o uf.o
	gcc -Wall -g tests_laby.c laby.o uf.o -o tests_laby

verif_valgrind_uf : tests_uf
	valgrind -v --leak-check=full ./tests_uf

verif_valgrind_laby : tests_laby
	valgrind -v --leak-check=full ./tests_laby

clean :
	rm -f *.o
	rm -f uf_exemple
	rm -f tests_uf
	rm -f tests_laby

