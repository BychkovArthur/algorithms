#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

int main() 
{
    int n;
	std::unordered_set<int> st;
    std::unordered_set<int> duplicates;
    int ans = 0;
    
    std::cin >> n;
    
    for (int i = 0; i < n; ++i) {
        int val;
        std::cin >> val;
        if (st.contains(val)) {
            duplicates.insert(val);
        } else {    
            st.insert(val);
        }
    }
    std::cout << st.size() - duplicates.size();
	return 0;
}