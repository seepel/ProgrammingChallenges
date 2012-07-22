#include <vector>
#include <iostream>

using namespace std;

void swap(vector<int> &array, int index1, int index2) {
  int tmp = array[index2];
  array[index2] = array[index1];
  array[index1] = tmp;
}

int partition(vector<int> &array, int begin, int end, int pivot) {
  int pivotValue = array[pivot];
  swap(array, pivot, end);
  int store = begin;
  for(int i=begin; i!=end; i++) {
    if(array[i] < pivotValue) {
      swap(array, i, store);
      store++;
    }
  }
  swap(array, store, end);
  return store;
};

void sort(vector<int> &array, int begin, int end) {
  if(begin < end) {
    int pivot = (begin+end)/2;
    int newPivot = partition(array, begin, end, pivot);
    sort(array, begin, newPivot-1);
    sort(array, newPivot+1, end);
  }
};

int main(void) {
  int array[6] = { 3, 6, 2, 5, 8, 4 };
  vector<int> result;
  result.assign(array, array + 6);
  sort(result, 0, result.size()-1);
  for(int i=0; i!=6; i++) {
    cout << result[i] << " ";
  }
  cout << endl;
  return 0;
}
