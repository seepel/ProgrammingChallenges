#include <stdio.h>

float seed(float number) {
  int tmp = number;
  int digits = 0;
  if(tmp > 1) {
    while(tmp > 0) {
      tmp /= 10;
      digits++;
    }
  }
  int n = 0;
  int factor = 0;
  if(digits % 2 == 0) {
    n = (digits - 2)/2;
    factor = 6;
  } else {
    n = (digits -1)/2;
    factor = 2;
  }
  int order = 1;
  while(n > 0) {
    order *= 10;
    n--;
  }
  return factor*order;
};

float squareRoot(float number, float precision) {
  float squareRoot = seed(number);
  float previousSquareRoot = number;
  while(previousSquareRoot - squareRoot > precision) {
    previousSquareRoot = squareRoot;
    squareRoot = 0.5*(squareRoot + number/squareRoot);
  }
  return squareRoot;
};

int main(void) {
  printf("%f",squareRoot(125348, 0.000000001));
  return 0;
}
