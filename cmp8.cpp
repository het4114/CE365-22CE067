#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

map<char, set<char>> f, fl;
map<char, vector<string>> g;
map<char, map<char, string>> table;
set<char> v1, v2;
string in;

void first(char x) {
    if (v1.count(x)) return;
    v1.insert(x);

    for (auto r : g[x]) {
        if (islower(r[0]) || r[0] == '(' || r[0] == ')') {
            f[x].insert(r[0]);
        } else {
            for (char c : r) {
                if (c == x) break;
                first(c);
                f[x].insert(f[c].begin(), f[c].end());
                if (!f[c].count('ε')) break;
            }
        }
    }
}

void follow(char x) {
    if (v2.count(x)) return;
    v2.insert(x);

    if (x == 'S') fl[x].insert('$');

    for (auto& [l, rs] : g) {
        for (auto r : rs) {
            for (size_t i = 0; i < r.size(); i++) {
                if (r[i] == x) {
                    if (i + 1 < r.size()) {
                        char n = r[i + 1];
                        if (islower(n) || n == '(' || n == ')') {
                            fl[x].insert(n);
                        } else {
                            fl[x].insert(f[n].begin(), f[n].end());
                            fl[x].erase('ε');
                            if (f[n].count('ε')) {
                                follow(l);
                                fl[x].insert(fl[l].begin(), fl[l].end());
                            }
                        }
                    } else {
                        follow(l);
                        fl[x].insert(fl[l].begin(), fl[l].end());
                    }
                }
            }
        }
    }
}

void make_table() {
    for (auto& [x, rs] : g) {
        for (auto r : rs) {
            set<char> t;
            if (islower(r[0]) || r[0] == '(' || r[0] == ')') t.insert(r[0]);
            else t = f[r[0]];

            for (char c : t) {
                if (c != 'ε') table[x][c] = r;
            }
            if (t.count('ε')) {
                for (char c : fl[x]) table[x][c] = r;
            }
        }
    }
}

bool is_ll1() {
    for (auto& [x, row] : table) {
        set<string> seen;
        for (auto& [t, prod] : row) {
            if (seen.count(prod)) return false;
            seen.insert(prod);
        }
    }
    return true;
}

bool parse() {
    vector<char> stk = {'$', 'S'};
    int i = 0;
    while (!stk.empty()) {
        char top = stk.back();
        stk.pop_back();
        if (top == in[i]) i++;
        else if (islower(top) || top == '(' || top == ')') return false;
        else if (table[top].count(in[i])) {
            string r = table[top][in[i]];
            if (r != "ε") for (int j = r.size() - 1; j >= 0; j--) stk.push_back(r[j]);
        } else return false;
    }
    return i == in.size();
}

int main() {
    g['S'] = {"AB", "C", "D"};
    g['A'] = {"a", "ε"};
    g['B'] = {"b", "ε"};
    g['C'] = {"(S)", "c"};
    g['D'] = {"AC"};

    for (auto& [x, _] : g) first(x);
    for (auto& [x, _] : g) follow(x);

    make_table();

    cout << "Predictive Parsing Table:\n";
    for (auto& [x, row] : table) {
        cout << x << ": ";
        for (auto& [t, prod] : row) cout << t << "->" << prod << " ";
        cout << "\n";
    }

    if (is_ll1()) cout << "Grammar is LL(1)\n";
    else {
        cout << "Grammar is not LL(1)\n";
        return 0;
    }

    cout << "Enter string: ";
    cin >> in;

    if (parse()) cout << "Valid string\n";
    else cout << "Invalid string\n";

    return 0;
}

