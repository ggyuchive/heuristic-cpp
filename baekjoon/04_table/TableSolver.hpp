#include <vector>
#include <iostream>
#include <sstream>
#include <set>
#include <algorithm>
#include <cmath>
#include "../Solver.hpp"

class TableSolver final : public Solver
{
public:
    TableSolver(string in_file_) : Solver(in_file_) {}

    void getInput() override {
        ifstream& fin = fileIO.fin;
        fin >> M >> N;
    }

    void solve() override {
        if (prob_num == 1 || prob_num == 2 || prob_num == 5 || prob_num == 6)
            bruteforceSolver();
        else if (prob_num == 3 || prob_num == 4)
            numberTheorySolver();
    }

    void validate() override {
        checkAnswer(ans, true);
    }

    void getOutput() override {
        ofstream& fout = fileIO.fout;
        fout << ans.size() << '\n';
        for (const auto& v : ans) {
            for (const auto& num : v) {
                fout << num << ' ';
            }
            fout << '\n';
        }
    }

private:
    void bruteforceSolver() {
        vector<vector<int>> v(N, vector<int>(N, 0));
        vector<int> cand;
        int MIN = pow(10, N-1);
        int MAX = pow(10, N) - 1;
        while (MIN % M > 0) MIN++;
        for (int num = MIN; num <= MAX; num += M) {
            cand.push_back(num);
        }
        int K = cand.size();
        long long complexity = 1;
        for (int i = K; i >= K-N+1; i--) complexity *= i;
        cout << "Complexity: " << complexity << '\n';
        // kPn permutation
        bool found = false;
        vector<bool> pick(K, false);
        fill(pick.begin(), pick.begin()+N, true);
        int loop = 0;
        do {
            vector<int> choose;
            for (int i = 0; i < K; i++)
                if (pick[i]) choose.push_back(cand[i]);
            do {
                for (int i = 0; i < N; i++) {
                    int num = choose[i];
                    for (int j = N-1; j >= 0; j--) {
                        v[i][j] = num%10;
                        num/=10;
                    }
                }
                if (checkAnswer(v))
                {
                    ans = v;
                    found = true;
                    break;
                }
                loop++;
                if (loop%10000000 == 0)
                    cout << loop << '\n';
            } while (next_permutation(choose.begin(), choose.end()));
            if (found) break;
        } while (prev_permutation(pick.begin(), pick.end()));
    }

    void numberTheorySolver() {

    }

    bool checkAnswer(vector<vector<int>>& v, bool printError = false) {
        stringstream ss;
        int sz = v.size();
        if (sz < 2)
            ss << "ans.size() >= 2 is not satisfied." << '\n';
        if (sz > N)
            ss << "ans.size() <= " << N << " is not satisfied." << '\n';

        set<long long> nums;
        for (int i = 0; i < sz; i++) {
            if (v[i].size() != sz)
                ss << "ans.size() != " << v[i].size() << '\n';
            long long num = 0;
            for (int j = 0; j < sz; j++) {
                if (j == 0 && v[i][j] == 0)
                    ss << "Start can not be 0" << '\n';
                num = num * 10 + v[i][j];
            }
            if (nums.contains(num))
                ss << "Duplicated number: " << num << '\n';
            nums.insert(num);
        }
        for (int i = 0; i < sz; i++) {
            long long num = 0;
            for (int j = 0; j < sz; j++) {
                if (j == 0 && v[j][i] == 0)
                    ss << "Start can not be 0" << '\n';
                num = num * 10 + v[j][i];
            }
            if (nums.contains(num))
                ss << "Duplicated number: " << num << '\n';
            nums.insert(num);
        }

        long long num1 = 0;
        long long num2 = 0;
        for (int i = 0; i < sz; i++) {
            num1 = num1 * 10 + v[i][i];
            num2 = num2 * 10 + v[i][sz-1-i];
        }
        if (nums.contains(num1))
            ss << "Duplicated number: " << num1 << '\n';
        if (nums.contains(num2))
            ss << "Duplicated number: " << num2 << '\n';
        nums.insert(num1);
        nums.insert(num2);

        for (auto& num : nums) {
            if (num % M > 0) {
                ss << "Error: " << num << "%" << M << " > 0" << '\n';
            }
        }
        
        if (printError)
            cout << ss.str();
        return ss.str().empty();
    }

    vector<vector<int>> ans;
    int M;
    int N;
};
