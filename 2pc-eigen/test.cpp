#include <bits/stdc++.h>
using namespace std;
const int T = 13;
pair <string, string> f[] = {
    // {"random", "random"},
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
string method;
double curT;
void run(string name) {
    string cmd = "python2 main.py " + name + " " + method + " > out";
    chrono::steady_clock::time_point start = chrono::steady_clock::now();
    system(cmd.c_str());
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    cmd = "./val ../datasets/" + name + ".txt out method 0 > tmp";
    system(cmd.c_str());
    curT = (end - start).count() / 1e9;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Call %s method\n", argv[0]);
        return 0;
    }
    method = argv[1];
    cout << setw(T) << "name"
         << setw(T) << "|V|"
         << setw(T) << "|E|"
         << setw(T) << "value"
         << setw(T) << "time" << endl;
    for (auto i : f) {
        run(i.first);
        int v, e;
        double value;
        ifstream fin("tmp");
        fin >> v >> e >> value;
        cout << setw(T) << i.second
             << setw(T) << v
             << setw(T) << e
             << setw(T) << fixed << setprecision(6) << value
             << setw(T) << fixed << setprecision(3) << curT << endl;
    }
    cout << endl;
    cout << "method: " << method << endl;
}