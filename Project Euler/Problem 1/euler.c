#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  int max = 1000;
  if(argc > 1) {
    max = atoi(argv[1]);
  }
  int i=0;
  int sum = 0;
  for(i=0; i!=max; i++) {
    if(i%3 == 0 || i%5 == 0) {
      sum += i;
      printf("%d ",i);
    }
  }
  printf("\n%d\n",sum);
  return 0;
}
