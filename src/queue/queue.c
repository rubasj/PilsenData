
#include "queue.h"



queue *createQueue(int capacity)
{
    queue *q;
    q = (queue *) malloc(sizeof(queue));
    q->capacity = capacity;
    q->front = q->size = 0;

    /* This is important, see the push */
    q->rear = capacity - 1;
    q->array = (int*)malloc(
            q->capacity * sizeof(int));
    return q;
}

/* Queue is full when size becomes
// equal to the capacity */
int isFull(queue* queue)
{
    return (queue->size == queue->capacity);
}

/* Queue is empty when size is 0 */
int isEmpty(const queue* queue)
{
    return (queue->size == 0);
}

/*Function to add an item to the queue.
 It changes rear and size */
void push(queue* queue, int item)
{
    if (isFull(queue)) {
        /* pokud je fronta plna, zvetsi se kapacita pole o dvojnasobek */
        queue->array = (int *) realloc(queue->array, queue->capacity * 2);
    }

    queue->rear = (queue->rear + 1)
                  % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
/*    printf("%d enqueued to queue\n", item); */
}

/* Function to remove an item from queue.
// It changes front and size */
void pop(queue* queue)
{

    if (isEmpty(queue))
        return;
    queue->front = (queue->front + 1)
                   % queue->capacity;
    queue->size = queue->size - 1;
}

/* Function to get front of queue */
int front(queue* queue)
{
    if (isEmpty(queue))
        return INT_MIN;
    return queue->array[queue->front];
}

/* Function to get rear of queue */
int rear(queue* queue)
{
    if (isEmpty(queue))
        return INT_MIN;
    return queue->array[queue->rear];
}


void free_queue(queue *queue) {

    free(queue->array);
    free(queue);
}