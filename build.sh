#!/bin/bash

g++ src/main.cpp src/game.cpp src/grid2.cpp src/pac.cpp src/ghost.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -g
