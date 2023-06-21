#!/bin/zsh

i=18

for (( j=1; j<=8; j++ ))
do
    echo "Running client iteration $j with i=$i"
    zsh scripts/run-client.sh cheetah relu12_23_34_45 >> /Users/eloise/workspace/SNNI/Library/result/ReluOnly_Cheetah/relu12_23_34_45/all-1/log_client_$i.txt
    i=$((i+1))
done