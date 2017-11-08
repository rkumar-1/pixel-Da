#pragma once
class bst_rb
{
	enum class Color {
		RED,
		BLACK
	};

	using Key = int;
	using Value = int;

	struct Node {
		Node() {};

		Node(Key key_in, Value value_in) : key(key_in), value(value_in), 
			color(Color::RED), number_of_nodes(1), height(1) {}

		Node* make_node(Key key, Value value) {
			return new Node(key, value);
		};

		Key key;
		Value value;
		Node* left, *right;

		// color of parent link (ending in us)
		Color color;

		// added state information
		int number_of_nodes; // in tree rooted here
		int height;			 // height of tree rooted here
	};


public:
	bst_rb();
	~bst_rb();

	int size() {
		return size(root);
	}
	
	int size(Node* x) {
		if (x == nullptr) {
			return 0;
		}
		else {
			return x->number_of_nodes;
		}
	}

	int root_rank() {
		if (root == nullptr) {
			return 0;
		}
		else {
			return size(root->left);
		}
	}

	int height() {
		return height(root);
	}

	int height(Node* x) {
		if (x == nullptr) {
			return 0;
		}
		else {
			return x->height;
		}
	}
private:
	Node* root;   // root of the BST
};

