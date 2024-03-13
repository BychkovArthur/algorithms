#include <array>
#include <compare>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using std::max;
using std::vector;

class BigInteger {
 private:
  bool is_positive = 1;

  vector<int> num;

  static BigInteger subtract(const BigInteger& a, const BigInteger& b);

  static BigInteger subtractWithAbs(const BigInteger& a, const BigInteger& b);

  void add(const BigInteger& b);

  BigInteger mulInt(int b) const;

 public:
  static const int kBase = 1'000'000'000;

  static const int kCount = 9;

  BigInteger() : is_positive(1){};

  BigInteger(long long new_num) : is_positive(new_num >= 0) {
    new_num = std::abs(new_num);
    while (new_num > 0) {
      num.push_back(new_num % kBase);
      new_num /= kBase;
    }
    removeLeadingZeros();
  }

  explicit BigInteger(const std::string& str) {
    is_positive = true;
    num.resize((str.size() + BigInteger::kCount - 1) / BigInteger::kCount, 0);
    int finish = 0;

    if (!str.empty() && str[0] == '-') {
      is_positive = 0;
      finish++;
    }

    int curindex = 0;
    for (int i = static_cast<int>(str.size()) - 1; i >= finish;
         i -= BigInteger::kCount) {
      int cur_block = 0;
      if (i - (BigInteger::kCount - 1) >= finish) {
        for (int j = i - (BigInteger::kCount - 1); j < i + 1; j++) {
          cur_block = 10 * cur_block + (str[j] - '0');
        }
      } else {
        for (int j = finish; j < i + 1; j++) {
          cur_block = 10 * cur_block + (str[j] - '0');
        }
      }
      num[curindex++] = cur_block;
    }
    removeLeadingZeros();
  }

  explicit BigInteger(int new_num)
      : BigInteger(static_cast<long long>(new_num)) {}

  explicit BigInteger(unsigned long long new_num) : is_positive(true) {
    while (new_num > 0) {
      num.push_back(new_num % kBase);
      new_num /= kBase;
    }
    removeLeadingZeros();
  }

  BigInteger(const BigInteger& new_biginteger) = default;

  BigInteger& operator=(const BigInteger& new_biginteger) = default;

  static BigInteger getPowerOf10(int power) {
    BigInteger res(1);
    res.InsertZerosFront(power);
    return res;
  }

 private:
  bool isLessAbs(const BigInteger& other) const {
    if (isZero() && other.isZero())
      return true;
    size_t sz_1 = num.size();
    size_t sz_2 = other.getSize();

    if (sz_1 < sz_2) {
      return true;
    } else if (sz_1 > sz_2) {
      return false;
    }
    for (int i = static_cast<int>(sz_1) - 1; i >= 0; i--) {
      if (num[i] < other.getBlock(i))
        return true;
      if (num[i] > other.getBlock(i))
        return false;
    }
    return true;
  }

  static std::strong_ordering getOrdering(bool val) {
    return val ? std::strong_ordering::less : std::strong_ordering::greater;
  }

  int getLeastPossibleDigit(const BigInteger& b) {
    int left = 0, right = BigInteger::kBase, mid;

    while (left < right - 1) {
      mid = (left + right) / 2;
      if (b.mulInt(mid) <= *this)
        left = mid;
      else
        right = mid;
    }
    return left;
  }

  static void karatsuba(const BigInteger& a,
                        const BigInteger& b,
                        BigInteger& c,
                        int offset_a,
                        int offset_b,
                        int offset_c,
                        long long sz_a,
                        long long sz_b);

  static void quadraticMultiply(const BigInteger& a,
                                const BigInteger& b,
                                BigInteger& c,
                                int offset_a,
                                int offset_b,
                                int offset_c,
                                int sz_a,
                                int sz_b);

  static void getSumOfTwoPolynoms(const BigInteger& from,
                                  BigInteger& to,
                                  int offset,
                                  size_t size_of_left_part,
                                  size_t sz);

 public:
  std::strong_ordering operator<=>(const BigInteger& other) const {
    if (isZero() && other.isZero())
      return std::strong_ordering::equal;

    size_t sz_1 = num.size();
    size_t sz_2 = other.getSize();

    bool is_positive_b = other.getSign();

    if (is_positive != is_positive_b && is_positive_b == 1) {
      return is_positive <=> is_positive_b;
    }

    bool to_reverse_sign = 0;
    if (is_positive == 0 && is_positive_b == 0) {
      to_reverse_sign = 1;
    }

    bool truth = 1 ^ to_reverse_sign;
    bool lie = 0 ^ to_reverse_sign;
    std::strong_ordering result = sz_1 <=> sz_2;

    if (sz_1 != sz_2) {
      return !is_positive ? 0 <=> result : result;
    }

    for (int i = static_cast<int>(sz_1) - 1; i >= 0; i--) {
      if (num[i] < other.getBlock(i))
        return getOrdering(truth);
      if (num[i] > other.getBlock(i))
        return getOrdering(lie);
    }
    return std::strong_ordering::equal;
  }

