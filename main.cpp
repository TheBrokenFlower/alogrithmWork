#include <bits/stdc++.h>
const int MAXN = 2e3 + 5;
const int INF = 0x7fffffff;
int n, arr[MAXN];
#define LL long long
#define mod %
#include "turing.h"
bool vis[MAXN][MAXN];
int weight[MAXN], val[MAXN], f[MAXN][MAXN];
int goodNum, capacity;
#include "functionStack.h"
std::map <int, int> discrete;

using namespace std;

inline int find (int l, int r, int x) {
    int mid = (l + r) >> 1;
    if (arr[mid] == x) {
        return mid;
    } else if (arr[mid] < x) {
        return find (l, mid - 1, x);
    } else {
        return find (mid + 1, r, x);
    }
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    sort (arr + 1, arr + n + 1);
    for (int i = 1; i <= n; i++)
        cout << arr[i] << endl;
    for (int i = 1; i <= n; i++) {
        turing.arr[i].type = 1;
        turing.arr[i].num = arr[i];
    }
    turing.arr[n + 1] = tuElement (0, 0, "$");
    turing.arr[n + 2] = tuElement (1, 1, "");
    turing.arr[n + 3] = tuElement (1, n, "");
    turing.arr[n + 4] = tuElement (0, 0, "$");
    TuringMachine Origin = turing;
    turing.cnt = n + 4;
    turing.print ();

    funcStack OriginStack = FuncStack;
    while (true) {
        cout << "_______________________________________\n";
        cout << "|                                     |\n";
        cout << "|  1.Turing Machine Binary Search     |\n";
        cout << "|                                     |\n";
        cout << "|  2.Recursive System Binary Search   |\n";
        cout << "|                                     |\n";
        cout << "|  3.Recursive System 01 bag DP       |\n";
        cout << "|                                     |\n";
        cout << "---------------------------------------\n";
        int x;
        cin >> x;
        if (x == 1) {
            cout << "Turing Machine" << endl;
            turing = Origin;
            int findX;
            cin >> findX;
            if (findX == -1)
                break;
            turing.cnt = n + 5;
            turing.arr[n + 5] = tuElement (1, findX, "");
            turing.print ();
            int findPos = turing.binSearch (findX);
            if (findPos == -1) {
                cout << "not found" << endl;
            } else {
                cout << "findPos = " << findPos << endl;
            }
            cout << "movTot = " << turing.moveTot << endl;
        } else if (x == 2) {
            cout << "Recursive System" << endl;
            int findX;
            cin >> findX;
            if (findX == -1)
                break;
            FuncStack = OriginStack;
            int findPos = FuncStack.executeBin (1, n, findX);
            if (findPos == -1) {
                cout << "not found!" << endl;
            } else {
                cout << "findPos = " << findPos << endl;
            }
        } else if (x == 3) {
            cout << "Recursive System 01 bag DP" << endl;
            cin >> goodNum >> capacity;
            for (int i = 1; i <= goodNum; i++) {
                cin >> weight[i] >> val[i];
            }
            FuncStack = OriginStack;
        } else {
            break;
        }
    }
    return 0;
}
