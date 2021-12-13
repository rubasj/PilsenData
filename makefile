# Makefile slouží jako návod pro sestavení aplikace.

# Název výsledného binárního souboru.
BIN = max_flow

# Použitý překladač a jeho argumenty, které jsou nám již povědomé.
# Díky přepínači -g (debug info) nám Valgrind dokáže říci místo vzniku memory leaku.
CC = gcc
CCFLAGS = -Wall -Wextra -pedantic -ansi -g

# Samotné návody na sestavení aplikace.
# Slinkování vytvořených modulů 
$(BIN): clean loader.o
	$(CC) edge.o matrix.o algorithm.o queue.o vector.o -o $(BIN) $(CCFLAGS)

# Návod na přeložení modulů.
loader.o: src/loader.c
	$(CC) -c src/loader.c $(CCFLAGS)

edge.o: src/edge/edge.c
	$(CC) -c src/edge/edge.c $(CCFLAGS)

matrix.o: src/matrix/matrix.c
	$(CC) -c src/matrix/matrix.c $(CCFLAGS)

algorithm.o: src/max_flow/algorithm.c
	$(CC) -c src/max_flow/algorithm.c $(CCFLAGS)

queue.o: src/queue/queue.c
	$(CC) -c src/queue/queue.c $(CCFLAGS)

vector.o: src/vector/vector.c
	$(CC) -c src/vector/vector.c $(CCFLAGS)
# Na linuxu je rm!
clean:
	del *.o $(BIN) -f