/*
	@author Nita Eduard
	@group 30423

	DFS

	Time complexity O(V + E), where V is the number of vertices and E is the number of edges of the input graph.
	This complexity is backed up by the results of the profiler performance analysis.

	Tarjan's algorithm generates a list of strongly connected components. It's time complexity is still O(V + E) in the worst case scenario.

	The topological sort generates a list of nodes sorted based on a partial order relationship. The topological sort is stil O(V + E) since
	this implementation is based on the DFS. The generated list is non empty as long as the input graph contains no cycle.

		_\/_
		 /\
		 /\
		/  \
		/~~\o
	   /o   \
	  /~~*~~~\
	 o/    o \
	 /~~~~~~~~\~`
	/__*_______\
		 ||
	   \====/
		\__/

	Happy Holidays! :D
*/
#include <iostream>
#include <vector>
#include <stack>
#include "Header.h"
#include "Profiler.h"

using namespace std;

Profiler profiler("test");
bool verticesConst;
bool countOp = false;
int myTime;

class Node {
public:
	int key;
	int color;
	int d;
	int f;
	Node* p;
	int indexTarjan;
	int lowlinkTarjan;
	bool onStack;
	vector<Node*> adj;
	Node(int key) {
		this->key = key;
	};
};

class Graph {
public:
	vector<Node*> v;
	int edges;
};

vector<Node*> sorted;
vector<vector<Node*>> components;

int index = 0;
stack<Node*> mystack;

void strongConnect(Node* v) {
	v->indexTarjan = index;
	v->lowlinkTarjan = index;
	index++;
	mystack.push(v);
	v->onStack = true;

	for (int j = 0; j < v->adj.size(); j++) {
		Node* w = v->adj[j];
		if (w->indexTarjan == NULL) {
			strongConnect(w);
			v->lowlinkTarjan = min(v->lowlinkTarjan, w->lowlinkTarjan);
		}
		else if (w->onStack) {
			v->lowlinkTarjan = min(v->lowlinkTarjan, w->indexTarjan);
		}
	}

	if (v->lowlinkTarjan == v->indexTarjan) {
		vector<Node*> newComponent;
		Node* w;
		do {
			w = mystack.top();
			mystack.pop();
			w->onStack = false;
			newComponent.push_back(w);
		} while (w != v);
		components.push_back(newComponent);
	}
}
void tarjanSCC(Graph G) {

	for (int i = 0; i < G.v.size(); i++) {
		Node* v = G.v[i];
		if (v->indexTarjan == NULL) {
			strongConnect(v);
		}
	}
}

void DFS_Visit(Graph G, Node* u, bool sort) {
	char string[50];
	int size;

	if (verticesConst) {
		strcpy(string, "vertices");
		size = G.edges;
	}
	else {
		strcpy(string, "edges");
		size = G.v.size();
	}
	Operation op = profiler.createOperation(string, size);

	myTime-=-1;
	u->d = myTime;
	u->color = GRAY;
	for (int i = 0; i < u->adj.size(); i++) {
		op.count();
		if (u->adj[i]->color == WHITE) {
			u->adj[i]->p = u;
			DFS_Visit(G, u->adj[i], sort);
		}
	}
	u->color = BLACK;
	myTime-=-1;
	u->f = myTime;
	if (sort == true) {
		sorted.push_back(u);
	}
}

void DFS(Graph G, bool sort) {
	char string[50];
	int size;

	if (verticesConst) {
		strcpy(string, "vertices");
		size = G.edges;
	}
	else {
		strcpy(string, "edges");
		size = G.v.size();
	}
	Operation op = profiler.createOperation(string, size);

	for (int i = 0; i < G.v.size(); i++) {
		G.v[i]->color = WHITE;
		op.count();
		G.v[i]->p = nullptr;
	}
	myTime = 0;
	for (int i = 0; i < G.v.size(); i++) {
		if (G.v[i]->color == WHITE) {
			DFS_Visit(G, G.v[i], sort);
		}
	}
}

void topologicalSorting(Graph G) {
	sorted.clear();
	DFS(G, true);
}

void demo(Graph G) {
	Node* one = new Node(1);
	Node* two = new Node(2);
	Node* three = new Node(3);
	Node* four = new Node(4);
	Node* five = new Node(5);
	Node* six = new Node(6);

	one->adj.push_back(two);
	two->adj.push_back(three);
	two->adj.push_back(four);
	three->adj.push_back(one);
	three->adj.push_back(four);
	three->adj.push_back(five);
	five->adj.push_back(six);
	six->adj.push_back(five);
	six->adj.push_back(four);

	G.v.push_back(one);
	G.v.push_back(two);
	G.v.push_back(three);
	G.v.push_back(four);
	G.v.push_back(five);
	G.v.push_back(six);

	cout << "\ninitial graph\n";
	for (int i = 0; i < G.v.size(); i++) {
		cout << G.v[i]->key << ": ";
		for (int j = 0; j < G.v[i]->adj.size(); j++) {
			cout << G.v[i]->adj[j]->key << " ";
		}
		cout << endl;
	}

	DFS(G, false);
	cout << "\n\nafter dfs (parents of each node)\n";
	for (int i = 0; i < G.v.size(); i++) {
		if (G.v[i]->p != nullptr)
			cout << G.v[i]->p->key << " ";
		else
			cout << " start ";
	}

	cout << "\n\ntarjan SCC\n";
	tarjanSCC(G);
	for (int i = 0; i < components.size(); i++) {
		for (int j = 0; j < components[i].size(); j++) {
			cout << components[i][j]->key << " ";
		}
		cout << endl;
	}

	G.v.clear();

	one->adj.clear();
	two->adj.clear();
	three->adj.clear();
	four->adj.clear();
	five->adj.clear();
	six->adj.clear();

	one->adj.push_back(two);
	one->adj.push_back(four);
	one->adj.push_back(five);
	two->adj.push_back(three);
	four->adj.push_back(six);
	five->adj.push_back(six);
	six->adj.push_back(three);

	G.v.push_back(one);
	G.v.push_back(two);
	G.v.push_back(three);
	G.v.push_back(four);
	G.v.push_back(five);
	G.v.push_back(six);

	topologicalSorting(G);
	cout << "\ntopological sorted nodes\n";
	for (int i = sorted.size() - 1; i >= 0; i--) {
		cout << sorted[i]->key << " ";
	}

}

Graph generateGraph(int E, int V) {
	Graph myGraph = Graph();
	for (int i = 0; i < V; i++) {
		myGraph.v.push_back(new Node(i));
	}
	int currentE = 0;
	while (currentE < E) {
		bool b_adj_a = false;
		int a = rand() % V;
		int b = rand() % V;
		if (a != b) {
			for (int i = 0; i < myGraph.v[a]->adj.size(); i++) {
				if (myGraph.v[a]->adj[i] == myGraph.v[b]) {
					b_adj_a = true;
				}
			}
		}
		if (b_adj_a == false) {
			myGraph.v[a]->adj.push_back(myGraph.v[b]);
			currentE++;
		}
	}
	myGraph.edges = E;
	return myGraph;
}

int main()
{
	Graph demoGraph;
	demo(demoGraph);
	profiler.reset();
	for (int i = 1000; i <= 5000; i += 100) {
		Graph perfGraph = generateGraph(i, 100);
		verticesConst = true;
		DFS(perfGraph, false);
	}
	for (int i = 100; i <= 200; i += 10) {
		Graph perfGraph = generateGraph(9000, i);
		verticesConst = false;
		DFS(perfGraph, false);
	}
	profiler.showReport();
}