  friend bool operator==(const BigInteger& a, const BigInteger& b);

  BigInteger& operator*=(int b);

  BigInteger& operator-=(const BigInteger& b) {
    if (b.getSign() == false) {
      if (is_positive) {
        add(b);
      } else {
        *this = subtractWithAbs(b, *this);
      }
    } else {
      if (!is_positive) {
        add(b);
      } else {
        *this = subtractWithAbs(*this, b);
      }
    }

    return *this;
  }

  BigInteger& operator+=(const BigInteger& b) {
    if (is_positive == b.getSign()) {
      add(b);
    } else {
      if (is_positive) {
        *this = subtractWithAbs(*this, b);
      } else {
        *this = subtractWithAbs(b, *this);
      }
    }
    return *this;
  }

  BigInteger& operator/=(const BigInteger& b) {
    BigInteger result(0ULL);

    bool is_positive_b = b.is_positive;

    int start = static_cast<int>(num.size()) - 1,
        first_pos_of_incomplete_dividend = -1;
    BigInteger curent_dividend(0ULL);

    vector<int> res;

    for (int i = start; i >= 0; i--) {
      curent_dividend.InsertZerosFront(1);
      curent_dividend += getBlock(i);
      first_pos_of_incomplete_dividend = i - 1;
      if (b.isLessAbs(curent_dividend)) {
        break;
      }
    }
    int first_digit = curent_dividend.getLeastPossibleDigit(b), next_digit;
    res.push_back(first_digit);
    curent_dividend -= b.mulInt(first_digit);

    while (first_pos_of_incomplete_dividend >= 0) {
      curent_dividend.InsertZerosFront(1);
      curent_dividend += getBlock(first_pos_of_incomplete_dividend);
      first_pos_of_incomplete_dividend--;
      next_digit = curent_dividend.getLeastPossibleDigit(b);
      res.push_back(next_digit);
      curent_dividend -= b.mulInt(next_digit);
    }
    for (int i = static_cast<int>(res.size()) - 1; i >= 0; i--) {
      result.addBlock(res[i]);
    }
    if (is_positive == is_positive_b)
      result.getSign() = 1;
    else
      result.getSign() = 0;
    *this = result;
    return *this;
  }

  BigInteger& operator*=(const BigInteger& b) {
    BigInteger result;
    size_t sz_1 = getSize();
    size_t sz_2 = b.getSize();
    size_t maxsize = max(sz_1, sz_2);
    result.resize(2 * maxsize);
    karatsuba(*this, b, result, 0, 0, 0, sz_1, sz_2);
    if (is_positive == b.getSign())
      result.getSign() = 1;
    else
      result.getSign() = 0;

    result.removeLeadingZeros();
    *this = result;
    return *this;
  }

  BigInteger operator-() {
    BigInteger copy = *this;
    copy.getSign() = 1 - copy.getSign();
    return copy;
  }

  BigInteger& operator++() {
    *this += 1;
    return *this;
  }

  BigInteger operator++(int) {
    BigInteger copy = *this;
    *this += 1;
    return copy;
  }

  BigInteger& operator--() {
    *this -= 1;
    return *this;
  }

  BigInteger operator--(int) {
    BigInteger copy = *this;
    *this -= 1;
    return copy;
  }

  explicit operator bool() const {
    bool res = 1;
    if (isEmpty() || (num.size() == 1 && num[0] == 0)) {
      res = 0;
    }
    return res;
  }

  int operator[](size_t index) const {
    int block = num[index / kCount];
    int cnt = index % kCount;
    while (cnt-- > 0) {
      block /= 10;
    }
    return block % 10;
  }

  bool isZero() const {
    if (num.empty())
      return 1;
    return (num[0] == 0 && num.size() == 1);
  }

  const bool& getSign() const { return is_positive; }

  bool& getSign() { return is_positive; }

