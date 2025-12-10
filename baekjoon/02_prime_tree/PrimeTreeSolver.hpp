#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include "../Solver.hpp"

struct Graph
{
    Graph(ifstream& fin, int V_): V(V_) {
        edge.assign(V, vector<int>());
        for (int i = 0; i < V-1; i++) {
            int a, b;
            fin >> a >> b;
            edge[a-1].push_back(b-1);
            edge[b-1].push_back(a-1);
        }
    }
    int V;
    vector<vector<int>> edge;
};

class PrimeTreeSolver final : public Solver
{
public:
    PrimeTreeSolver(string in_file_) : Solver(in_file_) {}

    void getInput() override {
        ifstream& fin = fileIO.fin;
        fin >> tc;
        for (int t = 0; t < tc; t++) {
            int V; fin >> V;
            Graph graph(fin, V);
            graphs.push_back(graph);
        }
    }

    void solve() override {
        for (int i = 0; i < tc; i++) {
            solver(graphs[i], i);
        }
    }

    void validate() override {
        for (auto v : ans) {
            vector<int> tmpv(v);
            sort(tmpv.begin(), tmpv.end());
            for (int i = 0; i < v.size(); i++) {
                if (tmpv[i] != i+1) {
                    cout << "Error: " << tmpv[i] << " is unexpected." << '\n';
                    return;
                }
            }
        }

        int total_edge = 0;
        int bad_edge = 0;
        for (int i = 0; i < tc; i++) {
            total_edge += (graphs[i].V - 1);
            bad_edge += countBadEdge(ans[i], i);
        }

        double ratio = double(bad_edge)/double(total_edge);
        cout << "Bad Edge: " << bad_edge << ", Total Edge: " << total_edge << ", Ratio: " << ratio << '\n';

        int score = 0;
        double score_table[10] = {0.4, 0.33, 0.26, 0.19, 0.12, 0.05, 0.01, 0.005, 0.001, 0.0};
        for (int i = 0; i < 10; i++) {
            if (ratio > score_table[i]) {
                score = i; break;
            }
            else score = i+1;
        }
        cout << "Score: " << score << '\n';
    }

    void getOutput() override {
        ofstream& fout = fileIO.fout;
        for (auto& v : ans) {
            for (auto& num : v) fout << num << ' ';
            fout << '\n';
        }
    }

private:
    void solver(const Graph& g, int t) {
        int N = g.V;
        vector<int> answer(N, 0);
        vector<int> adjCount(N, 0);
        vector<int> badCount = computeBad(N);
        for (int i = 0; i < g.edge.size(); i++) {
            for (auto j : g.edge[i]) {
                adjCount[i]++; adjCount[j]++;
            }
        }
        for (auto& num: adjCount) num/=2;
        vector<pair<int,int>> badInd; // bad count, number
        vector<pair<int,int>> adjInd; // adj count, number
        for (int i = 0; i < N; i++) {
            badInd.push_back({badCount[i], i+1});
            adjInd.push_back({adjCount[i], i+1});
        }
        // If bad is small, put adj large
        sort(badInd.begin(), badInd.end());
        sort(adjInd.begin(), adjInd.end(), greater<pair<int,int>>());
        for (int i = 0; i < N; i++) {
            int curInd = badInd[i].second;
            int toPut = adjInd[i].second;
            answer[toPut-1] = curInd;
        }
        for (int i = 0; i < 1000; i++) {
            pair<int,int> pr = pick_two(N);
            int prev = countBadEdge(answer, t);
            swap(answer[pr.first], answer[pr.second]);
            //cout << pr.first << ' ' << pr.second << '\n';
            int cur = countBadEdge(answer, t);
            //cout << prev << ' ' << cur << '\n';
            if (prev < cur) {
                swap(answer[pr.first], answer[pr.second]);
            }
        }
        ans.push_back(answer);
    }

    pair<int,int> pick_two(int N) {
        mt19937 rng((unsigned)chrono::steady_clock::now().time_since_epoch().count());
        uniform_int_distribution<int> dist(0, N-1);
        int u = dist(rng);
        int v = dist(rng);
        while (v == u) v = dist(rng);
        return {u, v};
    }

    vector<int> computeBad(int N) {
        vector<int> bad(N+1);
        for (int i = 0; i <= N; ++i) bad[i] = i;
        for (int i = 2; i <= N; ++i) {
            if (bad[i] == i) {
                for (int j = i; j <= N; j += i) {
                    bad[j] -= bad[j] / i;
                }
            }
        }
        for (int i = 1; i <= N; i++) bad[i] = (i-1)-bad[i];
        for (int i = 2; i <= N; i++) bad[i] += N/i-1;
        bad[1] = 0;
        return vector<int>(bad.begin()+1, bad.end());
    }

    int countBadEdge(vector<int>& answer, int t) {
        int bad_edge = 0;
        Graph& graph = graphs[t];
        for (int a = 0; a < graph.V; a++) {
            for (auto& b : graph.edge[a]) {
                if (gcd(answer[a], answer[b]) >= 2)
                    bad_edge++;
            }
        }
        bad_edge >>= 1;
        return bad_edge;
    }

    int gcd(int a, int b) { return b == 0 ? (a) : gcd(b, a%b); }

    int tc;
    vector<Graph> graphs;
    vector<vector<int>> ans;
    int total_edge;
};
