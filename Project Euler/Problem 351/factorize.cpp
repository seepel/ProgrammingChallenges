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

vector<uint64_t> factorize(uint64_t number) {
  vector<uint64_t> factors;
  factors.push_back(1);
  vector<uint64_t> primeFactors;
  for(uint64_t i=0; i!=primes.size() && primes[i] <= number; i++) {
    if(number % primes[i] == 0 && primes[i] != number) {
      primeFactors.push_back(primes[i]);
    }
  }
  for(uint64_t i=0; i!=primeFactors.size(); i++) {
    uint64_t prime = primeFactors[i];
    for(uint64_t j=prime; j < number; j+=prime) {
      if(number % j == 0 && find(factors.begin(), factors.end(), j) == factors.end()) {
	factors.push_back(j);
      } else {
      }
    }
  }
  sort(factors.begin(), factors.end());
  return factors;
}



int main(int argc, char **argv) {
  uint64_t max = 1000;
  if(argc > 1) {
    max = atoi(argv[1]);
  }


  primes = getPrimes(20000);

  vector<uint64_t> blocking;
  blocking.push_back(0);
  blocking.push_back(1);

  uint64_t blocked = 0;
  for(uint64_t i=2; i<=max; i++) {
    uint64_t side = i;
    vector<uint64_t> factors = factorize(i);
    for(uint64_t k=0; k!= factors.size(); k++) {
      uint64_t j = factors[k];
      blocked += 6*blocking[j];
      side -= blocking[j];
    }
    blocking.push_back(side);
  }

  for(int i=0; i!=blocking.size(); i++)
    printf("%2d ",i);
  printf("\n");
  for(int i=0; i!=blocking.size(); i++)
    printf("%2d ",blocking[i]);
  printf("\n");
  cout << blocked << endl;
  return 0;
}
