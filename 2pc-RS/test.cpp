#include <bits/stdc++.h>
using namespace std;
const int T = 13;
pair <string, string> f[] = {
    {"cloister", "cloister"},
    {"congress", "congress"},
    {"highlandtribes", "highland"},
    
    {"bitcoin", "bitcoin"},
    {"epinions", "epinions"},
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
    if (system(cmd.c_str())) exit(0);
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
    cout << setw(T) << "name"
         << setw(T) << "avgVal"
         << setw(T) << "varVal"
         << setw(T) << "medVal"
         << setw(T) << "optimal"
         << setw(T) << "|V|"
         << setw(T) << "|E|"
         << setw(T) << "avgTime"
         << endl;
    int rounds = atoi(argv[3]);
    for (auto i : f) {
        tuple <double, int, int> opt(0, 0, 0);
        double sumV = 0, sumV2 = 0, sumT = 0;
        vector <double> values;
        for (int t = 0; t < rounds; t++) {
            run(i.first);
            int v, e;
            double value;
            ifstream fin("tmp");
            fin >> v >> e >> value;
            sumV += value;
            sumV2 += value * value;
            sumT += curT;
            opt = max(opt, make_tuple(value, v, e));
            values.push_back(value);
        }
        sort(values.begin(), values.end());
        cout << setw(T) << i.second
             << setw(T) << fixed << setprecision(6) << sumV / rounds
             << setw(T) << fixed << setprecision(6) << sumV2 / rounds - sumV * sumV / rounds / rounds
             << setw(T) << fixed << setprecision(6) << values[rounds / 2]
             << setw(T) << fixed << setprecision(6) << get<0>(opt)
             << setw(T) << get<1>(opt)
             << setw(T) << get<2>(opt)
             << setw(T) << fixed << setprecision(3) << sumT / rounds
             << endl;
    }
    cout << endl;
    cout << "rounds: " << rounds << endl;
    cout << "method:\n";
    string tmp;
    ifstream fmethod(method);
    while (getline(fmethod, tmp)) cout << tmp << endl;
}