#!/bin/bash
read t
for ti in $(seq 1 $t); do
    read -r n
    read -r line
    bi=0
    best=0
    i=1
    for word in $line; do
        bi=$(( word > best ? i : bi ))
        best=$(( word > best ? word : best ))
        ((i++))
    done
    echo $bi
done
