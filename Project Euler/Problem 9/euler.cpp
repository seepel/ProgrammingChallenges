#include <iostream>
#include <cmath>

using namespace std;

int main(void) {
  int a = 0;
  int b = 0;
  for(a=1; a < 1000; a++) {
    for(b=1; b < 1000; b++) {
      if(a + b + sqrt(a*a + b*b) == 1000) break;
    }
    if(a + b + sqrt(a*a + b*b) == 1000) break;
  }
  int c = sqrt(a*a + b*b);
  cout << "a: " << a << " b: " << b << " c: " << c << " abc: " << a*b*c << endl;
  if(a + b + c != 1000) {
    cout << "Fail" << endl;
    abort();
  }
  return 0;
}
