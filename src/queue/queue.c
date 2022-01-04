
#include "queue.h"



queue *createQueue(int capacity)
{
    queue *q;
    q = (queue *) malloc(sizeof(queue));
    if (!q)
        return NULL;
    q->capacity = capacity;
    q->front = q->size = 0;

    /* This is important, see the push */
    q->rear = capacity - 1;
    q->data = (int*)malloc(
            q->capacity * sizeof(int));
    return q;
}

/* Queue is full when size becomes
  equal to the capacity */
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
void push(queue *queue, int item)
{
    int *tmp;
    if (!queue)
        return;
    if (isFull(queue)) {
        /* pokud je fronta plna, zvetsi se kapacita pole o dvojnasobek */
        tmp = (int *) realloc(queue->data, queue->capacity * 2);
        if (!tmp)
        {
            return;
        }
        queue->data = tmp;
    }

    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->data[queue->rear] = item;
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
    if (!queue)
        return INT_MIN;
    if (isEmpty(queue))
        return INT_MIN;
    return queue->data[queue->front];
}

/* Function to get rear of queue */
int rear(queue* queue)
{
    if (isEmpty(queue))
        return INT_MIN;
    return queue->data[queue->rear];
}


void free_queue(queue **poor) {
    if (!poor || !*poor)
        return;

    (*poor)->front = 0;
    (*poor)->capacity = 0;
    (*poor)->size = 0;
    (*poor)->rear = 0;

    free((*poor)->data);
    (*poor)->data = NULL;

    free(*poor);
    *poor = NULL;
}