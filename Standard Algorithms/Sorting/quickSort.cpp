#include <vector>
#include <iostream>

using namespace std;

vector<int> sort(vector<int> array) {
  if(array.size() <= 1)
    return array;
  vector<int> left;
  vector<int> right;
  int pivot = array[array.size()/2];
  array.erase(array.begin()+array.size()/2);
  for(int i=0; i!=array.size(); i++) {
    if(array[i] < pivot)
      left.push_back(array[i]);
    else
      right.push_back(array[i]);
  }
  left = sort(left);
  right = sort(right);
  vector<int> result;
  for(int i=0; i!= left.size(); i++)
    result.push_back(left[i]);
  result.push_back(pivot);
  for(int i=0; i!=right.size(); i++)
    result.push_back(right[i]);
  return result;
};

int main(void) {
  int array[6] = { 3, 6, 2, 5, 8, 4 };
  vector<int> result;
  result.assign(array, array + 6);
  result = sort(result);
  for(int i=0; i!=6; i++) {
    cout << result[i] << " ";
  }
  cout << endl;
  return 0;
}
