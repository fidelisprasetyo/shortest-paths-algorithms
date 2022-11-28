// Author: Fidelis Prasetyo (fprasetyo@cpp.edu)
// Desc: for Project 2, CS3310 Fall, Cal Poly Pomona 
// github: https://github.com/fidelisprasetyo
// github repo: https://github.com/fidelisprasetyo/shortest-paths-algorithms

#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include "floyd_warshall.h"
#include "dijkstra.h"
#include "util.h"

#define MAX_SIZE 1000		// max number of vertices
#define TEST_COUNT 10		// number of repeated tests with the same graph
#define PRINT_STATUS false	// for debugging purposes

typedef std::vector<std::vector<int>> graph;

int main() {
	srand(time(NULL));

	// ----SANITY CHECK----
	graph g1 = 
	{
		{0,3,8, INF, -4},
		{INF, 0, INF, 1, 7},
		{INF, 4, 0, INF, INF},
		{2, INF, -5, 0, INF},
		{INF, INF, INF, 6, 0}
	};

	graph g2 =
	{ 
		{0,3,8, INF, 4},
		{INF, 0, INF, 1, 7},
		{INF, 4, 0, INF, INF},
		{2, INF, 5, 0, INF},
		{INF, INF, INF, 6, 0}
	};

	std::cout << "---Directed Graph with negative weights:\n";
	floydWarshall(g1, true);
	
	std::cout << "---Directed Graph with non-negative weights:\n";
	dijkstraAllPaths(g2, true);
	floydWarshall(g2, true);
	
	// ----PERFORMANCE TEST----
	std::ofstream data;
	graph sparse;	// for sparse graphs (num of edges = n - 1)
	graph dense;	// for dense graphs (num of edges = n(n - 1)/2)

	data.open("dataxxx.csv");
	data << "size,iteration,floyd-warshall (sparse),floyd-warshall (dense),dijkstra (sparse),dijkstra (dense)\n";

	for(int n = 10; n <= MAX_SIZE; n+=10) {
		randomizeSparseGraph(sparse, n);	// sparse, undirected, non-negative weights, connected graph
		randomizeDenseGraph(dense, n);		// dense, directed, non-negative weights, connected graph

		for(int count = 0; count < TEST_COUNT; count++) {
			if(PRINT_STATUS) std::cout << "\nWorking on n = " << n << '\n';
			auto start = std::chrono::high_resolution_clock::now();
			floydWarshall(sparse);
			auto stop = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start).count();

			auto start1 = std::chrono::high_resolution_clock::now();
			floydWarshall(dense);
			auto stop1 = std::chrono::high_resolution_clock::now();
			auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(stop1-start1).count();

			auto start2 = std::chrono::high_resolution_clock::now();
			dijkstraAllPaths(sparse);
			auto stop2 = std::chrono::high_resolution_clock::now();
			auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop2-start2).count();
			
			auto start3 = std::chrono::high_resolution_clock::now();
			dijkstraAllPaths(dense);
			auto stop3 = std::chrono::high_resolution_clock::now();
			auto duration3 = std::chrono::duration_cast<std::chrono::microseconds>(stop3-start3).count();

			data << n << ',' << count << ',' << duration << ',' << duration1 << ',' << duration2 << ',' << duration3 << '\n';
		}
	}
    return 0;
    
}