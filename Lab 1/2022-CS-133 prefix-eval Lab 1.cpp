
// NOTE: You must provide the expression as a command line argument when running this program.
// Example: prefix-eval.exe "+ 2 3"

#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
using namespace std;

// helper function to print NumBers
string pretty(double v) {
    long long iv = (long long)v;
    if (fabs(v - iv) < 1e-9) return to_string(iv);
    ostringstream oss;
    oss.setf(ios::fixed);
    oss.precision(6);
    oss << v;
    string s = oss.str();
    while (!s.empty() && s.back() == '0') s.pop_back();
    if (!s.empty() && s.back() == '.') s.pop_back();
    return s;
}

// operator check
bool isOp(const string &s) {
    return s == "+" || s == "-" || s == "*" || s == "/" || s == "^";
}

// binary operator
double apply(double a, double b, const string &op) {
    if (op == "+") return a + b;
    if (op == "-") return a - b;
    if (op == "*") return a * b;
    if (op == "/") return a / b;
    if (op == "^") return pow(a, b);
    return 0;
}

// Split the expression into tokens
vector<string> tokenize(int argc, char* argv[]) {
    vector<string> tokens;
    // join all command line args into one space
    string expr;
    for (int i = 1; i < argc; ++i) {
        if (i > 1) expr += ' ';
        expr += argv[i];
    }
    istringstream iss(expr);
    string t;
    while (iss >> t) tokens.push_back(t);
    return tokens;
}

// Evaluate a prefix expression
double evaluatePrefix(const vector<string> &tokens) {
    stack<double> st;
    for (int i = (int)tokens.size() - 1; i >= 0; --i) {
        const string &tk = tokens[i];
        cout << "Token: " << tk << "\n";

        // Skip special bracket pair tokens
        if (tk == "[]" || tk == "()" || tk == "{}") continue;

        if (isOp(tk)) {
            if (st.size() < 2) throw runtime_error("Not enough operands");
            double left = st.top();  st.pop();
            double right = st.top(); st.pop();
            double res = apply(left, right, tk);
            cout << "Applied operator: " << tk
                 << " Left: " << pretty(left)
                 << " Right: " << pretty(right)
                 << " Result: " << pretty(res) << "\n";
            st.push(res);
        } else {
            // convert token to number
            st.push(stod(tk));
        }
    }
    if (st.empty()) return 0;
    return st.top();
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " \"prefix expression\"\n";
        return 1;
    }

    try {
        vector<string> tokens = tokenize(argc, argv);
        double result = evaluatePrefix(tokens);
        cout << "Result: " << pretty(result) << "\n";
    } catch (const exception &ex) {
        cerr << "Error: " << ex.what() << "\n";
        return 1;
    }
    return 0;
}
