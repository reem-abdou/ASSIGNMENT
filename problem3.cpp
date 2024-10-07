#include <iostream>
#include <vector>
#include <deque>

using namespace std;

struct dominoT {
    int leftDots;
    int rightDots;
};

void order(vector<dominoT> &dominos, deque<dominoT> &answer) {
    int i = 0;
    while (i < dominos.size()) {
        if (dominos[i].rightDots == answer[0].leftDots) {
            answer.push_front(dominos[i]);
            dominos.erase(dominos.begin() + i);
            return order(dominos, answer);
        } else if (dominos[i].leftDots == answer[answer.size() - 1].rightDots) {
            answer.push_back(dominos[i]);
            dominos.erase(dominos.begin() + i);
            return order(dominos, answer);
        }
        i++;
    }
}

bool FormsDominoChain(deque<dominoT> &answer) {
    bool Done = true;
    for (int k = 0; k < answer.size() - 1; k++) {
        if (answer[k].rightDots != answer[k + 1].leftDots) {
            Done = false;
            break;
        }
    }
    return Done;
}

int main() {
    int num, x, y;
    cout << "Enter number of dominos in the chain: \n";
    cin >> num;
    dominoT domin;
    vector<dominoT> dominos;
    deque<dominoT> answer;
    cout << "Enter your dominos chain\n" << "please, seperate between right dots and left dots with a space\n";
    int i = 0;
    while (i < num) {
        cout << "Dominos " << i + 1 << ":";
        cin >> x >> y;
        domin.leftDots = x;
        domin.rightDots = y;
        if (x == y || i == 0) {
            answer.push_back(domin);
        } else {
            dominos.push_back(domin);
        }
        i++;
    }
    order(dominos, answer);
    bool ans;
    ans = FormsDominoChain(answer);
    if (ans && answer.size() == num) {
        for (int i = 0; i < num; i++) {
            cout << answer[i].leftDots << '|' << answer[i].rightDots;
            if (i != num - 1) {
                cout << " - ";
            }
        }
    } else {
        cout << "Sorry, there is no way to form a domino chain";
    }
    return 0;
}
