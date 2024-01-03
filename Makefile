CC     = gcc
CFLAGS = -std=c11
LFLAGS = -Wall

PROG = seqDNA
OBJ = lista.o grafo.o euleriano.o spectrum.o $(PROG).o


.PHONY: clean purge all

%.o: %.c lista.h grafo.h euleriano.h spectrum.h
	$(CC) -c $(CFLAGS) $<

$(PROG): $(OBJ)
	$(CC) -o $@ $^ $(LFLAGS)

clean:
	@rm -f *~ *.bak

purge:   clean
	@rm -rf bin obj *.layout *.depend
	@rm -f *.dat *.o core a.out
	@rm -f $(PROG)
