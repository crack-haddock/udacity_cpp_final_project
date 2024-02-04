# Overview
This is a game of Snake for 1, 2 or 3 players based on the starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213)
There are a few things not implemented from the point of view of a Snake game (or a 'better' Snake game), most notably collision detection between snakes, and an AI player. I also wanted food to be a playable object in multiplayer. I did not have time for these, but as the point of this exercise is to satisfy the rubrics below, I've concentrated on those.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0.20
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

## Dev/Testing
Developed using VS Code on WSL2 (Windows Sub-system for Linux (Ubuntu 22.04)) on Windows 11. GCC:11.4. Make: v4.3. SDL: v2.0.20

## Problems Outstanding and Bugs
- Getting TTF fonts working with this game was really tough. Got it working eventually in my Windows/WSL dev env, but not in the Udacity workspace using v2.0.4 (I'm using Ubuntu v22 and SDL 2.0.20 locally).
    - I must cite the following as the source of the extra cmake file I needed:
    https://github.com/aminosbh/sdl2-ttf-sample/blob/master/cmake/sdl2/FindSDL2_ttf.cmake
- There are raw pointers in Renderer for the imported SDL and TTF classes. I've tried and failed wrapping TTF_Font in a smart pointer. I found a github repo that is able to do so for the SDL classes, but it looks complicated and I have little time for confidence for trying to adapt it to mine.
- VERY occasionally some combination of turns by a snake seems to cause it to get stuck. Not worked out why as I've found it impossible to recreate on demand. Suspect the problem is in Snake.cpp which is the one part of the original code I've barely touched.

## Features
- 1, 2 or 3 player [user prompted for number on startup]
- In a multiplayer game, the winner is the first to 10 (by default)
- Fully configurable from a config.txt file allowing user to set game params without recompiling. Config values include multiplayer winning score, target FPS, screen dims and grid dims. 

## Bugs
- Very occasionally a snake will become stuck. I suspect this involves a sudden reverse of direction but am unable to work out the exact cause.

## Rubric Points Addressed
- [3/3] ReadMe addressing rubrics etc [this file]
- [?/1] Compiling and Testing
    - Builds and runs (using cmake and make) INSIDE UDACITY WORKSPACE
        - cannot get the TTF library working inside workspace so does not build
            - when it does build, path to font in renderer code will be wrong
- [4/2] Loops, functions, I/O
    - [done] The project demonstrates an understanding of C++ functions and control structures
    - [done] Reads data from a file
        - config.cpp
    - [done] The project accepts user input and processes the input [other than controlling a snake]
        - press a key to 1) choose number of players 2) exit on Game Over
    - [done] data structures and immutable variables
        - keymaps in controller class, const used in several places
- [3/3] OOP
    - [done] One or more classes are added to the project
        - Config, GameObject, Food
    - [done] Class constructors utilize member initialization lists.
        - Renderer, Game, Snake
    - [maybe?] Classes abstract implementation details from their interfaces
    - [NO] Overloaded functions allow the same function to operate on different parameters.
    - [done] Classes follow an appropriate inheritance hierarchy with virtual and override functions
        - see GameObject and child object Snake (also Food, but not this wasn't used in the end)
    - [NO] Templates generalize functions or classes in the project.
- [4/3] Memory Management
    - [DONE] uses move semantics
        - creates Renderer object in main(), moves ownership to Game object
            - bonus points for dependency injection? :)
    - [PARTLY DONE] uses smart pointers [TO DO - remove all raw pointers where possible]
        - unique_ptr used for vector of snakes in game.h.
        - gave up trying to wrap SDL-related stuff in smart pointers
    - [DONE] The project follows the Rule of 5.
        - Renderer
    - [DONE] The project makes use of references in function declarations.
    - [DONE] The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate.
        - I think Renderer, created in main, moved into Game, and being destroyed when Game is, is the example here.
    - [MAYBE] uses destructors appropriately
        - the only place I found a need for destructors was Render, where I think it was already written 
- [2/2] Concurrency
    - [DONE] The project uses multithreading
        - Renderer::UpdateWindowTitle() runs in a thread that persists as long as the main game loop
    - [NO] A promise and future is used in the project
    - [DONE] A mutex or lock is used in the project
        - lock on the fps counter that is updated by the game loop but read from Renderer::UpdateWindowTitle() which itself runs in a thread. Ideally should have one on 'running' too, and maybe scores, but ran out of time.
    - [NO] A condition variable is used in the project

## Next?
If I had more time I would add or address the following:
### Technical
- more/better mutexes around vars shared with UpdateWindowTitle()
- Food class used as straight replacement for current implementation- I hate the food just being an SDL_Point
- more abstraction to reduce dependencies. I did this with Controller, but much harder for Renderer
- Abstract Renderer class so game could use something other than SDL if desired
- Sound!
### Gameplay
- Food is a player! Would just need to consider how scoring worked, although could be an AI non-player at least
- Collision detection between snakes
- More interesting scoring - e.g. timer on food, so faster eating = higher score
- AI snake(s)