  std::string toString() const {
    std::string res;

    if (isEmpty()) {
      res = "0";
    } else {
      if (is_positive == 0 && !isZero()) {
        res += '-';
      }
      res += std::to_string(num.back());
      for (int i = static_cast<int>(num.size()) - 2; i >= 0; i--) {
        std::string cur_block = std::to_string(num[i]);
        int cnt_of_zeros_to_add_front = 0;
        if (BigInteger::kCount > cur_block.size())
          cnt_of_zeros_to_add_front = BigInteger::kCount - cur_block.size();
        if (cnt_of_zeros_to_add_front >= 1) {
          std::string to_add(cnt_of_zeros_to_add_front, '0');
          cur_block = to_add + cur_block;
        }
        res += cur_block;
      }
    }
    return res;
  }

  static void Swap(BigInteger& a, BigInteger& b) {
    std::swap(a.getSign(), b.getSign());
    std::swap(a.getData(), b.getData());
  }

 private:
  void InsertZerosFront(int count) { num.insert(num.begin(), count, 0); }

  bool isEmpty() const { return num.empty(); }

  size_t getSize() const { return num.size(); }

  int getByIndex(size_t index) const {
    if (num.size() <= index)
      return 0;
    return num[index];
  }

  const int& getBack() const { return num.back(); }

  void addBlock(int digit) { num.push_back(digit); }

  const int& getBlock(size_t index) const { return num[index]; }

  int& getBlock(size_t index) { return num[index]; }

  const vector<int>& getData() const { return num; }

  vector<int>& getData() { return num; }

  void removeLeadingZeros() {
    while (num.size() > 0 && num.back() == 0)
      num.pop_back();
  }

  void resize(size_t newsize) { num.resize(newsize, 0); }

  bool makeDigitValid(size_t index) {
    int carry = 0;
    if (num.size() == 0)
      return false;
    if (num[index] >= BigInteger::kBase) {
      carry = num[index] / BigInteger::kBase;
      if (index == num.size() - 1) {
        num.push_back(carry);
      } else {
        num[index + 1] += carry;
      }
      num[index] -= carry * BigInteger::kBase;
      return true;
    } else if (num[index] < 0) {
      carry = (num[index] + 1) / BigInteger::kBase - 1;
      if (index == num.size() - 1) {
        num.push_back(carry);
      } else {
        num[index + 1] += carry;
      }
      num[index] -= carry * BigInteger::kBase;
      return true;
    }
    return false;
  }

  void normalize(size_t left, size_t right) {
    size_t cur_size = num.size();
    if (cur_size == 0)
      return;
    size_t border = std::min(right, cur_size);
    for (size_t i = left; i < border; i++) {
      makeDigitValid(i);
    }
  }
};

bool operator==(const BigInteger& a, const BigInteger& b) {
  if (a.isZero() && b.isZero())
    return true;
  size_t sz_1 = a.getSize();
  if (sz_1 != b.getSize() || a.getSign() != b.getSign())
    return false;

  return a.getData() == b.getData();
}

BigInteger operator""_bi(const char* str, size_t cnt) {
  BigInteger res = BigInteger(std::string(str).substr(0, cnt));
  return res;
}

BigInteger operator""_bi(unsigned long long in) {
  BigInteger res(in);
  return res;
}

// a - b
BigInteger BigInteger::subtractWithAbs(const BigInteger& a,
                                       const BigInteger& b) {
  bool is_b_Less = b.isLessAbs(a);
  BigInteger res;
  if (is_b_Less) {
    res = subtract(a, b);
    res.is_positive = 1;
  } else {
    res = subtract(b, a);
    res.is_positive = 0;
  }
  return res;
}

BigInteger BigInteger::subtract(const BigInteger& a, const BigInteger& b) {
  BigInteger res(a);
  size_t common_size = max(a.getSize(), b.getSize());
  int carry = 0;
  bool to_stop = 0;

  for (size_t i = 0; i < common_size || carry; i++) {
    int to_substract = 0;
    if (i < b.getSize())
      to_substract = b.getBlock(i);
    else {
      to_stop = 1;
    }
    res.getBlock(i) -= to_substract + carry;
    if (res.getBlock(i) < 0) {
      res.getBlock(i) += BigInteger::kBase;
      carry = 1;
    } else {
      carry = 0;
      if (to_stop)
        break;
    }
  }
  res.removeLeadingZeros();
  return res;
}

void BigInteger::add(const BigInteger& b) {
  bool carry = 0;
  size_t common_size = max(num.size(), b.getSize());
  bool to_stop = 0;
  for (size_t i = 0; i < common_size || carry; i++) {
    if (num.size() == i)
      addBlock(0);
    int to_add = 0;
    if (i < b.getSize())
      to_add = b.getBlock(i);
    else {
      to_stop = 1;
    }
    num[i] += carry + to_add;
    if (num[i] >= BigInteger::kBase) {
      num[i] -= BigInteger::kBase;
      carry = 1;
    } else {
      carry = 0;
      if (to_stop)
        break;
    }
  }
}

