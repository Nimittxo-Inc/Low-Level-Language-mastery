#include "head/dsa.h"

void BFS(int start) {
    printf("%d ", start);  // Print the first vertex
    int visited[n];         // Array to track visited nodes
    for (int i = 0; i < n; ++i) visited[i] = 0;  // Initialize all nodes as unvisited
    
    visited[start] = 1;  // Mark the start node as visited
    enqueue(q, start);   // Insert the start vertex in the Queue

    while (!IsEmpty(q)) {
        int explore = dequeue(q);  // Get the front of the queue

        // Explore all adjacent vertices of the current vertex
        for (int v = 0; v < n; ++v) {
            if (A[explore][v] == 1 && visited[v] == 0) {
                printf("%d ", v);   // Print the vertex
                visited[v] = 1;      // Mark it as visited
                enqueue(q, v);       // Add it to the queue
            }
        }
    }    
}
