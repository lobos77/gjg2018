#!/usr/bin/env bash
#to use a more recent compiler
#scl enable devtoolset-3 bash
#cmake -DCMAKE_CXX_COMPILER=g++
make -j4
mv pizouille res
cd res; ./pizouille; cd ..
