#include <stdio.h>
#include <stdlib.h>

typedef struct Node_ {
  int value;
  struct Node_ *next;
} Node;

void append(Node *list, Node *node) {
  if(list->next == NULL) {
    list->next = node;
    return;
  }
  append(list->next, node);
};

Node *reverse(Node *list, Node *previous) {
  Node *next = list->next;
  list->next = previous;
  if(next == NULL)
    return list;
  return reverse(next, list);
};

Node *reverseIter(Node *list) {
  Node *current = list;
  Node *previous = NULL;
  while(current->next != NULL) {
    Node *next = current->next;
    current->next = previous;
    previous = current;
    current = next;
  }
  current->next = previous;
  return current;
};


void print(Node *list) {
  printf("%d ", list->value);
  if(list->next != NULL)
    print(list->next);
};

int main(void) {
  Node *list = malloc(sizeof(Node));
  list->value = 0;
  list->next = NULL;
  int i;
  for(i=1; i!=10; i++) {
    Node *node = malloc(sizeof(Node));
    node->value = i;
    node->next = NULL;
    append(list, node);
  }

  print(list);
  printf("\n");

  list = reverse(list, NULL);
  print(list);
  printf("\n");

  list = reverseIter(list);
  print(list);
  printf("\n");

  return 0;
}