BigInteger operator+(const BigInteger& a, const BigInteger& b) {
  BigInteger new_a(a);
  new_a += b;
  return new_a;
}

BigInteger operator-(const BigInteger& a, const BigInteger& b) {
  BigInteger new_a(a);
  new_a -= b;
  return new_a;
}

BigInteger& BigInteger::operator*=(int b) {
  int carry = 0;
  size_t sz = num.size();
  for (size_t i = 0; i < sz || carry; ++i) {
    if (i == sz)
      addBlock(0);
    long long cur = carry + getBlock(i) * 1LL * b;
    getBlock(i) = static_cast<int>(cur % BigInteger::kBase);
    carry = static_cast<int>(cur / BigInteger::kBase);
  }
  removeLeadingZeros();
  return *this;
}

BigInteger BigInteger::mulInt(int b) const {
  BigInteger new_a(*this);
  new_a *= b;
  new_a.is_positive = 1;
  return new_a;
}

void BigInteger::quadraticMultiply(const BigInteger& a,
                                   const BigInteger& b,
                                   BigInteger& c,
                                   int offset_a,
                                   int offset_b,
                                   int offset_c,
                                   int sz_a,
                                   int sz_b) {
  long long carry = 0;
  long long curp;
  int glob_size_a = a.getSize();
  int glob_size_b = b.getSize();

  for (int i = 0; i < sz_a; i++) {
    if (offset_a + i >= glob_size_a) {
      break;
    }
    long long to_add = a.getBlock(offset_a + i);
    for (int j = 0; j < sz_b || carry > 0; j++) {
      long long mult = 0;
      if (offset_b + j < glob_size_b) {
        if (j < sz_b)
          mult = b.getBlock(offset_b + j);
      }
      curp = 1LL * to_add * mult +
             static_cast<long long>(c.getBlock(offset_c + i + j)) + carry;
      carry = curp / BigInteger::kBase;
      c.getBlock(offset_c + i + j) = (curp % BigInteger::kBase);
    }
  }
}

void BigInteger::getSumOfTwoPolynoms(const BigInteger& from,
                                     BigInteger& to,
                                     int offset,
                                     size_t size_of_left_part,
                                     size_t sz) {
  for (size_t i = 0; i < to.getSize(); i++) {
    int a_i = from.getByIndex(offset + i);
    if (i >= size_of_left_part) {
      a_i = 0;
    }
    int a_i_plus_k = from.getByIndex(offset + i + size_of_left_part);
    if (i >= sz - size_of_left_part) {
      a_i_plus_k = 0;
    }
    to.getBlock(i) += a_i + a_i_plus_k;
    to.makeDigitValid(i);
  }
}

void BigInteger::karatsuba(const BigInteger& a,
                           const BigInteger& b,
                           BigInteger& c,
                           int offset_a,
                           int offset_b,
                           int offset_c,
                           long long sz_a,
                           long long sz_b) {
  if (max(sz_a, sz_b) <= 64) {
    quadraticMultiply(a, b, c, offset_a, offset_b, offset_c, sz_a, sz_b);
    return;
  }
  long long k1 = sz_a / 2;
  long long k2 = sz_b / 2;
  long long k = std::max(k1, k2);
  BigInteger left, right, t;
  int border = max({k, sz_a - k, sz_b - k});
  left.resize(border);
  right.resize(border);
  getSumOfTwoPolynoms(a, left, offset_a, k, sz_a);
  getSumOfTwoPolynoms(b, right, offset_b, k, sz_b);

  border = max(left.getSize(), right.getSize());

  t.resize(2 * border);

  karatsuba(left, right, t, 0, 0, 0, left.getSize(), right.getSize());
  karatsuba(a, b, c, offset_a + k, offset_b + k, offset_c + 2 * k, sz_a - k,
            sz_b - k);
  karatsuba(a, b, c, offset_a, offset_b, offset_c, k, k);
  BigInteger res = c;
  int to_subtract1 = 0;
  int to_subtract2 = 0;
  int prev_size = t.getSize();
  int sum_k12 = 2 * k;
  int sum_left = sz_a + sz_b - 2 * k;
  bool is_last_overflow = false;
  for (int i = 0; i < prev_size; i++) {
    to_subtract1 = to_subtract2 = 0;
    if (i < sum_k12) {
      to_subtract1 = c.getBlock(offset_c + i);
    }
    if (i < sum_left) {
      to_subtract2 = c.getBlock(offset_c + i + 2 * k);
    }
    t.getBlock(i) -= to_subtract1 + to_subtract2;
  }
  for (size_t i = 0; i < t.getSize(); i++) {
    c.getBlock(offset_c + k + i) += t.getBlock(i);
    is_last_overflow = c.makeDigitValid(offset_c + k + i);
  }
  if (is_last_overflow)
    c.makeDigitValid(offset_c + t.getSize() + k);
}

