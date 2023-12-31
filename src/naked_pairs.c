#include "naked_pairs.h"

int naked_pairs(SudokuBoard *p_board) {
    int counter = 0;

    // Check for naked pairs in rows, columns, and boxes
    for (int i = 0; i < BOARD_SIZE; i++) {
        counter += find_naked_pairs(p_board->p_rows[i]);
        counter += find_naked_pairs(p_board->p_cols[i]);
        counter += find_naked_pairs(p_board->p_boxes[i]);
    }

    return counter;
}

int find_naked_pairs(Cell **p_cells) {
    int counter = 0;

    // Create a candidate pair array to store potential naked pairs
    NakedPair candidate_pairs[BOARD_SIZE * (BOARD_SIZE - 1) / 2];
    int pair_count = 0;

    // Find pairs of cells with the same two candidates
    for (int i = 0; i < BOARD_SIZE - 1; i++) {
        for (int j = i + 1; j < BOARD_SIZE; j++) {
            if (p_cells[i]->num_candidates == 2 &&
                p_cells[j]->num_candidates == 2 &&
                same_candidates(p_cells[i], p_cells[j])) {
                candidate_pairs[pair_count].p_cell1 = p_cells[i];
                candidate_pairs[pair_count].p_cell2 = p_cells[j];
                pair_count++;
            }
        }
    }

    // Check if each candidate pair is a true naked pair
    for (int i = 0; i < pair_count; i++) {
        NakedPair pair = candidate_pairs[i];
        if (is_naked_pair(p_cells, pair.p_cell1, pair.p_cell2)) {
            counter += remove_other_candidates(p_cells, pair.p_cell1, pair.p_cell2);
        }
    }

    return counter;
}

// Check if two cells form a naked pair (no other cells in the unit share their candidates)
bool is_naked_pair(Cell **p_cells, Cell *p_cell1, Cell *p_cell2) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (p_cells[i] != p_cell1 && p_cells[i] != p_cell2 &&
            has_common_candidate(p_cells[i], p_cell1)) {
            return false;
        }
    }
    return true;
}

// Remove other candidates from cells in the unit except the naked pair cells
int remove_other_candidates(Cell **p_cells, Cell *p_cell1, Cell *p_cell2) {
    int counter = 0;
    int candidates[2] = {0};  // Store the candidates of the naked pair
    get_candidates(p_cell1, candidates);

    for (int i = 0; i < BOARD_SIZE; i++) {
        if (p_cells[i] != p_cell1 && p_cells[i] != p_cell2) {
            for (int j = 0; j < 2; j++) {
                if (is_candidate(p_cells[i], candidates[j])) {
                    unset_candidate(p_cells[i], candidates[j]);
                    counter++;
                }
            }
        }
    }

    return counter;
}