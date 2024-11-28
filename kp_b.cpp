#include <iostream>
#include <vector>
using namespace std;

// Function to calculate the maximum value using backtracking
void knapsackBacktrack(int W, vector<int>& weights, vector<int>& values, 
                       int index, int currentWeight, int currentValue, int& maxValue) {
    // Base case: If we have processed all items
    if (index == weights.size()) {
        maxValue = max(maxValue, currentValue);
        return;
    }

    // Exclude the current item and move to the next
    knapsackBacktrack(W, weights, values, index + 1, currentWeight, currentValue, maxValue);

    // Include the current item only if it doesn't exceed capacity
    if (currentWeight + weights[index] <= W) {
        knapsackBacktrack(W, weights, values, index + 1, 
                          currentWeight + weights[index], 
                          currentValue + values[index], 
                          maxValue);
    }
}

int main() {
    // Input: weights and values of items, and knapsack capacity
    int n; // Number of items
    cout << "Enter number of items: ";
    cin >> n;

    vector<int> weights(n), values(n);
    cout << "Enter weights of items: ";
    for (int i = 0; i < n; i++) cin >> weights[i];

    cout << "Enter values of items: ";
    for (int i = 0; i < n; i++) cin >> values[i];

    int W; // Knapsack capacity
    cout << "Enter knapsack capacity: ";
    cin >> W;

    // Initialize the maximum value to 0
    int maxValue = 0;

    // Start backtracking
    knapsackBacktrack(W, weights, values, 0, 0, 0, maxValue);

    // Output the result
    cout << "Maximum value in the knapsack: " << maxValue << endl;

    return 0;
}
