#include <bits/stdc++.h>
using namespace std;
const int T = 13;
pair <string, string> f[] = {
    // {"random", "random"},
    {"bitcoin", "bitcoin"},
    {"twitterreferendum", "twitter"},
    {"wikielections", "elections"},
    // {"slashdot", "slashdot"},
    // {"epinions", "epinions"},
    // {"wikiconflict", "conflict"},
    // {"wikipolitics", "politics"},
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
    curT = (end - start).count() / 1e9;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Call %s path methodFile\n", argv[0]);
        return 0;
    }
    path = argv[1], method = argv[2];
    cout << setw(T) << "name" << setw(T) << "V1" << setw(T) << "V2" << setw(T) << "time" << endl;
    for (auto i : f) {
        run(i.first);
        double v1, v2;
        ifstream fin("out");
        fin >> v1 >> v2;
        cout << setw(T) << i.second << setw(T) << fixed << setprecision(3) << v1 << setw(T) << v2 << setw(T) << curT << endl;
    }
    cout << endl;
    cout << "method:\n";
    string tmp;
    ifstream fmethod(method);
    while (getline(fmethod, tmp)) cout << tmp << endl;
}