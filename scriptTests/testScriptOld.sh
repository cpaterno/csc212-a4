#!/bin/bash
g++ -g -Wall -std=c++11 board.cc main.cc -o a
for file in *.txt; do
    find puzzles -maxdepth 1 -type f -exec echo "{}" \;
done


