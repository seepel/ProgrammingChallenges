#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <map>
#include <bitset>

//#define DEBUG

using namespace std;

int main(int argc, char **argv) {
  uint64_t max = 1000;
  if(argc > 1) {
    max = atoi(argv[1]);
  }

  vector<uint64_t> blocking;
  blocking.push_back(0);
  blocking.push_back(1);

  uint64_t blocked = 0;
  for(uint64_t i=2; i<=max; i++) {
    uint64_t side = i;
    for(uint64_t j=1; j!=i; j++) {
      if(i % j == 0) {
	blocked += 6*blocking[j];
	side -= blocking[j];
      }
    }
    blocking.push_back(side);
  }
  cout << blocked << endl;
  return 0;
}
