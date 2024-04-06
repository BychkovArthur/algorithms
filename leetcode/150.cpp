class Solution {
public:

    static bool is_operator(const string& s) {
        return s.size() == 1 && (s[0] == '-' || s[0] == '+' || s[0] == '*' || s[0] == '/');
    }

    int evalRPN(vector<string>& tokens) {
        stack<int> st;

        for (const string& str : tokens) {
            if (is_operator(str) && st.size() >= 2) {
                int rhs = st.top();
                st.pop();
                int lhs = st.top();
                st.pop();

                if (str[0] == '+') {
                    st.push(lhs + rhs);
                } else if (str[0] == '-') {
                    st.push(lhs - rhs);
                } else if (str[0] == '*') {
                    st.push(lhs * rhs);
                } else if (str[0] == '/' && rhs != 0) {
                    st.push(lhs / rhs);
                }
            } else {
                st.push(atoi(str.c_str()));
            }
        }
        return st.top();
    }
};