#include <iostream>
//#include <bits/stdc++.h>
#include <map>
#include <set>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

const int maxt = 1e4;

map <int, int> nextState[maxt];
set <int> allState;
vector <int> allStates;
queue <int> stateQueue;
char T[maxt];

void initNFA(int& , int& );
void changeToDFA(int );
void printDFA(int );
int changeToInt(string );

int main(void) {
    int q, t;
    printf("********NFA-DFA转换系统********\n");
    initNFA(q, t);
    changeToDFA(t);
    printDFA(t);
    return 0;
}

void initNFA(int &q, int &t) {
    printf("请输入NFA状态总数q：");
    cin >> q;
    printf("共有%d个状态，状态表为：{", q);
    for (int i = 0; i < q; i ++) {
        if (i != q - 1) {
            cout << 'q' << i << ",";
        }
        else cout << 'q' << i << '}';
    }
    cout << endl;
    printf("请输入字母表字母总数：");
    cin >> t;
    printf("请输入字母表,字母之间用空格隔开：");
    for (int i = 0; i < t; i ++) {
        cin >> T[i];
    }
    getchar();
    printf("请输入NFA的转换函数，状态之间由空格隔开，空状态请输入NULL：\n");
    
    for (int i = 0; i < q; i ++) {
        int state = 1 << i;
        allState.insert(state);
        allStates.push_back(state);
    }
    for (int i = 0; i < q; i ++) {
        int thisstate = 1 << i;
        for (int j = 0; j < t; j ++) {
            int nextstate = 0;
            string strState;
            int states;
            char ch;
            printf("der(q%d,%c) = ", i, T[j]);
            while (1) {
                cin >> strState;
                states = changeToInt(strState);
                if (states < 0) break;
                nextstate = nextstate | (1 << states);
                ch = getchar();
                if (ch == '\n') break;
            }
            nextState[j][thisstate] = nextstate;
            if (nextstate && allState.find(nextstate) == allState.end()) {
                allState.insert(nextstate);
                stateQueue.push(nextstate);
                allStates.push_back(nextstate);
            }
        }
    }
}

void changeToDFA(int t) {
    while (!stateQueue.empty()) {
        for (int i = 0; i < t; i ++) {
            int thisState = stateQueue.front();
            int nextstate = 0;
            int j = 0;
            while(thisState) {
                if (thisState & 1) {
                    nextstate = nextstate | (nextState[i][(1 << j)]);
                }
                j ++;
                thisState >>= 1;
            }
            thisState = stateQueue.front();
            nextState[i][thisState] = nextstate;
            if (nextstate && allState.find(nextstate) == allState.end()) {
                allState.insert(nextstate);
                allStates.push_back(nextstate);
                stateQueue.push(nextstate);
            }
        }
        stateQueue.pop();
    }
}

void printDFA(int t) {
    printf("转换后的DFA转换函数：\n");
    for (int i = 0; i < allStates.size(); i ++) {
        for (int k = 0; k < t; k ++) {
            int thisstate = allStates[i];
            cout << "der(" ;
            cout << '[';
            int j = 0;
            int flag = 0;
            while (thisstate) {
                if (thisstate & 1) {
                    if (!flag) {
                        cout << 'q' << j;
                        flag = 1;
                    }
                    else {
                        cout << " q" << j;
                    }
                }
                thisstate >>= 1;
                j ++;
            }
            cout << "]," << T[k] << ") = ";
            thisstate = allStates[i];
            int nextstate = nextState[k][thisstate];
            cout << '[';
            if (nextstate) {
                int l = 0;
                flag = 0;
                while (nextstate) {
                    if (nextstate & 1) {
                        if (!flag) {
                            cout << 'q' << l;
                            flag = 1;
                        }
                        else {
                            cout << " q" << l;
                        }
                    }
                    nextstate >>= 1;
                    l ++;
                }
                cout << "] ";
            }
            else cout << "NULL]" << ' ' ;
            cout << endl;
        }
    }
}

int changeToInt(string str) {
    int len = int(str.length());
    if (str[0] == 'N') return -1;
    int res = 0;
    for (int i = 1; i < len; i ++) {
        res = res * 10 + int(str[i] - '0');
    }
    return res;
}
