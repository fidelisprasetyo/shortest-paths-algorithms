#pragma once
#include <iostream>
#include <vector>
#include <iomanip>

#define INF 999999

typedef std::vector<std::vector<int>> graph;

// print the distance matrix
void printMatrix(const graph& m) {
	int size = m.size();
	std::cout << "FLOYD-WARSHALL ALGORITHM result (D" << size << "):\n";
    for(int row = 0; row < size; row++) {
        for(int col = 0; col < size; col++) {
			std::cout << std::setw(5);
			if(m[row][col] == INF) {
				std::cout << "INF";
				continue;
			}
            std::cout << m[row][col];
        }
        std::cout << '\n';
    }
}

// print the distances
void printDistance(const graph& m) {
	int vertices = m.size();
	std::cout << "Shortest distances:";
	for(int v = 0; v < vertices; v++) {
		std::cout << "\n> Starting vertex = " << v << '\n';
		std::cout << "  Dest: ";
    	for(int i = 0; i < vertices; i++) {
        	std::cout << std::setw(5) << i;
    	}
		std::cout << '\n' << "  Dist: ";
		for(int u = 0; u < vertices; u++) {
			std::cout << std::setw(5) << m[v][u];
		}
	}
	std::cout << "\n\n";
}

// Find all pairs shortest paths
// g = General weight graph adjacency matrix
void floydWarshall(const graph& g, bool print = false) {
	int vertices = g.size();
	// Distance matrix, stores the shortest paths
	graph d(vertices, std::vector<int>(vertices, 0));

	// Base case (D0) = adjacency matrix
	for(int row = 0; row < vertices; row++) {
		for(int col = 0; col < vertices; col++) {
			d[row][col] = g[row][col];
		}
	}

	// Recurrence (Dk):
	for(int k = 0; k < vertices; k++) {
		for(int u = 0; u < vertices; u++) {
			for(int v = 0; v < vertices; v++) {
				if(d[u][k] + d[k][v] < d[u][v]) {
					d[u][v] = d[u][k] + d[k][v];
				}
			}
		}
	}
	if (print) {
		printMatrix(d);
		printDistance(d);
	}
}