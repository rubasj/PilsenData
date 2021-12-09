//
// Created by janru on 02.12.2021.
//

#ifndef PILSENDATA_QUEUE_H
#define PILSENDATA_QUEUE_H


#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct queue_ {
    int front, rear, size;
    int capacity;
    int* array;
} queue;

queue *createQueue(int capacity);
void push(queue* queue, int item);
void pop(queue* queue);
int isEmpty(const queue* queue);
int front(queue* queue);
int rear(queue* queue);
void free_queue(queue *queue);
#endif //PILSENDATA_QUEUE_H
