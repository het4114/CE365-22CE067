#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Automaton {
private:
    int totalStates;
    int totalSymbols;
    vector<int> finalStates;
    int startState;
    map<pair<int, char>, int> transitions;

public:
    Automaton(int totalStates, int totalSymbols, int startState, vector<int> finalStates) {
        this->totalStates = totalStates;
        this->totalSymbols = totalSymbols;
        this->startState = startState;
        this->finalStates = finalStates;
    }

    void addTransition(int fromState, char symbol, int toState) {
        transitions[{fromState, symbol}] = toState;
    }

    bool isFinalState(int state) {
        for (int i : finalStates) {
            if (state == i) {
                return true;
            }
        }
        return false;
    }

    bool checkString(string input) {
        int currentState = startState;

        for (char ch : input) {
            if (transitions.find({currentState, ch}) != transitions.end()) {
                currentState = transitions[{currentState, ch}];
            } else {
                return false;
            }
        }

        return isFinalState(currentState);
    }
};

int main() {
    int numSymbols, numStates, startState, numFinalStates;
    vector<int> finalStates;

    cout << "Enter number of input symbols: ";
    cin >> numSymbols;
    cout << "Input symbols: ";
    vector<char> symbols(numSymbols);
    for (int i = 0; i < numSymbols; i++) {
        cin >> symbols[i];
    }

    cout << "Enter number of states: ";
    cin >> numStates;
    cout << "Initial state: ";
    cin >> startState;

    cout << "Enter number of final states: ";
    cin >> numFinalStates;
    cout << "Final states: ";
    finalStates.resize(numFinalStates);
    for (int i = 0; i < numFinalStates; i++) {
        cin >> finalStates[i];
    }

    Automaton myAutomaton(numStates, numSymbols, startState, finalStates);

    cout << "Enter transition table: \n";
    for (int i = 0; i < numStates; i++) {
        for (int j = 0; j < numSymbols; j++) {
            int nextState;
            cout << "State " << i + 1 << " to " << symbols[j] << " -> ";
            cin >> nextState;
            myAutomaton.addTransition(i + 1, symbols[j], nextState);
        }
    }

    string inputString;
    cout << "Enter the input string: ";
    cin >> inputString;

    if (myAutomaton.checkString(inputString)) {
        cout << "Valid String" << endl;
    } else {
        cout << "Invalid String" << endl;
    }

    return 0;
}
