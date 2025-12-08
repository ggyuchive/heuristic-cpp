#include "SudokuSolver.hpp"

// Usage: ./run.sh 01_sudoku 01.in
int main(int argc, char* argv[]) {
    string filename = argv[1];
    SudokuSolver solver(filename);
    solver.solve();
}
