#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <unordered_set>
#include <vector>
#include <regex>

using namespace std;

unordered_set<string> kw = {
    "auto", "break", "case", "char", "const", "continue", "default", "do", "double",
    "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",
    "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef",
    "union", "unsigned", "void", "volatile", "while"
};

unordered_set<string> op = {"+", "-", "*", "/", "=", "++", "--", "==", "!=", "<", ">", "<=", ">=", "&&", "||"};

unordered_set<char> pn = {'(', ')', '{', '}', '[', ']', ',', ';'};

unordered_set<string> st;
vector<pair<string, int>> le;

bool isk(string &t) {
    return kw.find(t) != kw.end();
}

bool isi(string &t) {
    return regex_match(t, regex("[_a-zA-Z][_a-zA-Z0-9]*"));
}

bool isc(string &t) {
    return regex_match(t, regex("[0-9]+(\\.[0-9]+)?"));
}

bool iso(string &t) {
    return op.find(t) != op.end();
}

string rc(const string &cd) {
    string rs;
    bool bc = false, lc = false;
    for (size_t i = 0; i < cd.length(); i++) {
        if (lc && cd[i] == '\n') {
            lc = false;
            rs += cd[i];
        } else if (bc && cd[i] == '*' && i + 1 < cd.length() && cd[i + 1] == '/') {
            bc = false;
            i++;
        } else if (!lc && !bc) {
            if (cd[i] == '/' && i + 1 < cd.length() && cd[i + 1] == '/') {
                lc = true;
                i++;
            } else if (cd[i] == '/' && i + 1 < cd.length() && cd[i + 1] == '*') {
                bc = true;
                i++;
            } else {
                rs += cd[i];
            }
        }
    }
    return rs;
}

void tk(const string &cd) {
    stringstream ss(cd);
    string t;
    int ln = 1;

    while (ss >> t) {
        if (t == "\n") {
            ln++;
            continue;
        }

        if (isk(t)) {
            cout << "Keyword: " << t << endl;
        } else if (isi(t)) {
            cout << "Identifier: " << t << endl;
            st.insert(t);
        } else if (isc(t)) {
            cout << "Constant: " << t << endl;
        } else if (iso(t)) {
            cout << "Operator: " << t << endl;
        } else if (t.length() == 1 && pn.count(t[0])) {
            cout << "Punctuation: " << t << endl;
        } else {
            le.push_back({t, ln});
        }
    }
}

int main(int ac, char *av[]) {
    if (ac < 2) {
        cerr << "Usage: ./lexical <source_file.c>" << endl;
        return 1;
    }

    ifstream f(av[1]);
    if (!f.is_open()) {
        cerr << "Error: File '" << av[1] << "' not found." << endl;
        return 1;
    }

    stringstream b;
    b << f.rdbuf();
    f.close();

    string cc = rc(b.str());
    tk(cc);

    cout << "\nLEXICAL ERRORS\n";
    if (le.empty()) {
        cout << "None" << endl;
    } else {
        for (auto &[l, n] : le) {
            cout << "Line " << n << " : " << l << " invalid lexeme" << endl;
        }
    }

    cout << "\nSYMBOL TABLE\n";
    int i = 1;
    for (const auto &id : st) {
        cout << i++ << ") " << id << endl;
    }

    return 0;
}
