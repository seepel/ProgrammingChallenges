#include <stdio.h>

void printSumOfFactors(int n) {
  int i;
  int sum = 1;
  for(i=2; i*i <= n; i++) {
    int count = 0;
    if(n % i == 0) count++;
    while(n % i == 0) {
      n /= i;
      count = count*i+1;
    }
    if(count > 1)
      sum *= count;
  }
  if(n > 1)
    sum *= (1 + n);
  printf("%d\n",sum);
}

int main(int argc, char **argv) {
    int max = 10;
  if(argc > 1) {
    max = atoi(argv[1]);
  }

  int i;
  for(i=2; i!=max; i++) {
    printf("%d: ", i);
    printSumOfFactors(i);
  }
  return 0;
}
