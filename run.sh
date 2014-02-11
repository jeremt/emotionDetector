#!/bin/bash

if [ "$1" == "help" ]; then
  echo "Usage:"
  echo "  ./run.sh [command]"
  echo ""
  echo "Commands:"
  echo "  test           run all tests"
  echo "  testMachine   test the machine learning"
  echo ""
  exit
fi

mkdir -p build && cd build && cmake .. && make && cd ..

if [ "$1" == "test" ]; then
  ./testMachine
elif [ "$1" == "testMachine" ]; then
  ./testMachine
else
  ./emotionDetector
fi
