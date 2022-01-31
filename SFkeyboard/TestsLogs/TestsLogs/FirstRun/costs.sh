#!/bin/bash

grep 'Solving' Test1.txt | cut -d " " -f 3 > /tmp/instance
grep 'Best Global Solution Cost' Test1.txt | cut -d " " -f 5 > /tmp/cost
grep 'Global Time' Test1.txt | cut -d " " -f 3 > /tmp/times

paste /tmp/instance /tmp/cost /tmp/times > GlobalStatsT1.txt
