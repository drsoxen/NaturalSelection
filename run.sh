#!/bin/sh
# pkill QuickTime
rm -rf output
rm -rf Result.mp4
mkdir output

set -e

g++ -std=c++11 -c *.cpp -Ilib/include
g++ *.o -o MyApp -lgvc -lcgraph && rm *.o && ./MyApp && rm MyApp 

cd output
# echo Converting Images
# mogrify -format png *.ppm
# rm -r *.ppm
echo Resizing Images
mogrify *.ppm -filter point -resize 1000x1000 *.ppm
echo Creating Video
ffmpeg -framerate 30 -pattern_type glob -i '*.ppm' -c:v libx264 -r 30 -pix_fmt yuv420p Result.mp4
mv Result.mp4 ..
cd ..
qlmanage -p Result.mp4
rm -r output