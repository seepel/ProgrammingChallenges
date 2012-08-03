#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

void printNumber(vector<int> number) {
  for(int i=number.size()-1; i>=0; i--) {
    cout << number[i];
  }
}

vector<int> makeNumber(int number) {
  vector<int> result;
  while(number > 0) {
    result.push_back(number - (number/10)*10);
    number /= 10;
  }
  return result;
}

vector<int> add(vector<int> number1, vector<int> number2) {
  vector<int> result;
  int remainder = 0;
  for(int i=0; i != max(number1.size(), number2.size()); i++) {
    int sum = remainder;
    if(i < number1.size()) sum += number1[i];
    if(i < number2.size()) sum += number2[i];
    remainder = sum/10;
    sum -= remainder*10;
    result.push_back(sum);
  }

  while(remainder > 0) {
    int sum = remainder - (remainder/10)*10;
    result.push_back(sum);
    remainder /= 10;

  }
  return result;
};

int main(int argc, char **argv) {
  int max = 1000;
  if(argc > 1) {
    max = atoi(argv[1]);
  }

  vector<int> previous = makeNumber(1);
  vector<int> current = makeNumber(1);

  int count = 2;
  while(current.size() < max) {
    vector<int> next = add(previous, current);
    previous = current;
    current = next;
    count++;
  }


  return 0;
}
