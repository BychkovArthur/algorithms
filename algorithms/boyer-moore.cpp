#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iostream>


// std::vector<size_t> z_arr;
// std::vector<size_t> n_arr;
// std::vector<ssize_t> strong_L_arr;
// std::vector<ssize_t> strong_l_arr;
// std::unordered_map<char, std::vector<size_t>> R;

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
    for (const T& elem : v) {
        os << elem << ' ';
    }
    os << '\n';
    return os;
}

// void n_func(std::string s) {
//     size_t n = s.size();
//     n_arr.resize(n, 0);

//     std::reverse(s.begin(), s.end());
//     z_func(s);

//     for (size_t i = 0; i < n; ++i) {
//         n_arr[i] = z_arr[n - i - 1];
//     }

//     // std::cout << "N-function: " << n_arr << std::endl;
// }

// void strong_L_func(const std::string& s) {
//     size_t n = s.size();
//     strong_L_arr.resize(n, -1);

//     for (size_t j = 0; j < n - 1; ++j) {
//         if (n_arr[j]) {
//             size_t i = n - n_arr[j];
//             strong_L_arr[i] = j;
//         }
//     }
//     // std::cout << "                   ";
//     // for (int i = 0; i < n; ++i) std::cout << s[i] << "  ";
//     // std::cout << '\n';
//     // std::cout << "Strong L-function: " << strong_L_arr << std::endl;
// }

// void strong_l_func(const std::string& s) {
//     size_t n = s.size();
//     strong_l_arr.resize(n, 0);
//     size_t prev = 0;

//     for (size_t j = 0; j < n; ++j) {
//         size_t i = n - j - 1;
//         if (n_arr[j] == j + 1) {
//             prev = j + 1;
//         }
//         strong_l_arr[i] = prev;
//     }

//     // std::cout << "                   ";
//     // for (int i = 0; i < n; ++i) std::cout << s[i] << " ";
//     // std::cout << '\n';
//     // std::cout << "Strong l-function: " << strong_l_arr << std::endl;
// }

// void R_func(const std::string& s) {
//     size_t n = s.size();
//     for (ssize_t i = n - 1; i >= 0; --i) {
//         R[s[i]].push_back(i);
//     }
// }

// std::vector<ssize_t> boyer_moore(const std::string& text, const std::string& pattern) {
//     ssize_t n = text.size();
//     ssize_t p_sz = pattern.size();

//     std::vector<ssize_t> ans;

//     if (p_sz > n) return ans;

//     n_func(pattern);
//     strong_L_func(pattern);
//     strong_l_func(pattern);
//     R_func(pattern);
    
//     ssize_t shifted = p_sz - 1;
//     // std::cout << "M = " << p_sz << " N = " << n << std::endl;

//     while (shifted < n) {
//         ssize_t pattern_ptr = p_sz - 1;
//         ssize_t text_ptr = shifted;

//         // std::cout << "pattern_ptr = " << pattern_ptr << " text_ptr = " << text_ptr << std::endl;

//         while (pattern_ptr >= 0 && text[text_ptr] == pattern[pattern_ptr]) {
//             --pattern_ptr;
//             --text_ptr;
//         }

//         // Случай, когда ничего не совпало вообще.
//         if (pattern_ptr == p_sz - 1) {
//             shifted += 1;
//             continue;
//         }

//         // std::cout << "HERE" << std::endl;

