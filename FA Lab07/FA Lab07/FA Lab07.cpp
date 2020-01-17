/*
	@author Nita Eduard
	@group 30423

	Order statistic trees

	Build-tree
	Time complexity: O(n)

	To build the tree, this implementation takes as an input a sorted array and uses Divide et Impera approach.
	First, it gets the middle of the input array and makes it the root of the tree.
	Then, it recursively does the same for the left and right half of the array.
		->gets the middle of the left half of the array and makes it the left child of the root
		->same for right half
	This function also takes care of initialising the size field of each node (OST characteristic)
	using a post-order implementation. 

	OS Select
	Time complexity: O(log h)
	
	This function selects the i'th smallest element in the tree. (this implementation sets the smallest element's index as 0)
	Since we will need to find the smallest element, the algorithm focuses on the left parts of a binary tree.
	x->left->size tells us the number of nodes in that part of the subtree. If the number is less, 
	then our i, there is no point in searching there, so we go on the right.
	If the size of the left subtree is greater, that means the desired number is in the left part of our tree.
	The element is found once x->left->size (r) is equal to i.

	OS Delete
	Time complexity: O(log h)

	This implementation deletes the node with a specified key. Here, we use it in conjunction with
	the OS Select operation mentioned above, since it allows us to generate(select) non repeating numbers.
	While searching for the desired node, we decrement the size of the nodes in our path.
	When we find it, there can be a couple of situations that we must deal with:
	- node is a left -> just delete it
	- node has 1 children -> delete node and replace it with child
	- node has 2 children -> copy contents of the smallest node on the node's right path. Delete copied node.

*/

#include <iostream>
#include <vector>
#include "Profiler.h"
#include <iomanip>    
using namespace std;

int inputSize = 0;

Profiler profiler = Profiler("test");

class Node {
	public:
		int key;
		int size;
		Node* right;
		Node* left;

		Node(int keyData) {
			key = keyData;
			size = 0;
			right = nullptr;
			left = nullptr;
		}
};


Node* buildTree(vector<int> arr, int start, int end) {

	Operation bOp = profiler.createOperation("buildOperations", inputSize);
	bOp.count();
	if (start > end) {
		return nullptr;
	}

	bOp.count();
	int mid = (start + end) / 2;
	Node* root = new Node(arr[mid]);

	bOp.count(2);
	root->left = buildTree(arr, start, mid - 1);
	root->right = buildTree(arr, mid + 1, end);

	if (root->left != nullptr && root->right == nullptr) {
		root->size = root->left->size + 1;
		bOp.count();
	}else
	if (root->right != nullptr && root->left == nullptr) {
		root->size = root->right->size + 1;
		bOp.count();
	}
	else 
	if(root->right != nullptr && root->left != nullptr){
		root->size = root->left->size + root->right->size + 1;
		bOp.count();
	}
	else {
		root->size = 1;
	}

	return root;
}

class Tree{
	public:
	Node* root;
	Tree(const vector<int> arr) {
		root = buildTree(arr, 0, arr.size() - 1);
	}
};

Node* minValueNode(Node* start, Operation dOp) {
	Node* current = start;
	while (current != nullptr && current->left != nullptr) {
		current = current->left;
		dOp.count();
	}
	return current;
}

Node* OSDelete(Node* root, int key) {
	Operation dOp = profiler.createOperation("deleteOperations", inputSize);
	if (root == nullptr) {
		return root;
	} 
	root->size--;

	dOp.count();
	if (key < root->key) {
		dOp.count();
		root->left = OSDelete(root->left, key);
	}
	else if (key > root->key) {
		dOp.count(2);
		root->right = OSDelete(root->right, key);
	}
	else {
		if (root->left == nullptr) {
			Node* aux = root->right;
			free(root);
			return aux;
		}
		else if (root->right == nullptr) {
			Node* aux = root->left;
			free(root);
			return aux;
		}

		dOp.count(2);
		Node* aux = minValueNode(root->right, dOp);
		root->key = aux->key;
		root->right = OSDelete(root->right, aux->key);
	}
	return root;
}

