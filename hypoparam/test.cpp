#include <bits/stdc++.h>
using namespace std;
const int wT = 13;
pair <string, string> f[] = {
    // {"cloister", "cloister"},
    // {"congress", "congress"},
    // {"highlandtribes", "highland"},
    // {"random", "random"},
    {"bitcoin", "bitcoin"},
    {"epinions", "epinions"},
    {"slashdot", "slashdot"},
    {"twitterreferendum", "twitter"},
    {"wikiconflict", "conflict"},
    {"wikielections", "elections"},
    {"wikipolitics", "politics"},
};

string path;
double curT;
int Wv = 0, Wc = 1;
double Ww;
int K = 1, T = 20;
double p = 0.8, C = 1.5;
int run() {
    string cmd = "timeout -k 0s 500s ./main " + path + " out method";
    chrono::steady_clock::time_point start = chrono::steady_clock::now();
    if (system(cmd.c_str())) return 1;
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    cmd = "./val " + path + " out method 0 > tmp";
    system(cmd.c_str());
    curT = (end - start).count() / 1e9;
    return 0;
}
int main(int argc, char **argv) {
    if (argc != 5) {
        printf("Call %s inputfile beta rounds param\n", argv[0]);
        return 0;
    }
    path = argv[1], Ww = -atof(argv[2]) + 1;
    int rounds = atoi(argv[3]);
    cout << setw(wT) << "value"
         << setw(wT) << "maxValue"
         << setw(wT) << "avgValue"
         << setw(wT) << "medValue"
         << setw(wT) << "variance"
         << setw(wT) << "avgTime"
         << setw(wT) << "failCounts" << endl;
    string param = argv[4];
    function <void()> start, doit;
    function <bool()> end;
    double curVal;
    int pre;
    if (param == "T") {
        pre = 0;
        start = [&]() { curVal = T = 5; };
        doit = [&]() { curVal = T += 5; };
        end = [&]() { return curVal > 40; };
    }
    else if (param == "p") {
        pre = 6;
        start = [&]() { curVal = p = 0.4; };
        doit = [&]() { curVal = p += 0.05; };
        end = [&]() { return curVal > 0.95 + 1e-10; };
    }
    else if (param == "C") {
        pre = 2;
        start = [&]() { curVal = C = 0.5; };
        doit = [&]() { curVal = C += 0.25; };
        end = [&]() { return curVal > 3.25; };
    }
    else abort();
    for (start(); !end(); doit()) {
        double maxV = 0, sumV = 0, sumV2 = 0, sumTime = 0;
        int failrounds = 0;
        vector <double> values;
        for (int t = 0; t < rounds; t++) {
            ofstream method("method");
            method << "MBG\n" << Wv << ' ' << Wc << ' ' << fixed << setprecision(10) << Ww << '\n';
            method << K << ' ' << T << ' ';
            method << fixed << setprecision(10) << p << ' ' << fixed << setprecision(10) << p << ' ';
            method << fixed << setprecision(10) << C << '\n';
            method.close();
            if (run()) {
                failrounds++;
                continue;
            }
            int v, e;
            double value;
            ifstream fin("tmp");
            fin >> v >> e >> value;
            maxV = max(maxV, value);
            sumV += value;
            sumV2 += value * value;
            sumTime += curT;
            values.push_back(value);
        }
        sort(values.begin(), values.end());
        cout << setw(wT) << fixed << setprecision(pre) << curVal;
        if (failrounds == rounds) {
            for (int i = 0; i < 5; i++) cout << setw(wT) << "N/A";
        }
        else {
            int rr = values.size();
            cout << setw(wT) << fixed << setprecision(2) << maxV
                 << setw(wT) << fixed << setprecision(2) << sumV / rr
                 << setw(wT) << fixed << setprecision(2) << values[rr / 2]
                 << setw(wT) << fixed << setprecision(2) << sumV2 / rr - sumV * sumV / rr / rr
                 << setw(wT) << fixed << setprecision(2) << sumTime / rr;
        }
        if (failrounds) cout << setw(wT) << failrounds << endl;
        else cout << endl;
    }
    cout << endl;
    cout << "rounds: " << rounds << endl;
    cout << "beta: " << argv[2] << endl;
    cout << "method:\n";
    cout << "MBG\n" << Wv << ' ' << Wc << ' ' << Ww << '\n';
    cout << setprecision(1);
    if (param == "K") cout << "? ";
    else cout << K << ' ';
    if (param == "T") cout << "? ";
    else cout << T << ' ';
    if (param == "p") cout << "? ? ";
    else cout << p << ' ' << p << ' ';
    if (param == "C") cout << "? ";
    else cout << C << '\n';
}