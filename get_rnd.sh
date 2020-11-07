#!/bin/bash
# Длина генерируемой последовательности чисел.

ARG=$(shuf -i 1-$1 -n $2);
seeds=
for i in $ARG; do
	seeds="$seeds $i"
done; 
echo $seeds;
