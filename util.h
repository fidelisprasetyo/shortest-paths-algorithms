#pragma once

#include <algorithm>	// shuffle

#define RAND_RANGE 10   // max weight value
#define INF 999999

typedef std::vector<std::vector<int>> graph;

int getRandInt(int start, int end) {
    return rand() % end + start;
}

void resizeMat(graph& g, int size) {
	g.resize(size);
	for(int i = 0; i < size; i++) {
		g[i].resize(size);
	}
}

// Randomize g to a sparse, undirected, non-negative weights, connected graph
void randomizeSparseGraph(graph& g, int num_vertex) {
	int num_edge = num_vertex - 1;	// minimum number of edges possible (sparse)

	std::vector<int> v_list;
	for(int i = 0; i < num_vertex; i++) {
		v_list.push_back(i);
	}
	std::random_shuffle(v_list.begin(), v_list.end());  // shuffle the order of vertices

    // initialize matrix
	resizeMat(g, num_vertex);
	for(int i = 0; i < num_vertex; i++) {
		for(int j = 0; j < num_vertex; j++) {
			if(i == j) {
				g[i][j] = 0;
			}
			else {
				g[i][j] = INF;
			}
		}
	}

    // add vertex one by one
	for(int i = 1; i < num_vertex; i++) {
		int prev = v_list[i-1];
		int cur = v_list[i];
		g[prev][cur] = getRandInt(1, RAND_RANGE);
		g[cur][prev] = g[prev][cur];        // undirected
	}
}

// Randomize g to a dense, directed, non-negative weights, connected graph
void randomizeDenseGraph(graph& g, int num_vertex) {
	resizeMat(g, num_vertex);
	for(int i = 0; i < num_vertex; i++) {
		for(int j = 0; j < num_vertex; j++) {
			if(i == j) {
				g[i][j] = 0;
			}
			else {
				g[i][j] = getRandInt(1,RAND_RANGE); // fill with random non-negative weights
			}
		}
	}
}