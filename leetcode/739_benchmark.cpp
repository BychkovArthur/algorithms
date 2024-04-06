#include <iostream>
#include <vector>
#include <stack>
#include <chrono>

using std::vector;
using std::stack;

vector<int> dailyTemperatures1(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> ans(n, 0);
        int p = n - 1;

        for(int i = n - 2; i >= 0; i--) {
            if(temperatures[i] < temperatures[i + 1]){
                ans[i] = 1;

            } else if(temperatures[i] == temperatures[i + 1] && i + 1 != p) {
                ans[i] = ans[i + 1] + 1;

            } else if(temperatures[i] < temperatures[p]) {
                for(int j = p; j > i; j--) {
                    if(temperatures[i] < temperatures[j]){
                        ans[i] = j - i;
                    }
                }
            } else {
                p = i;
            }
        }
        return ans;
}

vector<int> dailyTemperatures2(vector<int>& temperatures) {
        size_t n = temperatures.size();
        vector<int> ans(n, 0);
        stack<int> st;

        for (int i = 0; i < n; ++i) {
            while (!st.empty() && temperatures[st.top()] < temperatures[i]) {
                ans[st.top()] = i - st.top();
                st.pop();
            }
            st.push(i);
        }
        return ans;
    }



int main() {

    int n = 100000;
    vector<int> input(n);


    int num = n;

    for (int i = 0; i < n / 2; ++i) {
        input[n - i] = num--;
        input[i] = num--;
    }

    auto start = std::chrono::system_clock::now();
    vector<int> res1 = dailyTemperatures1(input);
    auto stop = std::chrono::system_clock::now();

    std::cout << "Not my implementation " << std::chrono::duration_cast<std::chrono::seconds>(stop - start).count() << std::endl;

    start = std::chrono::system_clock::now();
    vector<int> res2 = dailyTemperatures2(input);
    stop = std::chrono::system_clock::now();

    std::cout << "My implementation " << std::chrono::duration_cast<std::chrono::seconds>(stop - start).count() << std::endl;

    std::cout << "Does answers same?? " << (res1 == res2) << std::endl;

}