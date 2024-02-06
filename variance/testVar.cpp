#include <bits/stdc++.h>
using namespace std;
const int T = 13;
pair <string, string> f[] = {
    // {"random", "random"},
    {"bitcoin", "bitcoin"},
    // {"cloister", "cloister"},
    // {"congress", "congress"},
    {"epinions", "epinions"},
    // {"highlandtribes", "highland"},
    {"slashdot", "slashdot"},
    {"twitterreferendum", "twitter"},
    {"wikiconflict", "conflict"},
    {"wikielections", "elections"},
    {"wikipolitics", "politics"},
};

string path, method;
double curT;
void run(string name) {
    string cmd = "./main " + path + name + ".txt out " + method;
    chrono::steady_clock::time_point start = chrono::steady_clock::now();
    system(cmd.c_str());
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    cmd = "./val " + path + name + ".txt out " + method + " 0 > tmp";
    system(cmd.c_str());
    curT = (end - start).count() / 1e9;
}

int main(int argc, char **argv) {
    if (argc != 4) {
        printf("Call %s path methodFile rounds\n", argv[0]);
        return 0;
    }
    path = argv[1], method = argv[2];
    int rounds = atoi(argv[3]);
    cout << setw(T) << "name"
         << setw(T) << "minValue"
         << setw(T) << "maxValue"
         << setw(T) << "avgValue"
         << setw(T) << "variance"
         << setw(T) << "avgTime" << endl;
    for (auto i : f) {
        double minV = INFINITY, maxV = 0, sumV = 0, sumV2 = 0, sumTime = 0;
        for (int t = 0; t < rounds; t++) {
            run(i.first);
            int v, e;
            double value;
            ifstream fin("tmp");
            fin >> v >> e >> value;
            maxV = max(maxV, value);
            minV = min(minV, value);
            sumV += value;
            sumV2 += value * value;
            sumTime += curT;
        }
        cout << setw(T) << i.second 
             << setw(T) << fixed << setprecision(3) << minV
             << setw(T) << fixed << setprecision(3) << maxV
             << setw(T) << fixed << setprecision(3) << sumV / rounds
             << setw(T) << fixed << setprecision(3) << sumV2 / rounds - sumV * sumV / rounds / rounds
             << setw(T) << fixed << setprecision(3) << sumTime / rounds << endl;
    }
    cout << endl;
    cout << "rounds: " << rounds << endl;
    cout << "method:\n";
    string tmp;
    ifstream fmethod(method);
    while (getline(fmethod, tmp)) cout << tmp << endl;
}