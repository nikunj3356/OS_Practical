#include <bits/stdc++.h>
using namespace std;
#define V 4

int findMinWeight(int weights[], bool visited[])
{
    int minWeight = INT_MAX, minIndex;
    for (int vertex = 0; vertex < V; vertex++)
        if (visited[vertex] == false && weights[vertex] < minWeight)
            minWeight = weights[vertex], minIndex = vertex;
    return minIndex;
}

void printMSTEdges(int parents[], int graph[V][V])
{
    cout << "MST Edges:\n";
    for (int i = 1; i < V; i++)
        cout << parents[i] << " - " << i << " : "
             << graph[i][parents[i]] << "\n";
}

void calculateMST(int graph[V][V])
{
    int parents[V];
    int weights[V];
    bool visited[V];
    for (int i = 0; i < V; i++)
        weights[i] = INT_MAX, visited[i] = false;
    weights[0] = 0;
    parents[0] = -1;
    for (int count = 0; count < V - 1; count++)
    {
        int u = findMinWeight(weights, visited);
        visited[u] = true;
        for (int v = 0; v < V; v++)
            if (graph[u][v] && visited[v] == false
                && graph[u][v] < weights[v])
                parents[v] = u, weights[v] = graph[u][v];
    }
    printMSTEdges(parents, graph);
}

int main()
{
    int graph[V][V] = {{0, 4, 0, 8},
                       {4, 0, 6, 12},
                       {0, 6, 0, 0},
                       {8, 12, 0, 0}};
    calculateMST(graph);
    return 0;
}

