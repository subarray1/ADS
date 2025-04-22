#include<iostream>
using namespace std;

class Node {
public:
    int player_id, score;
    Node* left;
    Node* right;

    Node(int player_id, int score) {
        this->player_id = player_id;
        this->score = score;
        left = NULL;
        right = NULL;
    }
};

class AVL {
public:
 Node *root=NULL;
    int height(Node* root) {
        if (root == NULL) {
            return 0;
        }
        int hl = height(root->left);
        int hr = height(root->right);
        return max(hl, hr) + 1;
    }

    int balanceFactor(Node* root) {
        if (root == NULL) {
            return 0;
        }
        return height(root->left) - height(root->right);
    }

    Node* leftRotate(Node* root) {
        Node* newRoot = root->right;
        root->right = newRoot->left;
        newRoot->left = root;
        return newRoot;
    }

    Node* rightRotate(Node* root) {
        Node* newRoot = root->left;
        root->left = newRoot->right;
        newRoot->right = root;
        return newRoot;
    }

    Node* insert(Node* root, int player_id, int score) {
        if (root == NULL) {
            return new Node(player_id, score);
        }
        if(root->player_id==player_id)
        {
            return NULL;
        }

        if (player_id < root->player_id) {
            root->left = insert(root->left, player_id, score);
        } 
        else 
        {
            root->right = insert(root->right, player_id, score);
        } 

        int bf = balanceFactor(root);

        if (bf > 1 && player_id < root->left->player_id) {
            return rightRotate(root);
        }
        if (bf < -1 && player_id > root->right->player_id) {
            return leftRotate(root);
        }
        if (bf > 1 && player_id > root->left->player_id) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        if (bf < -1 && player_id < root->right->player_id) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    void search(Node *root,int player_id) {
		Node* temp = root;
		while (temp) {
			if (player_id == temp->player_id) {
				cout << "PLayer found: " << temp->player_id << " -> " << temp->score << endl;
				return;
			} else if (player_id > temp->player_id) {
				temp = temp->right;
			} else {
				temp = temp->left;
			}
		}
		cout << "Word not found!" << endl;
	}

    void inorder(Node* root) {
        if (root == NULL) return;
        inorder(root->left);
        cout << "Player Id: " << root->player_id << " Score: " << root->score << endl;
        inorder(root->right);
    }

    void preorder(Node* root) {
        if (root == NULL) return;
        cout << "Player Id: " << root->player_id << " Score: " << root->score << endl;
        preorder(root->left);
        preorder(root->right);
    }

    void postorder(Node* root) {
        if (root == NULL) return;
        postorder(root->left);
        postorder(root->right);
        cout << "Player Id: " << root->player_id << " Score: " << root->score << endl;
    }

    Node* minValueNode(Node* root) {
        Node* temp = root;
        while (temp->left != nullptr)
            temp = temp->left;
        return temp;
    }

    Node* deleteNode(Node* root, int player_id) {
        
        if (!root) {
            cout << "Node not found!" << endl;
            return root;
        }
    
        if (player_id < root->player_id) {
            root->left = deleteNode(root->left, player_id);
        } 
        else if (player_id > root->player_id) {
            root->right = deleteNode(root->right, player_id);
        } 
        else {
            if (!root->left && !root->right) {
                delete root;
                return NULL;
            } else if (!root->left) {
                Node* temp = root->right;
                delete root;
                return temp;
            } else if (!root->right) {
                Node* temp = root->left;
                delete root;
                return temp;
            } else {
                Node* temp = minValueNode(root->right);
                root->player_id = temp->player_id;
                root->score = temp->score;
                root->right = deleteNode(root->right, temp->player_id);
            }
        }
    
        // Rebalancing
        int bf = balanceFactor(root);
    
        if (bf > 1 && balanceFactor(root->left) >= 0)
            return rightRotate(root);
            
        if (bf > 1 && balanceFactor(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        if (bf < -1 && balanceFactor(root->right) <= 0)
            return leftRotate(root);
        if (bf < -1 && balanceFactor(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    
        return root;
    }
    
};

int main() {
    AVL tree;

    tree.root = tree.insert(tree.root, 1, 20);
    tree.root = tree.insert(tree.root, 3, 50);
    tree.root = tree.insert(tree.root, 5, 60);
    tree.root = tree.insert(tree.root, 4, 20);
    tree.root = tree.insert(tree.root, 2, 80);
    tree.root = tree.insert(tree.root, 6, 20);
    tree.root = tree.insert(tree.root, 7, 90);

    cout << "Inorder Traversal" << endl;
    tree.inorder(tree.root);

    tree.search(tree.root, 7);

    tree.root = tree.deleteNode(tree.root, 5);
    cout << "\nAfter Deleting Player with ID 5:\n";
    tree.inorder(tree.root);

    return 0;
}
