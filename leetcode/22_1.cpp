class Solution {
public:

    static void add_answers(vector<string>& res, stack<int>& st, string& curr, int left_open_brackets) {

        // Сначала проверим, можно ли добавить открывающуюся скобку
        if (left_open_brackets > 0) {
            st.push(1);
            curr.push_back('(');
            add_answers(res, st, curr, left_open_brackets - 1);
            curr.pop_back();
            st.pop();
        }

        if (!st.empty()) {
            st.pop();
            curr.push_back(')');
            add_answers(res, st, curr, left_open_brackets);
            curr.pop_back();
            st.push(1);
        }

        if (st.empty() && !left_open_brackets) {
            res.push_back(curr);
        }

    }

    vector<string> generateParenthesis(int n) {
        vector<string> res;
        stack<int> st;
        string str;
        add_answers(res, st, str, n);
        return res;
    }
};