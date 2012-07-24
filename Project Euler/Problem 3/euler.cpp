#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <math.h>
#include <bitset>
#include <stdint.h>

using namespace std;

#define MAX_PRIME 1000000

vector<uint64_t> getPrimes(uint64_t limit) {
  bitset<MAX_PRIME> sieve;
  vector<uint64_t> primeList;
  sieve.flip();
  sieve[0].flip();
  sieve[1].flip();
  uint64_t p = 2;
  while(p <= limit) {
    primeList.push_back(p);
    for(uint64_t i=p*p; i <= limit; i+=p) {
      if(sieve[i]) {
	sieve[i].flip();
      }
    }
    p++;
    while(!sieve[p])
      p++;
  }
  return primeList;
};

int main(int argc, char **argv) {
  uint64_t number = 600851475143;
  if(argc > 1) {
    number = atoi(argv[1]);
  }

  cout << number << endl;
  vector<uint64_t> primes = getPrimes(sqrt(number)+1);

  for(uint64_t i=0; i!= primes.size(); i++) {
    uint64_t prime = primes[i];
    while(number % prime == 0)
      number /= prime;

    if(number <= 1) {
      cout << prime << endl;
      break;
    }
  }

  return 0;
}
