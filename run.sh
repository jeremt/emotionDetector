#!/bin/bash

if [ "$1" == "help" ]; then
  echo "Usage:"
  echo "  ./run.sh [command]"
  echo ""
  echo "Commands:"
  echo "  default           without argument, it will lauch the program"
  echo "  test              run all tests"
  echo "  testPatternFinder test the pattern finder"
  echo ""
  exit
fi

mkdir -p build && cd build && cmake .. && make && cd ..

if [ "$1" == "tests" ]; then
  ./testPatternFinder
elif [ "$1" == "PatternFinder" ]; then
  ./testPatternFinder
else
  ./emotionDetector
fi
