/*
	@author Nita Eduard
	@group 30423

	Constructing the R2 multi-way tree:
	From R1 representation we construct a table, where the index represents the parent node key,
	and the values in that row represent the children's keys of that node

	This structure takes O(n) to build and takes up O(n) auxiliary memory.
	We use this intermediate structure to build the R2 representation
	because it allows us to create each node in O(1) by accessing the table index (node's key) and the values at that index(node's children)

	We sacrifice memory in favour of faster running times.

	Constructing the R3 binary-tree:
	We parse through the R2 multi-way tree and construct the R3 binary tree on the run. 
	We transform R2 into R3 as follows:
		-> the children[0] data becomes child in the binary representation (left path)
		-> the children[1:children.size()] data becomes siblings:		   (right path)
			-> the children[i + 1] becomes a sibling only to children[i]
	
	This transformation performs in O(n) by accessing the n nodes in the multi-way tree.
*/
#include <iostream>
#include <vector>

using namespace std;

class NodeR2 {
public:
	int key = -1;
	vector<NodeR2*> children;

	NodeR2(int k) {
		this->key = k;
	}
};

class NodeR3 {
public:
	int key = -1;
	NodeR3* child;
	NodeR3* sibling;

	NodeR3(int k) {
		this->key = k;
	}
};

void printR2Table(vector<vector<NodeR2*>> t) {  // print table (nodes' values start from 1) O(n)
	for (int i = 0; i < t.size(); i++) {		// table indexes are 0 based
		cout << i << "| ";						// node -> children <=> (table index + 1) -> values at that index
		for (int j = 0; j < t[i].size(); j++) {
			cout << t[i][j]->key << " ";
		}
		cout << endl;
	}
}

void generateR2Tree(vector<vector<NodeR2*>> t, NodeR2* root) {  // generates R2 multi-way tree from table O(n)
	root->children = t[root->key - 1];							// since table indexes start from 0, to access element with key n, we will 
	for (int i = 0; i < t[root->key - 1].size(); i++) {			// access the table at the n - 1 location
			generateR2Tree(t, t[root->key - 1][i]);				// then we access it's children recursively
		}
}

void generateR3Tree(NodeR3* root, NodeR2* nodeR2) {						// generates R3 binary tree from R2 tree O(n); starts with R2 tree and root generated as R3 node beforehand
	if (nodeR2->children.size() != 0) {									// R3 is binary tree so it will have only 2 children; basically left -> child and right -> sibling
		root->child = new NodeR3(nodeR2->children[0]->key);				// we generate the nodeR3 child as the first nodeR2 children
		generateR3Tree(root->child, nodeR2->children[0]);				// we go down recursively and generate only children until current node is a leaf
		NodeR3* current = root->child;									// we save current node
		for (int i = 1; i < nodeR2->children.size(); i++) {				// we parse through all its siblings in R2 representation (from 1 to nodeR2->children.size() - 1)
			current->sibling = new NodeR3(nodeR2->children[i]->key);	// create a sibling for the current node in R3 representation
			generateR3Tree(current->sibling, nodeR2->children[i]);		// go down recursively from the sibling until current node is a leaf
			current = current->sibling;									// set the current node to the sibling mentioned above 
		}																// continue the for loop that keeps creating a sibling to the current node (that is a sibling as well from now on)
	}																		 
}

void printR1Tree(vector<int> arr) {
	for (int i = 0; i < arr.size(); i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
	for (int i = 1; i <= arr.size(); i++) {
		cout << i << " ";
	}
}

void printR2Tree(NodeR2* root, int padding) {
	for (int i = 0; i < padding; i++) {
		cout << "\t";
	}
	cout << root->key;
	cout << endl;
	for (int i = 0; i < root->children.size(); i++) {
		printR2Tree(root->children[i], padding + 1);
	}
}

void printR3Tree(NodeR3* root, int padding) {
	if (root != nullptr) {
		for (int i = 0; i < padding; i++) {
			cout << "\t";
		}
		cout << root->key;
		cout << endl;
		printR3Tree(root->child, padding + 1);
		printR3Tree(root->sibling, padding);
	}
}

NodeR2* rootR2;
NodeR3* rootR3;

int main()
{
    vector<int> P{2, 7, 5, 2, 7, 7, -1, 5, 2};
    vector<vector<NodeR2*>> table;
	vector<NodeR2*> emptyVector;


    for(int i = 0; i < P.size(); i++){ // initiate empty table
        vector<NodeR2*> aux;
        table.push_back(aux);
    }

	// generate a table of parents(index) and children(values) O(n)
    for(int i = 0; i < P.size(); i++){							// go through each node in R1 representation
		if (P[i] != -1) {										// check for root
			table[P[i] - 1].push_back(new NodeR2(i + 1));		// if not root add node to parent index
		}
		else {													// else
			rootR2 = new NodeR2(i + 1);							// generate root as R2 node structure
			rootR3 = new NodeR3(i + 1);							// generate root as R3 node structure
		}			
    }

	cout << "PRINTING R1 PARENT VECTOR:\n";
	printR1Tree(P);

	cout << "\n\nPRINTING TABLE FROM WHICH R2 IS GENERATED:\n";
	printR2Table(table); 

	generateR2Tree(table, rootR2);

	cout << "\nPRINTING R2 MULTI-WAY TREE:\n";
	printR2Tree(rootR2, 0);

	generateR3Tree(rootR3, rootR2);

	cout << "\n\nPRINTING R3 BINARY TREE TREE:\n";
	printR3Tree(rootR3, 0);



    return 0;
}
