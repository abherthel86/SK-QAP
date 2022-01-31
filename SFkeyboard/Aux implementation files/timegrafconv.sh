#!/bin/bash

#grep 'Solving' GrafConv.txt | cut -d " " -f 3 > /tmp/instance
#grep 'Best Global Solution Cost' GrafConv.txt | cut -d " " -f 5 > /tmp/cost
grep 'Global Time' GrafConv.txt | cut -d " " -f 3 > /tmp/times

paste /tmp/times > GrafConvStats.txt
