#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

int main() 
{
	
    int n, start, stop;
    bool path_exist = false;
    cin >> n;
    vector<vector<int>> a(n + 1, vector<int>(n + 1, 0));
    vector<int> path(n + 1, 0);
    vector<bool> visited(n + 1, false);    
    queue<int> q;
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> a[i + 1][j + 1];
        }
    }
    cin >> start >> stop;
    path_exist = start == stop;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        if (path_exist) break;
        int curr = q.front();
        q.pop();
        for (int i = 1; i <= n; ++i) {
            if (!visited[i] && a[curr][i]) {
                visited[i] = true;
                q.push(i);
                path[i] = curr;
                if (i == stop) {
                    path_exist = true;
                    break;
                }
            }
        }
    }

    if (!path_exist) cout << -1;
    else {
        vector<int> nodes;
        int curr = stop;
        nodes.push_back(stop);
        while (curr != start) {
            curr = path[curr];
            nodes.push_back(curr);
        }
        int n = nodes.size();
        cout << n - 1 << endl;
        for (int i = 0; i < n && n > 1; ++i) {
            cout << nodes[n - i - 1] << ' ';
        }
        
    }

    
	return 0;
}