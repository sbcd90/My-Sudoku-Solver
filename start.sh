#!/bin/bash
g++ -o poi sudoku_ex_cover_gen.cc
g++ -o poi1 sudoku_solver.cc
./poi
clear
./poi1
rm poi
rm poi1
rm row_format.txt
rm ex_cover.txt
