# Overview
This is a game of Snake for 1, 2 or 3 players. I extended the core game provided in the final project skeleton repo.
There are a few things not implemented from the point of view of a Snake game, most notably collision detection between snakes and an AI player. I also wanted food to be a playable object in multiplayer. Did not have time for these and some other stuff, but as the point of this exercise is to satisfy the rubrics below, I've concentrated on those.

## Installation
Unchanged from Udacity skeleton. Please see readme.md

## Features
- 1, 2 or 3 player [TODO user prompted for number on startup]
- Reads in fps and screen/grid dimensions from text file allowing user to set game params without recompiling

## Rubric Points Addressed
    - [3/3] ReadMe addressing rubrics etc [this file]
    - [0/1] Compiling and Testing
        - Builds and runs (using cmake and make) **INSIDE UDACITY WORKSPACE**
    - [2/2] Loops, functions, I/O
        - [done] The project demonstrates an understanding of C++ functions and control structures
        - [done] Reads data from a file
        - [] The project accepts user input and processes the input [other than controlling a snake]
        - [done] data structures and immutable variables
    - [3/3] OOP
        - [done] One or more classes are added to the project
        - [done] Class constructors utilize member initialization lists.
        - [] Classes abstract implementation details from their interfaces
        - [] Overloaded functions allow the same function to operate on different parameters.
        - [done] Classes follow an appropriate inheritance hierarchy with virtual and override functions
        - [] Templates generalize functions or classes in the project.
    - [4/3] Memory Management
        - [DONE] uses move semantics
        - [PARTLY DONE] uses smart pointers [TO DO - remove all raw pointers where possible]
        - [DONE] The project follows the Rule of 5.
        - [DONE] The project makes use of references in function declarations.
        - [DONE] makes use of references in function declarations
        - [] uses destructors appropriately
    - [0/2] Concurrency
        - [NO] The project uses multithreading
        - [NO] A promise and future is used in the project
        - [NO] A mutex or lock is used in the project
        - [NO] A condition variable is used in the project
