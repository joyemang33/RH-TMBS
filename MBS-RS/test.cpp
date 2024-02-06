#include <bits/stdc++.h>
using namespace std;
const int T = 13;
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
    if (argc != 3) {
        printf("Call %s path methodFile\n", argv[0]);
        return 0;
    }
    path = argv[1], method = argv[2];
    cout << setw(T) << "name" << setw(T) << "|V|" << setw(T) << "|E|" << setw(T) << "value" << setw(T) << "time" << endl;
    for (auto i : f) {
        run(i.first);
        int v, e;
        double value;
        ifstream fin("tmp");
        fin >> v >> e >> value;
        cout << setw(T) << i.second << setw(T) << v << setw(T) << e << setprecision(2) << setw(T) << fixed << value << setw(T) << setprecision(3) << curT << endl;
    }
    cout << endl;
    cout << "method:\n";
    string tmp;
    ifstream fmethod(method);
    while (getline(fmethod, tmp)) cout << tmp << endl;
}