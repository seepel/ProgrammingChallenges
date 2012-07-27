#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<int>::iterator Iterator;

int factorial(int n) { if(n == 1) return 1; return n*factorial(n-1); }

void print(Iterator begin, Iterator end) {
  for(Iterator it = begin; it != end; it++) cout << *it;
  cout << endl;
};

int permutate(Iterator begin, Iterator end, int maxCount) {
  int count = 0;
  int countForPermutation = factorial((end-begin));
  if(countForPermutation < maxCount) return countForPermutation - 1;
  if(end-begin <= 1) return 0;
  if(end-begin <= 2) { 
    iter_swap(begin, begin+1);
    return 1;
  }
  for(int i=0; i!=end-begin; i++) {
    int tmp = *(begin+i);
    for(int j=0; j!=i; j++) {
      iter_swap(begin+i-j,begin+i-j-1);
    }
    *(begin) = tmp;
    if(i > 0)
      count++;
    if(count >= maxCount) return count;
    count += permutate(begin+1, end, maxCount - count);
    if(count >= maxCount) return count;
    sort(begin, end);
  }
  return count;
};

int main(void) {
  vector<int> digits;
  for(int i=0; i!=10; i++)
    digits.push_back(i);

  permutate(digits.begin(), digits.end(), 999999);
  print(digits.begin(), digits.end());

  return 0;
}
