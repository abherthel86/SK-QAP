#!/bin/bash

grep 'Solving' PT15x4n.txt | cut -d " " -f 3 > /tmp/instance
grep 'Best Global Solution Cost' PT15x4n.txt | cut -d " " -f 5 > /tmp/cost
grep 'Global Time' PT15x4n.txt | cut -d " " -f 3 > /tmp/times

paste /tmp/instance /tmp/cost /tmp/times > GlobalStatsPT15x4n.txt
