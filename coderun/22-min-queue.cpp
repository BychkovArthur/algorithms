#include <stack>
#include <cstdint>
#include <iostream>

using namespace std;

template <typename T>
class MinStack {
private:

    std::stack<std::pair<T, T>> st;

public:

    using size_type = typename std::stack<T>::size_type;

    MinStack() = default;
    MinStack(const MinStack& other) : st(other.st) {}
    MinStack(MinStack&& other) : st(std::move(other.st)) {}

    bool empty() { return st.empty(); }
    size_type size() { return st.size(); }

    void swap(MinStack& other) { std::swap(st, other.st); }

    void push(const T& value) {
        if (empty()) {
            st.push({value, value});
        } else {
            st.push({value, std::min(value, st.top().second)});
        }
    }

    const T& top() { return st.top().first; }
    const T& min() { return st.top().second; }
    void pop() { st.pop(); }

};

template <typename T>
class MinDeque {
private:
    using size_type = typename MinStack<T>::size_type;
    MinStack<T> frontStack;
    MinStack<T> backStack;
    MinStack<T> buffer;

    void prepareForAccess() {
        if (frontStack.empty() && backStack.empty() || !frontStack.empty() && !backStack.empty()) {
            return;
        }

        // Делим с округлением в меньшую.
        // Так нужно, чтобы если в одном стеке 1, а в другом 0,
        // ТО, я сначала 0 перенесу в буффер, а потом в другой перенес этот единственный элемент
        size_type n = std::max(frontStack.size(), backStack.size()) / 2;

        MinStack<T>& empty = frontStack.empty() ? frontStack : backStack;
        MinStack<T>& nonEmpty = frontStack.empty() ? backStack : frontStack;

        for (size_type i = 0; i < n; ++i) {
            buffer.push(nonEmpty.top());
            nonEmpty.pop();
        }
        while (!nonEmpty.empty()) {
            empty.push(nonEmpty.top());
            nonEmpty.pop();
        }
        while (!buffer.empty()) {
            nonEmpty.push(buffer.top());
            buffer.pop();
        }
    }

public:
    MinDeque() = default;
    // Почему тут мне не надо писать шаблон????
    MinDeque(const MinDeque& other) : frontStack(other.frontStack), backStack(other.backStack) {}
    MinDeque(MinDeque&& other) : frontStack(std::move(other.frontStack)), backStack(std::move(other.backStack)) {}

    bool empty() { return frontStack.empty() && backStack.empty(); }
    size_type size() { return frontStack.size() + backStack.size(); }

    void push_front(const T& value) { frontStack.push(value); }
    void push_back(const T& value) { backStack.push(value); }

    void pop_front() {
        if (frontStack.empty()) prepareForAccess();
        frontStack.pop();
    }

    void pop_back() {
        if (backStack.empty()) prepareForAccess();
        backStack.pop();
    }

    const T& front() {
        if (frontStack.empty()) prepareForAccess();
        return frontStack.top();
    }

    const T& back() {
        if (backStack.empty()) prepareForAccess();
        return backStack.top();
    }

    const T& min() {
        if (frontStack.empty()) return backStack.min();
        if (backStack.empty()) return frontStack.min();
        return std::min(frontStack.min(), backStack.min());
    }

    void swap(MinDeque& other) {
        std::swap(frontStack, other.frontStack);
        std::swap(backStack, other.backStack);
        std::swap(buffer, other.buffer);
    }
};



int main() {
    MinDeque<long long int> dq;

    long long int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        if (dq.size() == k) {
            cout << dq.min() << '\n';
            dq.pop_front();
        }
        long long int val;
        cin >> val;
        dq.push_back(val);
    }
    cout << dq.min() << '\n';
}
