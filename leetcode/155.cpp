class MinStack {
    vector<int> mins;
    vector<int> data;
public:
    MinStack() {}
    
    void push(int val) {
        data.push_back(val);
        if (mins.empty() || mins.back() >= val) {
            mins.push_back(val);
        }
    }
    
    void pop() {
        if (data.back() == mins.back()) {
            mins.pop_back();
        }
        data.pop_back();
    }
    
    int top() {
        return data.back();
    }
    
    int getMin() {
        return mins.back();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */