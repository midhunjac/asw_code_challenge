#!/usr/bin/env bash
make
if [ ! -d "build" ]; then
mkdir build
fi
mv Challenge.exe build/Challenge.exe
rm *.o