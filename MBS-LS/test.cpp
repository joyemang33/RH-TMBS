#include <bits/stdc++.h>
using namespace std;
const int T = 13, K = 8;

string method1 = "MBG\n0 1 -", method2 = "\n1 20 0.8 0.8 1.5";

string ftoa(double x) {
    stringstream ss;
    ss << fixed << setprecision(3) << x;
    return ss.str();
}

pair <string, string> f[] = {
    // {"wikigrowth", "growth"},
    // {"random", "random"},
    {"bitcoin", "bitcoin"},
    {"twitterreferendum", "twitter"},
    {"wikielections", "elections"},
    // {"slashdot", "slashdot"},
    // {"epinions", "epinions"},
    // {"wikipolitics", "politics"},
    // {"wikiconflict", "conflict"},
    // {"cloister", "cloister"},
    // {"congress", "congress"},
    // {"highlandtribes", "highland"},
};

string path;
double curT;
void run(string name) {
    string cmd = "./main " + path + name + ".txt out method";
    chrono::steady_clock::time_point start = chrono::steady_clock::now();
    system(cmd.c_str());
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    cmd = "./val " + path + name + ".txt out method" + " 0 > tmp";
    system(cmd.c_str());
    curT = (end - start).count() / 1e9;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Call %s path\n", argv[0]);
        return 0;
    }
    path = argv[1];
    cout << setw(T) << "name" << setw(T) << "|V|" << setw(T) << "|E|" << setw(T) << fixed << "value" << setw(T) << "time" << endl;
    for (auto i : f) {
        string method = method1 + ftoa(1e9) + method2;
        ofstream fout("method");
        fout << method << endl;
        fout.close();
        run(i.first);
        int v, e;
        double value;
        ifstream fin("tmp");
        fin >> v >> e >> value;
        cout << setw(T) << i.second
             << setw(T) << v
             << setw(T) << e
             << setw(T) << fixed << setprecision(3) << value
             << setw(T) << fixed << setprecision(3) << curT << endl;
    }
    cout << "method:\n";
    cout << method1 << "?" << method2 << endl;
}