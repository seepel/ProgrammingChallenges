#include <stdio.h>

void printNumberOfFactors(int n) {
  int i;
  int factors = 1;
  for(i=2; i*i <= n; i++) {
    int count = 0;
    if(n % i == 0) count++;
    while(n % i == 0) {
      n /= i;
      count++;
    }
    if(count > 1)
      factors *= count;
  }
  if(n > 1)
    factors *= 2;
  printf("%d\n",factors);
}

int main(int argc, char **argv) {
    int max = 10;
  if(argc > 1) {
    max = atoi(argv[1]);
  }

  int i;
  for(i=2; i!=max; i++) {
    printf("%d: ", i);
    printNumberOfFactors(i);
  }
  return 0;
}
