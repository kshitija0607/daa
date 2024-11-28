#include <iostream>
#include<chrono>
using namespace std;

// Conquer function to merge two sorted subarrays
void conquer(int arr[], int beg, int mid, int end) {
    int merged[end - beg + 1];
    int idx1 = beg;        // Pointer for the first half
    int idx2 = mid + 1;    // Pointer for the second half
    int x = 0;             // Pointer for the merged array

    while (idx1 <= mid && idx2 <= end) {
        if (arr[idx1] <= arr[idx2]) {
            merged[x++] = arr[idx1++];
        } else {
            merged[x++] = arr[idx2++];
        }
    }

    while (idx1 <= mid) {
        merged[x++] = arr[idx1++];
    }

    while (idx2 <= end) {
        merged[x++] = arr[idx2++];
    }

    for (int i = 0; i < x; i++) {
        arr[beg + i] = merged[i];
    }
}

// Divide function to recursively split the array
void divide(int arr[], int beg, int end) {
    if (beg >= end) {
        return; // Base case: single element is already sorted
    }

    int mid = beg + (end - beg) / 2;

    divide(arr, beg, mid);       // Recursively sort the first half
    divide(arr, mid + 1, end);   // Recursively sort the second half
    conquer(arr, beg, mid, end); // Merge the sorted halves
}

// Function to print the array
void print_arr(int a[], int n) {
    for (int i = 0; i < n; i++) {
        cout << a[i] << "\t";
    }
    cout << endl;
}

// Main function
int main() {
    int n;
    cout << "Enter the size of the array: ";
    cin >> n;

    if (n <= 0) {
        cout << "Invalid array size." << endl;
        return 1;
    }

    int *a = new int[n]; // Dynamically allocate memory for the array

    cout << "\nEnter the elements: ";
    for (int i = 0; i < n; i++) {
       a[i] = rand() % 10000;
    }

    auto start = chrono::steady_clock::now();
    divide(a, 0, n - 1); // Perform merge sort
    auto stop = chrono::steady_clock::now();

    cout << "\nSorted Array: ";
    print_arr(a, n);

    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
    cout << "Duration : " << duration.count() << "nanoseconds";
    delete[] a; // Free the dynamically allocated memory
    return 0;
}
