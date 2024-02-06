#include "MBG.h"
#include <cassert>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <random>
#include <tuple>
#include <set>

double beta;
std::mt19937 rnd((std::random_device())());
std::tuple <double, int, int> ans, val[N];
std::set <int> curS;

int fa[N], sn[N], del[N];
int gf(int a) {
    if (fa[a] == a) return a;
    gf(fa[a]);
    sn[a] ^= sn[fa[a]];
    fa[a] = fa[fa[a]];
    return fa[a];
}
void upd(std::tuple <double, int, int> &a, std::tuple <double, int, int> b) {
    if (std::get<0>(b) < 0) return;
    std::get<0>(a) = std::max(std::get<0>(a), std::get<0>(b));
    std::get<1>(a) = std::max(std::get<1>(a), std::get<1>(b));
    std::get<2>(a) = std::max(std::get<2>(a), std::get<2>(b));
}
std::vector <int> eid;
void check() {
    eid.clear();
    for (auto i : curS) {
        fa[i] = i;
        sn[i] = 0;
        val[i] = {0, 1, 0};
        for (auto [j, w, id] : G.son[i]) if (!del[j] && j < i) eid.push_back(id);
    }
    std::shuffle(eid.begin(), eid.end(), rnd);
    for (auto i : eid) {
        auto u = G.u[i], v = G.v[i], w = G.w[i];
        gf(u), gf(v);
        if (fa[u] != fa[v]) {
            auto U = fa[u], V = fa[v], W = (w == 1 ? 0 : 1) ^ sn[u] ^ sn[v];
            std::get<0>(val[U]) += std::get<0>(val[V]);
            std::get<1>(val[U]) += std::get<1>(val[V]);
            std::get<2>(val[U]) += std::get<2>(val[V]);
            fa[V] = U;
            sn[V] = W;
            std::get<0>(val[U]) += 1;
            std::get<2>(val[U]) += 1;
        }
        else {
            std::get<2>(val[fa[u]]) += 1;
            std::get<0>(val[fa[u]]) += 1;
            if ((w == 1 ? 0 : 1) != (sn[u] ^ sn[v])) {
                std::get<0>(val[fa[u]]) -= beta;
            }
        }
    }
    for (auto i : curS) if (fa[i] == i) {
        upd(ans, val[i]);
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
    for (int i = 0; i < G.n; i++) curS.insert(i);
    int tmp;
    while (fout >> tmp, tmp != -1) {
        while (tmp--) {
            int p;
            fout >> p;
            curS.erase(p);
            del[p] = 1;
        }
        check();
        for (auto i : curS) val[i] = {0, std::get<1>(val[i]), 0}, gf(i);
        for (auto i : curS) {
            double v;
            fout >> v;
            sn[i] = v > 0;
        }
        for (auto i : eid) {
            auto u = G.u[i], v = G.v[i], w = G.w[i];
            std::get<2>(val[fa[u]]) += 1;
            std::get<0>(val[fa[u]]) += 1;
            if ((w == 1 ? 0 : 1) != (sn[u] ^ sn[v])) {
                std::get<0>(val[fa[u]]) -= beta;
            }
        }
        for (auto i : curS) if (fa[i] == i) {
            upd(ans, val[i]);
        }
    }
    while (fout >> tmp, tmp != -1) {
        curS.insert(tmp);
        del[tmp] = 0;
    }
    check();
    auto [a, b, c] = ans;
    printf("%d %d %.4lf\n", b, c, a);
    return 0;
}