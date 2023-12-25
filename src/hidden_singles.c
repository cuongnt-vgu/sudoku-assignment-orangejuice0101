#include "hidden_singles.h"


int hidden_singles(SudokuBoard *p_board)
{
    // Check for hidden singles in rows, columns, and boxes
    for (int unit_type = 0; unit_type < 3; unit_type++) {
        Cell **p_units[BOARD_SIZE];  // Pointers to rows, columns, or boxes
        if (unit_type == 0) {
            p_units = p_board->p_rows;
        } else if (unit_type == 1) {
            p_units = p_board->p_cols;
        } else {
            p_units = p_board->p_boxes;
        }

        for (int unit_index = 0; unit_index < BOARD_SIZE; unit_index++) {
            int candidate_counts[BOARD_SIZE] = {0};

            for (int cell_index = 0; cell_index < BOARD_SIZE; cell_index++) {
                Cell *cell = p_units[unit_index][cell_index];
                for (int i = 0; i < cell->num_candidates; i++) {
                    candidate_counts[cell->candidates[i] - 1]++;
                }
            }

            for (int candidate = 0; candidate < BOARD_SIZE; candidate++) {
                if (candidate_counts[candidate] == 1) {
                    // Hidden single found, set the value
                    for (int cell_index = 0; cell_index < BOARD_SIZE; cell_index++) {
                        Cell *cell = p_units[unit_index][cell_index];
                        if (is_candidate(cell, candidate + 1)) {
                            int *candidates = {candidate + 1};
                            set_candidates(cell, candidates, 1);
                        }
                    }
                }
            }
        }
    }
}

