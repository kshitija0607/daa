#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int N; // Number of cities

// Helper function for brute force TSP
int calculateTourCost(const vector<int>& path, const vector<vector<int>>& dist) {
    int cost = 0;
    for (int i = 0; i < N - 1; i++) {
        cost += dist[path[i]][path[i + 1]];
    }
    cost += dist[path[N - 1]][path[0]]; // Return to the starting city
    return cost;
}

// Brute Force Approach
int tspBruteForce(const vector<vector<int>>& dist) {
    vector<int> cities(N);
    for (int i = 0; i < N; i++) cities[i] = i;

    int minCost = INT_MAX;

    // Generate all permutations of cities
    do {
        int currentCost = calculateTourCost(cities, dist);
        minCost = min(minCost, currentCost);
    } while (next_permutation(cities.begin() + 1, cities.end()));

    return minCost;
}

// Dynamic Programming (Held-Karp) Approach
int tspDynamicProgrammingHelper(int pos, int mask, const vector<vector<int>>& dist, vector<vector<int>>& dp) {
    if (mask == (1 << N) - 1) return dist[pos][0]; // Return to starting city if all cities visited
    if (dp[pos][mask] != -1) return dp[pos][mask];

    int minCost = INT_MAX;
    for (int city = 0; city < N; city++) {
        if ((mask & (1 << city)) == 0) { // If city has not been visited
            int newCost = dist[pos][city] + tspDynamicProgrammingHelper(city, mask | (1 << city), dist, dp);
            minCost = min(minCost, newCost);
        }
    }

    return dp[pos][mask] = minCost;
}

int tspDynamicProgramming(const vector<vector<int>>& dist) {
    vector<vector<int>> dp(N, vector<int>(1 << N, -1));
    return tspDynamicProgrammingHelper(0, 1, dist, dp); // Start from city 0, with only city 0 visited
}

// Function to calculate the lower bound (cost) of the path being explored
int calculateLowerBound(vector<vector<int>>& dist, vector<bool>& visited, int currentCost) {
    int minCost = currentCost;

    // Add minimum outgoing edges for unvisited cities
    for (int i = 0; i < N; i++) {
        if (!visited[i]) {
            int nearest = INT_MAX;
            for (int j = 0; j < N; j++) {
                if (i != j) {
                    nearest = min(nearest, dist[i][j]);
                }
            }
            minCost += nearest;
        }
    }

    return minCost;
}

// Branch and Bound TSP solver function
void tspBranchAndBound(vector<vector<int>>& dist, vector<bool>& visited, int currentCity, int visitedCount, int currentCost, int& minCost) {
    // Base case: If all cities are visited, check the final cost
    if (visitedCount == N && dist[currentCity][0] != 0) {
        minCost = min(minCost, currentCost + dist[currentCity][0]); // Return to starting city
        return;
    }

    // Explore unvisited cities from the current city
    for (int nextCity = 0; nextCity < N; nextCity++) {
        if (!visited[nextCity] && dist[currentCity][nextCity] != 0) {
            int newCost = currentCost + dist[currentCity][nextCity];
            visited[nextCity] = true;

            // Calculate lower bound for the new path
            int bound = calculateLowerBound(dist, visited, newCost);

            // If the lower bound is smaller than the current minCost, continue exploring
            if (bound < minCost) {
                tspBranchAndBound(dist, visited, nextCity, visitedCount + 1, newCost, minCost);
            }

            visited[nextCity] = false; // Backtrack
        }
    }
}

int tspBranchAndBoundMain(vector<vector<int>>& dist) {
    vector<bool> visited(N, false);
    visited[0] = true; // Start from city 0
    int minCost = INT_MAX;
    tspBranchAndBound(dist, visited, 0, 1, 0, minCost);
    return minCost;
}

// Main Function with Switch-Case for various algorithms
int main() {
    // Input the number of cities
    cout << "Enter the number of cities: ";
    cin >> N;

    vector<vector<int>> dist(N, vector<int>(N)); // Distance matrix

    // Input the distance matrix
    cout << "Enter the distance matrix (NxN):\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> dist[i][j];
        }
    }

    int choice;
    cout << "\nChoose the algorithm to solve TSP:\n";
    cout << "1. Brute Force\n";
    cout << "2. Dynamic Programming (Held-Karp)\n";
    cout << "3. Branch and Bound\n";
    cout << "Enter your choice: ";
    cin >> choice;

    int minCost = 0;

    switch (choice) {
        case 1:
            minCost = tspBruteForce(dist);
            cout << "Minimum cost (Brute Force): " << minCost << endl;
            break;
        case 2:
            minCost = tspDynamicProgramming(dist);
            cout << "Minimum cost (Dynamic Programming): " << minCost << endl;
            break;
        case 3:
            minCost = tspBranchAndBoundMain(dist);
            cout << "Minimum cost (Branch and Bound): " << minCost << endl;
            break;
        default:
            cout << "Invalid choice! Please choose 1, 2, or 3." << endl;
            break;
    }

    return 0;
}
