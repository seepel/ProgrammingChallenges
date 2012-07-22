array = [ 3, 6, 2, 5, 8, 4 ]

def merge(left, right):
  result = [ ]
  while len(left) > 0 or len(right) > 0:
    if len(left) > 0 and len(right) > 0:
      if left[0] <= right[0]:
        result.append(left[0])
        left = left[1:len(left)]
      else:
        result.append(right[0])
        right = right[1:len(right)]
    if len(left) > 0:
      result.append(left[0])
      left = left[1:len(left)]
    if len(right) > 0:
      result.append(right[0])
      right = right[1:len(right)]
    
  return result


def sort(array):
  if len(array) <= 1:
    return array
  middle = len(array)/2
  left = [ ]
  right = [ ]
  for i in range(0,middle):
    left.append(array[i])
  for i in range(middle,len(array)):
    right.append(array[i])
  left = sort(left)
  right = sort(right)
  return merge(left, right)

print sort(array)
