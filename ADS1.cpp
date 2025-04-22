#include <iostream>
#include <queue>
using namespace std;

class Node {
public:
	string key, val;
	Node* left;
	Node* right;

	Node(string key, string val) {
		this->key = key;
		this->val = val;
		left = right = NULL;
	}
};

class BST {
public:
	Node* root;

	BST() {
		root = NULL;
	}

	// INSERT FUNCTION
	Node* insert(Node* root, string key, string val) {
		if (root == NULL) {
			cout << "Node added!" << endl;
			return new Node(key, val);
		}
		if (key == root->key) {
			cout << "Duplicate entry not allowed!" << endl;
			return root;
		}
		else if (key > root->key) {
			root->right = insert(root->right, key, val);
		}
		else {
			root->left = insert(root->left, key, val);
		}
		return root;
	}


	// FIND MINIMUM NODE (FOR INORDER SUCCESSOR)
	Node* findMin(Node* temp) {
		while (temp->left != NULL) {
			temp = temp->left;
		}
		return temp;
	}

	// DELETE FUNCTION (INCLUDING ALL CONDITIONS)
	Node* deleteNode(Node* root, string key) {
		if (!root) {
			cout << "Node not found!" << endl;
			return root;
		}

		if (key < root->key) {
			root->left = deleteNode(root->left, key);
		}
		else if (key > root->key) {
			root->right = deleteNode(root->right, key);
		}
		else {
			if (!root->left && !root->right) {
				delete root;
				return NULL;
			}
			else if (!root->left) {
				Node* temp = root->right;
				delete root;
				return temp;
			}
			else if (!root->right) {
				Node* temp = root->left;
				delete root;
				return temp;
			}
			else {
				Node* temp = findMin(root->right);
				root->key = temp->key;
				root->val = temp->val;
				root->right = deleteNode(root->right, temp->key);
			}
		}
		return root;
	}


	// SEARCH FUNCTION
	void search(string key) {
		Node* temp = root;
		while (temp) {
			if (key == temp->key) {
				cout << "Word found: " << temp->key << " -> " << temp->val << endl;
				return;
			}
			else if (key > temp->key) {
				temp = temp->right;
			}
			else {
				temp = temp->left;
			}
		}
		cout << "Word not found!" << endl;
	}

	// INORDER TRAVERSAL
	void inorder(Node* root) {
		if (!root) return;
		inorder(root->left);
		cout << root->key << " -> " << root->val << endl;
		inorder(root->right);
	}

	// MIRROR TREE FUNCTION
	Node* mirror(Node* root) {
		if (!root) return NULL;
		Node* temp = new Node(root->key, root->val);
		temp->left = mirror(root->right);
		temp->right = mirror(root->left);
		return temp;
	}

	// CLONE TREE FUNCTION
	Node* clone(Node* root) {
		if (!root) return NULL;
		Node* temp = new Node(root->key, root->val);
		temp->left = clone(root->left);
		temp->right = clone(root->right);
		return temp;
	}

	// LEVEL ORDER TRAVERSAL
	void levelorder() {
		if (!root) {
			cout << "Dictionary is empty!" << endl;
			return;
		}
		queue<Node*> q;
		q.push(root);
		while (!q.empty()) {
			Node* temp = q.front();
			q.pop();
			cout << temp->key << " -> " << temp->val << endl;
			if (temp->left) q.push(temp->left);
			if (temp->right) q.push(temp->right);
		}
	}
};

int main() {
	BST b;

	
	b.root = b.insert(b.root, "apple", "a fruit");
	b.root = b.insert(b.root, "book", "a source of knowledge");
	b.root = b.insert(b.root, "cat", "an animal");

	// Search for a word
	cout << "\nSearching for 'book':\n";
	b.search("book");

	// Display the dictionary using inorder traversal
	cout << "\nInorder Traversal of Dictionary:\n";
	b.inorder(b.root);

	// Delete a word
	cout << "\nDeleting 'apple':\n";
	b.root = b.deleteNode(b.root, "apple");

	// Display again after deletion
	cout << "\nInorder Traversal after Deletion:\n";
	b.inorder(b.root);

	// Create a mirror of the dictionary
	cout << "\nMirror of Dictionary:\n";
	Node* mirrorRoot = b.mirror(b.root);
	b.inorder(mirrorRoot);

	// Clone the dictionary
	cout << "\nCloned Dictionary:\n";
	Node* cloneRoot = b.clone(b.root);
	b.inorder(cloneRoot);

	// Display level order traversal
	cout << "\nLevel Order Traversal of Original Dictionary:\n";
	b.levelorder();

	return 0;
}
