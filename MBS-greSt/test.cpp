#include <bits/stdc++.h>
using namespace std;
const int T = 13, K = 8;

string ftoa(double x) {
    stringstream ss;
    ss << fixed << setprecision(3) << x;
    return ss.str();
}

pair <string, string> f[] = {
    // {"random", "random"},
    {"bitcoin", "bitcoin"},
    {"epinions", "epinions"},
    {"slashdot", "slashdot"},
    {"twitterreferendum", "twitter"},
    {"wikiconflict", "conflict"},
    {"wikielections", "elections"},
    {"wikipolitics", "politics"},
    // {"cloister", "cloister"},
    // {"congress", "congress"},
    // {"highlandtribes", "highland"},
    {"wikigrowth", "growth"},
};

string path;
double curT;
void run(string name, double beta) {
    string cmd = "./main " + path + name + ".txt tmp " + ftoa(beta);
    chrono::steady_clock::time_point start = chrono::steady_clock::now();
    system(cmd.c_str());
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    curT = (end - start).count() / 1e9;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Call %s path rounds\n", argv[0]);
        return 0;
    }
    path = argv[1];
    cout << setw(T) << "name" << setw(T) << "|V|" << setw(T) << "|E|" << setw(T) << fixed << "value" << setw(T) << "time" << endl;
    int rounds = atoi(argv[2]);
    for (auto i : f) {
        int bv = 0, be = 0;
        double bvalue = 0;
        for (int k = 0; k < rounds; k++) {
            run(i.first, 1e9);
            int v, e;
            double value;
            ifstream fin("tmp");
            fin >> v >> e >> value;
            bv = max(bv, v);
            be = max(be, e);
            bvalue = max(bvalue, value);
        }
        cout << setw(T) << i.second
                << setw(T) << bv
                << setw(T) << be
                << setw(T) << fixed << setprecision(3) << bvalue
                << setw(T) << fixed << setprecision(3) << curT << endl;
    }
    cout << endl;
    cout << "rounds: " << rounds << endl;
}