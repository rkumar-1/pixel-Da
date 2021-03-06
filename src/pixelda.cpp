// pixelda.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "graph.h"
#include "bst_234_v3.h"

#include <map>
#include <random>

using namespace pixelda;

int main()
{
	//
	// graph usage 
	//
	vector<graph::EdgeSpecs> edgespecs = {
		{ 5,{ 1,2 } },
		{ 4,{ 1,6 } },
		{ 1,{ 1,7 } },
		{ 6,{ 1,3 } },
		{ 4,{ 2,7 } },
		{ 2,{ 2,3 } },
		{ 3,{ 3,4 } },
		{ 2,{ 4,7 } },
		{ 3,{ 4,5 } },
		{ 2,{ 5,6 } },
		{ 2,{ 6,7 } }
	};

	// input edge specs to the graph
	graph g(7, edgespecs);

	// traverse and use Djistrika shortest path to record the path.
	g.traverse(traversal::Djistrika);

	// prints the shortest path discovered during the traversal
	vector<int> vpathg = g.shortestPath(5, 1);
	for (int x : vpathg) {
		cout << x << "\t";
	}


	//
	// bst usage
	//

	// generates and adds 250K randomly generated keys and values 

	vector<pair<int, int>> kv;

	std::random_device rd;
	std::mt19937 mt(8967);
	std::uniform_int_distribution<int> dist(0, 1000000);

	long number_of_elements = 250000; // -100000;
	pair<int, int> saved;
	while (number_of_elements--) {
		saved = { dist(mt), dist(mt) };
		kv.push_back(saved);
	}

	bst_234_v3 bst(kv);

	bst.print_bfs();

	// finding a value for a given key
	int value = bst.find(saved.first);
	
    return 0;
}

