CC = gcc

CFLAGS = -Wall -Wextra -pedantic -ansi
LDFLAGS = $(CFLAGS) -lm

BUILD_DIR = build
BIN = flow.exe

all: clean $(BUILD_DIR) $(BUILD_DIR)/$(BIN)

$(BUILD_DIR)/$(BIN): $(BUILD_DIR)/loader.o $(BUILD_DIR)/matrix.o $(BUILD_DIR)/edge.o $(BUILD_DIR)/algorithm.o $(BUILD_DIR)/queue.o $(BUILD_DIR)/vector.o
	$(CC) -o $@ $^ $(LDFLAGS)

# Návod na přeložení modulů.
$(BUILD_DIR)/loader.o: src/loader.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD_DIR)/edge.o: src/edge/edge.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD_DIR)/matrix.o: src/matrix/matrix.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD_DIR)/algorithm.o: src/max_flow/algorithm.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD_DIR)/queue.o: src/queue/queue.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD_DIR)/vector.o: src/vector/vector.c src/vector/vector.h
	$(CC) -c $(CFLAGS) -o $@ $<

#$(BUILD_DIR)/matrix.o: src/matrix/matrix.c src/matrix/matrix.h
#	$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD_DIR):
	mkdir $@
# Na linuxu je rm!
clean:
	del /F /Q $(BUILD_DIR)