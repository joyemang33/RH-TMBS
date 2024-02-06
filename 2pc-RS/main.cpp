#include "MBG.h"
#include <bits/stdc++.h>
using std::vector;
using std::set;
using std::pair;
using std::tuple;
using std::swap;
using std::min;
using std::max;
using std::cin;
using std::cout;
using std::cerr;
using std::endl;

template <class T> vector <T> operator += (vector <T> &a, const vector <T> &b) {
    for (auto i : b) a.push_back(i);
    return a;
}

typedef long long ll;
double &Wv = method.Wv, &Wc = method.Wc, &Ww = method.Ww;
std::mt19937_64 rnd((std::random_device())());

double Rand(double l, double r) {
    const double MAX = UINT64_MAX;
    return l + (rnd() / MAX) * (r - l);
}
int Rand(double p) {
    const double MAX = UINT64_MAX;
    return rnd() < MAX * p;
}

struct {
    int inSet, color;   // If the node is in the current set, if yes, and its color.
    double w0, w1;      // If the node is in the current set, w0 means change its color, w1 means delete it from the set.
                        // Otherwise w0 means add it to the set with color white, w1 means black.
    int ableAdd;        // if it can be add to the set. The value is the number of its neighbour that in the set.
    int ableDelete;     // if it can be delete from the set.
} a[N];
set <int> curS;
int &n = G.n;
double sumFI;
auto &son = G.son;
ll lstTag[N], lstTagCnt;
int d[N], ban[N];

void calcInfo(int x) {
    a[x].w0 = a[x].w1 = 0;
    if (a[x].inSet) {
        a[x].w1 = -Wv;
        for (auto [v, w, id] : son[x]) if (a[v].inSet) {
            if ((a[v].color == a[x].color) == (w == 1)) a[x].w0 += -Wc + Ww, a[x].w1 += -Wc;
            else a[x].w0 += Wc - Ww, a[x].w1 += -Ww;
        }
    }
    else {
        a[x].w0 = a[x].w1 = Wv;
        a[x].ableAdd = 0;
        for (auto [v, w, id] : son[x]) if (a[v].inSet) {
            a[x].ableAdd += 1;
            if ((a[v].color == 0) == (w == 1)) a[x].w0 += Wc, a[x].w1 += Ww;
            else a[x].w0 += Ww, a[x].w1 += Wc;
        }
    }
}


int dfn[N], low[N], dfsnow;
int sta[N], top;
void tarjan(int u) {
    dfn[u] = low[u] = ++dfsnow;
    sta[++top] = u;
    for (auto [v, w, id] : son[u]) if (a[v].inSet == 1) {
        if (dfn[v]) low[u] = min(low[u], dfn[v]);
        else {
            tarjan(v), low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u]) {
                do {
                    a[sta[top]].ableDelete++;
                } while (sta[top--] != v);
                a[u].ableDelete++;
            }
        }
    }
}

void calcAbleDelete() {
    top = dfsnow = 0;
    for (auto i : curS) dfn[i] = 0, a[i].ableDelete = 0;
    tarjan(*curS.begin());
    assert(top == 1);
    for (auto i : curS) a[i].ableDelete = a[i].ableDelete == 1;
}

