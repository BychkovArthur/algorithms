#include <array>
#include <compare>
#include <iomanip>
#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

template <typename T>
class Deque {
 private:

  T** buckets = nullptr;

  static const long long BLOCK_SIZE = 32;

  template <typename Type>
  class base_iterator {
   public:
    using value_type = Type;

    using block_pointer = T**;

    using pointer_type = Type*;

    using reference_type = Type&;

    using difference_type = ptrdiff_t;

   private:

    block_pointer num_of_bucket;

    pointer_type index_in_bucket;

   public:
    base_iterator()
        : num_of_bucket(nullptr), index_in_bucket(nullptr) {}

    base_iterator(block_pointer new_num_of_bucket,
                  pointer_type new_index_in_bucket)
        : num_of_bucket(new_num_of_bucket),
          index_in_bucket(new_index_in_bucket) {}

    base_iterator(const base_iterator& other) = default;

    operator base_iterator<const Type>() const {
      Type* new_index = index_in_bucket;
      T** new_num_of_bucket = num_of_bucket;

      base_iterator<const Type> copy(new_num_of_bucket, new_index);

      return copy;
    }

    base_iterator& operator=(const base_iterator& other) = default;

    std::strong_ordering operator<=>(const base_iterator& other) const = default;

    base_iterator& operator++() {
      return operator+=(1);
    }

    base_iterator operator++(int) {
      base_iterator copy = *this;
      operator++();
      return copy;
    }

    base_iterator& operator--() {
      return operator+=(-1);
    }

    base_iterator operator--(int) {
      base_iterator copy = *this;
      operator--();
      return copy;
    }

    base_iterator& operator+=(long long offset) {
      if (index_in_bucket == nullptr) {
        return *this;
      }
      index_in_bucket += offset;

      long long cnt_to_add = (index_in_bucket - *num_of_bucket) / BLOCK_SIZE;
      long long new_ind = (index_in_bucket - *num_of_bucket) - cnt_to_add * BLOCK_SIZE;
      if (new_ind < 0) {
        long long cnt_to_remove = std::abs((new_ind - BLOCK_SIZE + 1) / BLOCK_SIZE);
        new_ind += BLOCK_SIZE * cnt_to_remove;
        cnt_to_add -= cnt_to_remove;
      }
      num_of_bucket += cnt_to_add;
      index_in_bucket = *num_of_bucket + new_ind;

      return *this;
    }

    base_iterator operator+(long long offset) const {
      base_iterator copy(*this);
      copy += offset;
      return copy;
    }

    friend base_iterator operator+(long long offset, const base_iterator& iter) {
      base_iterator copy(iter);
      copy += offset;
      return copy;
    }

    base_iterator& operator-=(long long offset) {
      return operator+=(-offset);
    }

    base_iterator operator-(long long offset) const {
      base_iterator copy(*this);
      copy -= offset;
      return copy;
    }

    difference_type operator-(const base_iterator& other) const {
      if (index_in_bucket == nullptr) {
        return 0;
      }
      return (num_of_bucket - other.num_of_bucket) * BLOCK_SIZE +
             (index_in_bucket - *num_of_bucket) -
             (other.index_in_bucket - *other.num_of_bucket);
    }

    reference_type operator*() const { return *index_in_bucket; }

    const pointer_type operator->() const { return index_in_bucket; }

    block_pointer getNumOfBucket() const { return num_of_bucket; }

    pointer_type getIndexInBucket() const { return index_in_bucket; }

    reference_type operator[](size_t index) const {
      return *operator+(index);
    }
  };

  base_iterator<T> start = base_iterator<T>(nullptr, nullptr);

  base_iterator<T> finish = base_iterator<T>(nullptr, nullptr);

  size_t num_of_buckets = 0;

  size_t current_offset = 0;

  enum class query_type {
    front,
    back
  };

  long long getOffset(const base_iterator<T>& iter) const {
    long long v1 = iter - iterator(&buckets[0], buckets[0]);
    return v1;
  }

