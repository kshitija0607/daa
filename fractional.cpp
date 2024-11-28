#include<iostream>
#include<bits/stdc++.h>
using namespace std;

struct Item{
    int profit;
    int weight;
    float ratio;
};

void data(Item items[],int &n){
    cout << "Enter the number of items : ";
    cin >> n;

    for(int i = 0; i < n; i++){
        cout << "Enter the I" << i + 1 << " 's weight : ";
        cin >> items[i].weight;

        cout << "Enter the I" << i + 1 << " 's profit : ";
        cin >> items[i].profit;

        items[i].ratio = (float)items[i].profit/items[i].weight;
        cout << endl;
    }
}

void display(Item items[],int &n){

    cout << "Data : ";
    cout << "\nWeight : ";
    for(int i = 0;i < n;i++){
        cout << items[i].weight << "\t";
    }
    cout << "\nProfit : ";
    for(int i = 0;i < n;i++){
        cout << items[i].profit << "\t";
    }
    cout << endl;
}

bool compare(Item i1, Item i2){
    return(i1.ratio > i2.ratio);
}

float knapsack(Item items[],int n, int W){
    float totalWeight = 0;
    float totalProfit = 0;
    sort(items,items+n,compare);

    for(int i = 0;i < n;i++){
        if(totalWeight + items[i].weight <= W){
            totalProfit += items[i].profit;
            totalWeight += items[i].weight;
        }
        else{
            int wt = W - totalWeight;
            totalProfit += (wt * items[i].ratio);
            totalWeight += wt;
            break;
        }
    }

    cout << "Total Weight " << totalWeight << endl;
    return totalProfit;
}

int main(){
    int n , W;
    Item items[100];
    data(items,n);
    display(items,n);
    cout << "\nMax Weight : ";
    cin >> W;
    float totalProfit = knapsack(items,n,W);
    cout << totalProfit;
    return 0;

}