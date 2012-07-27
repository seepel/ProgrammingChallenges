#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <map>
#include <bitset>


using namespace std;

#define MAX 28123

int sumOfFactors(int number) {
  int factors = 1;
  for(int prime=2; prime*prime <= number; prime++) {
    int count = 1;
    while(number % prime == 0) {
      number /= prime;
      count=count*prime+1;
    }
    factors *= count;
  }
  if(number > 1)
    factors *=(number+1);
  return factors;
}


int main(int argc, char **argv) {
  int sum = 0;

  vector<int> abundants;
  for(int i=1; i!=MAX; i++)
    if(sumOfFactors(i)-i > i)
      abundants.push_back(i);

  cout << "Found " << abundants.size() << " abundants" << endl;

  bitset<MAX> abundantSums;
  for(int i=0; i!= abundants.size(); i++) {
    for(int j=i; j!= abundants.size(); j++) {
      if(abundants[i] + abundants[j] >= MAX || abundantSums[abundants[i]+abundants[j]])
        continue;
      abundantSums[abundants[i]+abundants[j]].flip();
      if(!abundantSums[abundants[i]+abundants[j]]) { cout << "FAIL" << endl; abort(); }
    }
  }

  cout << "Summed Abundants" << endl;

  for(int i=1; i!=MAX; i++)
    if(!abundantSums[i]) sum += i;

  cout << sum << endl;

  return 0;
  /*
  */
}
