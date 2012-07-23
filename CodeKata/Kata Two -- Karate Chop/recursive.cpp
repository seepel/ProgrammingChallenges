#include "test.h"

using namespace std;

vector<int>::const_iterator chop(int number, vector<int>::const_iterator begin, vector<int>::const_iterator end) {
  vector<int>::const_iterator middle = begin + (end - begin) / 2;

  if(end - begin < 1) return end;

  if(*middle == number) return middle;

  if(end - begin < 2) return end;

  vector<int>::const_iterator newBegin = begin;
  vector<int>::const_iterator newEnd = middle;

  if(number > *middle) {
    newBegin = middle + 1;
    newEnd = end;
  }

  vector<int>::const_iterator it = chop(number, newBegin, newEnd);
  if(it == newEnd) return end;
  
  return it;
}

int chop(int number, vector<int> array) {
  vector<int>::const_iterator it = chop(number, array.begin(), array.end());
  if(it == array.end()) return -1;

  return it - array.begin();
}

int main(void) {
  testChop();
  return 0;
}
