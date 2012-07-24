#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <map>
#include <bitset>
#include <cmath>

#define MAX_PRIME 1000000

using namespace std;

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
  int max = 5000;
  if(argc > 1) {
    max = atoi(argv[1]);
  }

  vector<uint64_t> primes = getPrimes(MAX_PRIME);
  int i=1;
  int numberOfFactors=1;
  int triangle = 1;
  while(numberOfFactors < max) {
    if(numberOfFactors >= max) break;
    i++;
    triangle += i;
    int p = 0;
    int factors = 1;
    int tmp = triangle;
    for(uint64_t prime = primes[p]; prime <= triangle && p < primes.size(); prime = primes[p++]) {
      if(prime == 0) { cout << "Prime failure" << endl; abort(); }
      int primeCount = 0;
      if(tmp % prime != 0 || tmp <= 1)
	continue;
      primeCount += 1;
      while(tmp % prime == 0) {
	if(tmp % prime != 0) break;
	tmp /= prime;
	primeCount++;
      }
      factors *= primeCount;
    }
    numberOfFactors = factors;
  }
  cout << triangle << endl;


  return 0;
}