void remove(int pos) {
    assert(curS.count(pos) && a[pos].inSet == 1);
    curS.erase(pos);
    sumFI -= Wv;
    for (auto [v, w, id] : son[pos]) {
        if (a[v].inSet) {
            if ((a[v].color == a[pos].color) == (w == 1)) a[v].w0 -= -Wc + Ww, a[v].w1 -= -Wc, sumFI -= Wc;
            else a[v].w0 -= Wc - Ww, a[v].w1 -= -Ww, sumFI -= Ww;
        }
        else {
            a[v].ableAdd--;
            if ((a[pos].color == 0) == (w == 1)) a[v].w0 -= Wc, a[v].w1 -= Ww;
            else a[v].w0 -= Ww, a[v].w1 -= Wc;
        }
    }
    a[pos].inSet = 0;
    calcInfo(pos);
}
void insert(int pos) {
    assert(curS.count(pos) == 0 && a[pos].inSet == 0);
    curS.insert(pos);
    sumFI += Wv;
    for (auto [v, w, id] : son[pos]) {
        if (a[v].inSet) {
            if ((a[v].color == a[pos].color) == (w == 1)) a[v].w0 += -Wc + Ww, a[v].w1 += -Wc, sumFI += Wc;
            else a[v].w0 += Wc - Ww, a[v].w1 += -Ww, sumFI += Ww;
        }
        else {
            a[v].ableAdd++;
            if ((a[pos].color == 0) == (w == 1)) a[v].w0 += 1, a[v].w1 += Ww;
            else a[v].w0 += Ww, a[v].w1 += 1;
        }
    }
    a[pos].inSet = 1;
    calcInfo(pos);
}


struct node {
    double value;
    int pos, opt;
    int operator < (const node &b) const {
        if (value != b.value) return value > b.value;
        if (pos != b.pos) return pos > b.pos;
        if (opt != b.opt) return opt > b.opt;
        return 0;
    }
};

vector < pair <int, node> > lstAdd[N];

struct valueSet {
    set <node> s;
    void clear() {
        s.clear();
    }
    void insert(const node &a) {
        s.insert(a);
    }
    void erase(const node &a) {
        s.erase(a);
    }
    vector <node> queryMaxK() {
        int rest = method.K;
        vector <node> ans;
        auto ite = s.begin();
        while (ite != s.end() && rest) {
            ans.push_back(*ite++);
            rest--;
        }
        return ans;
    }
} S1, S2;

vector <node> queryDeleteMaxK() {
    calcAbleDelete();
    vector <node> ans;
    for (auto i : curS) if (a[i].ableDelete) {
        ans.push_back({a[i].w1, i, 1});
    }
    sort(ans.begin(), ans.end());
    if (ans.size() > method.K) ans.resize(method.K);
    return ans;
}

void Init() {
    sumFI = 0;
    curS.clear();
    S1.clear(), S2.clear();
}

auto solve(int start) {
    Init();
    auto checkVertex = [&](int i) {
        if (ban[i]) return;
        for (auto [p, nd] : lstAdd[i]) {
            if (p == 1) S1.erase(nd);
            else if (p == 2) S2.erase(nd);
        }
        lstAdd[i].clear();
        if (a[i].inSet) {
            lstAdd[i].push_back({1, {a[i].w0, i, 0}});
        }
        else if (a[i].ableAdd) {
            lstAdd[i].push_back({2, {a[i].w0, i, 0}});
            lstAdd[i].push_back({2, {a[i].w1, i, 1}});
        }
        for (auto [p, nd] : lstAdd[i]) {
            if (p == 1) S1.insert(nd);
            else if (p == 2) S2.insert(nd);
        }
    };
    int neground = method.maxNegRound;
    insert(start);
    checkVertex(start);
    for (auto [v, w, id] : son[start]) checkVertex(v);
    double optimal = 0;
    vector < pair <int, int> > opts;
    while (1) {
        vector <node> curList;
        curList += S2.queryMaxK();
        if (Rand(method.c1)) curList += S1.queryMaxK();
        if (Rand(0.5) && Rand(2 * method.c2 * log(curS.size() + 1) / curS.size())) curList += queryDeleteMaxK();
        int p = curList.size();
        sort(curList.begin(), curList.end());
        p = min(p, method.K);
        if (curList.empty()) break;
        auto cnode = curList[rnd() % p];
        int pos = cnode.pos;
        if (a[pos].inSet) {
            if (cnode.opt == 0) {
                opts.push_back({pos, 0});
                remove(pos);
                a[pos].color ^= 1;
                insert(pos);
            }
            else {
                if (a[pos].color == 0) opts.push_back({pos, 1});
                else opts.push_back({pos, 2});
                remove(pos);
            }
        }
        else {
            opts.push_back({pos, 3});
            if (cnode.opt == 0) {
                a[pos].color = 0;
                insert(pos);
            }
            else {
                a[pos].color = 1;
                insert(pos);
            }
        }
        for (auto [v, w, id] : son[pos]) checkVertex(v);
        checkVertex(pos);
        if (sumFI / curS.size() <= optimal) {
            neground--;
        }
        else {
            neground += method.maxNegRound;
            opts.clear();
            optimal = sumFI / curS.size();
        }
        if (neground <= 0) break;
    }

    while (opts.size()) {
        auto [pos, opt] = opts.back();
        opts.pop_back();
        if (opt == 0) {
            remove(pos);
            a[pos].color ^= 1;
            insert(pos);
        }
        else if (opt == 3) {
            remove(pos);
        }
        else {
            a[pos].color = opt - 1;
            insert(pos);
        }
    }
    Solution S;
    S.value = sumFI;
    auto tmpS = curS;
    for (auto i : tmpS) {
        remove(i);
        if (a[i].color == 0) S.S1.push_back(i);
        else S.S2.push_back(i);
    }

    return S;
}

