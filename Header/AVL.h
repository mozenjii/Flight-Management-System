#pragma once
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

template <typename V>
struct AVLNode {
	V data;
	int height;
	AVLNode<V>* right;
	AVLNode<V>* left;
	AVLNode(V data) :data(data), height(1), right(NULL), left(NULL) {}
};

template <typename V>
class AVL {
	AVLNode<V>* root;
	int getBalanceFactor(AVLNode<V>* temp) {
		if (temp) {
			return getHeight(temp->left) - getHeight(temp->right);
		}
		return 0;
	}

	int getHeight(AVLNode<V>* AVLNode) {
		if (AVLNode)
			return AVLNode->height;
		return 0;
	}

	void updateHeight(AVLNode<V>*& temp) {
		if (temp)
			temp->height = 1 + (getHeight(temp->right) > getHeight(temp->left) ? getHeight(temp->right) : getHeight(temp->left));
	}

	AVLNode<V>* LR(AVLNode<V>* x) {
		if (!x->right)
			return x;
		AVLNode<V>* y = x->right;
		AVLNode<V>* z = y->left;
		y->left = x;
		x->right = z;
		updateHeight(x);
		updateHeight(y);
		return y;
	}

	AVLNode<V>* RR(AVLNode<V>* x) {
		if (!x->left)
			return x;
		AVLNode<V>* y = x->left;
		AVLNode<V>* z = y->right;
		y->right = x;
		x->left = z;
		updateHeight(x);
		updateHeight(y);
		return y;
	}

	AVLNode<V>* findMaxL(AVLNode<V>*& node) {
		if (!node->right) {
			AVLNode<V>* maxAVLNode = node;
			node = node->left;
			return maxAVLNode;
		}
		return findMaxL(node->right);
	}



	AVLNode<V>* insert(AVLNode<V>* temp, V& data) {
		if (!temp)
			return new AVLNode<V>(data);
		if (temp->data.getKey() < data.getKey())
			temp->right = insert(temp->right, data);
		else if (temp->data.getKey() > data.getKey())
			temp->left = insert(temp->left, data);
		else
			return temp;
		updateHeight(temp);
		int bf = getBalanceFactor(temp);
		if (bf == -2) {
			if (temp->right->data.getKey() > data.getKey()) {
				temp->right = RR(temp->right);
				return LR(temp);
			}
			else {
				return LR(temp);
			}

		}
		else if (bf == 2) {
			if (temp->left->data.getKey() < data.getKey()) {
				temp->left = LR(temp->left);
				return RR(temp);
			}
			else {
				return RR(temp);
			}
		}
		return temp;
	}

	AVLNode<V>* Delete(AVLNode<V>* temp, int data, bool& flag) {
		if (!temp) {
			return NULL;
		}
		else if (data > temp->data.getKey())
			temp->right = (Delete(temp->right, data,flag));
		else if (data < temp->data.getKey())
			temp->left = (Delete(temp->left, data, flag));
		else {
			flag = true;
			if (!temp->left && !temp->right) {
				delete temp;
				return NULL;
			}
			else if (!temp->left || !temp->right) {
				AVLNode<V>* temp2 = (temp->right ? temp->right : temp->left);
				delete temp;
				return temp2;
			}
			else {
				AVLNode<V>* copy = findMaxL(temp->left);
				bool flag2 = false;
				temp->left = (Delete(temp->left, copy->data.getKey(), flag2));
				copy->left = (temp->left);
				copy->right = (temp->right);
				return copy;
			}
		}
		updateHeight(temp);
		int bf = getBalanceFactor(temp);
		if (bf == -2) {
			if (temp->right->data.getKey() > data) {
				temp->right = RR(temp->right);
				return LR(temp);
			}
			else {
				return LR(temp);
			}

		}
		else if (bf == 2) {
			if (temp->left->data.getKey() < data) {
				temp->left = LR(temp->left);
				return RR(temp);
			}
			else {
				return RR(temp);
			}
		}
		return temp;
	}

	void preOrder(AVLNode<V>* temp) {
		if (!temp)
			return;
		temp->data.display();
		preOrder(temp->left);
		preOrder(temp->right);
	}

	void inOrder(AVLNode<V>* temp, fstream& file) {
		if (!temp) return;
		inOrder(temp->left, file);
		temp->data.saveData(file);
		inOrder(temp->right, file);
	}

	bool search(AVLNode<V>* temp, const int& id) {
		if (temp == NULL) {
			return false;
		}
		if (temp->data.getKey() == id) {
			return true;
		}
		else if (temp->data.getKey() < id) {
			return search(temp->right, id);
		}
		else {
			return search(temp->left, id);
		}
	}

	bool updateData(AVLNode<V>* temp, const int& id) {
		if (temp == NULL) {
			return false;
		}
		if (temp->data.getKey() == id) {
			temp->data.updateData();
			return true;
		}
		else if (temp->data.getKey() < id) {
			return updateData(temp->right, id);
		}
		else {
			return updateData(temp->left, id);
		}
	}

	bool display(AVLNode<V>* temp, const int& id) {
		if (temp == NULL) {
			return false;
		}
		if (temp->data.getKey() == id) {
			temp->data.display();
			return true;
		}
		else if (temp->data.getKey() < id) {
			return display(temp->right, id);
		}
		else {
			return display(temp->left, id);
		}
	}

	AVLNode<V>* getNode(AVLNode<V>* temp, const int& id) {
		if (temp == NULL) {
			return NULL;
		}
		if (temp->data.getKey() == id) {
			return temp;
		}
		else if (temp->data.getKey() < id) {
			return getNode(temp->right, id);
		}
		else {
			return getNode(temp->left, id);
		}
	}

	AVLNode<V>* getNode(AVLNode<V>* temp, const string& customerId, const int& flightNumber) {
		if (temp == NULL) {
			return NULL;
		}
		if (temp->data.getCustomerId() == customerId && temp->data.getFlightNum() == flightNumber) {
			return temp;
		}
		AVLNode<V>* leftResult = getNode(temp->left, customerId, flightNumber);
		if (leftResult != NULL)
			return leftResult;
		return getNode(temp->right, customerId, flightNumber);
	}

public:
	AVL() :root(NULL) {}
	void insert(V data) {
		root = insert(root, data);
	}

	bool Delete(int data) {
		bool flag = false;
		root = Delete(root, data, flag);
		return flag;
	}

	void display() {
		preOrder(root);
	}

	bool display(int id) {
		return display(root, id);
	}

	bool search(const unsigned int& id) {
		return search(root, id);
	}

	void saveData(fstream& file) {
		inOrder(root, file);
	}

	AVLNode<V>* getRoot() {
		return root;
	}

	bool updateData(int id) {
		return updateData(root, id);
	}

	AVLNode<V>* getNode(const string& customerId,const int& flightNumber) {
		return getNode(root, customerId, flightNumber);
	}

	AVLNode<V>* getNode(const int& id) {
		return getNode(root, id);
	}

};