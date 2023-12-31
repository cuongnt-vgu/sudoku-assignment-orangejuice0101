#pragma once

#include "sudoku.h"
#include "utils.c"
#include "cell.h"

int hidden_pairs(SudokuBoard *p_board);
int find_hidden_pairs(Cell **p_cells);