auto rmain1() {
    for (int i = 0; i < n; i++) a[i].w0 = a[i].w1 = Wv;
    ll rest = n * method.T;
    Solution ans;
    while (rest > 0) {
        auto curAns = solve(rnd() % n);
        ans = max(ans, curAns);
        rest -= curAns.n();
    }
    return ans;
}

int dfsBan(int pos, double chk) {
    ban[pos] = 1;
    int ans = 1;
    for (auto [v, w, id] : son[pos]) if (!ban[v]) {
        d[v]--;
        if (d[v] <= chk) ans += dfsBan(v, chk);
    }
    return ans;
}

auto rmain2() {
    method.maxNegRound = 7;
    double ans = 1;
    int rst = n;
    Solution S;
    for (int i = 0; i < n; i++) {
        a[i].w0 = a[i].w1 = 0;
        d[i] = son[i].size();
        ban[i] = 0;
    }
    Wv = -1;
    while (1) {
        int chk = 0, rounds = max(1., rst / max(ans, 1.) * method.T);
        int nxtstart;
        do nxtstart = rnd() % n; while (ban[nxtstart]);
        while (rounds--) {
            int start = nxtstart;
            do nxtstart = rnd() % n; while (ban[nxtstart]);
            auto curAns = solve(rnd() % n);
            if (curAns.value <= 0) continue;
            double dlt = curAns.value / (curAns.S1.size() + curAns.S2.size());
            ans += dlt;
            curAns.value = ans;
            S = curAns;
            chk = dlt / ans > 0.025;
            ans *= 0.98;
            Wv = -ans;
            for (int i = 0; i < n; i++) if (!ban[i]) {
                a[i].w0 = a[i].w1 = -ans;
                if (d[i] <= ans) rst -= dfsBan(i, ans);
            }
            for (int i = 0; i < n; i++) if (!ban[i]) {
                auto tmp = son[i];
                son[i].clear();
                for (auto [v, w, id] : tmp) if (!ban[v]) son[i].push_back({v, w, id});
            }
            method.maxNegRound = ans * 7;
            nxtstart = start;
            break;
        }
        if (chk == 0) break;
    }
    return S;
}

int main(int argc, char **argv) {
    if (argc != 4) {
        printf("Call %s inputFile outputFile methodFile\n", argv[0]);
        return 0;
    }
    std::ifstream fin(argv[1]), fmethod(argv[3]);
    std::ofstream fout(argv[2]);
    G.input(fin);
    method.input(fmethod);
    
    if (method.type == "MBG") {
        auto ans = rmain1();
        ans.output(fout);
    }
    else if (method.type == "MDBG") {
        auto ans = rmain2();
        ans.output(fout);
    }
}