#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <queue>

using namespace std;

namespace pixelda
{

	// class implements a Binary 2-3-4 Balanced Search Tree
	// ToDos: 
	// 1. Add delete functionality 
	// 2. and to Refactor to remove duplicate code.
	// 3. Optimize for memory usage
	// For now, it is useful to act as a test bed to performance measure a 
	// balanced search tree with Top-Down insertion.

	class bst_234_v3
	{
		using Key = int;
		using Value = int;
		using KVPair = pair<Key, Value>;

		enum class node_type {
			TWO_NODE,
			THREE_NODE,
			FOUR_NODE
		};

		struct Node {
			vector<KVPair> keys;
			vector<Node*> children;
			node_type nodeType;
			bool leaf_node;

			// empty node
			Node() : nodeType(node_type::TWO_NODE), leaf_node(true) {
			}

			// one key value - two node
			Node(KVPair key_in) : nodeType(node_type::TWO_NODE), leaf_node(true) {
				keys.push_back(key_in);

				children.push_back(nullptr);
				children.push_back(nullptr);

			};

			// Insert gets called on a 2 or 3-node type to insert a Key value pair
			void insert(KVPair element) {

				// no dups allowed - policy is to make the latest entry relevant
				if (element.first == keys.front().first) {
					keys.front().second = element.second;
					return;
				}

				if (element.first < keys.front().first) {
					keys.insert(keys.begin(), element);
				}
				else if (element.first > keys.back().first) {
					// can be a 2-node or 3-node
					keys.push_back(element);
				}
				else if (element.first < keys.back().first) {
					// must be a 3-node - insert into the middle
					keys.insert(keys.begin() + 1, element);
				}

				children.push_back(nullptr);
			}

			node_type get_type() {
				if (keys.size() >= 3) {
					return node_type::FOUR_NODE;
				}
				else if (keys.size() >= 2) {
					return node_type::THREE_NODE;
				}
				else {
					return node_type::TWO_NODE;
				}
			}

			bool leaf() {
				return leaf_node;
			}

			void set_leaf(bool value) {
				leaf_node = false;
			}

			bool empty() {
				return (keys.empty());
			}

			static Node* make_node() {
				return new Node();
			}

			static Node* make_node(KVPair kv) {
				return new Node(kv);
			}

			static void make_node(Node*& target, KVPair kv) {
				target = new Node(kv);

				if (!target) {
					throw "make_node unable to allocate resources: unable to continue.";
				}
			}

			void exchange(int& x, int& y) {
				x = x ^ y;
				y = x ^ y;
				x = x ^ y;
			};

			Value find(Key search)
			{
				Value found = INT_MIN;

				for_each(keys.begin(), keys.end(), [&](auto entry) {
					if (entry.first == search) {
						found = entry.second;
						return;
					}
				});

				return found;
			}

			bool insert_child_node(Node* node) {
				bool op_status = false;

				for (int index = 0; index < (int)children.size(); index++) {
					if (children[index] == nullptr) {
						children[index] = node;
						op_status = true;
						break;
					}
				}

				return op_status;
			}

			bool insert_key(KVPair& kv) {
				bool op_status = true;

				if (get_type() == node_type::FOUR_NODE) {
					cerr << "Node::insert_key called for a Four node. Check for Logical error!" << endl;

					return false;
				}

				for (auto it = keys.begin(); it != keys.end(); it++) {

					if (kv.first == it->first) {
						it->first = kv.first;
						it->second = kv.second;
						op_status = false;

						break;
					}
					else if (kv.first < it->first) {
						exchange(kv.first, it->first);
					}
				}

				keys.push_back(kv);

				return op_status;
			}
		};

		// Debug APIs
		int count_nodes;

	// Interface
	public:
		bst_234_v3(vector<KVPair>& keys) {
			buildTree(keys);
		};

		~bst_234_v3() {};

		inline void add_element(KVPair key) {
			insert(nullptr, 0, key);
		}

		inline bool empty() {
			return (root == nullptr);
		}

		Value find(Key search_key) {

			Node* element = root;

			while (element) {
				if (search_key < element->keys.front().first) {
					element = element->children.front();
					continue;
				}
				else if (search_key > element->keys.back().first) {
					element = element->children.back();
					continue;
				}

				for (int i = 0; i < (int) element->keys.size(); i++) {
					if (search_key == element->keys[i].first) {
						return element->keys[i].second;
					}
					else if (search_key < element->keys[i].first) {
						element = element->children[i];
						break;
					}
				}
			}

			return INT_MIN;
		}

		void print_bfs() {
			queue<Node*> q;

			Node* element = root;

			q.push(root);
			q.push(new Node(make_pair(INT_MAX, INT_MAX)));

			while (!q.empty()) {
				Node* e = q.front();
				q.pop();

				if (e == nullptr) {
					cout << " N ";
					continue;
				}

				if (!e->empty()) {
					if (e->keys.front().first != INT_MAX) {
						for (auto x : e->keys) {
							cout << x.first << " ";
						}
						cout << " ]  |  [  ";

						for (auto x : e->children) {
							q.push(x);
						}
					}
					else {
						cout << endl;
						if (q.empty())
							break;
						// level terminates and next level starts
						q.push(new Node(make_pair(INT_MAX, INT_MAX)));
					}
				}
			}
		}

