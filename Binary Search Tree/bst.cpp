#include <iostream>
#include <algorithm> // For std::max used in calculating height

class BST {
private:
	struct Node {
		int value;      // Value contained in the node
		Node* left;     // Pointer to the left child
		Node* right;    // Pointer to the right child

		// Constructor for creating a new node
		Node(int val) : value(val), left(nullptr), right(nullptr) {}
	};

	Node* root; // Root pointer of the BST

	// Helper function to insert a value into the subtree rooted at 'node'
	Node* insert(Node* node, int value) {
		if(node == nullptr) {
			return new Node(value);
		}

		if(value < node->value) {
			node->left = insert(node->left, value);
		} else if(value > node->value) {
			node->right = insert(node->right, value);
		}

		return node;
	}

	Node* removeNode(Node* node, int value) {
		if(node == nullptr) {
			// Return null if node to remove is not found
			return node;
		}

		if(value < node->value) {
			node->left = removeNode(node->left, value);
		} else if(value > node->value) {
			node->right = removeNode(node->right, value);
		} else {
			// Found the node to remove
			if(node->left == nullptr) {
				// Node has no left child
				Node* temp = node->right;
				delete node;
				return temp;
			} else if(node->right == nullptr) {
				// Node has no right child
				Node* temp = node->left;
				delete node;
				return temp;
			}

			// Node has two children
			Node* temp = minValueNode(node->right); // Find min value on the right subtree
			node->value = temp->value; // Copy the min value to the node to be removed
			node->right = removeNode(node->right, temp->value); // Remove the duplicate node
		}

		return node;
	}

	// Function to find the node with the minimum value in the subtree rooted at 'node'
	Node* minValueNode(Node* node) {
		Node* current = node;
		while(current && current->left != nullptr) {
			current = current->left;
		}
		return current;
	}

	// In-order traversal of the BST that prints node values
	void inOrderTraversal(Node* node) {
		if(node != nullptr) {
			inOrderTraversal(node->left);
			std::cout << node->value << " ";
			inOrderTraversal(node->right);
		}
	}

	// Helper function to search for a value in the subtree rooted at 'node'
	bool search(Node* node, int value) const {
		if(node == nullptr) {
			return false; // Return false if value is not found
		}

		// Return true if the node is found
		if(node->value == value) {
			return true;
		}

		// Continue searching on the left / right subtree
		if(value < node->value) {
			return search(node->left, value);
		} else {
			return search(node->right, value);
		}
	}

	// Function to calculate the size of the subtree rooted at 'node'
	int size(Node* node) const {
		if(node == nullptr)
			return 0;
		return 1 + size(node->left) + size(node->right);
	}

	// Function to calculate the height of the subtree rooted at 'node'
	int height(Node* node) const {
		if(node == nullptr)
			return -1; // Return -1 for an empty tree
		return 1 + std::max(height(node->left), height(node->right));
	}

	// Function to clear all nodes in the subtree rooted at 'node'
	void clear(Node*& node) {
		if(node != nullptr) {
			clear(node->left);
			clear(node->right);
			delete node;
			node = nullptr;
		}
	}

public:
	// Constructor initializes the tree with no nodes
	BST() : root(nullptr) {}

	// Destructor clears all nodes
	~BST() {
		clear(root);
	}

	// Public member function to insert a value into the BST
	void insert(int value) {
		root = insert(root, value);
	}

	// Public member function to remove a value from the BST
	void remove(int value) {
		root = removeNode(root, value);
	}

	// Public member function to search for a value in the BST
	bool search(int value) const {
		return search(root, value);
	}

	// Public member function to perform in-order traversal and print values
	void printInOrder() {
		inOrderTraversal(root);
	}

	// Public member function to get the size of the BST
	int getSize() const {
		return size(root);
	}

	// Public member function to get the height of the BST
	int getHeight() const {
		return height(root);
	}

	// Public member function to clear the BST
	void clearTree() {
		clear(root);
	}
};

