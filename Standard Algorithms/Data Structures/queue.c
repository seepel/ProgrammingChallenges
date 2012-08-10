#include <stdio.h>
#include <stdlib.h>

struct Queue_ *last;
typedef struct Queue_ {
  int value;
  struct Queue_ *next;
} Queue;

Queue *initQueue() {
  Queue *queue = malloc(sizeof(Queue));
  last = queue;
  return queue;
};

int isEmpty(Queue *queue) {
  return last == queue;
};

void enqueue(Queue *queue, int value) {
  last->value = value;
  last->next = malloc(sizeof(Queue));
  last = last->next;
};

int dequeue(Queue *queue) {
  if(queue == last)
    return 0;
  int value = queue->value;
  if(queue->next == last)
    last = queue;
  Queue *next = queue->next;
  queue->value = next->value;
  queue->next = next->next;
  free(next);
  return value;
};



int main(void) {
  Queue *queue = initQueue();
  int i;
  for(i=0; i!=100000; i++) {
    enqueue(queue, i);
  }
  //for(i=0; i!=10; i++) {
  while(!isEmpty(queue)) {
    printf("%d\n",dequeue(queue));
  }
  return 0;
}
