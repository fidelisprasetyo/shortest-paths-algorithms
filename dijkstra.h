// Author: Fidelis Prasetyo (fprasetyo@cpp.edu)
// Desc: for Project 2, CS3310 Fall, Cal Poly Pomona 
// github: https://github.com/fidelisprasetyo
// github repo: https://github.com/fidelisprasetyo/shortest-paths-algorithms

#pragma once

#include <iostream>
#include <iomanip>
#include <vector>

#define INF 999999

typedef std::vector<std::vector<int>> graph;

// Get the index of the nearest, unvisited vertex
int nearestVertex(const std::vector<int>& d, const std::vector<bool>& isVisited) {
	int min = INF;
	int i;
	for(int v = 0; v < d.size(); v++) {
		if(!isVisited[v] && d[v] <= min) {
			min = d[v];
			i = v;
		}
	}
	return i;
}

// print the distances
void printVector(const std::vector<int>& d) {
    std::cout << "  Dest: ";
    for(int i = 0; i < d.size(); i++) {
        std::cout << std::setw(5) << i;
    }
    std::cout << '\n' << "  Dist: ";
	for(auto i : d) {
		std::cout << std::setw(5);
        if(i == INF) {
			std::cout << "INF";
			continue;
		}
        std::cout << i;
	}
}

// Find single source shortest path.
// g = non-negative weight graph adjacency matrix
// start = index of starting vertex
// print = (default value = false) print the results
void dijkstra(const graph& g, int start, bool print = false) {
	int vertices = g.size();
    // Distance vector: contains the shortest paths from
    // the starting vertex to the corresponding vertices
    // initial distance is infinity (no paths added yet)
	std::vector<int> d(vertices, INF);
	std::vector<bool> isVisited(vertices, false);   // tracks the visited/ added vertices

	d[start] = 0;   // distance from the starting vertex to itself is always zero

	for(int i = 0; i < vertices - 1; i++) {
		int u = nearestVertex(d, isVisited);    // edge to vertex with smallest distance
		isVisited[u] = true;    // mark as visited
		for(int v = 0; v < vertices; v++) {
			int other = d[u] + g[u][v];     
			if(!isVisited[v] && g[u][v] != 0 && d[v] > other) {
				d[v] = other;       // replace with the better path
			}
		}
	}
	if (print) printVector(d);
}

// Find all single source shortest paths
// g = non-negative weight graph adjacency matrix
// print = (default value = false) print the results
void dijkstraAllPaths(const graph& g, bool print = false) {
    int vertices = g.size();
    
    if (print) std::cout << "DIJKSTRA ALGORITHM result:";

    for(int i = 0; i < vertices; i++) {
        if (print) std::cout << "\n> Starting vertex = " << i << '\n';
        dijkstra(g, i, print);
    }
	if (print) std::cout << "\n\n";
}