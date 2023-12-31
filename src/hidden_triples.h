#pragma once

#include "sudoku.h"
#include "utils.c"

int hidden_triples(SudokuBoard *p_board);
int find_hidden_triples(Cell **p_cells);