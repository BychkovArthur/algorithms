#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <sstream>

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
    for (const T& elem : v) {
        os << elem << ' ';
    }
    os << '\n';
    return os;
}

std::vector<ssize_t> naive_(const std::vector<uint32_t>& text, const std::vector<uint32_t>& pattern) {
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


class ApostolicoGiancarlo {
public:
    const std::vector<uint32_t> text;
    const std::vector<uint32_t> pattern;
    const size_t t_sz;
    const size_t p_sz;

    ApostolicoGiancarlo(const std::vector<uint32_t>& text, const std::vector<uint32_t>& pattern)
        : text(text), pattern(pattern), t_sz(text.size()), p_sz(pattern.size()), N(p_sz, 0), l(p_sz, 0), L(p_sz, -1), M(t_sz, 0) {
            n_func();
            strong_L_func();
            strong_l_func();
            R_func();
            find_pattern();
        }

    ApostolicoGiancarlo(const std::vector<uint32_t>&& text, const std::vector<uint32_t>&& pattern)
        : text(text), pattern(pattern), t_sz(text.size()), p_sz(pattern.size()), N(p_sz, 0), l(p_sz, 0), L(p_sz, -1), M(t_sz, 0) {
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
    std::vector<ssize_t> M;
    std::unordered_map<char, std::vector<ssize_t>> R;
    std::vector<ssize_t> ans;


    void z_func(const std::vector<uint32_t>& s) {
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
        std::vector<uint32_t> reversed_pattern = pattern;
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
        std::cout << "Не совпал T[" << text_ptr << "] = \'" << text[text_ptr] << "\' И P[" << pattern_ptr << "] = \'" << pattern[pattern_ptr] << "\'\n";
        std::cout << "R = [" << R[text[text_ptr]] << "]\n";
        if (char_ind == -1) std::cout << "Символ \'" << text[text_ptr] << "\', который будет левее " << pattern_ptr << " не найден" << '\n';
        else std::cout << "Символ \'" << text[text_ptr] << "\', который будет левее " << pattern_ptr << " располагается на " << char_ind << '\n';
        std::cout << "Сдвиг по правилу плохого символа: " << (char_ind == -1 ? pattern_ptr + 1 : pattern_ptr - char_ind) << "\n\n\n" << std::endl;
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
        std::cout << "Сдвиг по Правилу Хорошего Суффикса = " << good_suffix_shift << "\n\n\n" << std::endl;
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

            // while (pattern_ptr >= 0 && text[text_ptr] == pattern[pattern_ptr]) {
            //     --pattern_ptr;
            //     --text_ptr;
            // }

            bool pattern_finded = false;

            while (true) {

                #ifdef DEBUG
                std::cout << "M1 = " << M << '\n';
                std::cout << "Text PTR = " << text_ptr << " Pattern PTR = " << pattern_ptr << std::endl;
                #endif

                // Правило 1)
                if (M[text_ptr] == 0) {

                    #ifdef DEBUG
                    std::cout << "Сработало правило 1" << std::endl;
                    #endif

                    // Правило 1.1) Паттерн полностью совпал.
                    if (text[text_ptr] == pattern[pattern_ptr] && pattern_ptr == 0) {
                        #ifdef DEBUG
                        std::cout << "Сработало правило 1.1" << std::endl;
                        #endif

                        M[shift] = p_sz;
                        ans.push_back(text_ptr);
                        shift += p_sz - l[1];
                        pattern_finded = true;
                        break;

                    // Правило 1.2) Продолжаем сравнение.
                    } else if (text[text_ptr] == pattern[pattern_ptr] && pattern_ptr > 0) {
                        #ifdef DEBUG
                        std::cout << "Сработало правило 1.2" << std::endl;
                        #endif

                        --text_ptr;
                        --pattern_ptr;

                    // Правило 1.3) Нашли несовпадение.
                    } else {
                        #ifdef DEBUG
                        std::cout << "Сработало правило 1.3" << std::endl;
                        #endif

                        M[shift] = shift - text_ptr;
                        break;
                    }
                
                // Правило 2)
                } else if (M[text_ptr] < N[pattern_ptr]) {
                    #ifdef DEBUG
                    std::cout << "Сработало правило 2" << std::endl;
                    #endif

                    // Была ошибка здесь. Изначально строки были в другом порядке
                    // И потому, pattern_ptr -= M[text_ptr] работало неверно, т.к.
                    // text_ptr уже был другим.
                    pattern_ptr -= M[text_ptr];
                    text_ptr -= M[text_ptr];
                
                // Правило 3)
                } else if (M[text_ptr] >= N[pattern_ptr] && N[pattern_ptr] == pattern_ptr + 1) {
                    #ifdef DEBUG
                    std::cout << "Сработало правило 3" << std::endl;
                    #endif

                    
                    M[shift] = shift - text_ptr;
                    ans.push_back(shift - p_sz + 1);
                    shift += p_sz - l[1];
                    pattern_finded = true;
                    break;
                
                // Правило 4)
                // Чисто из логики, здесь допускается N[pattern_ptr] = 0
                // В этом случае просто text[text_ptr] != pattern[pattern_ptr] а всё правее (если оно есть) равно
                // Если же pattern_ptr = p_sz - 1, то мы сюда никак не попадём, т.к. N[p_sz - 1] = p_sz
                } else if (M[text_ptr] > N[pattern_ptr] && N[pattern_ptr] < pattern_ptr + 1) {
                    // Здесь, получается мы заключаем, что у нас есть несовпадение.
                    #ifdef DEBUG
                    std::cout << "Сработало правило 4" << std::endl;
                    #endif

                    M[shift] = shift - text_ptr;
                    text_ptr -= N[pattern_ptr];
                    pattern_ptr -= N[pattern_ptr];
                    break;
                
                // Правило 5) 
                } else if (M[text_ptr] == N[pattern_ptr] && 0 < N[pattern_ptr] && N[pattern_ptr] < pattern_ptr + 1) {
                    #ifdef DEBUG
                    std::cout << "Сработало правило 5" << std::endl;
                    #endif

                    // Была ошибка здесь. Изначально строки были в другом порядке
                    // И потому, pattern_ptr -= M[text_ptr] работало неверно, т.к.
                    // text_ptr уже был другим.
                    pattern_ptr -= M[text_ptr];
                    text_ptr -= M[text_ptr];
                
                // Что-то пошло не так.
                } else {
                    std::cout << "Всё плохо..." << std::endl;
                }
            }


            if (pattern_finded) continue;

            #ifdef DEBUG
            std::cout << "M2 = " << M << '\n';
            std::cout << "Text PTR = " << text_ptr << " Pattern PTR = " << pattern_ptr << std::endl;
            #endif
            

            // Случай, когда ничего не совпало вообще
            if (pattern_ptr == p_sz - 1) {
                shift += 1;
                continue;
            }
            

            ssize_t bad_char_shift = get_bad_char_shift(text_ptr, pattern_ptr);
            ssize_t good_suffix_shift = get_good_suffix_shift(pattern_ptr);
            shift += std::max(bad_char_shift, good_suffix_shift);
            
            #ifdef DEBUG
            std::cout << "max(ППС, ПХС) = " << std::max(bad_char_shift, good_suffix_shift) << '\n';
            std::cout << "Новый shift = " << shift << "\n\n\n" << std::endl;
            #endif
            
        }
    }
};


int main() {

    #ifndef BENCHMARK

    std::vector<uint32_t> text, pattern;
    std::vector<size_t> lines_length;
    
    size_t current_line_length = 0;
    uint32_t word;


    std::string line;
    std::getline(std::cin, line);
    std::stringstream ss(line);
    while (ss >> word) {
        pattern.push_back(word);
    }

    while (std::getline(std::cin, line)) {
        std::stringstream ss(line);
        while (ss >> word) {
            text.push_back(word);
            ++current_line_length;
        }
        lines_length.push_back(current_line_length);
        current_line_length = 0;
    }

    ApostolicoGiancarlo ag(std::move(text), std::move(pattern));

    std::vector<ssize_t> ans = ag.get_answer();
    for (auto& el : ans) ++el; // Переведём всё в 1-индексацию

    size_t words_before_current_line_exclude_current_line = 0;
    size_t words_before_current_line_include_current_line = 0;
    size_t current_ans_ind = 0;

    for (size_t i = 0; i < lines_length.size(); ++i) {
        words_before_current_line_include_current_line += lines_length[i];
        while (current_ans_ind < ans.size() && ans[current_ans_ind] <= words_before_current_line_include_current_line) {
            std::cout << i + 1 << ", " << ans[current_ans_ind++] - words_before_current_line_exclude_current_line << '\n';
        }
        words_before_current_line_exclude_current_line = words_before_current_line_include_current_line;
    }

    #else
    std::srand(time(NULL));
    
    for (int i = 0; i < 1'000; ++i) {

        int n = std::rand() % 50 + 5;
        int m = std::rand() % 5 + 1;
        std::string text;
        std::string pattern;
        for (int i = 0; i < n; ++i) text.push_back('a' + (std::rand() % 5));
        for (int i = 0; i < m; ++i) pattern.push_back('a' + (std::rand() % 5));

        std::vector<ssize_t> naive = naive_(text, pattern);

        ApostolicoGiancarlo ag(text, pattern);

        std::vector<ssize_t> apostolico = ag.get_answer();

        if (naive != apostolico) {
            std::cout << "ERROR on " << i + 1 << "!!!!" << std::endl;
            std::cout << "Text = " << text << '\n' << "Pattern = " << pattern << std::endl;
            std::cout << "Naive: " << naive << '\n' << "Apostolico-Giancarlo: " << apostolico << std::endl;
            break;
        } else {
            std::cout << "Ok on " << i + 1 << std::endl;
            std::cout << "Len = " << apostolico.size() << std::endl;
            // std::cout << "Text = " << text << '\n' << "Pattern = " << pattern << std::endl;
            // std::cout << "Naive: " << naive << '\n' << "Boyer: " << boyer << std::endl;
        }
    }
    #endif

    return 0;
}