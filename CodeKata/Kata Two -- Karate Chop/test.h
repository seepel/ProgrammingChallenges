#include <vector>
#include <cassert>

int chop(int number, std::vector<int> array);

void testChop(void) {
  std::vector<int> array;
  assert(-1 == chop(3, array));

  array.push_back(1);
  assert(-1 == chop(3, array));
  assert(0 == chop(1, array));

  array.push_back(3);
  array.push_back(5);
  assert(0 == chop(1, array));
  assert(1 == chop(3, array));
  assert(2 == chop(5, array));
  assert(-1 == chop(0, array));
  assert(-1 == chop(2, array));
  assert(-1 == chop(4, array));
  assert(-1 == chop(6, array));

  array.push_back(7);
  assert(0 == chop(1, array));
  assert(1 == chop(3, array));
  assert(2 == chop(5, array));
  assert(3 == chop(7, array));
  assert(-1 == chop(0, array));
  assert(-1 == chop(2, array));
  assert(-1 == chop(4, array));
  assert(-1 == chop(6, array));
  assert(-1 == chop(8, array));
};
