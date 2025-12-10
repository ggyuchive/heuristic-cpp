#include "TableSolver.hpp"

// Usage: ./run.sh 04_table 01.in
int main(int argc, char* argv[]) {
    string filename = argv[1];
    TableSolver solver(filename);
    solver.run();
}
