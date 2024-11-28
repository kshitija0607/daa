#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

/*void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}*/

void merge(int a[], int beg, int mid, int end)    
{    
    int i, j, k;  
    int n1 = mid - beg + 1;    
    int n2 = end - mid;    
      
    int LeftArray[n1], RightArray[n2]; //temporary arrays  
       
    for (int i = 0; i < n1; i++)    
    LeftArray[i] = a[beg + i];    
    for (int j = 0; j < n2; j++)    
    RightArray[j] = a[mid + 1 + j];    
      
    i = 0;  
    j = 0;    
    k = beg;    
      
    while (i < n1 && j < n2)    
    {    
        if(LeftArray[i] <= RightArray[j])    
        {    
            a[k] = LeftArray[i];    
            i++;    
        }    
        else    
        {    
            a[k] = RightArray[j];    
            j++;    
        }    
        k++;    
    }    
    while (i<n1)    
    {    
        a[k] = LeftArray[i];    
        i++;    
        k++;    
    }    
      
    while (j<n2)    
    {    
        a[k] = RightArray[j];    
        j++;    
        k++;    
    }    
}    
  
void mergeSort(int a[], int beg, int end)  
{  
    if (beg < end)   
    {  
        int mid = (beg + end) / 2;  
        mergeSort(a, beg, mid);  
        mergeSort(a, mid + 1, end);  
        merge(a, beg, mid, end);  
    }  
} 

// Heapify function to maintain heap property
/*void heapify(int a[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && a[left] > a[largest]) {
        largest = left;
    }

    if (right < n && a[right] > a[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(&a[i], &a[largest]);
        heapify(a, n, largest);  // Corrected this line to ensure the correct array size is used
    }
}

// Heap sort function
void heap_sort(int a[], int n) {
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(a, n, i);
    }

    // One by one extract elements
    for (int i = n - 1; i >= 0; i--) {
        // Move current root to end
        swap(&a[0], &a[i]);

        // Call heapify on the reduced heap
        heapify(a, i, 0);  // Corrected to use the reduced size i
    }
}*/

void binary_search(int arr[], int n, int key) {
    int beg = 0;
    int end = n - 1;

    while (beg <= end) {
        int mid = (beg + end) / 2;

        if (arr[mid] == key) {
            printf("Element found at index: %d\n", mid);
            return;
        }

        if (arr[mid] < key) {
            beg = mid + 1;
        } else {
            end = mid - 1;
        }
    }

    printf("Element not found in the array.\n");
}

int main() {
    int arr[500];
    int n = 500;
    int num;

    system("cls");

    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;  
    }


    printf("Unsorted Array:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

     mergeSort(arr, 0, n - 1); 
    //heap_sort(arr, n);

    printf("Sorted Array:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("Enter the number you want to search: ");
    scanf("%d", &num);

    binary_search(arr, n, num);

    return 0;
}
