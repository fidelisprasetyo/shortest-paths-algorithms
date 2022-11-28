#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include "floyd_warshall.h"
#include "dijkstra.h"
#include "util.h"

#define MAX_SIZE 2000
#define TEST_COUNT 10

typedef std::vector<std::vector<int>> graph;

int main() {
	srand(time(NULL));

	// sanity check
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
		{ 0, 4, 0, 0, 0, 0, 0, 8, 0 },
        { 4, 0, 8, 0, 0, 0, 0, 11, 0 },
        { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
        { 0, 0, 7, 0, 9, 14, 0, 0, 0 },
        { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
        { 0, 0, 4, 14, 10, 0, 2, 0, 0 },
        { 0, 0, 0, 0, 0, 2, 0, 1, 6 },
        { 8, 11, 0, 0, 0, 0, 1, 0, 7 },
        { 0, 0, 2, 0, 0, 0, 6, 7, 0 } 
	};

	floydWarshall(g1);
	dijkstraAllPaths(g2);
	
	// performance test
	std::ofstream data;
	data.open("data.csv");

	graph sparse;
	graph dense;
	data << "size,iteration,floyd-warshall (sparse),floyd-warshall (dense),dijkstra (sparse),dijkstra (dense)\n";
	for(int n = 10; n <= MAX_SIZE; n+=10) {
		randomizeSparseGraph(sparse, n);
		randomizeDenseGraph(dense, n);

		for(int count = 0; count < TEST_COUNT; count++) {
			std::cout << "Working on size = " << n << '\n';
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