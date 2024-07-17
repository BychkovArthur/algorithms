#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

int main() 
{
    int n;
    std::unordered_set<int> st;
    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;
        st.insert(x);
    }

    std::cout << st.size();
    
	return 0;
}