  void swap(Deque& other) {
    std::swap(buckets, other.buckets);
    std::swap(start, other.start);
    std::swap(finish, other.finish);
    std::swap(num_of_buckets, other.num_of_buckets);
  }

  bool isMemoryAllocated(size_t new_index) const {
    return buckets[new_index] != nullptr;
  }

  void allocateBucket(size_t new_index) {
    buckets[new_index] = reinterpret_cast<T*>(new char[BLOCK_SIZE * sizeof(T)]);
  }

  bool checkAndAllocate(size_t new_index) {
    if (buckets[new_index] == nullptr) {
      buckets[new_index] = reinterpret_cast<T*>(new char[BLOCK_SIZE * sizeof(T)]);
    }
    return buckets[new_index] == nullptr;
  }

  static void assign(Deque &dest, const Deque& source) {
    dest.buckets = source.buckets;
    dest.start = source.start;
    dest.finish = source.finish;
    dest.current_offset = source.current_offset;
    dest.num_of_buckets = source.num_of_buckets;
  }

  void reserve(size_t new_num_of_buckets,
               bool is_to_shift_start,
               Deque& old_deque,
               bool is_dangerous = false) {
    if (new_num_of_buckets <= num_of_buckets) {
      return;
    }

    if (is_dangerous) {
      assign(old_deque, *this);
    }

    auto [num_of_bucket_start, index_in_bucket_start] =
        getNumberAndIndex(start);
    auto [num_of_bucket_finish, index_in_bucket_finish] =
        getNumberAndIndex(finish);

    T** new_arr = new T* [new_num_of_buckets] {nullptr};

    size_t start_index = 0;

    if (is_to_shift_start)
      start_index = new_num_of_buckets / 3;

    current_offset = start_index;

    for (size_t i = 0; i < num_of_buckets; i++) {
      new_arr[i + start_index] = buckets[i];
    }

    buckets = new_arr;

    checkAndAllocate(num_of_bucket_start + start_index);
    checkAndAllocate(num_of_bucket_finish + start_index);

    start = {&buckets[num_of_bucket_start + start_index],
        buckets[num_of_bucket_start + start_index] + index_in_bucket_start};
    finish = {
        &buckets[num_of_bucket_finish + start_index],
        buckets[num_of_bucket_finish + start_index] + index_in_bucket_finish};

    num_of_buckets = new_num_of_buckets;
  }

  void realloc(Deque &old_deque, bool is_dangerous) {
    if (num_of_buckets == 0) {
      reserve(3, true, old_deque, is_dangerous);
      return;
    }

    reserve(3 * num_of_buckets, true, old_deque, is_dangerous);
  }

  void initializeIterators(size_t num_of_bucket, size_t index_in_bucket) {
    start = {&buckets[num_of_bucket], buckets[num_of_bucket] + index_in_bucket};
    finish = start;
  }

  void rollback() {
    while (start != finish) {
      pop_back();
      auto [num_of_bucket_finish, index_in_bucket_finish] =
          getNumberAndIndex(finish);

      if (index_in_bucket_finish == 0) {
        delete[] reinterpret_cast<char*>(buckets[num_of_bucket_finish]);
      }
    }
    delete[] buckets;
    start = finish = {nullptr, nullptr};
  }

  void rollbackRealloc(const Deque& old_deque) {
    if (buckets != nullptr) {
      delete[] buckets;
    }
    assign(*this, old_deque);
  }

  void addElement(const T& other) {
    auto [num_of_bucket_finish, index_in_bucket_finish] =
        getNumberAndIndex(finish);

    try {
      new (buckets[num_of_bucket_finish] + index_in_bucket_finish) T(other);
    } catch(...) {
      throw;
    }

    if (index_in_bucket_finish == BLOCK_SIZE - 1) {
      checkAndAllocate(num_of_bucket_finish + 1);
    }
    ++finish;
  }

 public:

  using iterator = base_iterator<T>;

