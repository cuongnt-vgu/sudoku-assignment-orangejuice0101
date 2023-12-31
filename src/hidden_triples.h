#pragma once

#include "sudoku.h"
#include "utils.c"
#include "cell.h"

int hidden_triples(SudokuBoard *p_board);
int find_hidden_triples(Cell **p_cells);