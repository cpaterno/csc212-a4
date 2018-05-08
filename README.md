# csc212-a4
Assignment 4 for CSC 212 Class @ URI
Using A* Search to Solve the N-Puzzle Problem

# Board Checklist
- [x] Datamembers
- [x] Default Constructor
- [x] Useful Constructor
- [x] Destructor 
- [x] `is_solvable` method
- [x] `is_goal` method
- [x] `neighbors` method
- [x] `hamming` method
- [x] `manhattan` method
- [x] `inversions` method

# Main Checklist 
- [x] `solve` method (A* search)
- [x] Write board comparator class
- [x] Use priority queue and unordered set (hash table)
- [x] File IO
- [x] Comments and Optimizations
- [ ] Think of an algorithm that could prevent collisions: 

For example 4 11 1 14
            2 8 0 15
            7 5 12 9
            6 3 13 10 
maps to the same string as 
            4 1 11 14
            2 8 0 15
            7 5 12 9
            6 3 13 10
