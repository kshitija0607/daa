#include <iostream>
#include <vector>
#include <climits>
#include <string>
using namespace std;

const int INF = INT_MAX;

void printMatrix(int V , vector<vector<int>> M , vector<string> &cities){
    for (int i = 0; i < V; i++) {
        cout << cities[i] << "\t";
    }
    cout << endl;

    for (int i = 0; i < V; i++) {
        cout << cities[i] << "\t";
        for (int j = 0; j < V; j++) {
            if (M[i][j] == INF)
                cout << "INF\t";
            else
                cout << M[i][j] << "\t";
        }
        cout << endl;
    }
}

 void floyd(vector<vector<int>> &G , vector<string> &cities){
    int V = G.size();
    vector<vector<int>> dist(G);

    for(int k = 0; k < V; k++){
        for(int i = 0; i < V; i++){
            for(int j = 0; j < V; j++){

                if(dist[i][k] == INF || dist[k][j] == INF)
                  continue;
                dist[i][j] = min(dist[i][j] , dist[i][k] + dist[k][j]);
            }
        }
    }

cout << "\nShortest Path Matrix :\n";
printMatrix(V,dist,cities);
}
 
int main(){
    
    int V;
    cout << "Enter the number of cities : ";
    cin >> V ;

    vector<string> cities(V);
    cout << "\nEnter the names of the cities :\n";
    for(int i = 0; i < V; i++){
        cin >> cities[i];
    }

    vector<vector<int>> G(V,vector<int>(V,INF));
    for (int i = 0; i < V; i++) {
        G[i][i] = 0;
    }

    int E; // Number of edges (flight routes)
    cout << "\nEnter the number of flights (edges): ";
    cin >> E;

    cout << "\nEnter the flight details (source, destination, distance):\n";
    for (int i = 0; i < E; i++) {
        string source, destination;
        int distance;
        cin >> source >> destination >> distance;

        // Get the indices of the source and destination cities
        int srcIdx = -1, destIdx = -1;
        for (int j = 0; j < V; j++) {
            if (cities[j] == source) {
                srcIdx = j;
            }
            if (cities[j] == destination) {
                destIdx = j;
            }
        }

        if (srcIdx != -1 && destIdx != -1) {
            G[srcIdx][destIdx] = distance;
        }
    }
    
    cout << "\nAdjacency Matrix : ";
    printMatrix(V,G,cities);
    floyd(G, cities);
    return 0;

}