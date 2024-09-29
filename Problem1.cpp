#include <iostream>
#include <cstring>

using namespace std;
int main()
{
    string sent;
    string ans;
    getline(cin,sent);
    bool first=false;
    for(int i = 0; i<sent.size(); i++){
        if(isalpha(sent[i]) && first==false){
            ans+=toupper(sent[i]);
            first=true;
        }
        else if(sent[i]==' '){
            if(!ans.empty()){
                ans+=' ';
            }
            while(sent[i+1]==' '){
                i++;
                continue;
            }
        }
        
        else{
            ans+=tolower(sent[i]);
        }
    }
    cout << ans;
    return 0;
}
