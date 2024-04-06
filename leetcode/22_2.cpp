class Solution {
public:

    static void foo(int n, int left, int right, string&& str, vector<string>& res) {
        if (str.size() == 2 * n) {
            res.push_back(move(str));
            return;
        }

        if (left < n && left > right) {
            string copy = str;
            str.push_back('(');
            copy.push_back(')');
            foo(n, left + 1, right, move(str), res);
            foo(n, left, right + 1, move(copy), res);
        } else if (left < n) {
            str.push_back('(');
            foo(n, left + 1, right, move(str), res);
        } else if (left > right) {
            str.push_back(')');
            foo(n, left, right + 1, move(str), res);
        }
    }

    vector<string> generateParenthesis(int n) {
        vector<string> res;
        foo(n, 0, 0, "", res);
        return res;
    }
};  