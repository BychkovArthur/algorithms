#include <string>
#include <vector>
#include <iostream>

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
    for (const T& elem : v) {
        os << elem << ' ';
    }
    os << '\n';
    return os;
}

class KMP {
public:
    const std::string text;
    const std::string pattern;
    const size_t t_sz;
    const size_t p_sz;

    KMP(const std::string& text, const std::string& pattern) :
        text(text), pattern(pattern), t_sz(text.size()), p_sz(pattern.size()), sp(p_sz, 0) {
            strong_prefix_function();
            find_pattern();
        }

    std::vector<size_t> get_ans() {return ans;} 
private:
    // ssize_t for negative 1 in sp[0], because sp[0] undefined
    std::vector<ssize_t> sp;
    std::vector<size_t> ans;

    void z_func() {
        ssize_t l = 0, r = 0;
        sp[0] = 0;

        for (ssize_t i = 1; i < p_sz; ++i) {
            if (i < r) sp[i] = std::min(sp[i - l], r - i);
            while (i + sp[i] < p_sz && pattern[sp[i]] == pattern[i + sp[i]]) ++sp[i];
            if (i + sp[i] > r) {
                l = i;
                r = i + sp[i];
            }
        }
        #ifdef DEBUG
        std::cout << "Z-func: " << sp << std::endl;
        #endif
    }

    void strong_prefix_function() {
        z_func();

        std::vector<ssize_t> new_sp(p_sz, 0);
        new_sp[0] = 0;
        for (ssize_t i = 1; i < p_sz; ++i) {
            if (sp[i] && !new_sp[i + sp[i] - 1]) new_sp[i + sp[i] - 1] = sp[i];
        }
        sp = new_sp;
        #ifdef DEBUG
        std::cout << "Strong prefix: " << sp << std::endl;
        #endif
    }

    void find_pattern() {
        ssize_t pattern_ptr = 0, text_ptr = 0;
        while (text_ptr < t_sz) {
            while (pattern_ptr < p_sz && text[text_ptr] == pattern[pattern_ptr]) {
                ++pattern_ptr;
                ++text_ptr;
            }

            // Первый случай - ничего не совпало.
            if (pattern_ptr == 0) {
                ++text_ptr;
            
            // Второй случай - паттерн найден.
            // Указатели всё-равно будут указывать на элемент, следующий за совпавшим.
            } else if (pattern_ptr == p_sz) {
                ans.push_back(text_ptr - p_sz);
                pattern_ptr = sp[pattern_ptr - 1];
            
            // Несовпадение где-то, но не в начале.
            } else {
                pattern_ptr = sp[pattern_ptr - 1];
            }
        }
    }
};

int main() {
    std::string text = "abobabaabboba";
    std::string pattern = "ab";
    KMP solution(text, pattern);
    std::cout << solution.get_ans() << std::endl;
}
