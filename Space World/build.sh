#!/bin/bash

# Compile each source file into an object file
clang -c planet.c -o planet.o
clang -c navigation.c -o navigation.o
clang -c main.c -o main.o

# Link the object files into a single executable
clang planet.o navigation.o main.o -o space_navigator

echo "Build complete."

./space_navigator
