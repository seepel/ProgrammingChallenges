Problem 25
==========
The Fibonacci sequence is defined by the recurrence relation:

Fn = Fn1 + Fn2, where F1 = 1 and F2 = 1.
Hence the first 12 terms will be:

F1 = 1
F2 = 1
F3 = 2
F4 = 3
F5 = 5
F6 = 8
F7 = 13
F8 = 21
F9 = 34
F10 = 55
F11 = 89
F12 = 144
The 12th term, F12, is the first term to contain three digits.

What is the first term in the Fibonacci sequence to contain 1000 digits?

Comment
=======
Fn = 1/sqrt(5)*((1+sqrt(5))/2)^n - 1/sqrt(5)*((1-sqrt(5))/2)^n

Can use log of the first term to find that this will be on the oder of 4785th term. At this point I wrote the following program.

Of course one can rewrite the equation

Fn = 1 + ((1-sqrt(5))/(1+sqrt(5)))^n

And one can solve for n without numerical calculations (with the exception of log).
