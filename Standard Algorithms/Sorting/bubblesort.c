#include <stdio.h>
int main(void) {
  int length = 6;
  int array[6] = {3, 6, 2, 5, 8, 4};
  int swapped = 1;
  while(swapped == 1) {
    swapped = 0;
    int i=0;
    for(i=1; i!=length; i++) {
      if(array[i-1] > array[i]) {
	int tmp = array[i-1];
	array[i-1] = array[i];
	array[i] = tmp;
	swapped = 1;
      }
    }
    if(swapped == 0)
      break;
  }
  int i = 0;
  for(i=0; i!=length; i++) {
    printf("%d ", array[i]);
  }
  printf("\n");
  return 0;
}
