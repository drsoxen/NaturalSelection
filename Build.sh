#!/bin/sh
g++ -std=c++11 -c *.cpp -Ilib/include
g++ *.o -o MyApp -lgvc -lcgraph && rm *.o && ./MyApp && rm MyApp 
