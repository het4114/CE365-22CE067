#include <iostream>
#include <sstream>
#include <stack>
#include <cctype>
using namespace std;

string opt(string s) {
    stack<int> nums;
    stack<char> ops;
    string res = "";

    for (int i = 0; i < s.size(); i++) {
        if (isdigit(s[i])) {
            string num = "";
            while (i < s.size() && isdigit(s[i])) num += s[i++];
            i--;
            nums.push(stoi(num));
        } else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {
            ops.push(s[i]);
        } else if (isalpha(s[i])) {
            res += s[i];
        } else if (s[i] == ' ') {
            res += ' ';
        }
    }

    while (!ops.empty() && nums.size() > 1) {
        int a = nums.top(); nums.pop();
        int b = nums.top(); nums.pop();
        char op = ops.top(); ops.pop();
        int val = (op == '+') ? b + a : (op == '-') ? b - a : (op == '*') ? b * a : (b / a);
        nums.push(val);
    }

    if (!nums.empty()) res += to_string(nums.top());
    return res;
}

int main() {
    string s;
    cout << "Enter expr: ";
    getline(cin, s);
    cout << opt(s) << endl;
    return 0;
}

