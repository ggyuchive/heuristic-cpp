#include <vector>
#include <iostream>
#include <queue>
#include "../Solver.hpp"

struct Coor {
    int L; int R; int T; int B;
};

class XorSolver final : public Solver
{
public:
    XorSolver(string in_file_) : Solver(in_file_) {}

    void getInput() override {
        ifstream& fin = fileIO.fin;
        fin >> N;
        arr.assign(N, vector<int>(N, 0));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                fin >> arr[i][j];
            }
        }
    }

    void solve() override {
        if (prob_num <= 9)
            greedySolver();
        else
            adhocSolver();
    }

    void validate() override {
        int K = ans.size();
        if (K > 40000) {
            cout << "Error: ans size must be less than 40000, but " << K << '\n';
        }
        vector<vector<int>> rep(N, vector<int>(N, 0));
        for (const auto& coor : ans) {
            if (!(1 <= coor.L && coor.L <= N))
                cout << "Error: L is " << coor.L << '\n';
            if (!(1 <= coor.R && coor.R <= N))
                cout << "Error: R is " << coor.R << '\n';
            if (!(1 <= coor.T && coor.T <= N))
                cout << "Error: T is " << coor.T << '\n';
            if (!(1 <= coor.B && coor.B <= N))
                cout << "Error: B is " << coor.B << '\n';
            if (coor.L > coor.R)
                cout << "Error: not " << coor.L << " <= " << coor.R << '\n';
            if (coor.T > coor.B)
                cout << "Error: not " << coor.T << " <= " << coor.B << '\n';

            flip(rep, coor);
        }
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (rep[i][j] != arr[i][j])
                    cout << "Error: (" << i << "," << j << ") is different; "
                        << "expected: " << arr[i][j] << ", real: " << rep[i][j] << '\n';
            }
        }
        cout << "Score: " << K << '\n';
    }

    void getOutput() override {
        ofstream& fout = fileIO.fout;
        fout << ans.size() << '\n';
        for (const auto& coor : ans) {
            fout << coor.L << ' ' << coor.R << ' ' << coor.T << ' ' << coor.B << '\n';
        }
    }

private:
    void adhocSolver() {
        // TODO
        greedySolver();
    }

    void greedySolver() {
        vector<vector<bool>> visited(N, vector<bool>(N, false));
        for (int sx = 0; sx < N; sx++) {
            for (int sy = 0; sy < N; sy++) {
                if (arr[sx][sy] == 1 && !visited[sx][sy]) {
                    int py = sy;
                    while (py < N && arr[sx][py] == 1 && !visited[sx][py]) {
                        py++;
                    }
                    py--;
                    int px = sx;
                    while (px < N) {
                        bool tmp = true;
                        for (int y = sy; y <= py; y++) {
                            if (arr[px][y] == 0 || visited[px][y])
                                tmp=false;
                        }
                        if (!tmp) break;
                        for (int y = sy; y <= py; y++)
                            visited[px][y] = true;
                        px++;
                    }
                    px--;
                    //cout << sx << ' ' << px << ' ' << sy << ' ' << py << '\n';
                    ans.emplace_back(Coor{sy+1, py+1, sx+1, px+1});
                }
            }
        }
    }

    void flip(vector<vector<int>>& arr, const Coor& coor) {
        for (int x = coor.L-1; x < coor.R; x++) {
            for (int y = coor.T-1; y < coor.B; y++) {
                arr[y][x] ^= 1;
            }
        }
    }

    int N;
    vector<vector<int>> arr;
    vector<Coor> ans;
};