  using const_iterator = base_iterator<const T>;

  using reverse_iterator = std::reverse_iterator<iterator>;

  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  Deque()
      : buckets(nullptr),
        start({nullptr, nullptr}),
        finish({nullptr, nullptr}),
        num_of_buckets(0), current_offset(0) {};

  Deque(size_t size, const T& other = T()) {
    size_t cnt = (size + BLOCK_SIZE - 1) / BLOCK_SIZE + 1;
    Deque old_deq;
    reserve(cnt, false, old_deq, false);

    for (size_t i = 0; i < cnt; i++) {
      checkAndAllocate(i);
    }

    try {
      for (size_t cnt = 0; cnt < size; cnt++) {
        addElement(other);
      }
    } catch (...) {
      rollback();
      throw;
    }
  }

  ~Deque() {
    if (buckets == nullptr) {
      return;
    }

    while (finish != start) {
      pop_back();
    }
    for (size_t i = 0; i < num_of_buckets; i++) {
      if (buckets[i] != nullptr) {
        delete[] reinterpret_cast<char*>(buckets[i]);
      }
    }
    if (buckets != nullptr) {
      delete[] buckets;
    }
  }

  Deque& operator=(Deque other) {
    swap(other);
    return *this;
  }

  Deque(const Deque& other) {
    if (other.num_of_buckets == 0) {
      return;
    }

    auto [num_of_bucket_start, index_in_bucket_start] =
        other.getNumberAndIndex(other.start);
    auto [num_of_bucket_finish, index_in_bucket_finish] =
        other.getNumberAndIndex(other.finish);

    size_t other_sz = other.size();

    Deque old_deq;

    reserve(other.num_of_buckets, false, old_deq, false);

    checkAndAllocate(num_of_bucket_start);
    initializeIterators(num_of_bucket_start, index_in_bucket_start);

    try {
      for (size_t cnt = 0; cnt < other_sz; cnt++) {
        addElement(*(other.start + cnt));
      }
    } catch(...) {
      rollback();
      throw;
    }

    if (buckets == nullptr) {
      start = finish = {nullptr, nullptr};
    } else {
      start = {&buckets[num_of_bucket_start],
               buckets[num_of_bucket_start] + index_in_bucket_start};
      finish = {&buckets[num_of_bucket_finish],
                buckets[num_of_bucket_finish] + index_in_bucket_finish};
    }
  }

  size_t size() const {
    size_t sz = finish - start;
    return sz;
  }

  const T& operator[](size_t ind) const {
    const_iterator destination = start + ind;
    return *destination;
  }

  T& operator[](size_t ind) {
    iterator destination = start + ind;
    return *destination;
  }

  const T& at(size_t ind) const {
    iterator destination = start + ind;
    if (destination >= finish || destination < start) {
      throw std::out_of_range("out_of_range");
    }
    return *destination;
  }

  T& at(size_t ind) {
    iterator destination = start + ind;
    if (destination >= finish || destination < start) {
      throw std::out_of_range("out_of_range");
    }
    return *destination;
  }

 private:
  std::pair<long long, long long> getNumberAndIndex(const iterator& ind) const {
    if (ind.getIndexInBucket() == nullptr) {
      return {0, 0};
    }
    size_t global_offset = getOffset(ind);

    size_t num_of_bucket = global_offset / BLOCK_SIZE;
    size_t index_in_bucket = global_offset - num_of_bucket * BLOCK_SIZE;
    return {num_of_bucket, index_in_bucket};
  }

