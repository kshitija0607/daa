#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to store items with weight, value, and value-to-weight ratio
struct Item {
    int weight, value;
    double ratio;
};

// Structure to represent a node in the branch and bound tree
struct Node {
    int level, profit, weight;
    double bound;
};

// Comparator for sorting items based on value-to-weight ratio
bool compare(Item a, Item b) {
    return a.ratio > b.ratio;
}

// Function to calculate the upper bound of profit for a node
double calculateBound(Node u, int n, int W, vector<Item>& items) {
   if(u.weight >= W)
    return 0;

    double bound = u.profit;
    int totalweight = u.weight;
    int j = u.level + 1;

    while(j < n && totalweight + items[j].weight <= W){
        totalweight += items[j].weight;
        bound += items[j].value;
        j++;
    }

    if(j < n){
        bound += (W - totalweight) * items[j].ratio;
    }

    return bound;
}

// Function to solve the knapsack problem using branch and bound
int knapsackBranchAndBound(int W, vector<Item>& items) {
    //sorting 
    sort(items.begin(), items.end(), compare);

    //queue and node define
    queue<Node> q;
    Node u, v;

    //initial node in decision tree
    u.level = -1;
    u.profit = 0;
    u.weight = 0;
    u.bound = calculateBound(u,items.size(),W,items);

    //push in queue
    q.push(u);

    int maxprofit = 0;

    while(!q.empty()){
        u = q.front();
        q.pop();

    //next nodes
        if(u.level == -1 || u.bound > maxprofit){
            v.level = u.level + 1;

        //Include item
            v.weight = u.weight + items[v.level].weight;
            v.profit = u.weight + items[v.level].value;
            v.bound = calculateBound(v,items.size(),W,items);
        }

    //update maxprofit
        if(v.weight <= W && v.profit > maxprofit){
            maxprofit = v.profit;
        }

    // update bound 
        if(v.bound > maxprofit){
            q.push(v);
        }

    //exclude items
        v.weight = u.weight;
        v.profit = u.profit;
        v.bound = calculateBound(v,items.size(),W,items);

        if(v.bound > maxprofit){
            q.push(v);
        }
    }

    return maxprofit;
}

int main() {
    int W = 50; // Capacity of the knapsack
    vector<Item> items = {
        {10, 60, 0}, 
        {20, 100, 0}, 
        {30, 120, 0}
    };

    // Calculate value-to-weight ratio for each item
    for (auto& item : items) {
        item.ratio = (double)item.value / item.weight;
    }

    cout << "Maximum profit: " << knapsackBranchAndBound(W, items) << endl;

    return 0;
}
