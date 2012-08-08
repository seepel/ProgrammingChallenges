#include <stdio.h>
#include <stdlib.h>

#define HASHSIZE 997

typedef struct List_ {
  int key;
  int value;
  struct List_ *next;
} List;

List *initList(int key, int value) {
  List *list = malloc(sizeof(List));
  list->key = key;
  list->value = value;
  list->next = NULL;
  return list;
};

void append(List *list, int key, int value) {
  if(list->next == NULL) {
    list->next = initList(key, value);
    return;
  }
  append(list->next, key, value);
};

typedef struct HashTable_ {
  List *data[HASHSIZE];
} HashTable;

HashTable *initHashTable() {
  HashTable *hashTable = malloc(sizeof(HashTable));
  int i;
  for(i=0; i!=HASHSIZE; i++) {
    hashTable->data[i] = NULL;
  }
  return hashTable;
};

int hash(int key) {
  return key % HASHSIZE;
};

void insert(HashTable *hashTable, int key, int value) {
  List *list = hashTable->data[hash(key)];
  if(list == NULL) {
    list = initList(key, value);
    hashTable->data[hash(key)] = list;
    return;
  }
  append(hashTable->data[hash(key)], key, value);
};

int lookup(HashTable *hashTable, int key) {
  List *list = hashTable->data[hash(key)];
  if(list == NULL)
    return -1;
  while(list->key != key) {
    if(list->next == NULL) {
      return -1;
    }
    list = list->next;
  }
  return list->value;
};

int main(void) {

  HashTable *hashTable = initHashTable();
  int i=0;
  for(i=1; i != 10000; i++) {
    insert(hashTable,  i, i);
  }

  for(i=0; i != 10000; i++) {
    printf("%d\n", lookup(hashTable, i));
  }

  return 0;
}
