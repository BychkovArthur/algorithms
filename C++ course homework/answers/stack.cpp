#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string.h"
#include "biginteger.h"

const int kMax = 1e8;

int cur_size = 0;
long long cap = 0;

char** mystack;

void my_exit() {
  printf("bye");
  exit(0);
}

void size() {
  printf("%d\n", cur_size);
}

void push(char* str) {
  if (cap > cur_size) {
    mystack[cur_size++] = str;
    printf("ok\n");
    return;
  }
  cap = (cap * 2) + 1;
  mystack = static_cast<char **>(realloc(mystack, cap * sizeof(char *)));
  mystack[cur_size++] = str;
  printf("ok\n");
}

void pop() {
  if (cur_size == 0) {
    printf("error\n");
    return;
  }
  printf("%s\n", mystack[cur_size - 1]);
  cur_size--;
  if (cur_size < cap / 2) {
    cap /= 2;
    mystack = static_cast<char **>(realloc(mystack, cap * sizeof(char *)));
  }
}

void back() {
  if (cur_size == 0) {
    printf("error\n");
    return;
  }
  printf("%s\n", mystack[cur_size - 1]);
}

void clear() {
  //for (int i = cap - 1; i >= 0; i--) {
  //  delete mystack[i];
  //}
  mystack = static_cast<char **>(realloc(mystack, 0));
  cap = 0;
  cur_size = 0;
  printf("ok\n");
}

char* read_string(void) {
  size_t size = 1, len = 0;
  char* str = nullptr;
  char ch;
  std::cin.get(ch);

  while (std::isspace(ch) && !std::cin.eof())
    std::cin.get(ch);
  while (!std::isspace(ch) && !std::cin.eof()) {
    if (len + 1 >= size) {
      size = size * 2 + 1;
      str = static_cast<char *>(realloc(str, sizeof(char) * size));
    }
    str[len++] = ch;
    if (std::cin.eof()) {
      str[len] = '\0';
      return str;
    }
    std::cin.get(ch);
  }
  if (str != NULL) {
    str[len] = '\0';
  }
  return str;
}

int main(void) {
  BigInteger bb(-1237812);
  BigInteger bb1(-123);
  cout << bb - bb1;
  //cout << bb[5];
  //char* query,* instr;
  //String mys("baasdasdasdas");
  //std::cout << mys.substr(9, 1234);
  //while (true) {
  //  query = read_string();
  //  if (strcmp(query, "exit") == 0) {
  //    my_exit();
  //  } else if (strcmp(query, "push") == 0) {
  //    instr = read_string();
  //    push(instr);
  //  } else if (strcmp(query, "pop") == 0) {
  //    pop();
  //  } else if (strcmp(query, "back") == 0) {
  //    back();
  //  } else if (strcmp(query, "size") == 0) {
  //    size();
  //  } else if (strcmp(query, "clear") == 0) {
  //    clear();
  //  }
  //}
}