#!/bin/bash

grep 'Solving' Test10x2n.txt | cut -d " " -f 3 > /tmp/instance
grep 'Best Global Solution Cost' Test10x2n.txt | cut -d " " -f 5 > /tmp/cost
grep 'Global Time' Test10x2n.txt | cut -d " " -f 3 > /tmp/times

paste /tmp/instance /tmp/cost /tmp/times > GlobalStatsT10x2n.txt
