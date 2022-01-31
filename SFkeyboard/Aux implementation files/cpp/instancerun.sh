#!/bin/bash
#./exeSFkey Instances/English.txt charlists/Char_English.txt Instances/b_matrix.txt
for i in {1..10}
do
  for i in English #Spanish French Italian
  do
    ./exeSFkey Instances/${i}.txt charlists/Char_${i}.txt Instances/b_matrix.txt
  done
done

exit 0

