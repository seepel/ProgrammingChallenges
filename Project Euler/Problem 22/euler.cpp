#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdint.h>

using namespace std;

int main(void) {

  ifstream ifs("names.txt", ifstream::in);

  uint64_t base = 'A';



  vector<string> names;
  while(ifs.good()) {
    string name;
    ifs >> name;
    names.push_back(name);
  }

  sort(names.begin(), names.end());
  uint64_t sum = 0;
  for(int i=0; i!=names.size(); i++) {
    string name = names[i];
    uint64_t score = 0;
    for(int j=0; j!=name.size(); j++) {
      uint64_t character = name[j];
      score += character - base + 1;
    }
    sum += score * i;
  }

  cout << sum << endl;
   

  return 0;
}
