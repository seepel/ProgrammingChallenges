Datacenter Cooling
============
We have some rooms in our datacenter, and we need to connect them all with a single cooling duct.

Here are the rules:
The datacenter is represented by a 2D grid.
Rooms we own are represented by a 0.
Rooms we do not own are represented by a 1.
The duct has to start at the air intake valve, which is represented by a 2.
The duct has to end at the air conditioner, which is represented by a 3.
The duct cannot go in multiple directions out of the intake or the AC - they must be the two endpoints of the duct.
The duct must pass through each room exactly once.
The duct cannot pass through rooms we do not own.
The duct can connect between rooms horizontally or vertically but not diagonally.

Here is an example datacenter:

```2  0  0  0
 
0  0  0  0
 
0  0  3  1
 
```

There are two possible ways to run the duct here:

```
2--0--0--0
         |
0--0--0--0
|
0--0--3  1
```

or
```
2  0--0--0
|  |     |
0  0  0--0
|  |  |
0--0  3  1
```


Write a program to compute the number of possible ways to run the duct. For the above example, the correct answer is 2.

Input format (read from STDIN):
---------------------------
The input will be a series of integers separated by whitespace.

The first two integers will be W and H, with width and height of the datacenter. These will be followed by W*H more integers, specifying the 2D grid representing the datacenter.

Output format (write to STDOUT):
----------------------------
Your program should write a single integer out: the number of possible ways to run the duct.

See how fast you can make it.

Notes
-----
Our best solution (written in C) can solve the following test case in under 5 seconds on a 2.4GHz Pentium 4, but it's pretty good if you can get to within 1-2 orders of magnitude of that.

```7 8
2 0 0 0 0 0 0
0 0 0 0 0 0 0
0 0 0 0 0 0 0
0 0 0 0 0 0 0
0 0 0 0 0 0 0
0 0 0 0 0 0 0
0 0 0 0 0 0 0
3 0 0 0 0 1 1
```
