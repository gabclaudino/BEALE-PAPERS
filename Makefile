CFLAGS = -std=c99

.PHONY : clean

all: beale

beale: beale.o codifica.o cria_chaves.o decodifica_ac.o decodifica_lc.o fila.o
	gcc $(CFLAGS) beale.o codifica.o cria_chaves.o decodifica_ac.o decodifica_lc.o fila.o -o beale
	
beale.o: beale.c funcs.h
	gcc -c beale.c -o beale.o
	
codifica.o: codifica.c funcs.h
	gcc -c codifica.c -o codifica.o
	
cria_chaves.o: cria_chaves.c funcs.h
	gcc -c cria_chaves.c -o cria_chaves.o
	
decodifica_ac.o: decodifica_ac.c funcs.h
	gcc -c decodifica_ac.c -o decodifica_ac.o
	
decodifica_lc.o: decodifica_lc.c funcs.h
	gcc -c decodifica_lc.c -o decodifica_lc.o
	
fila.o: fila.c funcs.h
	gcc -c fila.c -o fila.o
	
clean:
	rm -f *.o
	
purge: clean
	rm -f beale