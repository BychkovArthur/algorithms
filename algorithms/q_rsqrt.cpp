#include <bits/stdc++.h>

using namespace std;


float q_sqrt(float x) {
    float xdiv2 = x * 0.5f;
    uint32_t i = *(uint32_t*)&x;
    i = 0x5f3759df - (i >> 1);
    x = *(float*)&i;
    x = x * (1.5f - xdiv2 * x * x);
    return x;
}


int main() {
    
}