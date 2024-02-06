const int N = 2000000;
const int M = 40000000;
#include <vector>
#include <iostream>
#include <fstream>
#include <tuple>
struct SignedGraph {
    int n, m;
    std::vector < std::tuple <int, int, int> > son[N];
    int u[M], v[M], w[M];
    void input(std::ifstream &fin) {
        fin.ignore();
        fin >> n;
        while (fin >> u[m] >> v[m] >> w[m]) {
            son[u[m]].push_back({v[m], w[m], m});
            son[v[m]].push_back({u[m], w[m], m});
            m++;
        }
    }
} G;
struct Solution {
    std::vector <int> S1, S2;
    double value;
    Solution() { value = 0; }
    void input(std::ifstream &fin) {
        int t;
        fin >> t;
        S1.resize(t);
        for (auto &i : S1) fin >> i;
        fin >> t;
        S2.resize(t);
        for (auto &i : S2) fin >> i;
        fin >> value;
    }
    void output(std::ostream &fout) {
        fout << S1.size() << '\n';
        int firtag = 1;
        for (auto i : S1) {
            if (firtag) firtag = 0;
            else fout << ' ';
            fout << i;
        }
        fout << '\n';
        fout << S2.size() << '\n';
        firtag = 1;
        for (auto i : S2) {
            if (firtag) firtag = 0;
            else fout << ' ';
            fout << i;
        }
        fout << '\n';
        fout << value << '\n';
    }
    void trans(std::vector < std::pair <int, int> > v) {
        S1.clear(), S2.clear();
        for (auto [u, w] : v) {
            if (w == 1) S1.push_back(u);
            else S2.push_back(u);
        }
    }
    int operator < (const Solution &b) const {
        return value < b.value;
    }
    int n() const {
        return S1.size() + S2.size();
    }
} S;
struct Method {
    std::string type;
    double Wv, Wc, Ww;
    int K;
    int maxNegRound;
    double c1, c2, T;
    void input(std::ifstream &fin) {
        fin >> type;
        if (type == "MBG") {
            fin >> Wv >> Wc >> Ww;
            fin >> K >> maxNegRound >> c1 >> c2 >> T;
        }
        else if (type == "MDBG") {
            abort();
            Wv = 0;
            fin >> Wc >> Ww;
        }
        else abort();
    }
} method;