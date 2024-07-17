#!/bin/bash

g++ main.cpp game.cpp grid2.cpp pac.cpp ghost.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -g
