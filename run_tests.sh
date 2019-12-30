#!/bin/bash

cd ./test
echo '***** Starting pqs test suite...'
make clean
echo '***** Building with gcc7 c++11...'
make gcc7_cpp11
make clean
echo '***** Building with gcc9 c++2a...'
make gcc9_cpp2a
make clean
echo '***** Building with gcc9 c++2a concepts...'
make gcc9_concepts_cpp2a
make clean
cd ./compile_fail
make clean
echo '***** running compile fail tests...'
make
make clean
echo '***** ...Tests completed'