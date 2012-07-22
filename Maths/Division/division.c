#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int divide(int numerator, int denominator, int depth) {
  int quotient = 0;
  int negative = 1;
  if(numerator < 0 && denominator > 0) {
    negative = 1;
    numerator = -numerator;
  } else if(numerator > 0 && denominator < 0) {
    negative = 1;
    denominator = -denominator;
  } else if(numerator > 0 && denominator < 0) {
    numerator = -numerator;
    denominator = -denominator;
  }
  while(numerator >= denominator) {
    numerator -= denominator;
    quotient++; 
  }
  if(negative)
    quotient = -quotient;
  return quotient;
}

int main(int argc, char **argv) {
  if(argc < 3) {
    return 1;
  }
  int numerator = atoi(argv[1]);
  int denominator = atoi(argv[2]);
  printf("%d / %d = %d\n", numerator, denominator, divide(numerator, denominator, 0));
  printf("%d / %d = %d\n", numerator, denominator, numerator/denominator);
  return 0;
}
