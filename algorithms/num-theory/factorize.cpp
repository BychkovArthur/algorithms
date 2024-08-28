#include <iostream>
#include <vector>
#include <algorithm>


/*
* Работает за O(sqrt(n))
*/

std::vector<int> factorize(int n) {
    std::vector<int> res;
    for (int i = 2; i * i <= n; ++i) {
        while (n % i == 0) {
            res.push_back(i);
            n /= i;
        }
    } 
    if (n > 1) res.push_back(n);
    return res;
}


/*
* Можно модифицировать решето, 
* тогда можно будет быстро факторизовать числа
*/

int N = 1e6;
std::vector<int> prime_div(N + 1, 0);
void sieve() {
    for (int i = 2; i * i <= N; ++i) {
        if (prime_div[i]) continue;
        for (int j = i * i; j <= N; j += i) {
            prime_div[j] = i;
        }
    }
}

std::vector<int> factorize2(int n) {
    /*
    * Минус такой факторизации в том, что 
    * делители получаем в немного хаотичном порядке.
    * 
    * В такой факторизации решето работает быстро,
    * но делители в немного хаотичном порядке.
    */
    std::vector<int> res;
    while(prime_div[n]) {
        res.push_back(prime_div[n]);
        n /= prime_div[n];
    }
    res.push_back(n);
    return res;
}



/*
* 
* Чтобы получать делители в нормальном порядке, надо изменить 
* решето:
* 
* Т.е. в такой факторизации решето работает медленно,
* но делители получаются по убыванию.
*/
void sieve2() {
    for (int i = 2; i <= N; ++i) {
        if (prime_div[i]) continue;
        for (int j = 2 * i; j <= N; j += i) {
            prime_div[j] = i;
        }
    }
}

std::vector<int> factorize3(int n) {
    std::vector<int> res;
    while(prime_div[n]) {
        res.push_back(prime_div[n]);
        n /= prime_div[n];
    }
    res.push_back(n);
    return res;
}



/*
* Еще одна версия (сам придумал только что)
* 
* Можно факторизовать быстрым решетом + получить 
* Делители в порядке от меньшего к большему:
* 
* САМАЯ ЛУЧШАЯ ВЕРСИЯ!!!
*/

void sieve4() {
    for (int i = 2; i * i <= N; ++i) {
        if (prime_div[i]) continue;
        for (int j = i * i; j <= N; j += i) {
            if (!prime_div[j]) prime_div[j] = i;
        }
    }
}
std::vector<int> factorize4(int n) {
    std::vector<int> res;
    while(prime_div[n]) {
        res.push_back(prime_div[n]);
        n /= prime_div[n];
    }
    res.push_back(n);
    return res;
}


int main() {
    sieve4();

    for (int i = 2; i <= 100000; ++i) {
        // auto fact = factorize(i);

        // std::cout << "1) Num = " << i << " : ";
        // for (auto el : fact) {
        //     std::cout << el << ' ';
        // }
        // std::cout << '\n';

        // fact = factorize4(i);

        // std::cout << "2) Num = " << i << " : ";
        // for (auto el : fact) {
        //     std::cout << el << ' ';
        // }
        // std::cout << "\n\n\n\n";

        auto fact1 = factorize(i);
        auto fact2 = factorize4(i);
        if (fact1 != fact2) {
            std::cout << "bad on " << i << std::endl;

            for (auto el : fact1) {
                std::cout << el << ' ';
            }
            std::cout << '\n';
            for (auto el : fact2) {
                std::cout << el << ' ';
            }
            std::cout << '\n';
            return 0;
        }
    }

}