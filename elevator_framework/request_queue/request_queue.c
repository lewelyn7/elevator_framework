// C program for array implementation of queue
#include <limits.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define CAPACITY 16

enum elev_req_type{
    ORDER, TRANSPORT
};
typedef struct request{
    enum elev_req_type type;
    int from;
    int to;
    time_t timestamp;
    struct request * next; 
} request;

// A structure to represent a queue
struct request_queue {
    request * front;
    request * end;
    int size;
    unsigned capacity;
};
 
// function to create a queue
// of given capacity.
// It initializes size of queue as 0
int createQueue(struct request_queue *q)
{
    

    q->front = q->end = NULL;
    q->size = 0;
    q->capacity = CAPACITY;
    return 0;
}  
 
// Queue is full when size becomes
// equal to the capacity
int isFull(struct request_queue* queue)
{
    return (queue->size == queue->capacity);
}
 
// Queue is empty when size is 0
int isEmpty(struct request_queue* queue)
{
    return (queue->size == 0);
}
 
// Function to add an item to the queue.
// It changes rear and size

// The function to add a key k to q
// A utility function to create a new linked list node.
request* newNode(request * req)
{
    request* temp = (struct request*)malloc(sizeof(request));
    *temp = *req;
    temp->next = NULL;
    return temp;
}

int enqueue(struct request_queue* q, request * req)
{
    if(q->capacity <= q->size){
        return -2; // ERROR is full
    }

    request * temp = newNode(req);
    q->size++;
    // If queue is empty, then new node is front and rear both
    if (q->end == NULL) {
        q->front = q->end = temp;
        return 0;
    }
  
    // Add the new node at the end of queue and change rear
    q->end->next = temp;
    q->end = temp;
    return 0;
}

// int enqueue(struct request_queue* queue, const request *item)
// {
//     if (isFull(queue))
//         return -2;
//     queue->rear = (queue->rear + 1)
//                   % queue->capacity;
//     queue->array[queue->rear] = *item;
//     queue->size = queue->size + 1;
//     return 0;
// }
 
int dequeue(struct request_queue* q, request * req)
{
    // If queue is empty, return NULL.
    if (q->front == NULL)
        return -2;
  
    q->size--;
    // Store previous front and move front one node ahead
    request* temp = q->front;
    *req = *temp;
    q->front = q->front->next;
  
    // If front becomes NULL, then change rear also as NULL
    if (q->front == NULL)
        q->end = NULL;
  
    free(temp);
}


// Function to remove an item from queue.
// It changes front and size
// int dequeue(struct request_queue* queue, request * res)
// {
//     if(res == NULL){
//         return -1;
//     }
//     if (isEmpty(queue))
//         return -2;
//     request item = queue->array[queue->front];
//     queue->front = (queue->front + 1)
//                    % queue->capacity;
//     queue->size = queue->size - 1;
//     *res = item;
//     return 0;
// }
 
// Function to get front of queue
int front(struct request_queue* q, request * res)
{
    if(res == NULL){
        return -1;
    }    
    if (q->size == 0)
        return -2;

    *res = *(q->front);
    return 0;
}
 

 
