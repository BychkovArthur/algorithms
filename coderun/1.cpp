#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main() 
{
    int a[3];
    std::cin >> a[0] >> a[1] >> a[2];
    std::sort(a, a + 3);
    std::cout << a[1];
	return 0;
}