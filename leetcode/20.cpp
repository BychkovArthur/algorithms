class Solution {
public:
    static bool is_open_bracket(char c) {
        return c == '(' || c == '{' || c == '[';
    }

    static char get_open_bracket(char c) {
        if (c == ')') {
            return '(';
        } else if (c == '}') {
            return '{';
        } else {
            return '[';
        }
    }

    bool isValid(string s) {
        stack<char> st;

        for (size_t i = 0; i < s.size(); ++i) {
            if (is_open_bracket(s[i])) {
                st.push(s[i]);
            } else {
                if (st.empty() || st.top() != get_open_bracket(s[i])) {
                    return false;
                }
                st.pop();
            }
        }

        return st.empty();
    }
};