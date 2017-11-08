#pragma once

#include <vector>

using namespace std;

namespace pixelda 
{

	// node visit status
	enum class visit {
		Done,
		Discovered,
		None
	};


	class node {

		int label;

		vector<node*> adjList;
		vector<int>  weights;

		node* parent;
		visit status;

		int	cost;

	public:
		node(int id) : label(id), parent(nullptr), cost(INT_MAX), status(visit::None) {};

		void add_adjacent(node* peer, int edgeWeight) {
			adjList.push_back(peer);
			weights.push_back(edgeWeight);
		}

		int get_label() {
			return label;
		}

		node* get_parent() {
			return parent;
		}

		int get_cost() {
			return cost;
		}

		visit visited() {
			return status;
		}

		void set_visited(visit value) {
			status = value;
		}

		void set_cost(int value) {
			cost = value;
		}

		void set_parent(node* ref) {
			parent = ref;
		}

		auto get_adjacentsBegin() {
			return adjList.begin();
		}

		auto get_adjacentsEnd() {
			return adjList.end();
		}

		auto get_weightsBegin() {
			return weights.begin();
		}

		auto get_weightsEnd() {
			return weights.end();
		}

	};
};
