#include <iostream>
#include <vector>
#include <cctype>
using namespace std;

struct quad {
    char op;
    string op1, op2, res;
};

vector<quad> q;
int t_cnt = 1;

string gen(string op1, char op, string op2) {
    string t = "t" + to_string(t_cnt++);
    q.push_back({op, op1, op2, t});
    return t;
}

string parseE(string &s, int &i);
string parseT(string &s, int &i);
string parseF(string &s, int &i);

string parseE(string &s, int &i) {
    string left = parseT(s, i);
    while (i < s.size() && (s[i] == '+' || s[i] == '-')) {
        char op = s[i++];
        string right = parseT(s, i);
        left = gen(left, op, right);
    }
    return left;
}

string parseT(string &s, int &i) {
    string left = parseF(s, i);
    while (i < s.size() && (s[i] == '*' || s[i] == '/')) {
        char op = s[i++];
        string right = parseF(s, i);
        left = gen(left, op, right);
    }
    return left;
}

string parseF(string &s, int &i) {
    if (s[i] == '(') {
        i++;
        string val = parseE(s, i);
        i++;
        return val;
    }
    string num;
    while (i < s.size() && (isdigit(s[i]) || s[i] == '.')) num += s[i++];
    return num;
}

int main() {
    string s;
    cout << "Enter expression: ";
    getline(cin, s);
    int i = 0;
    t_cnt = 1;
    q.clear();
    parseE(s, i);

    cout << "Operator  Operand1  Operand2  Result\n";
    for (auto &e : q) cout << e.op << "         " << e.op1 << "        " << e.op2 << "        " << e.res << "\n";
    return 0;
}
