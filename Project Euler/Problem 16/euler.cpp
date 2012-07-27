#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <map>

using namespace std;

map<int, vector<int> > memoized;

vector<int> add(vector<int> number1, vector<int> number2) {
  vector<int> result;
  int remainder = 0;
  for(int i=0; i!=max(number1.size(), number2.size()); i++) {
    int sum = remainder;
    if(number1.size() > i)
      sum += number1[i];
    if(number2.size() > i)
      sum += number2[i];
    remainder = sum/10;
    sum -= remainder*10;
    result.push_back(sum);
  }
  while(remainder > 0) {
    if(remainder == 0) break;
    result.push_back(remainder - (remainder/10)*10);
    remainder /= 10;
  }
  return result;
};


vector<int> powerOf2(int n) {
  if(n == 1) { 
    vector<int> result(1,2);
    return result;
   }

  if(memoized.find(n) != memoized.end()) return memoized[n];

  vector<int> result = add(powerOf2(n-1), powerOf2(n-1));
  memoized[n] = result;
  return result;
}

int main(int argc, char **argv) {
  int max = 1000;
  if(argc > 1) {
    max = atoi(argv[1]);
  }

  vector<int> number = powerOf2(max);
  uint64_t sum = 0;
  for(int i=number.size()-1; i>= 0; i--) {
    sum += number[i];
    cout << number[i];
  }
  cout << endl;
  cout << sum << endl;

  return 0;
}
