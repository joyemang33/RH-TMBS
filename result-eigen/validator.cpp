#include "MBG.h"
#include <cassert>
#include <cmath>
#include <iomanip>
#include <tuple>

double beta;

int inSet[N];
int vis[N];

std::tuple <double, int, int> ans, cur;

void dfs(int u) {
    std::get<1>(cur) += 2;
    vis[u] = 1;
    for (auto [v, w, id] : G.son[u]) if (inSet[v]) {
        std::get<2>(cur) += 1;
        std::get<0>(cur) += w * inSet[u] * inSet[v] == 1 ? 1 : 1 - beta;
        if (!vis[v]) dfs(v);
    }
}

int main(int argc, char **argv) {
    if (argc != 4) {
        printf("Call %s inputFile outputFile beta\n", argv[0]);
        return 0;
    }
    std::ifstream fin(argv[1]), fout(argv[2]);
    beta = atof(argv[3]);
    G.input(fin);
    S.input(fout);
    for (auto i : S.S1) inSet[i] = 1;
    for (auto i : S.S2) inSet[i] = -1;
    
    for (int i = 0; i < G.n; i++) if (inSet[i] && !vis[i]) {
        cur = std::make_tuple(0., 0, 0);
        dfs(i);
        if (std::get<0>(cur) < 0) continue;
        std::get<0>(ans) = std::max(std::get<0>(ans), std::get<0>(cur));
        std::get<1>(ans) = std::max(std::get<1>(ans), std::get<1>(cur));
        std::get<2>(ans) = std::max(std::get<2>(ans), std::get<2>(cur));
    }
    auto [a, b, c] = ans;
    printf("%d %d %.4lf\n", b / 2, c / 2, a / 2);
    return 0;
}