BigInteger operator*(const BigInteger& a, const BigInteger& b) {
  BigInteger new_a(a);
  new_a *= b;
  return new_a;
}

BigInteger operator/(const BigInteger& a, const BigInteger& b) {
  BigInteger new_a(a);
  new_a /= b;
  return new_a;
}

BigInteger& operator%=(BigInteger& a, const BigInteger& b) {
  BigInteger res = a / b;
  a -= res * b;
  return a;
}

BigInteger operator%(const BigInteger& a, const BigInteger& b) {
  BigInteger new_a(a);
  new_a %= b;
  return new_a;
}

std::istream& operator>>(std::istream& in, BigInteger& bi) {
  std::string res;
  in >> res;
  bi = BigInteger(res);
  return in;
}

std::ostream& operator<<(std::ostream& out, const BigInteger& bi) {
  out << bi.toString();
  return out;
}

BigInteger gcd(const BigInteger& cur_block_a, const BigInteger& cur_block_b) {
  BigInteger a(cur_block_a), b(cur_block_b);

  if (a < b) {
    BigInteger::Swap(a, b);
  }

  if (b == 0)
    return a;

  while (a % b != 0) {
    BigInteger::Swap(a, b);

    b %= a;
  }
  return b;
}

class Rational {
 private:
  BigInteger numerator;
  BigInteger denominator;

  void Reduce() {
    bool ressign = 0;
    if (numerator.getSign() == denominator.getSign()) {
      ressign = 1;
    }
    numerator.getSign() = 1;
    denominator.getSign() = 1;
    BigInteger fracgcd = gcd(numerator, denominator);
    numerator /= fracgcd;
    denominator /= fracgcd;
    numerator.getSign() = ressign;
  }

 public:
  Rational() : numerator(0ULL), denominator(0ULL){};

  Rational(long long newv) : numerator(newv), denominator(1ULL) {}

  Rational(const BigInteger& newv) : numerator(newv), denominator(1LL) {}

  Rational(const Rational& newRational) = default;

  Rational& operator=(const Rational& newRational) = default;

  std::strong_ordering operator<=>(const Rational& other) const {
    if (numerator == 0 && other.getNumer() == 0)
      return std::strong_ordering::equal;
    if (numerator == other.getNumer() && denominator == other.getDenom())
      return std::strong_ordering::equal;

    return numerator * other.getDenom() <=> other.getNumer() * denominator;
  }

  bool operator==(const Rational& other) const = default;

  Rational& operator+=(const Rational& b) {
    numerator *= b.getDenom();
    numerator += b.getNumer() * denominator;
    denominator = denominator * b.getDenom();
    Reduce();
    return *this;
  }

  Rational& operator-=(const Rational& b) {
    numerator *= b.getDenom();
    numerator -= b.getNumer() * denominator;
    denominator = denominator * b.getDenom();
    Reduce();
    return *this;
  }

  Rational& operator*=(const Rational& b) {
    numerator *= b.getNumer();
    denominator *= b.getDenom();
    Reduce();
    return *this;
  }

  Rational& operator/=(const Rational& b) {
    numerator *= b.getDenom();
    denominator *= b.getNumer();
    Reduce();
    return *this;
  }

  Rational operator-() {
    Rational copy = *this;
    copy.numerator.getSign() = 1 - copy.numerator.getSign();
    return copy;
  }

  const BigInteger& getDenom() const { return denominator; }

  BigInteger& getDenom() { return denominator; }

  const BigInteger& getNumer() const { return numerator; }

  BigInteger& getNumer() { return numerator; }

  std::string toString() const {
    std::string res;
    res = numerator.toString();
    if (denominator != 1 && denominator != 0) {
      res += '/' + denominator.toString();
    }
    return res;
  }

