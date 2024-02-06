#include <bits/stdc++.h>
using namespace std;
const int T = 17, K = 8;

string ftoa(double x) {
    stringstream ss;
    ss << x;
    return ss.str();
}

pair <string, string> f[] = {
    {"wikigrowth", "growth"},
    // {"random", "random"},
    // {"bitcoin", "bitcoin"},
    // {"epinions", "epinions"},
    // {"slashdot", "slashdot"},
    // {"twitterreferendum", "twitter"},
    // {"wikiconflict", "conflict"},
    // {"wikielections", "elections"},
    // {"wikipolitics", "politics"},

    // {"cloister", "cloister"},
    // {"congress", "congress"},
    // {"highlandtribes", "highland"},
};

string method;
double curT;
void run(string name, int id) {
    string cmd = "python2 main.py " + name + " " + method + " > out" + ftoa(id);
    chrono::steady_clock::time_point start = chrono::steady_clock::now();
    system(cmd.c_str());
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    curT = (end - start).count() / 1e9;
}
void chk(string name, int id, double beta) {
    string cmd = "./val ../datasets/" + name + ".txt out" + ftoa(id) + " " + ftoa(beta) + " > tmp";
    system(cmd.c_str());
}

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Call %s method count\n", argv[0]);
        return 0;
    }
    method = argv[1];
    cout << setw(T) << "beta"
         << setw(T) << "max|V|"
         << setw(T) << "max|E|"
         << setw(T) << "avgValue"
         << setw(T) << "maxValue"
         << setw(T) << "varValue"
         << setw(T) << "avgTime" << endl;
    int CNT = atoi(argv[2]);
    for (auto i : f) {
        cout << i.second << ":\n";
        double sumT = 0;
        for (int t = 0; t < CNT; t++) {
            run(i.first, t);
            sumT += curT;
        }
        for (double j = 1; j <= K + 0.5; j += 0.5) {
            double beta = j == K + 0.5 ? 1e9 : pow(2, j);
            int maxV = 0, maxE = 0;
            double sumVal = 0, sumVal2 = 0, maxVal = 0;
            for (int t = 0; t < CNT; t++) {
                chk(i.first, t, beta);
                int v, e;
                double value;
                ifstream fin("tmp");
                fin >> v >> e >> value;
                maxV = max(maxV, v);
                maxE = max(maxE, e);
                sumVal += value;
                sumVal2 += value * value;
                maxVal = max(maxVal, value);
            }
            cout << setw(T) << beta
                 << setw(T) << fixed << setprecision(3) << maxV
                 << setw(T) << fixed << setprecision(3) << maxE
                 << setw(T) << fixed << setprecision(3) << sumVal / CNT
                 << setw(T) << fixed << setprecision(3) << maxVal
                 << setw(T) << fixed << setprecision(3) << sumVal2 / CNT - sumVal * sumVal / CNT / CNT
                 << setw(T) << fixed << setprecision(3) << sumT / CNT << endl;
        }
    }
    cout << endl;
    cout << "method: " << method << endl;
    for (int i = 0; i < CNT; i++) {
        system(("rm out" + ftoa(i)).c_str());
    }
}