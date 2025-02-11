#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

int main(){
    int n, k;
    cin>>n>>k;
    set<int> ab;
    set<int> cd;
    set<int> ef;

    for (int i=0;i<n;i++){
        int x;
        cin>>x;
        ab.insert(x);
    }

    for (int i=0;i<n;i++){
        int x;
        cin>>x;
        cd.insert(x);
    }

    for (int i=0;i<n;i++){
        int x;
        cin>>x;
        ef.insert(x);
    }

    set<int> ans;

    for (int a: ab){
        bool b = find(cd.begin(), cd.end(), a)!=cd.end() && find(ef.begin(), ef.end(), a)!=ef.end();
        if (b){
            ans.insert(a);
        }
    }

    cout<<ans.size()<<"\n";

}