#include <vector>
#include <iostream>

using namespace std;

vector<int> merge(vector<int> left, vector<int> right) {
  vector<int> result;
  while(left.size() > 0 || right.size() > 0) {
    if(left.size() > 0 && right.size() > 0) {
      if(left[0] <= right[0]) {
	result.push_back(left[0]);
	left.erase(left.begin());
      } else {
	result.push_back(right[0]);
	right.erase(right.begin());
      }
    }
    else if(left.size() > 0) {
      result.push_back(left[0]);
      left.erase(left.begin());
    }
    else if(right.size() > 0) {
      result.push_back(right[0]);
      right.erase(right.begin());
    }
  }
  return result;
}

vector<int> sort(vector<int> array) {
  if(array.size() <= 1)
    return array;
  int middle = array.size()/2;
  vector<int> left;
  vector<int> right;
  for(int i=0; i!=middle; i++) {
    left.push_back(array[i]);
  }
  for(int i=middle; i!=array.size(); i++) {
    right.push_back(array[i]);
  }
  left = sort(left);
  right = sort(right);
  return merge(left, right);
}

vector<int> sort(int *array, int length) {
  vector<int> result;
  result.assign(array, array + length);
  return sort(result);
}

int main(void) {
  int array[6] = { 3, 6, 2, 5, 8, 4 };
  vector<int> result = sort(array, 6);
  for(int i=0; i!=6; i++) {
    cout << result[i] << " ";
  }
  cout << endl;
  return 0;
}
