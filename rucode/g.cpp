#include <iostream>

using namespace std;

int main(){
    int x;
    for (int i = 0; i < 297; ++i){
        cout<<"get" << endl;
        cin>>x;
        // if (x==-1){
        //     break;
        // }
    }

    cout << "put 3" << endl;
    cout<<"put 4" << endl;

    cout<<"get" << endl;
    cin>>x;

    if (x==3){
        cout<<"queue" << endl;
    }else{
        cout<<"stack" << endl;
    }
}