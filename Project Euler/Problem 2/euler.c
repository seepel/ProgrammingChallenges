#include <stdio.h>
#include <stdlib.h>


int nextFibonnaci(int previous, int current) {
  return previous + current;
}

int naiveFibonacciSum(int max) {
  int previous = 0;
  int current = 1;
  int sum = 0;
  int tmp = 0;
  while(current < max) {
    tmp = nextFibonnaci(previous, current);
    if(tmp > max) break;
    previous = current;
    current = tmp;
    if(current % 2 == 0) {
      printf("%d ", current);
      sum += current;
    }
  }
  return sum;
}

int nextFibonacciPair(int *fibonacciPair) {
/* Every third number is even.
   Example of reasoning...
   x, y, x + y, Initial value
   x + 2y, 2x + 3y, 3x + 5y, start: 1,1 -> 1 + 1 + 1 = 3 : 1 + 2 + 2 = 5
   5x + 8y, 8x + 13y, 13x + 21y start: 3,5 -> 3 + 5 + 5 = 13 : 5 + 8 + 8 = 21
*/
  int tmp = fibonacciPair[0] + fibonacciPair[1];
  fibonacciPair[0] += fibonacciPair[1] + fibonacciPair[1]; 
  fibonacciPair[1] += tmp + tmp;
  return fibonacciPair[0] + fibonacciPair[1];
};

int fastFibonacciSum(int max) {
  int fibonacciPair[2] = { 1, 1 };
  int sum = 2;
  int current = 2;
  while(current < max) {
    current = nextFibonacciPair(fibonacciPair);
    if(current > max) break;
    printf("%d ", current);
    sum += current;
  }
  return sum;
}

int main(int argc, char **argv) {
  int max = 4000000;
  if(argc > 1) {
    max = atoi(argv[1]);
  }
  printf("naive: %d\n", naiveFibonacciSum(max));
  printf("fast: %d\n", fastFibonacciSum(max));
  return 0;
}
