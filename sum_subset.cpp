#include <iostream>
#include <vector>
using namespace std;

void printSubset(const vector<int>& subset) {
    cout << "{ ";
    for (int num : subset)
        cout << num << " ";
    cout << "}" << endl;
}

// Backtracking function 
void find_Subsets(vector<int>& arr, vector<int>& subset, int index, int sum, int total, bool &found) {

    if (sum == total) {
        printSubset(subset);
        found = true;
        return;
    }

    // If sum exceeds the total or we've considered all elements, return
    if (sum > total || index >= arr.size())
        return;

    // Include the current element in the subset and recurse
    subset.push_back(arr[index]);
    find_Subsets(arr, subset, index + 1, sum + arr[index], total, found);

    // Exclude the current element and recurse
    subset.pop_back();
    find_Subsets(arr, subset, index + 1, sum, total, found);
}

int main() {
    int n, total;

    cout << "Enter the size of the set: ";
    cin >> n;

    vector<int> arr(n);

    cout << "Enter the elements of the set: ";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    cout << "Enter the total sum: ";
    cin >> total;

    cout << "Subsets that sum to " << total << " are:" << endl;
    vector<int> subset;
    bool found = false;
    find_Subsets(arr, subset, 0, 0, total, found);

    if (!found)
        cout << "No solution found." << endl;

    return 0;
}
