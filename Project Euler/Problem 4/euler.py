def isPalindrome(number):
  string = str(number)
  return string == string[::-1]


palindrome = 0
left = 0
right = 0
count = 0
for i in range(100, 1000):
  for j in range(100, 1000):
    if isPalindrome(i*j) and i*j > palindrome:
      count += 1
      left = i
      right = j
      palindrome = i*j


print count
print str(left) + " " + str(right)
print palindrome

  

