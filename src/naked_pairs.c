#include "naked_pairs.h"

bool hasTwoCandidates(Cell *cell) {
    return cell->num_candidates == 2;
}
int countNakedPairsInRow(Cell **row) {
    int count = 0;

    for (int i = 0; i < 8; i++) {
        for (int j = i + 1; j < 9; j++) {
            if (hasTwoCandidates(&row[i]) && hasTwoCandidates(&row[j])) {
                // Check if the candidates are the same
                if (row[i].candidates[0] == row[j].candidates[0] &&
                    row[i].candidates[1] == row[j].candidates[1]) {
                    count++;
                }
            }
        }
    }

    return count;
}
int countNakedPairsInColumn(Cell **column) {
    int count = 0;

    for (int i = 0; i < 8; i++) {
        for (int j = i + 1; j < 9; j++) {
            if (hasTwoCandidates(&column[i]) && hasTwoCandidates(&column[j])) {
                // Check if the candidates are the same
                if (column[i].candidates[0] == column[j].candidates[0] &&
                    column[i].candidates[1] == column[j].candidates[1]) {
                    count++;
                }
            }
        }
    }

    return count;
}
int countNakedPairsInCell(Cell **cell) {
    int count = 0;

    for (int i = 0; i < 8; i++) {
        for (int j = i + 1; j < 9; j++) {
            if (hasTwoCandidates(&cell[i]) && hasTwoCandidates(&cell[j])) {
                // Check if the candidates are the same
                if (cell[i].candidates[0] == cell[j].candidates[0] &&
                    cell[i].candidates[1] == cell[j].candidates[1]) {
                    count++;
                }
            }
        }
    }

    return count;
}
int naked_pairs(SudokuBoard *p_board)
{
    int result;
    result=countNakedPairsInRow(p_rows)+countNakedPairsInColumn(p_cols)+countNakedPairsInCell(p_cells);
    printf("The number of naked pairs is %d", result);
    return 0;
}