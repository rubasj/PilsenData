#ifndef PILSENDATA_QUEUE_H
#define PILSENDATA_QUEUE_H


#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct queue_ {
    int front, rear; /** index pro prvni prvek, koncovy, */
    int size; /* velikost fronty*/
    int capacity; /* kapacita (aktualni) */
    int *data; /* data */
} queue;

queue *createQueue(int capacity);
/**
 * Vlozeni prvku na konec fronty
 * @param queue fronta do ktere se to vlozi
 * @param item prvek pro ulozeni
 */
void push(queue* queue, int item);

/**
 * vyjmuti prvku z fronty
 * @param queue fronta
 */
void pop(queue* queue);

/**
 * Zjisteni zda je fronta plna
 * @param queue fronta
 * @return 0 - neni prazdna, 1 - je prazdna
 */
int isEmpty(const queue* queue);
/**
 * Zjisteni zda je fronta plna
 * @param queue fronta
 * @return 0 - neni plna, 1 - je plna
 */
int isFull(queue* queue);
/**
 * Zjisteni indexu, kde se nachazi prvni v poradi
 * @param queue fronta
 * @return vrati index, kde se v poli nachazi prvni prvek
 */
int front(queue* queue);

/**
 * Ziskani posledniho indexu, kde jsou data
 * @param queue fronta
 * @return index v poli, kde se nachazi posledni prvek
 */
int rear(queue* queue);

/**
 * Uvolneni fronty
 * @param poor fronta pro uvolneni pameti
 */
void free_queue(queue **poor);
#endif
