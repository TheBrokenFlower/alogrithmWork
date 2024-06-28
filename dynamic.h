//
// Created by 13154179008 on 2024/6/27.
//

#ifndef DYNAMIC_H
#define DYNAMIC_H
#include <bits/stdc++.h>
#include "turing.h"
int bag, w[MAXN], v[MAXN];
int dp[MAXN];
using namespace std;

void loadInitialTape() {
    turing.cnt = 0;
    turing.pos = 0;

    for (int i = 1; i <= n; i++) {
        turing.arr[turing.cnt++] = tuElement(1, w[i], "");
        turing.arr[turing.cnt++] = tuElement(1, v[i], "");
    }
    turing.arr[turing.cnt++] = tuElement (0, 0, "$");
    turing.arr[turing.cnt++] = tuElement(1, n, "");
    turing.arr[turing.cnt++] = tuElement(1, bag, "");
    turing.arr[turing.cnt++] = tuElement (0, 0, "$");
    for (int i = 0; i <= bag; i++) {
        turing.arr[turing.cnt++] = tuElement(1, dp[i], "");
    }
    turing.arr[turing.cnt++] = tuElement (0, 0, "$");
}

void knapsack() {
    for (int i = 1; i <= n; i++) {
        turing.pos = (i - 1) * 2; // 指向当前物品的重量
        turing.printTape("ReadWeight");
        turing.pos = (i - 1) * 2 + 1; // 指向当前物品的重量
        turing.printTape("ReadValue");

        for (int j = bag; j >= w[i]; j--) {
            int newValue = dp[j - w[i]] + v[i];
            turing.pos = n * 2 + 4 + j; // 移动读写头到 dp 数组的位置
            turing.printTape("Cmp");
            if (newValue > dp[j]) {
                dp[j] = newValue;
                turing.arr[n * 2 + 4+ j] = tuElement(1, dp[j], ""); // 更新纸带上的 dp 数组
                turing.pos = n * 2 + 4 + j; // 移动读写头到 dp 数组的位置
                turing.printTape("Write data");
            }
        }
    }
}

int dp_all() {
    cout<<"Please input n and bag : ";
    cin >> n >> bag;
    cout<<"Please input weight and value : ";
    for (int i = 1; i <= n; i++) {
        cin >> w[i] >> v[i];
    }

    for (int i = 0; i <= bag; i++) {
        dp[i] = 0;
    }
    turing.moveTot = 0;
    loadInitialTape();
    turing.printTape("Initial tape");
    knapsack();
    // Print the final maximum value
    turing.pos = n * 2 + 4 + bag;
    turing.printTape("Final tape");
    cout << "Max of value ：  " << dp[bag] << endl;
    return 0;
}


#endif //DYNAMIC_H
