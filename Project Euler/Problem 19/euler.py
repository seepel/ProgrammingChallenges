months = [ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 ]

count = 0
day = 0
for year in range(1900, 2001):
  for month in months:
    day += month
    if year % 4 == 0 and month == 28:
      day += 1
    if year > 1900 and day % 7 == 0:
      count += 1
print count
  
