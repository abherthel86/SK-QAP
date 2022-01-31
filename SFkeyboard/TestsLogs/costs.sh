#!/bin/bash

grep 'Solving' GenTestPT20x10n.txt | cut -d " " -f 3 > /tmp/instance
grep 'Best Global Solution Cost' GenTestPT20x10n.txt | cut -d " " -f 5 > /tmp/cost

paste /tmp/instance /tmp/cost > GlobalCostsPT20x10n.txt
