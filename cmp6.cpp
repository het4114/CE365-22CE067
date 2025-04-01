#include <iostream>
#include <string>
using namespace std;
string input;
int pos;
bool S();
bool L();
bool Lp();
bool S() {
    if (pos < input.length() && input[pos] == 'a') {
        pos++;
        return true;
    }
    if (pos < input.length() && input[pos] == '(') {
        pos++;
        if (L()) {
            if (pos < input.length() && input[pos] == ')') {
                pos++;
                return true;
            }
        }
    }
    return false;
}
bool L() {
    if (S()) {
        return Lp();
    }
    return false;
}
bool Lp() {
    if (pos < input.length() && input[pos] == ',') {
        pos++;
        if (S()) {
            return Lp();
        }
        return false;
    }
    return true;
}
int main() {
    getline(cin, input);
    pos = 0;
    if (S() && pos == input.length()) {
        cout << "Valid string" << endl;
    } else {
        cout << "Invalid string" << endl;
    }
    return 0;
}

