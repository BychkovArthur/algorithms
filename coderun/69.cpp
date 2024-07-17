#include <iostream>

int main() 
{
	int cnt = 0;
    int curr, prev, preprev;
    
    int nums_readed = 0;

    while (std::cin >> curr) {
        ++nums_readed;
        if (nums_readed >= 3 && prev > preprev && prev > curr) ++cnt;
        preprev = prev;
        prev = curr;
    }

    std::cout << cnt;
        
	return 0;
}