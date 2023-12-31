#include "hidden_singles.h"


int hidden_singles(SudokuBoard *p_board)
{
    int counter = 0;
    HiddenSingle hidden_singles[BOARD_SIZE * 3];  // Array to store hidden single cell and value pairs

    // Check for hidden singles in rows, columns, and boxes
    for (int i = 0; i < BOARD_SIZE; i++) {
        find_hidden_single(p_board->p_rows[i], hidden_singles, &counter);
        find_hidden_single(p_board->p_cols[i], hidden_singles, &counter);
        find_hidden_single(p_board->p_boxes[i], hidden_singles, &counter);
    }

    // Apply the found hidden singles to the board
    for (int i = 0; i < counter; i++) {
        Cell *p_cell = hidden_singles[i].p_cell;
        int value = hidden_singles[i].value;
        // Ensure the cell hasn't been solved by other techniques
        if (p_cell->num_candidates > 1) {
            set_candidates(p_cell, &value, 1);
            p_board->solved_counter++;
        }
    }

    return counter;
}

int find_hidden_single_values(Cell **p_cells, int *hidden_single_values) {
    int counter = 0;
    int candidate_counts[BOARD_SIZE] = {0};  // Array to count candidate occurrences

    // Count occurrences of candidates in the cells
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (is_candidate(p_cells[i], j + 1)) {
                candidate_counts[j]++;
            }
        }
    }

    // Find candidates that appear exactly once
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (candidate_counts[i] == 1) {
            hidden_single_values[counter++] = i + 1;
        }
    }

    return counter;
}

void find_hidden_single(Cell **p_cells, HiddenSingle *p_hidden_singles, int *p_counter) {
    int hidden_single_values[BOARD_SIZE];
    int num_hidden_singles = find_hidden_single_values(p_cells, hidden_single_values);

    // Find the cell containing each hidden single value
    for (int i = 0; i < num_hidden_singles; i++) {
        int value = hidden_single_values[i];
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (is_candidate(p_cells[j], value)) {
                p_hidden_singles[*p_counter].p_cell = p_cells[j];
                p_hidden_singles[*p_counter].value = value;
                (*p_counter)++;
                break;  // Move to the next hidden single value
            }
        }
    }
}

