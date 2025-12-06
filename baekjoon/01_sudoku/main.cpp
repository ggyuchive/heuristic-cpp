#include "solver.hpp"

// Usage: ./run.sh 01.in
int main(int argc, char* argv[]) {
    std::string filename = argv[1];
    Solver solver(filename);
    solver.solve();
}
