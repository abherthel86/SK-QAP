#!/bin/bash

grep 'Solving' TestP10x3n.txt | cut -d " " -f 3 > /tmp/instance
grep 'Best Global Solution Cost' TestP10x3n.txt | cut -d " " -f 5 > /tmp/cost
grep 'Global Time' TestP10x3n.txt | cut -d " " -f 3 > /tmp/times

paste /tmp/instance /tmp/cost /tmp/times > GlobalStatsTP10x3n.txt
