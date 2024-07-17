#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() 
{
	int a, b, n;
    cin >> a >> b >> n;

    int max_in_a = a;
    int min_in_b = b % n ? b / n + 1 : b / n;
    cout << (max_in_a > min_in_b ? "Yes" : "No");
	return 0;
}