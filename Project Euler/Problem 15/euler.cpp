#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <map>
#include <utility>
#include <stdint.h>

using namespace std;

map<pair<uint64_t, uint64_t>, uint64_t> memoized;

uint64_t numberOfPaths(uint64_t i, uint64_t j) {
  cout << i << " " << j << endl;
  pair<uint64_t, uint64_t> node;
  node.first = i;
  node.second = j;
  if(memoized.find(node) != memoized.end()) return memoized[node];
  uint64_t paths = 0;
  if(i > 0)
    paths += numberOfPaths(i-1, j);
  if(j > 0)
    paths += numberOfPaths(i, j-1);
  if(i == 0 && j == 0)
    paths = 1;

  memoized[node] = paths;

  return paths;
}

int main(int argc, char **argv) {
  int max = 20;
  if(argc > 1) {
    max = atoi(argv[1]);
  }
  cout << numberOfPaths(max, max) << endl;
  return 0;
}
