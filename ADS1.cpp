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
    int choice;
    string key, val;

    do {
        cout << "\n--- Dictionary Menu ---\n";
        cout << "1. Insert Word\n";
        cout << "2. Search Word\n";
        cout << "3. Delete Word\n";
        cout << "4. Inorder Traversal\n";
        cout << "5. Mirror Dictionary (Inorder)\n";
        cout << "6. Clone Dictionary (Inorder)\n";
        cout << "7. Level Order Traversal\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter word: ";
                cin >> key;
                cout << "Enter meaning: ";
                cin >> val;
                b.root = b.insert(b.root, key, val);
                break;
            case 2:
                cout << "Enter word to search: ";
                cin >> key;
                b.search(key);
                break;
            case 3:
                cout << "Enter word to delete: ";
                cin >> key;
                b.root = b.deleteNode(b.root, key);
                break;
            case 4:
                cout << "Inorder Traversal:\n";
                b.inorder(b.root);
                break;
            case 5: {
                cout << "Mirror of Dictionary (Inorder):\n";
                Node* mirrorRoot = b.mirror(b.root);
                b.inorder(mirrorRoot);
                break;
            }
            case 6: {
                cout << "Cloned Dictionary (Inorder):\n";
                Node* cloneRoot = b.clone(b.root);
                b.inorder(cloneRoot);
                break;
            }
            case 7:
                cout << "Level Order Traversal:\n";
                b.levelorder();
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}
