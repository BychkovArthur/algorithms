#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, t;
    cin >> n >> t;

    int pSum = 0;
    int nSum = 0;

    for (int i = 0; i < n; ++i) {
        char status;
        int value;
        cin >> status >> value;
        if (status == 'P') {
            pSum += value;
        } else {
            nSum += value;
        }
    }
    double pSpeed = (double) t / 4 * 3;
    double nSpeed = (double) t / 4;
    double answer;
    // приоритетные скачались быстрее
    if ((double)pSum / pSpeed < (double)nSum / nSpeed) {
        answer = (double)pSum / pSpeed;
        answer += ( (double)nSum - answer * nSpeed ) / (double) t;
    } else {
        answer = (double)nSum / nSpeed;
        answer += ( (double) pSum - answer * pSpeed ) / (double) t;
    }

    cout.precision(10);
    cout << answer << endl;



}