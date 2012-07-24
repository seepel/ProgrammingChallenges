#include <iostream>
#include <stdlib.h>
#include <map>

using namespace std;

map<int64_t, int64_t> counts;

int64_t countSequence(int64_t number) {
  if(number == 1) return 1;
  if(counts.find(number) != counts.end()) { return counts[number]; }
  int64_t count = 0;
  if(number % 2 == 0) count = 1+countSequence(number/2);
  else count = 1+countSequence(3*number + 1);
  counts[number] = count;
  return count;
}


int main(int argc, char **argv) {
  int max = 1000;
  if(argc > 1) {
    max = atoi(argv[1]);
  }


  int64_t maxCount = 0;
  int64_t maxNumber = 1;
  for(int64_t i=1; i!=max; i++) {
    int64_t count = countSequence(i);
    if(count > maxCount) {
      maxCount = count;
      maxNumber = i;
    }
  }
  cout << maxNumber << ": " << maxCount << endl;
  return 0;
}
