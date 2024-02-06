// use data on http://konect.cc/networks/wikipedia-growth/

#include <bits/stdc++.h>
using namespace std;
const int n = 1870709;
int main() {
    ifstream fin("./wikipedia-growth/out.wikipedia-growth");
    ofstream fout("./wikigrowth.txt");
    string tmp;
    getline(fin, tmp);
    fout << "# " << n << '\n';
    int u, v;
    while (fin >> u >> v) {
        int w;
        fin >> w;
        fin >> w;
        fout << u - 1 << '\t' << v - 1 << '\t' << (w < 1144447200 ? -1 : 1) << '\n';
    }
}

/*
39953145 e
19956191 -1
19996954 1
*/