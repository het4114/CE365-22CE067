#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

map<char, set<char>> f, fl;
map<char, vector<string>> g;
set<char> v1, v2;

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

int main() {
    g['S'] = {"AB", "C", "D"};
    g['A'] = {"a", "ε"};
    g['B'] = {"b", "ε"};
    g['C'] = {"(S)", "c"};
    g['D'] = {"AC"};

    for (auto& [x, _] : g) first(x);
    for (auto& [x, _] : g) follow(x);

    for (auto& [x, s] : f) {
        cout << "First(" << x << ") = {";
        for (char c : s) cout << c << " ";
        cout << "}\n";
    }

    for (auto& [x, s] : fl) {
        cout << "Follow(" << x << ") = {";
        for (char c : s) cout << c << " ";
        cout << "}\n";
    }

    return 0;
}

