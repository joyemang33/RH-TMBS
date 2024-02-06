#include "MBG.h"
#include <cassert>
#include <cmath>
#include <iomanip>

int inSet[N];
int vis[N];

int dfs(int u) {
    if (vis[u]) return 0;
    int ans = 1;
    vis[u] = 1;
    for (auto [v, w, id] : G.son[u]) if (inSet[v]) ans += dfs(v);
    return ans;
}
int checkConnectity() {
    for (int i = 0; i < G.n; i++) if (inSet[i]) {
        if (dfs(i) == S.S1.size() + S.S2.size()) return 1;
        return 0;
    }
    return 1;
}

int main(int argc, char **argv) {
    if (argc != 4) {
        printf("Call %s inputFile outputFile beta\n", argv[0]);
        return 0;
    }
    std::ifstream fin(argv[1]), fout(argv[2]);
    method.Wc = 1;
    method.Ww = 1 - atof(argv[3]);
    G.input(fin);
    S.input(fout);
    for (auto i : S.S1) inSet[i] = 1;
    for (auto i : S.S2) inSet[i] = -1;
    
    double value = 0;
    int E = 0;
    for (int i = 0; i < G.n; i++) if (inSet[i]) {
        value += 2 * method.Wv;
        for (auto [j, w, id] : G.son[i]) if (inSet[j]) {
            if ((w == 1) == (inSet[i] == inSet[j])) value += method.Wc;
            else value += method.Ww;
            E++;
        }
    }
    value /= 2;
    E /= 2;
    std::cout << S.S1.size() + S.S2.size() << ' ' << E << ' ' << std::fixed << std::setprecision(6) << value << '\n';
}