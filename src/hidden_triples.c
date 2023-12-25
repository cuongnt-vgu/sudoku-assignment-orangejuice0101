#include "hidden_triples.h"


int hidden_triples(SudokuBoard *p_board)
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
            int candidate_triples[BOARD_SIZE * BOARD_SIZE][3] = {0};
            int triple_count = 0;

            for (int cell_index = 0; cell_index < BOARD_SIZE; cell_index++) {
                Cell *cell = p_units[unit_index][cell_index];
                if (cell->num_candidates == 3) {
                    bool found_triple = false;
                    for (int i = 0; i < triple_count; i++) {
                        if (is_subset(cell->candidates, 3, candidate_triples[i], 3)) {
                            found_triple = true;
                            break;
                        }
                    }
                    if (!found_triple) {
                        memcpy(candidate_triples[triple_count], cell->candidates, 3 * sizeof(int));
                        triple_count++;
                    }
                }
            }

            for (int i = 0; i < triple_count; i++) {
                int triple[3] = {candidate_triples[i][0], candidate_triples[i][1], candidate_triples[i][2]};
                // Check if the triple is hidden within the unit
                bool hidden = true;
                for (int j = 0; j < BOARD_SIZE; j++) {
                    Cell *cell = p_units[unit_index][j];
                    if (cell->num_candidates > 3 &&
                        has_common_elements(cell->candidates, cell->num_candidates, triple, 3)) {
                        hidden = false;
                        break;
                    }
                }
                if (hidden) {
                    // Hidden triple found, eliminate other candidates from cells in the unit
                    for (int j = 0; j < BOARD_SIZE; j++) {
                        Cell *cell = p_units[unit_index][j];
                        if (cell->num_candidates > 3) {
                            for (int k = 0; k < 3; k++) {
                                unset_candidate(cell, triple[k]);
                            }
                        }
                    }
                }
            }
        }
    }
}