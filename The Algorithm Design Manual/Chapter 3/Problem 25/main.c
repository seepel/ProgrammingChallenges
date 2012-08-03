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

int hasLoop(Node *list, int loopSize) {
  Node *check = list;
  while(list != NULL && check != NULL) {
    int i=0;
    for(i=0; i!=2; i++) {
      if(check->next == NULL) return 0;
      check = check->next;
      printf("%d == %d\n", list->value, check->value);
      if(check == list) return 1;
    }
    list = list->next;
  }
  return 0;
};


Node *findLoop(Node *list) {
  int i,j;
  Node *start = list;
  int loopSize = 1;
  while(start != NULL) {
    start = list;
    for(i=0; i!=loopSize; i++) {
      Node *check = start;
      for(j=0; j!=loopSize; j++) {
        check = check->next;
        if(check == NULL)
          return NULL;
      }
      if(start == check) return check;
      start = start->next;
    }
    loopSize++;
  }
  return NULL;
}

int main(void) {
  Node *list = malloc(sizeof(Node));
  list->value = 0;
  list->next = NULL;
  int i;
  Node *loop;
  for(i=1; i!=10; i++) {
    Node *node = malloc(sizeof(Node));
    node->value = i;
    node->next = NULL;
    append(list, node);
    if(i == 9)
      loop = node;
  }
  append(list, loop);

  Node *find = findLoop(list);
  if(find != NULL)
    printf("%d\n", find->value);

  return 0;
}