//         // Паттерн совпал полностью
//         if (pattern_ptr == -1) {
//             // std::cout << "Index = " << text_ptr + 1 << std::endl;
//             // std::cout << text_ptr + 1 << '\n';
//             ans.push_back(text_ptr + 1);
//             shifted += p_sz - strong_l_arr[1];
//             // std::cout << "TOTAL" << std::endl;
//         } else {
//             // 1) Найдём сдвиг для правила плохого символа
//             // Мне надо в паттерне найти первый индекс, который
//             // для буквы text[text_ptr] и такой, что char_ind < pattern_ptr
//             ssize_t char_ind = 0;
//             bool char_find = false;
//             // std::cout << "Не совпал " << text[text_ptr] << " и " << pattern[pattern_ptr] << std::endl;
//             // std::cout << "R = " << R[text[text_ptr]] << std::endl;
//             for (ssize_t i = 0; i < R[text[text_ptr]].size(); ++i) { // Была тут ошибка, щёл с конца
//                 if (R[text[text_ptr]][i] < pattern_ptr) {
//                     char_ind = R[text[text_ptr]][i];
//                     char_find = true;
//                     // std::cout << "finded " << R[text[text_ptr]][i] << std::endl;
//                     break;
//                 }
//             }
//             ssize_t bad_char_shift = 0;
//             if (char_find) { // Буква для правила плохого символа найдёна
//                 // std::cout << "IN CHAR FIND \n\n\n" << std::endl;
//                 bad_char_shift = pattern_ptr - char_ind; // была тут очень тупая ошибка, писал char_find вместо char_ind
//             } else {
//                 bad_char_shift = pattern_ptr + 1;
//             }
//             // std::cout << "BAD CHAR SHIFT = " << bad_char_shift << std::endl;

//             // 2) Найдём сдвиг для правила хорошего суффикса
//             ssize_t good_suffix_shift = 0;
            
//             // Была везде тут ошибка, писал strong_L_arr[pattern_ptr] и strong_l_arr[pattern_ptr]
//             // вместо strong_L_arr[pattern_ptr + 1] и strong_l_arr[pattern_ptr + 1]
//             if (strong_L_arr[pattern_ptr + 1] != -1) {
//                 // std::cout << "INSIDE L ARR STRONG" << std::endl;
//                 good_suffix_shift = p_sz - 1 - strong_L_arr[pattern_ptr + 1];

//             } else if (strong_L_arr[pattern_ptr + 1] == -1) {
//                 good_suffix_shift = p_sz - strong_l_arr[pattern_ptr + 1];
//             }
//             // std::cout << "GOOD SUFFIX = " << good_suffix_shift << std::endl;

//             shifted += std::max(bad_char_shift, good_suffix_shift);
//         }

//         // std::cout << "SHIFTED = " << shifted << std::endl;
//     }
//     z_arr.clear();
//     n_arr.clear();
//     strong_L_arr.clear();
//     strong_l_arr.clear();
//     R.clear();
//     return ans;
// }

std::vector<ssize_t> naive_(const std::string& text, const std::string& pattern) {
    std::vector<ssize_t> ans;
    ssize_t n = text.size();
    ssize_t m = pattern.size();

    if (m > n) return ans;

    for (ssize_t i = 0; i <= n - m; ++i) {
        bool exist = true;
        for (ssize_t j = 0; j < m; ++j) {
            if (text[i + j] != pattern[j]) {
                exist = false;
                break;
            }
        }
        if (exist) {
            ans.push_back(i);
        }
    }

    return ans;
}


class BoyerMoore {
public:
    const std::string text;
    const std::string pattern;
    const size_t t_sz;
    const size_t p_sz;

    BoyerMoore(const std::string& text, const std::string& pattern)
        : text(text), pattern(pattern), t_sz(text.size()), p_sz(pattern.size()), N(p_sz, 0), l(p_sz, 0), L(p_sz, -1) {
            n_func();
            strong_L_func();
            strong_l_func();
            R_func();
            find_pattern();
        }

    BoyerMoore(const std::string&& text, const std::string&& pattern)
        : text(text), pattern(pattern), t_sz(text.size()), p_sz(pattern.size()), N(p_sz, 0), l(p_sz, 0), L(p_sz, -1) {
            n_func();
            strong_L_func();
            strong_l_func();
            R_func();
            find_pattern();
        }
    
    std::vector<ssize_t> get_answer() { return ans; }

private:
    std::vector<ssize_t> N;
    std::vector<ssize_t> l;
    std::vector<ssize_t> L;
    std::unordered_map<char, std::vector<ssize_t>> R;
    std::vector<ssize_t> ans;


    void z_func(const std::string& s) {
        ssize_t l = 0, r = 0;

        N[0] = p_sz;

        for (ssize_t i = 1; i < p_sz; ++i) {
            if (i < r) N[i] = std::min(r - i, N[i - l]);

            while (i + N[i] < p_sz && s[N[i]] == s[i + N[i]]) ++N[i];

            if (i + N[i] > r) {
                l = i;
                r = i + N[i];
            }
        }

        #ifdef DEBUG
        std::cout << "Z-function for reversed pattern:\n" << N << "\n\n\n" << std::endl;
        #endif
    }

