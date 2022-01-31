#!/bin/bash

grep 'Solving' Test5.txt | cut -d " " -f 3 > /tmp/instance
grep 'Best Global Solution Cost' Test5.txt | cut -d " " -f 5 > /tmp/cost
grep 'Global Time' Test5.txt | cut -d " " -f 3 > /tmp/times

paste /tmp/instance /tmp/cost /tmp/times > GlobalStatsT5.txt
