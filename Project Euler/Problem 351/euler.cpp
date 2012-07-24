#include <iostream>
#include <stdint.h>
#include <stdlib.h>
#include <vector>

using namespace std;


uint64_t blocked(uint64_t number) {
  for(int i=1; i!=number; i++) {
  }
}

int main(int argc, char **argv) {
  uint64_t number = 100000000;
  if(argc > 1) {
    number = atoi(argv[1]);
  }

  cout << blocked(number) << endl;
  return 0;
}