    void n_func() {
        std::string reversed_pattern = pattern;
        std::reverse(reversed_pattern.begin(), reversed_pattern.end());
        z_func(reversed_pattern);
        std::reverse(N.begin(), N.end());

        #ifdef DEBUG
        std::cout << "N-function:\n" << N << "\n\n\n" << std::endl;
        #endif
    }

    void strong_L_func() {
        for (ssize_t j = 0; j < p_sz - 1; ++j) {
            if (N[j]) {
                ssize_t i = p_sz - N[j];
                L[i] = j;
            }
        }

        #ifdef DEBUG
        std::cout << "Strong L-function:\n" << L << "\n\n\n" << std::endl;
        #endif
    }

    void strong_l_func() {
        ssize_t prev = 0;
        for (ssize_t j = 0; j < p_sz; ++j) {
            ssize_t i = p_sz - j - 1;
            if (N[j] == j + 1) {
                prev = j + 1;
            }
            l[i] = prev;
        }

        #ifdef DEBUG
        std::cout << "Strong l-function:\n" << l << "\n\n\n" << std::endl;
        #endif 
    }

    void R_func() {
        for (ssize_t i = p_sz - 1; i >= 0; --i) {
            R[pattern[i]].push_back(i);
        }
    
        #ifdef DEBUG
        std::cout << "R-function: \n";
        for (const auto& kv : R) {
            std::cout << "Char: " << kv.first << ", indexes: " << kv.second << std::endl;
        }
        std::cout << "\n\n\n";
        #endif 
    }

    ssize_t get_bad_char_shift(ssize_t text_ptr, ssize_t pattern_ptr) {
        /*
            Найдём сдвиг для правила плохого символа
            Мне надо в паттерне найти первый индекс, который
            для буквы text[text_ptr] и такой, что char_ind < pattern_ptr
        */

        ssize_t char_ind = -1;
        ssize_t n = R[text[text_ptr]].size();

        for (ssize_t i = 0; i < n; ++i) { // Была тут ошибка, шёл с конца
            if (R[text[text_ptr]][i] < pattern_ptr) {
                char_ind = R[text[text_ptr]][i];
                break;
            }
        }
    
        #ifdef DEBUG
        std::cout << "Внутри Правила Плохого Символа\n";
        std::cout << "Не совпал T[" << text_ptr << "] = " << text[text_ptr] << " И P[" << pattern_ptr << " = " << pattern[pattern_ptr] << '\n';
        std::cout << "R = " << R[text[text_ptr]] << '\n';
        if (char_ind == -1) std::cout << "Символ " << text[text_ptr] << ", который будет левее " << pattern_ptr << " не найден" << '\n';
        else std::cout << "Символ " << text[text_ptr] << ", который будет левее " << pattern_ptr << " располагается на " << char_ind << '\n';
        std::cout << "Сдвиг по правилу плохого символа:" << (char_ind == -1 ? pattern_ptr + 1 : pattern_ptr - char_ind) << "\n\n" << std::endl;
        #endif

        return char_ind == -1 ? pattern_ptr + 1 : pattern_ptr - char_ind;
    }

