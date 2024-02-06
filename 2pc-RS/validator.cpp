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
    if (argc != 5) {
        printf("Call %s inputFile outputFile methodFile ifCheck\n", argv[0]);
        return 0;
    }
    std::ifstream fin(argv[1]), fout(argv[2]), fmethod(argv[3]);
    std::string ifCheck(argv[4]);
    G.input(fin);
    S.input(fout);
    method.input(fmethod);
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
    if (method.type == "MDBG") value /= S.S1.size() + S.S2.size();
    E /= 2;
    
    if (ifCheck == "1") {
        assert(checkConnectity());
        assert(fabs(value - S.value) <= 1e-3 * std::max(value, 1.));
    }
    else {
        assert(ifCheck == "0");
        std::cout << S.S1.size() + S.S2.size() << ' ' << E << ' ' << std::fixed << std::setprecision(6) << value << '\n';
    }
}