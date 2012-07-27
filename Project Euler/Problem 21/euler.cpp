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
  uint64_t max = 10000;
  if(argc > 1) {
    max = atoi(argv[1]);
  }


  primes = getPrimes(20000);

  map<int, int> sums;
  for(uint64_t i=1; i!=max; i++) {
    vector<uint64_t> factors = factorize(i);
    uint64_t sum = 0;
    for(int j=0; j!=factors.size(); j++) {
      sum += factors[j];
    }
    sums[i] = sum;
  }

  int count = 0;
  int sum = 0;
  for(int i=1; i!=max; i++) {
    if(sums[sums[i]] == i && sums[i] != i) {
      cout << "d(" << i << ") =  " << sums[i] << " d(" << sums[i] << ")" << " = " << sums[sums[i]] << endl;
      sum += i;
      count++;
    }
  }

  cout << sum << endl;

  /*
  vector<uint64_t> factors = factorize(220);
  for(int i=0; i!=factors.size(); i++)
    cout << factors[i] << " ";
  cout << endl;
  */
  return 0;
}
