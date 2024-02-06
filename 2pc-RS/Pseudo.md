```
K = 1
p = 0.6
C = 6
T: maxNegRound
alpha = 0.98
beta = 0.005
T1 = 7
Solution solve(start, Wv) {                                        // min(|V|T,n)log(n)delta
    S = {start};
    negRound = T;
    opt = 0;
    while (negRound > 0) {
        curList = AddTopK();
        if (Rand(p)) curList += FlipTopK();
        if (Rand(p / |S|)) curList += DelTopK();                   // delta |S|
        curList = TopK(curList);
        act = RandFrom(curList);
        if (act.value < 0) negRound--;
        else negRound += T;
        Action(act);
        for (x: neighbours of act.pos) update(x);                  // delta log(|S|)
        update(act.pos);
        if (chkMax(opt, curVal / |V|)) negRound += T;              // curVal = E - 2 * wrongEdges + Wv * |V|
        else negRound--;
    }
    undo last some operations;
    return;
}
solution solve() {                                                 // nT1log^2(n)log(1/beta)delta
    ans = 1;
    sol = emptyset;
    T = T1;
    nxt = rand from V;
    do {                                                           // nT1log(n)delta+nlog(n)delta
        cnt = max(1, |V| / max(ans, 1) * C);
        chk = 0;
        repeat (cnt) rounds {
            cur = solve(nxt, -ans);
            if (cur.polarize < ans) {
                nxt = rand from V;
                continue;
            }
            sol = cur;
            chk = ans / cur.polarize < 1 - (alpha + beta);
            ans = cur.polarize * alpha;
            T = T1 * ans;
            remove nodes with degree less than ans;
            break;
        }
    } while (chk == 1);
    return sol;
}
```