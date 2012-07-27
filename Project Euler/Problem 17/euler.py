import sys
numbers = {
  0 : '',
  1 : 'one',
  2 : 'two',
  3 : 'three',
  4 : 'four',
  5 : 'five',
  6 : 'six',
  7 : 'seven',
  8 : 'eight',
  9 : 'nine',
  10 : 'ten',
  11 : 'eleven',
  12 : 'twelve',
  13 : 'thirteen',
  14 : 'fourteen',
  15 : 'fifteen',
  16 : 'sixteen',
  17 : 'seventeen',
  18 : 'eighteen',
  19 : 'nineteen',
  20 : 'twenty',
  30 : 'thirty',
  40 : 'forty',
  50 : 'fifty',
  60 : 'sixty',
  70 : 'seventy',
  80 : 'eighty',
  90 : 'ninety',
  100 : 'hundred',
  1000 : 'thousand'
}

count = 0

def singleLength(i):
  return len(numbers[i])

def doubleLength(i):
  if numbers.has_key(i): return len(numbers[i])
  return len(numbers[(i/10)*10]) + singleLength(i - (i/10)*10)

def tripleLength(i):
  length = len(numbers[i/100]) 
  print length
  if i/100 > 0:
    length += len(numbers[100])
  print length
  if (i/100)*100 != i and i > 100:
    length += 3 # and
  print length
  length += doubleLength(i-(i/100)*100)
  print length
  return length


for i in range(1,1000):
  count += tripleLength(i)
count += len(numbers[1]) + len(numbers[1000])

print count
