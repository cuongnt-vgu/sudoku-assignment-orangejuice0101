#include "naked_triples.h"

#include "naked_triples.h"
#include "sudoku.c"

int naked_triples(SudokuBoard *p_board) {
    int counter = 0;

    // Check for naked triples in rows, columns, and boxes
    for (int i = 0; i < BOARD_SIZE; i++) {
        counter += find_naked_triples(p_board->p_rows[i]);
        counter += find_naked_triples(p_board->p_cols[i]);
        counter += find_naked_triples(p_board->p_boxes[i]);
    }

    return counter;
}

int find_naked_triples(Cell **p_cells) {
    int counter = 0;

    // Create a candidate triple array to store potential naked triples
    NakedTriple candidate_triples[BOARD_SIZE * (BOARD_SIZE - 1) * (BOARD_SIZE - 2) / 6];
    int triple_count = 0;

    // Find triples of cells with the same three candidates
    for (int i = 0; i < BOARD_SIZE - 2; i++) {
        for (int j = i + 1; j < BOARD_SIZE - 1; j++) {
            for (int k = j + 1; k < BOARD_SIZE; k++) {
                if (p_cells[i]->num_candidates == 3 &&
                    p_cells[j]->num_candidates == 3 &&
                    p_cells[k]->num_candidates == 3 &&
                    same_candidates(p_cells[i], p_cells[j]) &&
                    same_candidates(p_cells[i], p_cells[k])) {
                    candidate_triples[triple_count].p_cell1 = p_cells[i];
                    candidate_triples[triple_count].p_cell2 = p_cells[j];
                    candidate_triples[triple_count].p_cell3 = p_cells[k];
                    triple_count++;
                }
            }
        }
    }

    // Check if each candidate triple is a true naked triple
    for (int i = 0; i < triple_count; i++) {
        NakedTriple triple = candidate_triples[i];
        if (is_naked_triple(p_cells, triple.p_cell1, triple.p_cell2, triple.p_cell3)) {
            counter += remove_other_candidates(p_cells, triple.p_cell1, triple.p_cell2, triple.p_cell3);
        }
    }

    return counter;
}

// Check if three cells form a naked triple (no other cells in the unit share their candidates)
bool is_naked_triple(Cell **p_cells, Cell *p_cell1, Cell *p_cell2, Cell *p_cell3) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (p_cells[i] != p_cell1 && p_cells[i] != p_cell2 && p_cells[i] != p_cell3 &&
            has_common_candidate(p_cells[i], p_cell1)) {
            return false;
        }
    }
    return true;
}

// Remove other candidates from cells in the unit except the naked triple cells
int remove_other_candidates(Cell **p_cells, Cell *p_cell1, Cell *p_cell2, Cell *p_cell3) {
    int counter = 0;
    int candidates[3] = {0};  // Store the candidates of the naked triple
    get_candidates(p_cell1, candidates);

    for (int i = 0; i < BOARD_SIZE; i++) {
        if (p_cells[i] != p_cell1 && p_cells[i] != p_cell2 && p_cells[i] != p_cell3) {
            for (int j = 0; j < 3; j++) {
                if (is_candidate(p_cells[i], candidates[j]))
                                      unset_candidate(p_cells[i], candidates[j]);
                      counter++;
                  }
              }
          }
       return counter;
      }


     
  


