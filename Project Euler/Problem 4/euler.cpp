#include <iostream>
#include <map>
#include <utility>

using namespace std;

int reverse(int number) {
  int reversed = 0;
  while(number > 0) {
    reversed = reversed * 10 + number % 10;
    number /= 10;
  }
  return reversed;
};

map<pair<int, int>, int> palindromes;

int findPalindrome(int left, int right, int minProduct, int minFactor, int *count) {
  *count = *count + 1;
  cout << *count << endl;
  pair<int, int> factors;
  factors.first = left;
  factors.second = right;
  if(palindromes.find(factors) != palindromes.end())
    return palindromes[factors];
  if(left < minFactor || right < minFactor) { 
    palindromes[factors] = 0;
    return minProduct;
  }
  int product = left*right;
  if(product < minProduct) {
    palindromes[factors] = 0;
    return 0;
  }

  //cout << left << " x " << right << " = " << product << " : " << minProduct << " : " << minFactor << endl;

  if(product == reverse(product)) {
    palindromes[factors] = product;
    return product;
  }

  if((left-1)*right > left*(right-1)) {
    int palindrome = findPalindrome(left-1, right, minProduct, minFactor, count);
    if(palindrome >= minProduct) minProduct = palindrome;
    palindrome = findPalindrome(left, right-1, minProduct, minFactor, count);
    palindromes[factors] = palindrome;
    return palindrome;
  } else {
    int palindrome = findPalindrome(left, right-1, minProduct, minFactor, count);
    if(palindrome >= minProduct) minProduct = palindrome;
    palindrome = findPalindrome(left-1, right, minProduct, minFactor, count);
    palindromes[factors] = palindrome;
    return palindrome;
  }
}

int main(void) {
  int count = 0;
  cout << findPalindrome(999, 999, 100*100, 913, &count) << endl;;
  cout << count << endl;
  return 0;
}