		/********** INSTANT UNIT TESTS*************/
		inline void insert_key_test() {
			Node* node = Node::make_node();

			vector<KVPair> key = { { 4, 1 },{ 3, 1 },{ 2, 1 },{ 1, 1 } };

			int i = 0;
			int j = key.size() - 1;
			while (i < j) {
				node->exchange(key[i++].first, key[j--].first);
			}

			int op_status = node->insert_key(key[0]);
			assert(op_status);
			op_status = node->insert_key(key[1]);
			assert(op_status);

			op_status = node->insert_key(key[2]);
			assert(op_status);

			op_status = node->insert_key(key[3]);
			assert(!op_status);

		}

	private:
		void buildTree(vector<KVPair>& keys) {
			count_nodes = 0;

			for (KVPair entry : keys) {
				count_nodes++;
				//			cout << count_nodes << endl;

				if (empty()) {
					Node::make_node(root, entry);
					continue;
				}

				insert(nullptr, 0, entry);
			}
		}

		void insert(Node* parent, int index, KVPair entry) {
			Node* node = root;

			if (parent) {
				node = parent->children[index];
			}

			// About to step into a four-node, make room for the new key by splitting it
			if (node->get_type() == node_type::FOUR_NODE) {
				if (parent) {
					split(parent, index, entry);
				}
				else {
					split_root(node, entry);
				}

				// split and insert done.
				return;
			}

			while (node != nullptr) {

				// Top-down insertion makes sure leaf is either a 2-node or 3-node
				// and always has room.
				if (node->leaf()) {
					node->insert(entry);
					break;
				}

				if (entry.first < node->keys.front().first) {
					// going left
					insert(node, 0, entry);
					break;

				}
				else if (entry.first > node->keys.back().first) {
					// going right
					insert(node, node->children.size() - 1, entry);
					break;

				} // entering 3-node territory (key falls into the interval )
				else if (entry.first < node->keys.back().first) {
					// go middle (2nd node)
					insert(node, 1, entry);
					break;
				}
				else if (entry.first == node->keys.front().first || entry.first == node->keys.back().first) {
					// duplicate value - return
					break;
				}

			}
		}

		void split(Node* parent, int index, KVPair kv) {
			Node* element = parent->children[index];

			KVPair middle_kv = { element->keys[1] };

			Node* left = Node::make_node(element->keys.front());
			Node* right = Node::make_node(element->keys.back());

			// now insert the new value into one of the two nodes
			bool op_status;
			if (kv.first <= middle_kv.first) {
				op_status = left->insert_key(kv);
				assert(op_status);
			}
			else {
				op_status = right->insert_key(kv);
				assert(op_status);
			}

			parent->insert_key(middle_kv);


			// replaces the child (4-node) with the newly formed 2 or 3-nodes
			Node* deleteMe = element;

			Node* child = deleteMe->children.front();
			if (child) {
				left->insert_child_node(child);
			}

			child = deleteMe->children[1];
			if (child) {
				left->insert_child_node(child);
			}

			child = deleteMe->children[2];
			if (child) {
				right->insert_child_node(child);
			}

			child = deleteMe->children.back();
			if (child) {
				right->insert_child_node(child);
			}


			if (kv.first < parent->keys.front().first) {
				parent->children[index] = left;
				parent->children.insert(parent->children.begin() + 1, right);
			}
			else if (kv.first > parent->keys.back().first) {
				Node* deleteMe = element;
				parent->children[index] = left;
				parent->children.push_back(right);
			}
			else {
				// middle
				Node* deleteMe = element;
				parent->children[index] = left;
				parent->children.push_back(right);
			}


			delete deleteMe;
			parent->set_leaf(false);
		}

		void split_root(Node* element, KVPair kv) {
			KVPair middle_kv = { element->keys[1] };

			Node* deleteMe = root;

			root = Node::make_node(middle_kv);

			Node* left = Node::make_node(element->keys.front());
			Node* right = Node::make_node(element->keys.back());

			Node* child = deleteMe->children.front();
			if (child) {
				left->insert_child_node(child);
			}

			child = deleteMe->children[1];
			if (child) {
				left->insert_child_node(child);
			}

			child = deleteMe->children[2];
			if (child) {
				right->insert_child_node(child);
			}

			child = deleteMe->children.back();
			if (child) {
				right->insert_child_node(child);
			}

			root->insert_child_node(left);
			root->insert_child_node(right);

			root->set_leaf(false);

			// now insert the new value into one of the two split nodes
			if (kv.first <= middle_kv.first) {
				left->insert_key(kv);
			}
			else {

				right->insert_key(kv);
			}

			delete deleteMe;
		}

	private:
		Node *root;
	};
};