  std::string asDecimal(size_t precision = 0) {
    std::string res;
    bool is_positive = numerator.getSign();
    if (numerator.getSign() == 0 && !numerator.isZero()) {
      res += '-';
    }
    numerator.getSign() = 1;
    BigInteger fraction = numerator / denominator;
    res += fraction.toString();
    fraction = numerator - fraction * denominator;
    if (precision > 0) {
      res += '.';
      int cnt_zeros_to_add = precision / BigInteger::kCount;

      fraction = fraction * BigInteger::getPowerOf10(cnt_zeros_to_add);

      int left = precision % BigInteger::kCount;
      for (int i = 0; i < left; i++) {
        fraction *= 10;
      }
      std::string cur_block = (fraction / denominator).toString();
      size_t cnt = 0;
      if (cur_block.size() < precision)
        cnt = precision - static_cast<long long>(cur_block.size());
      if (cnt >= 1) {
        std::string to_add_zeros(cnt, '0');
        cur_block = to_add_zeros + cur_block;
      }
      res += cur_block;
    }
    numerator.getSign() = is_positive;
    return res;
  }

  explicit operator double() {
    std::string conv = asDecimal(1074);
    double res = stod(conv);
    return res;
  }
};

Rational operator+(const Rational& a, const Rational& b) {
  Rational new_a(a);
  new_a += b;
  return new_a;
}

Rational operator-(const Rational& a, const Rational& b) {
  Rational new_a(a);
  new_a -= b;
  return new_a;
}

Rational operator*(const Rational& a, const Rational& b) {
  Rational new_a(a);
  new_a *= b;
  return new_a;
}

Rational operator/(const Rational& a, const Rational& b) {
  Rational new_a(a);
  new_a /= b;
  return new_a;
}

template <size_t N, size_t D>
constexpr bool isPrime() {
  if constexpr (D * D == N)
    return false;
  if constexpr (D * D > N)
    return true;
  else
    return N % D == 0 ? false : isPrime<N, D + 1>();
}

template <size_t N>
struct IsPrime {
  static constexpr bool value = isPrime<N, 2>();
};

template <>
struct IsPrime<1> {
  static constexpr bool value = false;
};

template <long long N>
class Residue {
 private:
  long long value;

  static Residue binpow(const Residue& a, int k) {
    if (k == 0)
      return Residue(1);
    if (k == 1)
      return Residue(a);
    if (k % 2 == 0) {
      Residue val = binpow(a, k / 2);
      return val * val;
    }
    return a * binpow(a, k - 1);
  }

 public:
  Residue() : value(0) {}

  Residue(long long new_v) : value(((new_v % N) + N) % N) {}

  bool operator==(const Residue& other) const {
    long long difference = value - other.getValue();
    if (difference % N == 0)
      return true;
    return false;
  }

  explicit operator long long() const {
    return value;
  }

  long long getValue() const {
    return value;
  }

  Residue& operator+=(const Residue& other) {
    value += other.value;
    value = (((value % N) + N) % N);
    return *this;
  }

  Residue& operator-=(const Residue& other) {
    value -= other.value;
    value = (((value % N) + N) % N);

    return *this;
  }

  Residue& operator*=(const Residue& other) {
    long long result = static_cast<long long>(value) * other.getValue();
    value = (result % N);
    value = (((value % N) + N) % N);
    return *this;
  }

  Residue& operator/=(const Residue& other) {
    static_assert(IsPrime<N>::value);
    *this = *this * binpow(other, N - 2);
    value = (((value % N) + N) % N);
    return *this;
  }

  Residue operator-() { return Residue(-value); }

  std::string toString() const { return std::to_string(value); }
};

template <long long N>
Residue<N> operator+(const Residue<N>& a, const Residue<N>& b) {
  Residue<N> new_a(a);
  new_a += b;
  return new_a;
}

template <long long N>
Residue<N> operator-(const Residue<N>& a, const Residue<N>& b) {
  Residue<N> new_a(a);
  new_a -= b;
  return new_a;
}

template <long long N>
Residue<N> operator*(const Residue<N>& a, const Residue<N>& b) {
  Residue<N> new_a(a);
  new_a *= b;
  return new_a;
}

template <long long N>
Residue<N> operator/(const Residue<N>& a, const Residue<N>& b) {
  Residue<N> new_a(a);
  new_a /= b;
  return new_a;
}

template <size_t N, typename Field = Rational>
class row {
 private:
  Field arr[N];

 public:
  row() { std::fill(arr, arr + N, Field(0)); }

  const Field& operator[](size_t index) const { return arr[index]; }

  Field& operator[](size_t index) { return arr[index]; }

  row& operator+=(const row& other) {
    for (size_t i = 0; i < N; i++) {
      arr[i] += other[i];
    }
    return *this;
  }

