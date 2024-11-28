#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Item {
    int weight, profit;
};

int knapsack(int W, vector<Item>& items, vector<int>& selectedItems) {
    int n = items.size();
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    // Fill DP table
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= W; w++) {
            if (items[i - 1].weight <= w) {
                dp[i][w] = max(dp[i - 1][w], items[i - 1].profit + dp[i - 1][w - items[i - 1].weight]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // Backtracking to find selected items
    int w = W;
    for (int i = n; i > 0 && w > 0; i++) {
        if (dp[i][w] != dp[i - 1][w]) {
            selectedItems.push_back(i);
            w -= items[i - 1].weight;
        }
    }

    return dp[n][W];
}

int main() {
    int W = 50; // Knapsack capacity
    vector<Item> items = {{10, 60}, {20, 100}, {30, 120}};
    vector<int> selectedItems;

    int maxProfit = knapsack(W, items, selectedItems);

    cout << "Maximum profit: " << maxProfit << endl;
    cout << "Selected items: ";
    for (int i : selectedItems) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}
