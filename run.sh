#!/bin/sh
g++ -std=c++11 -c *.cpp ./imgui/src/*.cpp -I ./imgui/include -Ilib/include
g++ -framework OpenGL *.o -o MyApp -lGLEW -lglfw && rm *.o && ./MyApp && rm MyApp 