#!/bin/bash

grep 'Solving' newENPTtest.txt | cut -d " " -f 3 > /tmp/instance
grep 'Best Global Solution Cost' newENPTtest.txt | cut -d " " -f 5 > /tmp/cost
grep 'Global Time' newENPTtest.txt | cut -d " " -f 3 > /tmp/time


paste /tmp/instance /tmp/cost > Statsnewenpt.txt
paste /tmp/time > Timesnewenpt.txt
#paste /tmp/instance > CostsMergeXb.txt
paste /tmp/cost > Costsnewenpt.txt
