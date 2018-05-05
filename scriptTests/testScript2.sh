#!/bin/bash
g++ -g -Wall -std=c++11 board.cc main.cc -o a
while IFS='' read -r line || [[ -n "$line" ]]; do
	echo "$line"
	./a m < "$line"
done < "$1"