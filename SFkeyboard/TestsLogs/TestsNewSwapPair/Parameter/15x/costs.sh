#!/bin/bash

grep 'Solving' Test15x6n.txt | cut -d " " -f 3 > /tmp/instance
grep 'Best Global Solution Cost' Test15x6n.txt | cut -d " " -f 5 > /tmp/cost
grep 'Global Time' Test15x6n.txt | cut -d " " -f 3 > /tmp/times

paste /tmp/instance /tmp/cost /tmp/times > GlobalStatsT15x6n.txt
