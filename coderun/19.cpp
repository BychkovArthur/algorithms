#include <bits/stdc++.h>

using namespace std;

map<char, int> priority = {
        {'!', 3},
        {'&', 2},
        {'|', 1},
        {'^', 1},
        {'(', 0}
};

bool is_op(char c) {
    return c != '(' && priority.count(c);
}

queue<char> get_polish_notation(const std::string& s) {
    stack<char> st;
    queue<char> q;

    for (char c : s) {

        if (c == '1' || c == '0') {
//            cout << "HERE1 c = " << c << endl;
            q.push(c);
        }

        if (is_op(c)) {
//            cout << "HERE2 ";
            while (!st.empty() && !(priority[c] > priority[st.top()])) {
                q.push(st.top());
                st.pop();
            }
            st.push(c);

        }

        if (c == '(') {
            st.push(c);
        }
        if (c == ')') {
            while (st.top() != '(') {
                q.push(st.top());
                st.pop();
            }
            st.pop();
        }
    }

    while (!st.empty()) {
        q.push(st.top());
        st.pop();
    }

    return q;
}

int main() {
    string s;
    cin >> s;

    auto q = get_polish_notation(s);

//    while (!q.empty()) {
//        cout << q.front() << endl;
//        q.pop();
//    }

    stack<bool> res;
    while (!q.empty()) {
        char el = q.front();
        q.pop();

//        cout << el << endl;

        if (el == '1' || el == '0') {
            res.push((bool)(el - '0'));
        }
        if (el == '!') {
            bool top = res.top();
            res.pop();
            res.push(!top);
        }
        if (el == '&') {
            bool a1 = res.top();
            res.pop();
            bool a2 = res.top();
            res.pop();
            res.push(a1 & a2);
        }
        if (el == '|') {
            bool a1 = res.top();
            res.pop();
            bool a2 = res.top();
            res.pop();
            res.push(a1 | a2);
        }
        if (el == '^') {
            bool a1 = res.top();
            res.pop();
            bool a2 = res.top();
            res.pop();
            res.push(a1 ^ a2);
        }
    }
    cout << res.top() << endl;
}