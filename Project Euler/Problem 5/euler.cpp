#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <map>
#include <bitset>


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

vector<uint64_t> primes;

int main(int argc, char **argv) {
  uint64_t max = 20;
  if(argc > 1) {
    max = atoi(argv[1]);
  }


  primes = getPrimes(max);

  uint64_t number = 1;
  for(int i=2; i!=max+1; i++) {
    if(number % i != 0) {
      for(int j=0; j!=primes.size(); j++) {
	if(i % primes[j] == 0) {
	  while(number % i != 0) { 
	    number *= primes[j];
	  }
	}
      }
    }
  }


  cout << number << endl;

  return 0;
}
