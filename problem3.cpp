#include <iostream>
#include <vector>

using namespace std;

struct dominoT {
   int leftDots;
   int rightDots;
};
bool FormsDominoChain(vector<dominoT> & dominos){
    bool Done = true;
    int i,j;
    for(int k = dominos.size()-1 ; k>0 ; k--){
        if(dominos[k].leftDots != dominos[k-1].rightDots){
            i=k;
            j=k-1;
            Done = false;
            break;
        }
    }
    if(!Done){
        for(int k = j ; k>=0 ; k--){
            if(dominos[k].rightDots == dominos[i].leftDots){
                dominoT temp = dominos[j];
                dominos[j] = dominos[k];
                dominos[k] = temp;
                return FormsDominoChain(dominos);
                break;
            }
            else if(dominos[k].leftDots == dominos[dominos.size()-1].rightDots){
                dominos.push_back(dominos[k]);
                dominos.erase(dominos.begin()+k);
                return FormsDominoChain(dominos);
                break;
            }
        }
        
    }
    return Done;
}

int main()
{
    int num, x, y;
    cout << "Enter number of dominos in the chain: \n";
    cin >> num;
    dominoT domin;
    vector <dominoT> dominos;
    cout << "Enter your dominos chain\n" << "please, seperate between right dots and left dots with a space\n";
    for(int i = 0 ; i < num ; i++){
        cout << "Dominos " << i+1 << " : ";
        cin >> x >> y;
        domin.leftDots=x;
        domin.rightDots=y;
        dominos.push_back(domin);
    }
    bool ans = FormsDominoChain(dominos);
    if(ans){
        for(int i = 0 ; i < num ; i++){
           cout << dominos[i].leftDots << '|' << dominos[i].rightDots << ' ';
        }
    }
    else {
        cout << "Sorry, there is no way to form a domino chain";
    }
    return 0;
}
