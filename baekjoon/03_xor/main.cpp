#include "XorSolver.hpp"

// Usage: ./run.sh 03_xor 01.in
int main(int argc, char* argv[]) {
    string filename = argv[1];
    XorSolver solver(filename);
    solver.run();
}
