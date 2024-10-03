#include <iostream>
#include <vector>

using namespace std;
int main()
{
    vector <int> vec;
    int n;
    cin >> n;
    for(int i=2 ; i<n ; i++){
        vec.push_back(i);
    }
    for(int i=0 ; i<vec.size() ; i++){
        for(int j=i+1 ; j<vec.size() ; j++){
            if(vec[j]%vec[i]==0){
                vec.erase(vec.begin()+j);
            }
        }
    }
    for(int i : vec){
        cout << i << ' ';
    }
    return 0;
}
