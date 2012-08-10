#include <stdio.h>
#include <stdlib.h>

typedef struct Stack_ {
  int value;
  struct Stack_ *next;
  struct Stack_ *previous;
} Stack;

Stack *last;

Stack *initStack() {
  Stack *stack = malloc(sizeof(Stack));
  last = stack;
  return stack;
};

void push(Stack *stack, int value) {
  last->next = malloc(sizeof(Stack));
  last->next->previous = last;
  last = last->next;
  last->next = NULL;
  last->value = value;
};


int isEmpty(Stack *stack) {
  return last == stack;
};

int pop(Stack *stack) {
  if(last == stack)
    return 0;
  int value = last->value;
  Stack *stackToPop = last;
  last = last->previous;
  last->next = NULL;
  free(stackToPop);
  return value;
};

int main(void) {
  Stack *stack = initStack();
  int i;
  for(i=0; i!=10; i++) {
    push(stack, i);
  }
 
  for(i=0; i!=10; i++) {
    printf("%d\n",pop(stack));
  }
 
  return 0;
}
