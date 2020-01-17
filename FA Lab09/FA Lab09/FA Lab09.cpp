/*
	@author Nita Eduard
	@group 30423

	This assignment requires us to implement disjoint-set operations using the tree representation as well as
	implementing Kruskal's minimum spanning tree algorithm using the aforementioned data structure.

	The disjoint-set operations are as follows:

	makeSet
		this functions generates a set containing only the element passed as a parameter
	findSet
		this function returns the representative of the set from which the parameter belongs to
	makeUnion
		this function combines the two sets from which the parameters belong to

	To test these operations, this program presents 3 demos:
		-> one that first creates 10 sets containing only one distinct number in the range between 0 and 9,
			which then keeps merging the sets until they are separated into two distinct ones: Odd and Even

		-> the second one also creates 10 sets containing only one disting number in the range between 0 and 9,
			but this time, it merges them into 3 distinct sets based on their remainder class for 3 (% 3 result)

		-> the final demo implements an example from the Introduction to algorithms textbook (page 563),
 			the results after each operation are shown by printing each node's set representative

	Kruskal's algorithm can be implemented using this data structure, 
	resulting in a running time of O(E log E) (mostly due to the sorting of the edges) which can also be expressed as O(E log V)

	A demo for kruskal's algorithm is provided in this program, which generates a random graph and prints it's content, 
	then this graph is passed as an input to the algorithm. After the algorithm is finished, the program prints the output graph content.


*/

#include <iostream>
#include "Profiler.h"
using namespace std;

Profiler profiler("kruskal");

class Node {
public:
	int key;
	int rank;
	Node* p; // parent
	Node(int k) {
		this->key = k;
	}
};
class Edge {
public:
	int weight;
	Node* u;
	Node* v;
	Edge(Node* u, Node* v, int w) {
		this->u = u;
		this->v = v;
		this->weight = w;
	}
};
class Graph {
public:
	vector<Node*> nodes;
	vector<Edge*> edges;
};

vector<Node*> testNodes;
int currentInputSize;

void makeSet(Node* x) {
	profiler.countOperation("makeSet", currentInputSize);
	profiler.countOperation("all", currentInputSize);

	x->p = x;
	x->rank = 0;
}
void link(Node* x, Node* y) {
	profiler.countOperation("link", currentInputSize);
	profiler.countOperation("all", currentInputSize);

	if (x->rank > y->rank) {
		y->p = x;
		profiler.countOperation("link", currentInputSize);
		profiler.countOperation("all", currentInputSize);
	}
	else {
		x->p = y;

		profiler.countOperation("link", currentInputSize);
		profiler.countOperation("link", currentInputSize);

		profiler.countOperation("all", currentInputSize);
		profiler.countOperation("all", currentInputSize);

		if (x->rank == y->rank) {
			y->rank++;
		}
	}
}
Node* findSet(Node* x) {
	profiler.countOperation("findSet", currentInputSize);
	profiler.countOperation("all", currentInputSize);

	if (x != x->p) {
		x->p = findSet(x->p);
		profiler.countOperation("findSet", currentInputSize);
		profiler.countOperation("all", currentInputSize);
	}
	return x->p;
}
void makeUnion(Node* x, Node* y) { // renamed to makeUnion due to name conflict
	link(findSet(x), findSet(y));
}
void printSet(Node* x) {

}
void oddEvenDemo() {
	for (int i = 0; i < 10; i++) {
		testNodes.push_back(new Node(i));
		makeSet(testNodes[i]);
	}

	Node* evenSet = testNodes[0];
	Node* oddSet = testNodes[1];
	for (int i = 2; i < 10; i++) {
		if (i % 2 == 0) {
			makeUnion(testNodes[i], evenSet);
		}
		else {
			makeUnion(testNodes[i], oddSet);
		}
	}

	for (int i = 0; i < 10; i++) {
		cout << i << " is ";
		if (findSet(testNodes[i])->key) {
			cout << "Odd";
		}
		else {
			cout << "Even";
		}
		cout << endl;
	}

	testNodes.clear();
}
void remainderClassesDemo() {
	for (int i = 0; i < 10; i++) {
		testNodes.push_back(new Node(i));
		makeSet(testNodes[i]);
	}

	// remainders for the % 3 operation
	Node* remainderZero = testNodes[0];
	Node* remainderOne = testNodes[1];
	Node* remainderTwo = testNodes[2];

	for (int i = 3; i < 10; i++) {
		switch (i % 3) {
		case 0:
			makeUnion(testNodes[i], remainderZero);
			break;
		case 1:
			makeUnion(testNodes[i], remainderOne);
			break;
		case 2:
			makeUnion(testNodes[i], remainderTwo);
			break;
		}
	}

	cout << endl;
	for (int i = 0; i < 10; i++) {
		cout << i << " % 3 is from";
		switch (findSet(testNodes[i])->key) {
		case 0:
			cout << " remainder class Z0";
			break;
		case 1:
			cout << " remainder class Z1";
			break;
		case 2:
			cout << " remainder class Z2";
			break;
		}
		cout << endl;
	}
	testNodes.clear();
}
void printCormenSets() {
	for (int i = 0; i < 10; i++) {
		cout << (char)findSet(testNodes[i])->key << " ";
	}
	cout << endl;
} 
void cormenDemo() {
	cout << endl; 
	for (int i = 'a'; i <= 'j'; i++) {
		testNodes.push_back(new Node(i));
		makeSet(testNodes[i - 97]);
	}		

	printCormenSets();

	makeUnion(testNodes['b' - 97], testNodes['d' - 97]);
	printCormenSets();

	makeUnion(testNodes['e' - 97], testNodes['g' - 97]);
	printCormenSets();

	makeUnion(testNodes['a' - 97], testNodes['c' - 97]);
	printCormenSets();

	makeUnion(testNodes['h' - 97], testNodes['i' - 97]);
	printCormenSets();

	makeUnion(testNodes['a' - 97], testNodes['b' - 97]);
	printCormenSets();

	makeUnion(testNodes['e' - 97], testNodes['f' - 97]);
	printCormenSets();

	makeUnion(testNodes['b' - 97], testNodes['c' - 97]);
	printCormenSets();
}

