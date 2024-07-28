#!/bin/bash



if [ "$1" == "--debug" ];
then
    g++ *.cpp -Wall -Ihelper  -Iexternal -Lexternal  -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -g -o build/debug/pacman
elif [ "$1" == "--release" ];
then
    g++ *.cpp -Ihelper  -Iexternal -Lexternal -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -O0 -o build/release/pacman
elif [ "$1" == "--run" ];
then
    ./build/debug/pacman
elif [ "$1" == "--cleanup" ];
then
    rm */**/*.cpp~
    rm */**/*.hpp~
    rm */**/*.sh~
    rm *.cpp~
    rm *.hpp~
    rm *.sh~
else
    echo "code will be compiled in debug mode as none of the options was selected"
    g++ *.cpp -Wall -Ihelper  -Iexternal -Lexternal  -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -g -o build/debug/pacman
fi


