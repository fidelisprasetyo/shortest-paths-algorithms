#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>	// shuffle
#include "floyd_warshall.h"
#include "dijkstra.h"

#define SANITY_CHECK true
#define RAND_RANGE 10
#define MAX_SIZE 20
#define INF 999999

typedef std::vector<std::vector<int>> graph;

int getRandInt(int start, int end) {
    return rand() % end + start;
}

bool rand_bool() {
	return rand() & 1;
}

void resizeMat(graph& g, int size) {
	g.resize(size);
	for(int i = 0; i < size; i++) {
		g[i].resize(size);
	}
}

int main() {
	srand(time(NULL));

	graph g = 
	{
		{0,3,8, INF, -4},
		{INF, 0, INF, 1, 7},
		{INF, 4, 0, INF, INF},
		{2, INF, -5, 0, INF},
		{INF, INF, INF, 6, 0}
	};

	graph g2 =
	{ { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
                        { 4, 0, 8, 0, 0, 0, 0, 11, 0 },
                        { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
                        { 0, 0, 7, 0, 9, 14, 0, 0, 0 },
                        { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
                        { 0, 0, 4, 14, 10, 0, 2, 0, 0 },
                        { 0, 0, 0, 0, 0, 2, 0, 1, 6 },
                        { 8, 11, 0, 0, 0, 0, 1, 0, 7 },
                        { 0, 0, 2, 0, 0, 0, 6, 7, 0 } };

	//floydWarshall(g);
	//dijkstraAllPaths(g1);

	// performance test

	int num_vertex = 10;
	int num_edges = 9;
	std::vector<bool> isAdded(num_vertex, false);
	std::vector<int> v_list;

	for(int i = 0; i < num_vertex; i++) {
		v_list.push_back(i);
	}

	std::random_shuffle(v_list.begin(), v_list.end());

	// initialize
	graph gr(num_vertex, std::vector<int>(num_vertex, INF));
	for(int i = 0; i < num_vertex; i++) {
		gr[i][i] = 0;
	}

	// add vertices
	for(int i = 1; i < num_vertex; i++) {
		int prev = v_list[i-1];
		int cur = v_list[i];
		gr[prev][cur] = getRandInt(1, 10);
		gr[cur][prev] = gr[prev][cur];
	}

	printMatrix(gr);

	floydWarshall(gr);

    return 0;
    
}