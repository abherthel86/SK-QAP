#!/bin/bash

grep 'Solving' GenTestPT20x10n.txt | cut -d " " -f 3 > /tmp/instance
grep 'Best Global Solution Cost' GenTestPT20x10n.txt | cut -d " " -f 5 > /tmp/cost
grep 'Global Time' GenTestPT20x10n.txt | cut -d " " -f 3 > /tmp/times

paste /tmp/instance /tmp/cost /tmp/times > GlobalStatsPT20x10n.txt