  row& operator-=(const row& other) {
    for (size_t i = 0; i < N; i++) {
      arr[i] -= other[i];
    }
    return *this;
  }

  row& operator*=(const Field& factor) {
    for (size_t i = 0; i < N; i++) {
      arr[i] *= factor;
    }
    return *this;
  }

  row& operator/=(const Field& factor) {
    for (size_t i = 0; i < N; i++) {
      arr[i] /= factor;
    }
    return *this;
  }

  bool isRowZero() const {
    for (size_t i = 0; i < N; i++) {
      if (arr[i] != 0) {
        return false;
      }
    }
    return true;
  }
};

template <size_t N, typename Field = Rational>
row<N, Field> operator+(const row<N, Field>& a, const row<N, Field>& b) {
  row<N, Field> new_a(a);
  new_a += b;
  return new_a;
}

template <size_t N, typename Field = Rational>
row<N, Field> operator-(const row<N, Field>& a, const row<N, Field>& b) {
  row<N, Field> new_a(a);
  new_a -= b;
  return new_a;
}

template <size_t N, typename Field = Rational>
row<N, Field> operator*(const row<N, Field>& a, const Field& factor) {
  row<N, Field> new_a(a);
  new_a *= factor;
  return new_a;
}

template <size_t M, size_t N, typename Field = Rational>
class Matrix {
 private:

  row<N, Field> matr[M];

 public:
  Matrix() = default;

  Matrix(std::initializer_list<std::initializer_list<Field>> new_matr) {
    int cur_index_j = 0;
    int cur_index_i = 0;

    for (const auto& in_row : new_matr) {
      cur_index_j = 0;
      for (const auto& in_elem : in_row) {
        matr[cur_index_i][cur_index_j++] = in_elem;
      }
      cur_index_i++;
    }
  }

  bool operator==(const Matrix& other) const {
    for (size_t i = 0; i < M; i++) {
      for (size_t j = 0; j < N; j++) {
        if (matr[i][j] != other[i][j])
          return false;
      }
    }
    return true;
  };

  Matrix& operator+=(const Matrix& other) {
    for (size_t i = 0; i < M; i++) {
      matr[i] += other[i];
    }
    return *this;
  }

  Matrix& operator-=(const Matrix& other) {
    for (size_t i = 0; i < M; i++) {
      matr[i] -= other[i];
    }
    return *this;
  }

  Matrix& operator*=(const Matrix<M, M, Field>& other) {
    *this = *this * other;
    return *this;
  }

  Matrix& operator*=(const Field& num) {
    for (size_t i = 0; i < M; i++) {
      matr[i] *= num;
    }
    return *this;
  }

  const row<N, Field>& operator[](size_t index) const { return matr[index]; }

  row<N, Field>& operator[](size_t index) { return matr[index]; }

  std::array<Field, M> getColumn(size_t index_row) const {
    std::array<Field, M> result;
    for (size_t i = 0; i < M; i++) {
      result[i] = matr[i][index_row];
    }
    return result;
  }

  std::array<Field, N> getRow(size_t index_column) const {
    std::array<Field, N> result;

    for (size_t i = 0; i < N; i++) {
      result[i] = matr[index_column][i];
    }
    return result;
  }

  Field trace() const {
    static_assert(N == M);
    Field sum = 0;
    for (size_t i = 0; i < N; i++) {
      sum += matr[i][i];
    }
    return sum;
  }

  static Matrix IdentityMatrix() {
    static_assert(N == M);
    Matrix res;

    for (size_t i = 0; i < N; i++) {
      res[i][i] = 1;
    }
    return res;
  }

  Matrix toUpperTriangular(long long& cnt_of_swaps) const {
    Matrix res(*this);

    for (size_t i = 0; i < N; i++) {
      bool is_finded_non_zero = false;
      size_t row_index = 0;
      for (size_t j = i; j < M; j++) {
        if (res[j][i] != 0) {
          is_finded_non_zero = true;
          row_index = j;
          break;
        }
      }
      if (!is_finded_non_zero) {
        continue;
      }
      std::swap(res[row_index], res[i]);
      if (row_index != i) {
        cnt_of_swaps++;
      }

      for (size_t j = i + 1; j < M; j++) {
        res[j] -= res[i] * (res[j][i] / res[i][i]);
      }
    }
    return res;
  }

