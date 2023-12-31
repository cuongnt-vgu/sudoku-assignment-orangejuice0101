#pragma once

#include "sudoku.h"
#include "utils.c"

int naked_triples(SudokuBoard *p_board);
int find_naked_triples(Cell **p_cells);
bool is_naked_triple(Cell **p_cells, Cell *p_cell1, Cell *p_cell2, Cell *p_cell3);
int remove_other_candidates(Cell **p_cells, Cell *p_cell1, Cell *p_cell2, Cell *p_cell3) 