#include <iostream>
#include <vector>

/* @author Vladyslav Depeshko 26.04.2021
 * @brief set implementation
 */

using namespace std;

template <typename T>
class Set {
private:
	typedef struct Node_s {
		T data;
		struct Node_s *left;
		struct Node_s *right;
	} Node_t;

	Node_t *createNode(T data) {
		Node_t *node = new Node_t;
		node->data  = data;
		node->left  = nullptr;
		node->right = nullptr;
		return node;
	}

	Node_t *binaryTree = nullptr;

	void __delete__(Node_t **root) {
		if (*root != nullptr) {
			if ((*root)->left != nullptr) {
				__delete__(&((*root)->left));
			}
			if ((*root)->right != nullptr) {
				__delete__(&((*root)->right));
			}
			delete (*root);
			*root = nullptr;
		} 
	}

	void printInSortedOrder(Node_t **root, bool inlineFlag) {
		if (*root != nullptr) { 
			printInSortedOrder(&((**root).left), inlineFlag); 
			cout << (*root)->data;
			if (inlineFlag) {cout << " ";}
			else {cout << endl;}
			printInSortedOrder(&((**root).right), inlineFlag); 
		}
	}

	void push(Node_t **root, T data) {
		if (*root == nullptr) {
			*root = createNode(data);
		}
		else if (data < (*root)->data) {
			if ((*root)->left == nullptr) {
				Node_t *node = createNode(data);
				(*root)->left = node;
			}
			else {
				push(&((*root)->left), data);
			}
		}
		else if (data > (*root)->data) {
			if ((*root)->right == nullptr) {
				Node_t *node = createNode(data);
				(*root)->right = node;
			}
			else {
				push(&((*root)->right), data);
			}
		}
	}

	Node_t *search(Node_t *root, T data) {
		if (root == nullptr) {
			return 0;
		}
		Node_t *node = root;
		vector<Node_t *> stack;
		stack.push_back(node);

		while(stack.empty() == false) {
			node = stack.back();
			if (node->data == data) {
				return node;
			}
			stack.pop_back();
			if (node->right != nullptr) {
				stack.push_back(node->right);
			}
			if (node->left != nullptr) {
				stack.push_back(node->left);
			}
		}
		return nullptr;
	}

	// recursive func for deleting elem from tree
	void deletElemWrapper(Node_t **newTree, Node_t *oldTree, T data) {
		if (oldTree != nullptr) {
			if (oldTree->data != data) {
				push(newTree, oldTree->data);
			}
			deletElemWrapper(newTree, oldTree->left, data); 
			deletElemWrapper(newTree, oldTree->right, data); 
		}
	}

	// delete elem from tree
	void deleteElem(Node_t **root, T data) {
		Node_t *newTree = nullptr;
		if (*root != nullptr) {
			deletElemWrapper(&newTree, *root, data);
			__delete__(root);
			*root = newTree;
		}
	}

	int treeSize() {
		int s = 0;
		if (binaryTree == nullptr) {return s;}
		Node_t *node = binaryTree;
		vector<Node_t *> stack;
		stack.push_back(node);
		s++;
		while(stack.empty() == false) {
			node = stack.back();
			stack.pop_back();
			if (node->right != nullptr) {
				stack.push_back(node->right);
				s++;
			}
			if (node->left != nullptr) {
				stack.push_back(node->left);
				s++;
			}
		}
		return s;
	}

	// returns vector of data, that is keeping in binary tree.
	vector<T> _returnVectorOfData(Node_t *root) {
		vector<T> res;
		if (binaryTree == nullptr) {return res;}
		Node_t *node = binaryTree;
		vector<Node_t *> stack;
		stack.push_back(node);

		while(stack.empty() == false) {
			node = stack.back();
			res.push_back(node->data);
			stack.pop_back();
			if (node->right != nullptr) {
				stack.push_back(node->right);
			}
			if (node->left != nullptr) {
				stack.push_back(node->left);
			}
		}
		return res;
	}

public:
	~Set() {__delete__(&binaryTree);}

	void add(T data) {
		push(&binaryTree, data);
	}

	void del(T data) {
		deleteElem(&binaryTree, data);
	}

	void show() {
		printInSortedOrder(&binaryTree, 0);
	}

	void showInline() {
		printInSortedOrder(&binaryTree, 1);
		cout << endl;
	}

	bool in(T data) {
		if (search(binaryTree, data) == nullptr) {return 0;}
		return 1;
	}

	bool empty() {
		if (binaryTree == nullptr) {return 1;}
		return 0;
	}

	int size() {return treeSize();}

	vector<T> returnVectorOfData() {return _returnVectorOfData(binaryTree);}

	// creates set with items, which are the different in set1 and set2
	Set<T> operator+(const Set<T> &obj) {
		Set<T> &ref = const_cast<Set<T>&>(obj);
		vector<T> objElems  = ref.returnVectorOfData();
		vector<T> currElems = this->returnVectorOfData();
		Set<T> newSet;
		for(T i: objElems) {if (in(i) == false) {newSet.add(i);}}
		for(T i: currElems) {newSet.add(i);}
		return newSet;
	};

	// creates set with items, which are the same in set1 and set2
	Set<T> operator*(const Set<T> &obj) {
		Set<T> &ref = const_cast<Set<T>&>(obj);
		vector<T> objElems  = ref.returnVectorOfData();
		Set<T> newSet;
		for(T i: objElems) {if (in(i) == true) {newSet.add(i);}}
		return newSet;
	};
};

template <typename T>
ostream &operator << (ostream &out, const Set<T> &s) {
	Set<T> &ref = const_cast<Set<T>&>(s);
	ref.showInline();
	return out;
}


int main() {
	Set<int> s;
	s.add(2);
	s.add(4);
	s.add(1);
	Set<int> s1;
	s1.add(3);
	s1.add(4);
	s1.add(5);
	s1.add(510);

	Set<int> s3 = s + s1;
	cout << s3 << endl;
}