void postorderKey(Node* p, int indent = 0)
{
	if (p != NULL) {
		if (p->right) {
			postorderKey(p->right, indent + 4);
		}
		if (indent) {
			std::cout << std::setw(indent) << ' ';
		}
		if (p->right) std::cout << " /\n" << std::setw(indent) << ' ';
		std::cout << p->key << "\n ";
		if (p->left) {
			std::cout << std::setw(indent) << ' ' << " \\\n";
			postorderKey(p->left, indent + 4);
		}
	}
}
void postorderSize(Node* p, int indent = 0)
{
	if (p != NULL) {
		if (p->right) {
			postorderSize(p->right, indent + 4);
		}
		if (indent) {
			std::cout << std::setw(indent) << ' ';
		}
		if (p->right) std::cout << " /\n" << std::setw(indent) << ' ';
		std::cout << p->size << "\n ";
		if (p->left) {
			std::cout << std::setw(indent) << ' ' << " \\\n";
			postorderSize(p->left, indent + 4);
		}
	}
}

Node* OSSelect(Node* x, int i, bool del) {    // returns the i'th element (zero-indexed) of the elements in myTree
	Operation sOp = profiler.createOperation("selectOperations", inputSize);
	int r;
	if (x == nullptr) {
		//cout << "Tree unitialised or i'th element out of bounds ";
		return new Node(-1);
	}
	if (x->left == nullptr) {
		r = 0;
	}
	else {
		r = x->left->size;
		if (!del)
			sOp.count();
	}

	if (i == r) {
		if (!del)
			sOp.count();
		return x;
	}
	else if (i < r) {
		if (!del)
			sOp.count();
		return OSSelect(x->left, i, del);
	}
	else{
		if (!del)
			sOp.count();
		return OSSelect(x->right, i - r - 1, del);
	}
}


int main()
{
	cout << "Testing tree build procedures:" << endl;
	int myNodes[10];
	int n = 10;
	vector<int> myData;
	FillRandomArray(myNodes, n, 1, 10, true, 1);

	myData.assign(myNodes, myNodes + 10);
	Tree* myTree = new Tree(myData);

	cout << "Testing building tree from 1 to 10:" << endl;
	postorderKey(myTree->root);
	cout << "Testing size field of each node: " << endl;
	postorderSize(myTree->root);
	for(int i = 0; i < 10; i++)
	cout << OSSelect(myTree->root, i, true)->key << endl;
	postorderKey(myTree->root);

	cout << "\ndeleting index 2\n";
	myTree->root=OSDelete(myTree->root, OSSelect(myTree->root, 2, true)->key);
	cout << "\nkey\n";
	postorderKey(myTree->root);
	cout << "\nsize\n";
	postorderSize(myTree->root);

	cout << "\ndeleting index 4\n";
	myTree->root=OSDelete(myTree->root, OSSelect(myTree->root, 4, true)->key);
	cout << "\nkey\n";
	postorderKey(myTree->root);
	cout << "\nsize\n";
	postorderSize(myTree->root);

	cout << "\ndeleting index 1\n";
	myTree->root=OSDelete(myTree->root, OSSelect(myTree->root, 1, true)->key);
	cout << "\nkey\n";
	postorderKey(myTree->root);
	cout << "\nsize\n";
	postorderSize(myTree->root);


	int myInputData[10001];
	int numberOfElementsRemaining;
	for (int i = 0; i < 5; i++) {
		for (int j = 100; j <= 10000; j+=100) {
			inputSize = j;

			FillRandomArray(myInputData, j, 1, j, true, 0);
			myData.clear();
			myData.assign(myInputData, myInputData + j);
			Tree* myTree = new Tree(myData);

			numberOfElementsRemaining = j;

			while(numberOfElementsRemaining >= 0) {
				int index = rand() % (numberOfElementsRemaining + 1);
				OSSelect(myTree->root, index, false);
				numberOfElementsRemaining--;
			}

			numberOfElementsRemaining = j;

			while (numberOfElementsRemaining >= 0) {
				int index = rand() % (numberOfElementsRemaining + 1);
				myTree->root = OSDelete(myTree->root, OSSelect(myTree->root, index, true)->key);
				numberOfElementsRemaining--;
			}
		}
	}
	profiler.divideValues("deleteOperations", 5);
	profiler.divideValues("selectOperations", 5);
	profiler.divideValues("buildOperations", 5);
	profiler.createGroup("Operations OST", "deleteOperations", "selectOperations", "buildOperations");
	profiler.showReport();
}
