#!/usr/bin/env python
import sys
import random

for i in range(10000):
    n = random.randint(1, 10)
    print n
    for j in range(n):
        c = random.random() * 100000
        print "%.2f" % c
print 0
