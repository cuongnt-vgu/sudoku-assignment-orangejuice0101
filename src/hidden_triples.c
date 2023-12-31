#include "hidden_triples.h"
#include "cell.h"


int hidden_triples(SudokuBoard *p_board) {
    int counter = 0;

    // Check for hidden triples in rows, columns, and boxes
    for (int i = 0; i < BOARD_SIZE; i++) {
        counter += find_hidden_triples(p_board->p_rows[i]);
        counter += find_hidden_triples(p_board->p_cols[i]);
        counter += find_hidden_triples(p_board->p_boxes[i]);
    }

    return counter;
}

int find_hidden_triples(Cell **p_cells) {
    int counter = 0;
    int candidate_counts[BOARD_SIZE] = {0};
    int triple_candidates[3] = {0};

    // Count occurrences of candidates in the cells
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (is_candidate(p_cells[i], j + 1)) {
                candidate_counts[j]++;
            }
        }
    }

    // Find three candidates that appear exactly three times
    int triple_count = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (candidate_counts[i] == 3) {
            triple_candidates[triple_count] = i + 1;
            triple_count++;
            if (triple_count == 3) {
                break;
            }
        }
    }

    // If a hidden triple is found, remove other candidates from cells containing the triple
    if (triple_count == 3) {
        for (int i = 0; i < BOARD_SIZE; i++) {
            bool contains_triple = true;
            for (int j = 0; j < 3; j++) {
                if (!is_candidate(p_cells[i], triple_candidates[j])) {
                    contains_triple = false;
                    break;
                }
            }
            if (contains_triple) {
                for (int j = 0; j < BOARD_SIZE; j++) {
                    if (!is_candidate(p_cells[i], triple_candidates[j])) {
                        unset_candidate(p_cells[i], j + 1);
                        counter++;
                    }
                }
            }
        }
    }

    return counter;
}