  void invert() {
    static_assert(M == N);

    Matrix inv_Matrix = IdentityMatrix();

    for (size_t i = 0; i < N; i++) {
      bool is_finded_non_zero = false;
      size_t row_index = 0;
      for (size_t j = i; j < M; j++) {
        if (matr[j][i] != Field(0)) {
          is_finded_non_zero = true;
          row_index = j;
          break;
        }
      }
      if (!is_finded_non_zero) {
        continue;
      }
      std::swap(matr[row_index], matr[i]);
      std::swap(inv_Matrix[row_index], inv_Matrix[i]);

      for (size_t j = i + 1; j < M; j++) {
        Field factor = matr[j][i] / matr[i][i];
        row r = matr[i] * factor;
        matr[j] -= r;
        inv_Matrix[j] -= inv_Matrix[i] * factor;
      }
    }

    for (int i = N - 1; i >= 0; i--) {
      Field factor = matr[i][i];
      matr[i] /= factor;
      inv_Matrix[i] /= factor;
      int current_row = M - 1 - (N - 1 - i);
      for (int j = current_row - 1; j >= 0; j--) {
        factor = matr[j][i];
        matr[j] -= matr[current_row] * factor;
        inv_Matrix[j] -= inv_Matrix[current_row] * factor;
      }
    }
    *this = inv_Matrix;
  }

  Matrix inverted() const {
    Matrix res(*this);
    res.invert();
    return res;
  }

  Field det() const {
    static_assert(N == M);

    long long cnt_of_swaps = 0;
    Matrix result = toUpperTriangular(cnt_of_swaps);
    Field determinant = 1;
    for (size_t i = 0; i < N; i++) {
      determinant *= result[i][i];
    }
    if (cnt_of_swaps & 1LL) {
      determinant = -determinant;
    }
    return determinant;
  }

  long long rank() const {
    long long cnt_of_swaps;

    Matrix result = toUpperTriangular(cnt_of_swaps);

    long long rk = M;

    for (int i = static_cast<int>(M) - 1; i >= 0; i--) {
      if (result[i].isRowZero()) {
        rk--;
      } else {
        break;
      }
    }
    return rk;
  }

  Matrix<N, M, Field> transposed() const {
    Matrix<N, M, Field> res;

    for (size_t i = 0; i < M; i++) {
      for (size_t j = 0; j < N; j++) {
        res[j][i] = matr[i][j];
      }
    }
    return res;
  }
};

template <size_t N, typename Field = Rational>
using SquareMatrix = Matrix<N, N, Field>;

template <size_t M, size_t N, typename Field = Rational>
Matrix<M, N, Field> operator+(const Matrix<M, N, Field>& a,
                              const Matrix<M, N, Field>& b) {
  Matrix<M, N, Field> new_a(a);
  new_a += b;
  return new_a;
}

template <size_t M, size_t N, typename Field = Rational>
Matrix<M, N, Field> operator-(const Matrix<M, N, Field>& a,
                              const Matrix<M, N, Field>& b) {
  Matrix<M, N, Field> new_a(a);

  new_a -= b;
  return new_a;
}

template <size_t M, size_t N, size_t K, typename Field = Rational>
Matrix<M, K, Field> operator*(const Matrix<M, N, Field>& a,
                              const Matrix<N, K, Field>& b) {
  Matrix<M, K, Field> new_matr;

  for (size_t i = 0; i < M; i++) {
    for (size_t j = 0; j < K; j++) {
      for (size_t k = 0; k < N; k++) {
        new_matr[i][j] += a[i][k] * b[k][j];
      }
    }
  }
  return new_matr;
}

template <size_t M, size_t N, typename Field = Rational>
Matrix<M, N, Field> operator*(const Matrix<M, N, Field>& a,
                              const Field& b) {
  Matrix<M, N, Field> new_a(a);

  new_a *= b;
  return new_a;
}

template <size_t M, size_t N, typename Field = Rational>
Matrix<M, N, Field> operator*(const Field& b, const Matrix<M, N, Field>& a) {
  Matrix<M, N, Field> new_a(a);

  new_a *= b;
  return new_a;
}

template <size_t M, size_t N, typename Field = Rational>
std::ostream& operator<<(std::ostream& out, Matrix<M, N, Field> matr) {
  for (size_t i = 0; i < M; i++) {
    for (size_t j = 0; j < N; j++) {
      out << matr[i][j].toString() << " ";
    }
    out << '\n';
  }

  return out;
}

template <size_t N, typename Field = Rational>
std::ostream& operator<<(std::ostream& out, const row<N, Field>& row) {
  for (size_t i = 0; i < N; i++) {
    out << row[i].toString() << " ";
  }
  out << '\n';
  return out;
}

std::istream& operator>>(std::istream& in, Rational& rat) {
  std::string result;
  in >> result;
  rat.getNumer() = BigInteger(result);
  return in;
}
