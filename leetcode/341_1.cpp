/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */

class NestedIterator {

    struct ListPosition {
        int unprocessedPos;
        const vector<NestedInteger>& list;
    };
    stack<ListPosition> st;
    bool _hasNext;
    int _next;

    void prepare() {

        while (true) {
            if (st.empty()) {
                _hasNext = false;
                return;
            }
            int pos = st.top().unprocessedPos;
            const vector<NestedInteger>& list = st.top().list;
            st.pop();
            if (pos < list.size()) {
                if (list[pos].isInteger()) {
                    _next = list[pos].getInteger();
                    _hasNext = true;
                    ++pos;
                    st.push({pos, list});
                    return;
                } else {
                    ++pos;
                    st.push({pos, list});
                    st.push({0, list[pos - 1].getList()});
                }
            }
        }
    }
public:
    NestedIterator(const vector<NestedInteger> &nestedList) : _hasNext(false), _next(0) {
        st.push({0, nestedList});
    }

    int next() {
        return _next;
    }

    bool hasNext() {
        prepare();
        return _hasNext;
    }
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */