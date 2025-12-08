#include "PrimeTreeSolver.hpp"

// Usage: ./run.sh 02_prime_tree 01.in
int main(int argc, char* argv[]) {
    string filename = argv[1];
    PrimeTreeSolver solver(filename);
    solver.solve();
}
