#include <iostream>
#include <stack>
#include <cmath>
#include <cctype>
using namespace std;

double eval(string s) {
    stack<double> num;
    stack<char> op;
    int i = 0;

    auto apply_op = [&]() {
        if (num.size() < 2 || op.empty()) return;
        double b = num.top(); num.pop();
        double a = num.top(); num.pop();
        char o = op.top(); op.pop();
        if (o == '+') num.push(a + b);
        else if (o == '-') num.push(a - b);
        else if (o == '*') num.push(a * b);
        else if (o == '/') num.push(b == 0 ? NAN : a / b);
        else if (o == '^') num.push(pow(a, b));
    };

    auto prec = [&](char o) {
        if (o == '+' || o == '-') return 1;
        if (o == '*' || o == '/') return 2;
        if (o == '^') return 3;
        return 0;
    };

    while (i < s.size()) {
        if (isspace(s[i])) { i++; continue; }
        if (isdigit(s[i]) || s[i] == '.') {
            double val = 0, dec = 1;
            bool is_dec = false;
            while (i < s.size() && (isdigit(s[i]) || s[i] == '.')) {
                if (s[i] == '.') { is_dec = true; }
                else {
                    if (is_dec) { dec *= 10; val += (s[i] - '0') / dec; }
                    else val = val * 10 + (s[i] - '0');
                }
                i++;
            }
            num.push(val);
            continue;
        }
        if (s[i] == '(') op.push(s[i]);
        else if (s[i] == ')') {
            while (!op.empty() && op.top() != '(') apply_op();
            if (op.empty() || op.top() != '(') return NAN;
            op.pop();
        } else {
            while (!op.empty() && prec(op.top()) >= prec(s[i]) && s[i] != '^') apply_op();
            op.push(s[i]);
        }
        i++;
    }
    while (!op.empty()) apply_op();
    return num.size() == 1 ? num.top() : NAN;
}

int main() {
    string in;
    cout << "Enter expression: ";
    getline(cin, in);
    double res = eval(in);
    if (isnan(res)) cout << "Invalid expression\n";
    else cout << res << endl;
    return 0;
}

