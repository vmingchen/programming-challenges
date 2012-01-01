#!/usr/bin/env python
import sys
import random

str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
print "I 250 250"

for i in range(10000):
    c = random.choice('LVHKF')
    if c == 'L':
        print "L %d %d %s" % (random.randint(1, 250), 
                random.randint(1, 250),
                random.choice(str))
    elif c == 'G':
        print "G %d %d" % (random.randint(1, 250),
                random.randint(1, 250))
    elif c == 'V':
        print "V %d %d %d %s" % (random.randint(1, 250),
                random.randint(1, 250),
                random.randint(1, 250),
                random.choice(str))
    elif c == 'H':
        print "H %d %d %d %s" % (random.randint(1, 250),
                random.randint(1, 250),
                random.randint(1, 250),
                random.choice(str))
    elif c == 'K':
        print "K %d %d %d %d %s" % (
                random.randint(1, 250),
                random.randint(1, 250),
                random.randint(1, 250),
                random.randint(1, 250),
                random.choice(str))
    elif c == 'F':
        print "F %d %d %s" % (
                random.randint(1, 250),
                random.randint(1, 250),
                random.choice(str))
print "S one.bmp"
print "X"