  void addByIndex(iterator& ind, const T& value, const query_type& query) {
    auto [num_of_bucket, index_in_bucket] = getNumberAndIndex(ind);

    if (query == query_type::front) {
      index_in_bucket--;
      if (index_in_bucket < 0) {
        index_in_bucket += BLOCK_SIZE;
        num_of_bucket--;
      }
    }

    bool was_allocated = checkAndAllocate(num_of_bucket);

    try {
      new (buckets[num_of_bucket] + index_in_bucket) T(value);
    } catch (...) {
      if (was_allocated) {
        delete[] reinterpret_cast<char*>(buckets[num_of_bucket]);
        buckets[num_of_bucket] = nullptr;
      }
      throw;
    }

    if (query == query_type::back) {
      if (index_in_bucket + 1 == BLOCK_SIZE) {
        checkAndAllocate(num_of_bucket + 1);
      }
      ++ind;
    } else {
      --ind;
    }
  }

  void deleteByIndex(iterator& ind) {
    if constexpr (!std::is_trivially_destructible_v<T>) {
      ind->~T();
    }
  }

 public:

  void push_back(const T& value) {
    bool was_realloc = false;
    Deque old_deque;
    if (num_of_buckets == 0 ||
        getOffset(finish) - 1 ==
            static_cast<long long>(num_of_buckets) * (BLOCK_SIZE - 1)) {
      realloc(old_deque, true);
      was_realloc = true;
    }
    try {
      addByIndex(finish, value, query_type::back);
      if (was_realloc) {
        if (old_deque.buckets != nullptr) {
          delete[] old_deque.buckets;
          old_deque.buckets = nullptr;
        }
      }
    } catch (...) {
      if (was_realloc) {
        rollbackRealloc(old_deque);
      }
      old_deque.buckets = nullptr;
      throw;
    }
  }

  void push_front(const T& value) {
    bool was_realloc = false;
    Deque old_deque;
    if (num_of_buckets == 0 || getOffset(start) == 0) {
      realloc(old_deque, true);
      was_realloc = true;
    }
    try {
      addByIndex(start, value, query_type::front);
      if (was_realloc) {
        if (old_deque.buckets != nullptr) {
          delete[] old_deque.buckets;
          old_deque.buckets = nullptr;
        }
      }
    } catch (...) {
      if (was_realloc) {
        rollbackRealloc(old_deque);
      }
      old_deque.buckets = nullptr;
      throw;
    }
  }

  void pop_back() {
    --finish;
    deleteByIndex(finish);
  }

  void pop_front() {
    deleteByIndex(start);
    ++start;
  }

  iterator begin() { return start; }

  iterator end() { return finish; }

  const_iterator begin() const { return start; }

  const_iterator end() const { return finish; }

  const_iterator cbegin() const { return start; }

  const_iterator cend() const { return finish; }

  reverse_iterator rbegin() { return std::reverse_iterator(end()); }

  reverse_iterator rend() { return std::reverse_iterator(begin()); }

  const_reverse_iterator crbegin() const { return finish - 1; }

  const_reverse_iterator crend() const { return start - 1; }

  void insert(const iterator& iter, const T& value) {
    auto [num_of_bucket_iter, index_in_bucket_iter] = getNumberAndIndex(iter);
    bool was_realloc = false;
    Deque old_deq;
    if (num_of_buckets == 0 ||
        getOffset(finish) - 1 ==
            static_cast<long long>(num_of_buckets) * (BLOCK_SIZE - 1)) {
      realloc(old_deq, false);
      was_realloc = true;
    }

    auto [num_of_bucket_finish, index_in_bucket_finish] =
        getNumberAndIndex(finish);

    iterator new_iter;

    if (was_realloc) {
      new_iter = iterator(buckets + num_of_bucket_iter + current_offset,
                          *(buckets + num_of_bucket_iter + current_offset) +
                          index_in_bucket_iter);
    } else {
      new_iter = iter;
    }

    for (iterator it = finish; it != new_iter; --it) {
      *it = *(it - 1);
    }

    if (index_in_bucket_finish == BLOCK_SIZE - 1) {
      checkAndAllocate(num_of_bucket_finish + 1);
    }

    ++finish;
    *new_iter = value;
  }

  void erase(const iterator& iter) {
    for (iterator it = iter; it != finish - 1; ++it) {
      *it = *(it + 1);
    }
    --finish;
  }
};
