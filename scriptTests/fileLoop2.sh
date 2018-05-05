#!/bin/bash
for file in *.txt; do
    find puzzles -maxdepth 1 -type f -exec echo "put {}" \;
done


