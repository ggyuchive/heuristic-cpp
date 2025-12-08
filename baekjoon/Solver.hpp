#pragma once
using namespace std;

/*Solver base class*/
class Solver
{
public:
    // Get input from file
    virtual void getInput() = 0;

    // Solve problem which runs in main
    virtual void solve() = 0;

    // Get output to file
    virtual void getOutput() = 0;
    
    virtual ~Solver() {}
};
