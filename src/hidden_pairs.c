#include "hidden_pairs.h"


int hidden_pairs(SudokuBoard *p_board)
{
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
            int candidate_pairs[BOARD_SIZE * BOARD_SIZE][2] = {0};
            int pair_count = 0;

            for (int cell_index = 0; cell_index < BOARD_SIZE; cell_index++) {
                Cell *cell = p_units[unit_index][cell_index];
                if (cell->num_candidates == 2) {
                    bool found_pair = false;
                    for (int i = 0; i < pair_count; i++) {
                        if (cell->candidates[0] == candidate_pairs[i][0] &&
                            cell->candidates[1] == candidate_pairs[i][1] ||
                            cell->candidates[0] == candidate_pairs[i][1] &&
                            cell->candidates[1] == candidate_pairs[i][0]) {
                            found_pair = true;
                            break;
                        }
                    }
                    if (!found_pair) {
                        candidate_pairs[pair_count][0] = cell->candidates[0];
                        candidate_pairs[pair_count][1] = cell->candidates[1];
                        pair_count++;
                    }
                }
            }

            for (int i = 0; i < pair_count; i++) {
                int pair[2] = {candidate_pairs[i][0], candidate_pairs[i][1]};
                // Check if the pair is hidden within the unit
                bool hidden = true;
                for (int j = 0; j < BOARD_SIZE; j++) {
                    Cell *cell = p_units[unit_index][j];
                    if (cell->num_candidates > 2 &&
                        (is_candidate(cell, pair[0]) || is_candidate(cell, pair[1]))) {
                        hidden = false;
                        break;
                    }
                }
                if (hidden) {
                    // Hidden pair found, eliminate other candidates from cells in the unit
                    for (int j = 0; j < BOARD_SIZE; j++) {
                        Cell *cell = p_units[unit_index][j];
                        if (cell->num_candidates > 2) {
                            unset_candidate(cell, pair[0]);
                            unset_candidate(cell, pair[1]);
                        }
                    }
                }
            }
        }
    }
}