    ssize_t get_good_suffix_shift(ssize_t pattern_ptr) {
        
        /*
            Найдём сдвиг для правила хорошего суффикса
            У меня тут везде была ошибка:
                писал strong_L_arr[pattern_ptr] и strong_l_arr[pattern_ptr]
                вместо strong_L_arr[pattern_ptr + 1] и strong_l_arr[pattern_ptr + 1]
            Надо писать именно (+1), т.к. pattern_ptr - первый не совпадающий символ,
            а в массивах лежат данные относительно последнего совпадающего.
        */

        ssize_t good_suffix_shift = -1;

        if (L[pattern_ptr + 1] != -1) {
            good_suffix_shift = p_sz - 1 - L[pattern_ptr + 1];

        } else if (L[pattern_ptr + 1] == -1) {
            good_suffix_shift = p_sz - l[pattern_ptr + 1];
        }

        #ifdef DEBUG
        std::cout << "Внутри Правила Хорошего Суффикса" << '\n';
        if (L[pattern_ptr + 1] != -1) {
            std::cout << "Внутри `L[pattern_ptr + 1] != -1`" << '\n';
            std::cout << "Значит, часть которая уже совпала (некий суффикс P), найдена левее pattern_ptr`\n";
        } else if (L[pattern_ptr + 1] == -1) {
            std::cout << "Внутри `L[pattern_ptr + 1] == -1`" << '\n';
            std::cout << "Значит, часть которая уже совпала (некий суффикс P), НЕнайдена левее pattern_ptr`\n";
            std::cout << "Нужен либо сдвиг так, чтобы совместился некий префикс P с суффиксом уже совпавщей части в T, либо pattern будет сдвинут полностью\n";
        } else {
            std::cout << "Явная ошибка!!! Я не должен сюда попасть...\n";
        }
        std::cout << "Сдвиг по Правилу Хорошего Суффикса = " << good_suffix_shift << std::endl;
        #endif
        return good_suffix_shift;
    }

    void find_pattern() {
        if (p_sz > t_sz) return;

        /*
            Индекс в тексте, у которого стоит правая граница шаблона
                  0123456789
            T:    abobaameba
            P:        bbb
            shift = 6
        */ 
        ssize_t shift = p_sz - 1;

        while (shift < t_sz) {
            ssize_t pattern_ptr = p_sz - 1;
            ssize_t text_ptr = shift;

            while (pattern_ptr >= 0 && text[text_ptr] == pattern[pattern_ptr]) {
                --pattern_ptr;
                --text_ptr;
            }

            // Случай, когда ничего не совпало вообще
            if (pattern_ptr == p_sz - 1) {
                shift += 1;
                continue;
            }
            
            if (pattern_ptr == -1) { // Паттерн полностью найден
                ans.push_back(text_ptr + 1);
                shift += p_sz - l[1];
            } else {
                ssize_t bad_char_shift = get_bad_char_shift(text_ptr, pattern_ptr);
                ssize_t good_suffix_shift = get_good_suffix_shift(pattern_ptr);
                shift += std::max(bad_char_shift, good_suffix_shift);
                
                #ifdef DEBUG
                std::cout << "max(ППС, ПХС) = " << std::max(bad_char_shift, good_suffix_shift) << '\n';
                std::cout << "Новый shift = " << shift << std::endl;
                #endif
            }
        }
    }
};




int main() {
    std::string text, pattern;
    std::cin >> text >> pattern;
    // std::string text = "hebdaaeeaca";
    // std::string pattern = "eeaca";
    BoyerMoore bm(text, pattern);
    std::vector<ssize_t> ans = bm.get_answer();
    for (auto el : ans) {
        std::cout << el << '\n';
    }

    // std::srand(time(NULL));
    
    // for (int i = 0; i < 1'000; ++i) {

    //     int n = std::rand() % 50 + 5;
    //     int m = std::rand() % 5 + 1;
    //     std::string text;
    //     std::string pattern;
    //     for (int i = 0; i < n; ++i) text.push_back('a' + (std::rand() % 3));
    //     for (int i = 0; i < m; ++i) pattern.push_back('a' + (std::rand() % 3));

    //     std::vector<ssize_t> naive = naive_(text, pattern);

    //     BoyerMoore bm(text, pattern);

    //     std::vector<ssize_t> boyer = bm.get_answer();

    //     if (naive != boyer) {
    //         std::cout << "ERROR on " << i + 1 << "!!!!" << std::endl;
    //         std::cout << "Text = " << text << '\n' << "Pattern = " << pattern << std::endl;
    //         std::cout << "Naive: " << naive << '\n' << "Boyer: " << boyer << std::endl;
    //         break;
    //     } else {
    //         std::cout << "Ok on " << i + 1 << std::endl;
    //         std::cout << "Len = " << boyer.size() << std::endl;
    //         // std::cout << "Text = " << text << '\n' << "Pattern = " << pattern << std::endl;
    //         // std::cout << "Naive: " << naive << '\n' << "Boyer: " << boyer << std::endl;
    //     }
    // }

}