#pragma once

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <limits.h>
#include "node_intf.h"


using namespace std;

namespace pixelda {

	enum class traversal {
		Bfs,
		Dfs,
		Djistrika
	};

	class graph
	{
	public:
		using EdgeSpecs = pair<int, pair<int, int> >;

		graph(int nVertices, vector<EdgeSpecs>& edges) {
			build_graph(nVertices, edges);
		}
		~graph() {};

		void traverse(traversal mode) {
			if (mode == traversal::Dfs) {
				dfs(vlist[1]);
			}
			else if (mode == traversal::Bfs) {
				bfs(vlist[1]);
			}
			else  if (mode == traversal::Djistrika) {
				djistra_weighted_shortest(vlist[1]);
			}
		}

		vector<int> shortestPath(int start, int end) {
			node* ebegin = vlist[start];
			node* eend = vlist[end];

			vector<int> path;
			node *tr = ebegin;
			while (tr != eend) {
				path.push_back(tr->get_label());
				tr = tr->get_parent();
			}

			// start node
			path.push_back(tr->get_label());

			return (std::move(path));
		}

	private:
		void build_graph(int nVertices, vector<EdgeSpecs>& edges) {
			for (int id = 0; id <= nVertices; id++) {
				vlist.push_back(make_vertex(id));
			}

			for (EdgeSpecs& edge : edges) {
				node* vx = vlist[edge.second.first];
				node* vy = vlist[edge.second.second];
				int weight = edge.first;

				vx->add_adjacent(vy, weight);
				vy->add_adjacent(vx, weight);
			}
		}

		void dfs(node* start) {
			stack<node*> s;
			start->set_visited(visit::Discovered);
			s.push(start);

			while (!s.empty()) {
				node* e = s.top();
				s.pop();

				process(e, s);
				e->set_visited(visit::Done);
			}
		}

		void bfs(node* start) {
			queue<node*> q;
			start->set_visited(visit::Discovered);
			q.push(start);

			while (!q.empty()) {
				node* e = q.front();
				q.pop();

				process(e, q);
				e->set_visited(visit::Done);
			}
		}

		void djistra_weighted_shortest(node* start) {

			start->set_cost(0);
			node*e = start;
			while (e->visited() == visit::None) {
				e->set_visited(visit::Done);

				int i = 0;
				auto weightsIt = e->get_weightsBegin();
				for (auto it = e->get_adjacentsBegin(); it != e->get_adjacentsEnd(); it++) {
					node* adj = *it;
					if ((e->get_cost() + *weightsIt) < adj->get_cost()) {
						adj->set_cost(e->get_cost() + *weightsIt);
						adj->set_parent(e);
					}
					i++;
				}

				int dist = INT_MAX;

				for (node* x : vlist) {
					if (x->visited() == visit::None && x->get_cost() < dist) {
						dist = x->get_cost();
						e = x;
					}
				}
			}
		}


		void process(node*e, stack<node*>& s) {

			auto weightsIt = e->get_weightsBegin();
			for (auto it = e->get_adjacentsBegin(); it != e->get_adjacentsEnd(); it++) {
				node* adj = *it;

				if (adj->visited() == visit::None) {
					adj->set_parent(e);
					adj->set_visited(visit::Discovered);
					s.push(adj);
				}
			}

			cout << e->get_label() << "\t";
		}

		void process(node*e, queue<node*>& q) {

			auto weightsIt = e->get_weightsBegin();
			for (auto it = e->get_adjacentsBegin(); it != e->get_adjacentsEnd(); it++) {
				node* adj = *it;
				if (adj->visited() == visit::None) {
					adj->set_parent(e);
					adj->set_visited(visit::Discovered);
					q.push(adj);
				}
			}

			cout << e->get_label() << "\t";
		}

		node* make_vertex(int label) {
			node* e = new node(label);
			if (e == nullptr) {
				throw "memory alloc failure. ::graph builder";
			}

			return e;
		}
	private:
		vector<node*> vlist;
	};

};
