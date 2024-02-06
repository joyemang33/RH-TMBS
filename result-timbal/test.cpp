#include <bits/stdc++.h>
using namespace std;
const int T = 17, K = 8;

string ftoa(double x) {
    stringstream ss;
    ss << x;
    return ss.str();
}

pair <string, string> f[] = {
    // {"wikigrowth", "growth"},
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
};

double curT;
void run(string name) {
    string cmd = "python launcher.py < ../datasets/" + name + ".txt > out 2> /dev/null";
    chrono::steady_clock::time_point start = chrono::steady_clock::now();
    system(cmd.c_str());
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    curT = (end - start).count() / 1e9;
}
void chk(string name, int beta) {
    string cmd = "./val ../datasets/" + name + ".txt out " + ftoa(beta) + " > tmp";
    system(cmd.c_str());
}

int main(int argc, char **argv) {
    cout << setw(T) << "beta" << setw(T) << "|V|" << setw(T) << "|E|" << setw(T) << "value" << setw(T) << "time" << endl;
    for (auto i : f) {
        cout << i.second << ":\n";
        run(i.first);
        for (double j = 1; j <= K; j += 0.5) {
            chk(i.first, pow(2, j));
            int v, e;
            double value;
            ifstream fin("tmp");
            fin >> v >> e >> value;
            cout << fixed << setprecision(3) << setw(T) << pow(2, j)
                 << setw(T) << v
                 << setw(T) << e
                 << fixed << setprecision(3) << setw(T) << value
                 << fixed << setprecision(3) << setw(T) << curT << endl;
        }
    }
}