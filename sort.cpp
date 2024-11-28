#include<bits/stdc++.h>
#include<chrono>
using namespace std;
using namespace std::chrono;

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b =temp;
}

int partition(int a[], int beg , int end){
    int pivot = a[end];
    int i = beg - 1;
    
    for(int j = beg ;j <= end - 1; j++){
        if(a[j] < pivot){
            i++;
            swap(&a[i],&a[j]);
        }
    }
    swap(&a[i+1],&a[end]);
    return i+1;

}

void quick_sort(int a[], int beg , int end){
    if(beg < end){

    int piv = partition(a, beg, end);
    quick_sort(a, beg , piv-1);
    quick_sort(a, piv + 1, end);
    }
}

void print_arr(int a[],int n){
    for(int i = 0; i < n; i++){
        cout << a[i] << " ";
    }
}
int main(){
    int n;
    cout << "Enter the number of elements :  ";
    cin >> n;

    int *arr = new int[n]; 

    cout << "Elements : ";
    for(int i = 0; i < n; i++){
        arr[i] = rand() % 10000;
    }
    print_arr(arr, n);

    auto start = steady_clock::now();;
    quick_sort(arr, 0, n-1);
    auto stop = steady_clock::now();

    cout << "\nSorted Array : ";
    print_arr(arr, n);
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
    cout << " Duration: " << duration.count() << " nanoseconds";
    return 0;
}