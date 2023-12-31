#pragma once

#include "sudoku.h"
#include "cell.h"

int naked_pairs(SudokuBoard *p_board);
int find_naked_pairs(Cell **p_cells);
bool is_naked_pair(Cell **p_cells, Cell *p_cell1, Cell *p_cell2);
int remove_other_candidates(Cell **p_cells, Cell *p_cell1, Cell *p_cell2);