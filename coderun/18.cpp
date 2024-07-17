#include <bits/stdc++.h>

using namespace std;

map<string , int> priority = {
        {"*", 2},
        {"~", 3},
        {"-", 1},
        {"+", 1},
        {"(", 0}
};

bool is_op(const string& c) {
    return c != "(" && priority.count(c);
}

bool is_num(const string& s){
  return all_of(s.begin(), s.end(), ::isdigit);
}

queue<string> get_polish_notation(const vector<string>& vct) {
    stack<string> st;
    queue<string> q;

    for (const string& s : vct) {

        if (is_num(s)) {
//            cout << "HERE1 c = " << c << endl;
            q.push(s);
        }

        if (is_op(s)) {
//            cout << "HERE2 ";
            while (!st.empty() && !(priority[s] > priority[st.top()])) {
                q.push(st.top());
                st.pop();
            }
            st.push(s);

        }

        if (s == "(") {
            st.push(s);
        }
        if (s == ")") {
            if (st.empty()) {
                throw invalid_argument("invalid brackets");
            }
            while (st.top() != "(") {
                q.push(st.top());
                st.pop();
                if (st.empty()) {
                    throw invalid_argument("invalid brackets");
                }
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

vector<string> input;

void parse() {
    char c;
    bool can_be_unary_minus = true;

    string curr_number;
    bool inside_number = false;

    while ((c = getchar()) != '\n') {

        if (c == ' ' && inside_number) {
            inside_number = false;
            input.push_back(curr_number);
            curr_number.clear();
            can_be_unary_minus = false;
            continue;
        }

        if (c == ' ' && !inside_number) {
            continue;
        }

        if (isdigit(c) && !inside_number) {
            curr_number.push_back(c);
            inside_number = true;
            can_be_unary_minus = false;
            continue;
        }

        if (isdigit(c) && inside_number) {
            can_be_unary_minus = false;
            curr_number.push_back(c);
            continue;
        }

        if (c == '(') {
            if (inside_number) {
                inside_number = false;
                input.push_back(curr_number);
                curr_number.clear();
            }
            can_be_unary_minus = true;
            input.push_back("(");
            continue;
        }
        if (c == ')') {
            if (inside_number) {
                inside_number = false;
                input.push_back(curr_number);
                curr_number.clear();
            }
            input.push_back(")");
            can_be_unary_minus = false;
            continue;
        }
        if (c == '+') {
            if (inside_number) {
                inside_number = false;
                input.push_back(curr_number);
                curr_number.clear();
            }
            input.push_back("+");
            can_be_unary_minus = false;
            continue;
        }
        if (c == '*') {
            if (inside_number) {
                inside_number = false;
                input.push_back(curr_number);
                curr_number.clear();
            }
            input.push_back("*");
            can_be_unary_minus = false;
            continue;
        }

        if (c == '-' && !can_be_unary_minus) {
            if (inside_number) {
                inside_number = false;
                input.push_back(curr_number);
                curr_number.clear();
            }
            input.push_back("-");
            continue;
        }

        if (c == '-' && can_be_unary_minus) {
            input.push_back("~");

            can_be_unary_minus = false;
            continue;
        }

        throw invalid_argument("invalid char");
    }

    if (inside_number) {
        input.push_back(curr_number);
    }
}

int main() {

    try {
        parse();
    } catch(...) {
        cout << "WRONG";
        return 0;
    }

    for (int i = 1; i < input.size(); ++i) {
        if (is_num(input[i]) && is_num(input[i - 1])) {
            cout << "WRONG";
            return 0;
        }
    }




//    for (const auto& el : input) {
//        cout << el << endl;
//    }
//    return 0;


    queue<string> q;
    try {
        q = get_polish_notation(input);
    } catch(...) {
        cout << "WRONG";
        return 0;
    }

//    while (!q.empty()) {
//        cout << q.front() << endl;
//        q.pop();
//    }

    if (q.empty()) {
        cout << "WRONG";
        return 0;
    }

    // в стеке ровно 1
    // в промежуточные могу достать
    // не достаю операцию

//    while (!q.empty()) {
//        cout << q.front() << endl;
//        q.pop();
//    }
//
    stack<long long int> res;
    while (!q.empty()) {
        string el = q.front();
        q.pop();

//        cout << el << endl;

        if (is_num(el)) {
            res.push(stoll(el));
        }
        if (el == "~") {
            if (res.size() < 1) {
                cout << "WRONG";
                return 0;
            }
            auto top = res.top();
            res.pop();
//            cout << "PUSH~ " << -top << endl;
            res.push(-top);
        }
        if (el == "+") {
            if (res.size() < 2) {
                cout << "WRONG";
                return 0;
            }
            auto a1 = res.top();
            res.pop();
            auto a2 = res.top();
            res.pop();
//            cout << "PUSH+ " << a1 + a2 << endl;
            res.push(a1 + a2);
        }
        if (el == "-") {
            if (res.size() < 2) {
                cout << "WRONG";
                return 0;
            }
            auto a1 = res.top();
            res.pop();
            auto a2 = res.top();
            res.pop();
//            cout << "PUSH- " << a2 - a1 << endl;
            res.push(a2 - a1);
        }
        if (el == "*") {
            if (res.size() < 2) {
                cout << "WRONG";
                return 0;
            }
            auto a1 = res.top();
            res.pop();
            auto a2 = res.top();
            res.pop();
//            cout << "PUSH* " << a1 * a2 << endl;
            res.push(a1 * a2);
        }
    }

//    cout << "HERE" << endl;
//    cout << res.size() << endl;
    if (res.size() != 1) {
        cout << "WRONG";
    } else {
        cout << res.top() << endl;
    }
}