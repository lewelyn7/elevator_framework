// C program for array implementation of queue
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define QUEUE_SIZE 3  

typedef struct request{
    int from_floor;
} request;
// A structure to represent a queue
struct RequestQueue {
    int front, rear, size;
    unsigned capacity;
    request array[QUEUE_SIZE];
};
  
// function to create a queue
// of given capacity.
// It initializes size of queue as 0
void initQueue(struct RequestQueue * queue)
{

    queue->capacity = QUEUE_SIZE;
    queue->front = queue->size = 0;
    // This is important, see the enqueue
    queue->rear = QUEUE_SIZE - 1;
     
}
  
// Queue is full when size becomes
// equal to the capacity
bool isFull(struct RequestQueue* queue)
{
    return (queue->size == queue->capacity);
}
  
// Queue is empty when size is 0
bool isEmpty(struct RequestQueue* queue)
{
    return (queue->size == 0);
}
  
// Function to add an item to the queue.
// It changes rear and size
void enqueue(struct RequestQueue* queue, request item)
{
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1)
                  % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
}
  
// Function to remove an item from queue.
// It changes front and size
request dequeue(struct RequestQueue* queue)
{
    // if (isEmpty(queue))
    //     return INT_MIN;
    request item = queue->array[queue->front];
    queue->front = (queue->front + 1)
                   % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}
  
// Function to get front of queue
request front(struct RequestQueue* queue)
{
    // if (isEmpty(queue))
    //     return INT_MIN;
    return queue->array[queue->front];
}
  
// Function to get rear of queue
request rear(struct RequestQueue* queue)
{
    // if (isEmpty(queue))
    //     return request{from_floor=-1};
    return queue->array[queue->rear];
}
  

void print_queue(struct RequestQueue* queue){
    printf("%d,%d,%d", queue->size, queue->front, queue->rear);
    int end_arr = queue->rear;
    if(queue->rear < queue->front) end_arr = queue->capacity-1;
    if(queue->size > 0){

        for(int i = queue->front; i <= end_arr; i++){
            printf(",%d", queue->array[i].from_floor);
        }
        if(queue->rear < queue->front){
            for(int i = 0; i <= queue->rear; i++){
                printf(",%d", queue->array[i].from_floor);
            }        
        }

    }

    printf("\n");
}
// Driver program to test above functions./
// int main()
// {
//     struct RequestQueue* queue = createQueue(1000);
  
//     enqueue(queue, 10);
//     enqueue(queue, 20);
//     enqueue(queue, 30);
//     enqueue(queue, 40);
  

  
//     return 0;
// }