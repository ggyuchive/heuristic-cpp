#include <vector>
#include <iostream>
#include "../Solver.hpp"

typedef vector<vector<bool>> BoolVec2;
typedef vector<vector<vector<bool>>> BoolVec3;

class SudokuSolver final : public Solver
{
public:
    SudokuSolver(string in_file_)
    : Solver(in_file_), total_count(0), blank_count(0), filled_count(0) {}

    void getInput() override {
        ifstream& fin = fileIO.fin;
        fin >> N;
        D = N * N;
        total_count = D * D;
        arr.assign(D, vector<int>(D, 0));
        ans.assign(D, vector<int>(D, 0));
        for (int i = 0; i < D; i++) {
            for (int j = 0; j < D; j++) {
                fin >> arr[i][j];
                ans[i][j] = arr[i][j];
                if (arr[i][j] == 0)
                    blank_count++;
            }
        }
    }

    void solve() override {
        int& prob_num = fileIO.problem_num;
        cout << "Problem: " << prob_num << ", Blank Count: " << blank_count << ", Total Count: " << total_count << '\n';
        if (prob_num == 5)
            constructSolver();
        else if (prob_num == 1 || prob_num == 2)
            bruteforceSolver();
        //else
        //    bruteforceSolver();
    }

    void validate() override {
        for (int i = 0; i < D; i++) {
            for (int j = 0; j < D; j++) {
                if (arr[i][j] == 0 && ans[i][j] > 0)
                    filled_count++;
            }
        }
        for (int i = 0; i < D; i++) {
            vector<bool> haveRow(D, false);
            vector<bool> haveCol(D, false);
            for (int j = 0; j < D; j++) {
                int& numRow = ans[i][j];
                int& numCol = ans[j][i];

                if (numRow <= 0 || numRow > D) {
                    cout << "Error: There is number " << numRow << " in answer." << '\n';
                }
                if (haveRow[numRow-1]) {
                    cout << "Error: Duplicate number " << numRow << " in answer." << '\n';
                }
                haveRow[numRow-1] = true;

                if (numCol <= 0 || numCol > D) {
                    cout << "Error: There is number " << numCol << " in answer." << '\n';
                }
                if (haveCol[numCol-1]) {
                    cout << "Error: Duplicate number " << numCol << " in answer." << '\n';
                }                
                haveCol[numCol-1] = true;
            }
        }
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                int sx = (i/N)*N; int sy = (j/N)*N;
                vector<bool> haveGrid(D, false);
                for (int p = sx; p < sx+N; p++) {
                    for (int q = sy; q < sy+N; q++) {
                        int& num = ans[p][q];
                        if (num <= 0 || num > D) {
                            cout << "Error: There is number " << num << " in answer." << '\n';
                        }
                        if (haveGrid[num-1]) {
                            cout << "Error: Duplicate number " << num << " in answer." << '\n';
                        }                
                        haveGrid[num-1] = true;
                    }
                }
            }
        }
        cout << "Filled count: " << filled_count << '\n';
    }

    void getOutput() override {
        ofstream& fout = fileIO.fout;
        for (auto& v : ans) {
            for (auto& num : v) fout << num << ' ';
            fout << '\n';
        }
    }

private:
    uint64_t bruteforceSolver() {
        BoolVec3 candidate(D, BoolVec2(D, vector<bool>(D, true)));

        uint64_t complexity = 1;

        // O (D * D * D)
        while (true) {
            int filledCnt = 0;
            // Check if candidate is 1
            for (int i = 0; i < D; i++) {
                for (int j = 0; j < D; j++) {
                    if (ans[i][j] > 0)
                        continue;
                    // check row
                    for (int a = 0; a < D; a++) {
                        int& num = ans[i][a];
                        if (num > 0)
                            candidate[i][j][num-1] = false;
                    }
                    // check col
                    for (int a = 0; a < D; a++) {
                        int& num = ans[a][j];
                        if (num > 0)
                            candidate[i][j][num-1] = false;
                    }
                    // check grid
                    int sx = (i/N)*N; int sy = (j/N)*N;
                    for (int a = sx; a < sx+N; a++) {
                        for (int b = sy; b < sy+N; b++) {
                            int& num = ans[a][b];
                            if (num > 0)
                                candidate[i][j][num-1] = false;
                        }
                    }
                    int possCnt = 0; int possNum = 0;
                    for (int k = 0; k < D; k++) {
                        if (candidate[i][j][k]) possCnt++, possNum = k+1;
                    }
                    if (possCnt == 1) {
                        ans[i][j] = possNum;
                        filledCnt++;
                    }
                }
            }
            if (filledCnt == 0) break;
        }
        return complexity;
    }

    void constructSolver() {
        for (int a = 0; a < N; a++) {
            for (int b = 0; b < N; b++) {
                int i = a*N+b;
                for (int c = 0; c < N; c++) {
                    for (int d = 0; d < N; d++) {
                        int j = c*N+d;
                        int num = 1;
                        num += (a + b * N + c * N + d);
                        num %= D;
                        if (num == 0) num = D;
                        ans[i][j] = num;
                    }
                }
            }
        }
    }

    vector<vector<int>> arr; // D * D
    vector<vector<int>> ans; // D * D
    int N;
    int D;
    int total_count;
    int blank_count;
    int filled_count;
};
