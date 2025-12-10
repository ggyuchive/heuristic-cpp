#pragma once
#include "IOUtil.hpp"
using namespace std;

// Solver base class
class Solver
{
public:
    explicit Solver(string in_file_) : fileIO(FileIO(in_file_)) {
        prob_num = fileIO.problem_num;
    }
    virtual ~Solver() {}

    // Get input from file
    virtual void getInput() = 0;

    // Real logic for solution
    virtual void solve() = 0;

    // Validate solution's condition
    virtual void validate() = 0;

    // Get output to file
    virtual void getOutput() = 0;

    // Solve problem which runs in main
    virtual void run() {
        getInput();
        solve();
        validate();
        getOutput();
    }

protected:
    FileIO fileIO;
    int prob_num;
};