bool compare(Edge* a, Edge* b) {
	return (a->weight < b->weight);
}

Graph* Kruskal(Graph* G) {
	Graph* A = new Graph();
	A->nodes = G->nodes;
	for (int i = 0; i < G->nodes.size(); i++) {
		makeSet(G->nodes[i]);
	}
	sort(G->edges.begin(), G->edges.end(), compare);
	for (int i = 0; i < G->edges.size(); i++) {
		if (findSet(G->edges[i]->u) != findSet(G->edges[i]->v)) {
			A->edges.push_back(G->edges[i]);
			makeUnion(G->edges[i]->u, G->edges[i]->v);
		}
	}
	return A;

}

void graphDemo() {
	int edgesV[10];
	int nodesV[10];
	Graph* myGraph = new Graph();
	for (int i = 0; i < 5; i++) {
		myGraph->nodes.push_back(new Node(i));
	}
	for (int i = 0; i < 4; i++) {
		FillRandomArray(edgesV, 5, 1, 10);
		FillRandomArray(nodesV, 5, 0, 4, true);
		for (int j = 0; j < 4; j++) { // generates 4 edges
			myGraph->edges.push_back(new Edge(myGraph->nodes[nodesV[j]], myGraph->nodes[nodesV[j + 1]], edgesV[j]));
		}
	}
	cout << "NODES: " << endl;
	for (int i = 0; i < myGraph->nodes.size(); i++) {
		cout << myGraph->nodes[i]->key << " ";
	}
	cout << endl << "EDGES:" << endl;
	for (int i = 0; i < myGraph->edges.size(); i++) {
		cout << "(" << myGraph->edges[i]->u->key << "," << myGraph->edges[i]->v->key << ") - " << myGraph->edges[i]->weight << endl;
	}
	cout << endl << "AFTER KRUSKAL: " << endl;
	Graph* kruskalGraph = Kruskal(myGraph);
	cout << "NODES: " << endl;
	for (int i = 0; i < kruskalGraph->nodes.size(); i++) {
		cout << kruskalGraph->nodes[i]->key << " ";
	}
	cout << endl << "EDGES:" << endl;
	for (int i = 0; i < kruskalGraph->edges.size(); i++) {
		cout << "(" << kruskalGraph->edges[i]->u->key << "," << kruskalGraph->edges[i]->v->key << ") - " << kruskalGraph->edges[i]->weight << endl;
	}
}

int main()
{
	oddEvenDemo();
	remainderClassesDemo();
	cormenDemo(); 
	graphDemo();
	
	int edgeValues[10001];
	int nodeBuffer[10001]; // buffer for generating edges by nodes
	for (int i = 100; i <= 10000; i += 100) {
		currentInputSize = i;
		Graph* myGraph = new Graph();
		for (int j = 0; j < i; j++) {
			myGraph->nodes.push_back(new Node(j));
		}
		for (int k = 0; k < 4; k++) { 
			FillRandomArray(edgeValues, i, 1, 1000);
			FillRandomArray(nodeBuffer, i, 0, i - 1, true); 
			for (int j = 0; j < i - 1; j++) { // generates 4*(i - 1) edges
				myGraph->edges.push_back(new Edge(myGraph->nodes[nodeBuffer[j]], myGraph->nodes[nodeBuffer[j + 1]], edgeValues[j]));
			}
		}
		for (int k = 0; k < 4; k++) {
			FillRandomArray(edgeValues, 4, 1, 1000);
			FillRandomArray(nodeBuffer, 4, 0, i - 1, true);
			for (int j = 0; j < 4; j++) { // generates 4 edges
				myGraph->edges.push_back(new Edge(myGraph->nodes[nodeBuffer[j]], myGraph->nodes[nodeBuffer[j + 1]], edgeValues[j]));
			}
		}
		Graph* newGraph = Kruskal(myGraph);
	}
	profiler.createGroup("Operations", "makeSet", "link", "findSet");
	profiler.showReport();


}
