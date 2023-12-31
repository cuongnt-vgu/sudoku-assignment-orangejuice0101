#include "hidden_pairs.h"
#include "cell.h"


int hidden_pairs(SudokuBoard *p_board) {
    int counter = 0;

    // Check for hidden pairs in rows, columns, and boxes
    for (int i = 0; i < BOARD_SIZE; i++) {
        counter += find_hidden_pairs(p_board->p_rows[i]);
        counter += find_hidden_pairs(p_board->p_cols[i]);
        counter += find_hidden_pairs(p_board->p_boxes[i]);
    }

    return counter;
}

int find_hidden_pairs(Cell **p_cells) {
    int counter = 0;
    int candidate_counts[BOARD_SIZE] = {0};
    int pair_candidates[2][BOARD_SIZE] = {0};

    // Count occurrences of candidates in the cells
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (is_candidate(p_cells[i], j + 1)) {
                candidate_counts[j]++;
            }
        }
    }

    // Find two candidates that appear exactly twice
    int pair_count = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (candidate_counts[i] == 2) {
            pair_candidates[pair_count][pair_count] = i + 1;
            pair_count++;
            if (pair_count == 2) {
                break;
            }
        }
    }

    // If a hidden pair is found, remove other candidates from cells containing the pair
    if (pair_count == 2) {
        for (int i = 0; i < BOARD_SIZE; i++) {
            if (is_candidate(p_cells[i], pair_candidates[0][0]) &&
                is_candidate(p_cells[i], pair_candidates[1][0])) {
                for (int j = 0; j < BOARD_SIZE; j++) {
                    if (j + 1 != pair_candidates[0][0] && j + 1 != pair_candidates[1][0]) {
                        unset_candidate(p_cells[i], j + 1);
                        counter++;
                    }
                }
            }
        }
    }

    return counter;
}