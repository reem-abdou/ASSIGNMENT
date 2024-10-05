#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;
int main()
{
    char st[1000];
    string ans="";
    cout << "Please, Enter your sentence:\n";
    cin.getline (st,1000, '.');
    string sent = st;
    sent+='.';
    bool first=false;
    int i=0;
    for (int i = 0 ; i < sent.size() ; i++){
        if(isalpha(sent[i]) && !first){
            ans+=toupper(sent[i]);
            first=true;
        }
        else if(sent[i]==' ' || sent[i]=='\n'){
            while(sent[i+1]==' ' || sent[i+1]=='\n'){
                i++;
            }
            if(!ans.empty() && (isalpha(sent[i+1])||isdigit(sent[i+1]))){
                ans+=' ';
            }
        }
        else{
            ans+=tolower(sent[i]);
        }
    }
    cout << ans;
    return 0;
}
