#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <map>
#include <bitset>


using namespace std;

#define MAX_PRIME 2000000

int main(int argc, char **argv) {
  uint64_t limit = 2000000;
  if(argc > 1) {
    limit = atoi(argv[1]);
  }

  uint64_t sum = 0;

  bitset<MAX_PRIME> sieve;
  sieve.flip();
  sieve[0].flip();
  sieve[1].flip();
  uint64_t p = 2;
  while(p <= limit) {
    if(p > limit) break;
    sum += p;
    for(uint64_t i=p*p; i <= limit; i+=p) {
      if(sieve[i]) {
	sieve[i].flip();
      }
    }
    p++;
    while(!sieve[p])
      p++;
  }

  cout << sum << endl;

  return 0;
}
