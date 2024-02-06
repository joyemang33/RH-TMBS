#include "MBG.h"
#include <bits/stdc++.h>
using namespace std;

double bet;
mt19937 rnd((random_device())());
int fa[N], sn[N];
int updT[N];
double val[N];
int gf(int a) {
    if (fa[a] == a) return a;
    gf(fa[a]);
    sn[a] ^= sn[fa[a]];
    fa[a] = fa[fa[a]];
    return fa[a];
}

tuple <double, int, int> res[N];
tuple <double, int, int> rmain() {
    vector <int> pid(G.m);
    for (int i = 0; i < G.m; i++) pid[i] = i;
    shuffle(pid.begin(), pid.end(), rnd);
    for (int i = 0; i < G.n; i++) fa[i] = i;
    for (auto i : pid) {
        int u = G.u[i], v = G.v[i], w = G.w[i] == -1;
        gf(u), gf(v);
        if (fa[u] != fa[v]) {
            fa[fa[v]] = fa[u];
            sn[fa[v]] = w ^ sn[u] ^ sn[v];
        }
    }
    for (int i = 0; i < G.m; i++)
        G.w[i] = (G.w[i] == -1) ^ sn[G.u[i]] ^ sn[G.v[i]];
    for (int i = 0; i < G.n; i++) gf(i);
    priority_queue < tuple <double, int, int> > pq;
    for (int i = 0; i < G.n; i++) {
        for (auto& [j, w, id] : G.son[i]) {
            w = G.w[id];
            if (w == 0) val[i] -= 1;
            else val[i] += bet;
        }
        pq.push({val[i], i, updT[i]});
    }
    vector <int> ids;
    while (!pq.empty()) {
        auto [V, id, chk] = pq.top();
        pq.pop();
        if (chk != updT[id]) continue;
        ids.push_back(id);
        sn[id] = -1;
        for (auto& [j, w, id] : G.son[id]) {
            if (w == 0) val[j] += 1;
            else val[j] -= bet;
            if (sn[j] != -1) {
                updT[j]++;
                pq.push({val[j], j, updT[j]});
            }
        }
    }
    reverse(ids.begin(), ids.end());
    for (int i = 0; i < G.n; i++) fa[i] = i, res[i] = {0, 1, 0};
    tuple <double, int, int> ans{0, 0, 0};
    for (auto u : ids) {
        sn[u] = 0;
        for (auto [j, w, id] : G.son[u]) {
            if (sn[j] == -1) continue;
            int v = gf(j);
            if (u != v) {
                get<0>(res[u]) += get<0>(res[v]);
                get<1>(res[u]) += get<1>(res[v]);
                get<2>(res[u]) += get<2>(res[v]);
                fa[v] = u;
            }
            get<0>(res[u]) += w == 0 ? 1 : -bet;
            get<2>(res[u]) += 1;
        }
        if (get<0>(res[u]) < 0) continue;
        get<0>(ans) = max(get<0>(res[u]), get<0>(ans));
        get<1>(ans) = max(get<1>(res[u]), get<1>(ans));
        get<2>(ans) = max(get<2>(res[u]), get<2>(ans));
    }
    return ans;
}

int main(int argc, char **argv) {
    if (argc != 4) {
        printf("Call %s inputFile outputFile beta\n", argv[0]);
        return 0;
    }
    std::ifstream fin(argv[1]);
    std::ofstream fout(argv[2]);
    bet = atof(argv[3]) - 1;
    G.input(fin);
    
    auto ans = rmain();
    fout << get<1>(ans) << ' '
         << get<2>(ans) << ' '
         << setprecision(6) << fixed << get<0>(ans) << '\n';
}