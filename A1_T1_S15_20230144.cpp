//Purpose: problem 1, problem 4, problem 7, problem 10.
//Author: Reem Abdou Mohamed
//Section: S15
//TA:
//Date: 8 oct 2024
// problem 1  -> Rewrite the sentence in the correct format (remove extra spaces, capitalize the first letter).
// problem 4  -> Remove all non-prime numbers from 0 to N and print the prime numbers.
// problem 7  -> It takes N dominos and check if it possible to build a chain consisting of every domino or not.
// problem 10 -> It changes words that could be censored with other alternatives.

#include <iostream>
#include <cctype>
#include <vector>
#include <deque>
#include <fstream>
#include <sstream>
#include <map>
#include <codecvt>

using namespace std;

struct dominoT {
    int leftDots;
    int rightDots;
};

void order(vector<dominoT> &dominos, deque<dominoT> &answer) {
    for (int i = 0; i < dominos.size(); i++) {
        if (dominos[i].rightDots == answer[0].leftDots && dominos[i].leftDots == answer[answer.size() - 1].rightDots &&
            i != dominos.size() - 1) {
            for (int j = i + 1; j < dominos.size(); j++) {
                if (dominos[j].rightDots == dominos[i].leftDots) {
                    answer.push_front(dominos[i]);
                    dominos.erase(dominos.begin() + i);
                    return order(dominos, answer);
                } else if (dominos[j].leftDots == dominos[i].rightDots) {
                    answer.push_back(dominos[i]);
                    dominos.erase(dominos.begin() + i);
                    return order(dominos, answer);
                }
            }
        } else if (dominos[i].rightDots == answer[0].leftDots) {
            answer.push_front(dominos[i]);
            dominos.erase(dominos.begin() + i);
            return order(dominos, answer);
        } else if (dominos[i].leftDots == answer[answer.size() - 1].rightDots) {
            answer.push_back(dominos[i]);
            dominos.erase(dominos.begin() + i);
            return order(dominos, answer);
        }
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


void check(wofstream &answer, map<wstring, wstring> mp, wstring txt) {
    wstring sent;
    bool F = true;
    for (auto x: mp) {
        if (txt == x.first) {
            answer << x.second;
            F = false;
        }
    }
    if (F) {
        answer << txt;
    }
}


void problem1() {
    char st[1000];
    string ans;
    cout << "Note: put a dot at the end of the sentence\n"
         << "Please, Enter your sentence:\n";
    cin.getline(st, 1000, '.');
    string sent = st;
    sent += '.';
    bool first = false;
    for (int i = 0; i < sent.size(); i++) {
        if (isalpha(sent[i]) && !first) {
            ans += toupper(sent[i]);
            first = true;
        } else if (sent[i] == ' ' || sent[i] == '\n') {
            while (sent[i + 1] == ' ' || sent[i + 1] == '\n') {
                i++;
            }
            if (!ans.empty() && (isalpha(sent[i + 1]) || isdigit(sent[i + 1]))) {
                ans += ' ';
            }
        } else {
            ans += tolower(sent[i]);
        }
    }
    cout << ans << '\n';
}


void problem4() {
    vector<int> vec;
    int n;
    cout << "Enter a number: \n";
    cin >> n;
    for (int i = 2; i < n; i++) {
        vec.push_back(i);
    }
    for (int i = 0; i < vec.size(); i++) {
        for (int j = i + 1; j < vec.size(); j++) {
            if (vec[j] % vec[i] == 0) {
                vec.erase(vec.begin() + j);
            }
        }
    }
    cout << "Prime numbers from 2 to " << n << " are:\n";
    for (int i: vec) {
        cout << i << ' ';
    }
    cout << '\n';
}

void problem7() {
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
    cout << '\n';
}


void problem10() {
    locale::global(locale(""));
    wifstream Ifile("Ifile.txt");
    wifstream words("words.txt");
    wofstream answer("answer.txt");

    Ifile.imbue(locale(Ifile.getloc(), new codecvt_utf8<wchar_t>));
    words.imbue(locale(words.getloc(), new codecvt_utf8<wchar_t>));
    answer.imbue(locale(answer.getloc(), new codecvt_utf8<wchar_t>));

    map<wstring, wstring> mp;
    wstring word, alt;
    while (!words.eof()) {
        getline(words, word, L',');
        getline(words, alt, L'\n');
        mp[word] = alt;
    }
    while (!Ifile.eof()) {
        wstring txt;
        Ifile >> txt;
        if (!txt.empty() && !iswalpha(txt[txt.size() - 1])) {
            wchar_t x;
            x = txt[txt.size() - 1];
            txt = txt.substr(0, txt.size() - 1);
            check(answer, mp, txt);
            answer << x;
        } else {
            check(answer, mp, txt);
        }
        wchar_t chr;
        Ifile.get(chr);
        answer << chr;
    }
    cout << "The message is alternated successfully\n";
}


int main() {
    while (true) {
        cout << "1)Problem 1  : sentences correction\n"
             << "2)problem 4  : Prime numbers\n"
             << "3)problem 7  : The game of dominos\n"
             << "4)problem 10 : Avoid Censorship\n"
             << "Choose: \n";
        char choice;
        cin >> choice;
        if (choice == '1') {
            problem1();
        } else if (choice == '2') {
            problem4();
        } else if (choice == '3') {
            problem7();
        } else if (choice == '4') {
            problem10();
        } else {
            cout << "Your choice is not valid, please try again\n";
        }
        char opt;
        cout << "a)Continue\n"
             << "b)exite\n";
        cin >> opt;
        if (opt == 'a') {
            continue;
        } else if (opt == 'b') {
            break;
        }
    }
    return 0;
}


