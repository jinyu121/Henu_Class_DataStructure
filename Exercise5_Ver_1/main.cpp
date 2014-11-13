/*
ID: jinyu121
PROG:
LANG: C++
EDIT: 1.0
*/

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdio>
#include <cmath>
#include <queue>

#define oo 168430090

using namespace std;

/* Something else... */
bool *visited;

/* Edge */
struct GraphEdge {
	int point;  // I used to call it 'Y'
	int edgeValue;  // And this is 'V'
	GraphEdge* next;
};

/* Vertex */
struct GraphVertex {
	int vertexValue;
	GraphEdge* edgeStart;
};

/* Graph */
struct Graph {
	int numOfEdge, numOfVertex;
	GraphVertex* vertex;
};
/* Prim */
struct PriQueStruct {
	int value;
	int x;
	int y;
	bool operator() ( const PriQueStruct a , const PriQueStruct b ) const {
		return a.value > b.value ;
	}
};
void __addEdge ( Graph &graph, int x, int y, int v ) {
	GraphEdge* newEdge = new GraphEdge;
	newEdge->edgeValue = v;
	newEdge->point = y;
	newEdge->next = graph.vertex[x].edgeStart;
	graph.vertex[x].edgeStart = newEdge;
}

void GraphInit ( Graph &graph ) {
	int x, y, v;
	freopen ( "graphBuild.in", "r", stdin );
	/* Input the number of Vertex and Edge  */
	cin >> graph.numOfVertex >> graph.numOfEdge;
	graph.vertex = new GraphVertex[graph.numOfVertex + 1];
	/* Initialize ??!!! OMG! */
	memset ( graph.vertex, 0, sizeof ( GraphVertex ) * ( graph.numOfVertex + 1 ) );

	/* input the all edges */
	for ( int i = 1; i <= graph.numOfEdge ; i++ ) {
		cin >> x >> y >> v;
		__addEdge ( graph, x, y, v );
		__addEdge ( graph, y, x, v );
	}

	fclose ( stdin );
}

void __graphDFS ( Graph g, int root ) {
	/* Visit it */
	cout << root << " ";
	/* Mark it */
	visited[root] = true;

	/* Continue DFS */
	for ( GraphEdge *e = g.vertex[root].edgeStart; e ; e = e->next ) {
		if ( !visited[e->point] ) {
			__graphDFS ( g, e->point );
		}
	}
}

void GraphDFS ( Graph graph ) {
	/* Initialize the array visited */
	visited = new bool[graph.numOfVertex + 1];
	memset ( visited, false, sizeof ( bool ) * ( graph.numOfVertex + 1 ) );

	for ( int i = 1; i <= graph.numOfVertex ; i++ ) {
		if ( !visited[i] ) {
			__graphDFS ( graph, i );
		}
	}
}

void __graphBFS ( Graph g, int root ) {
	queue<int> iQueue;
	iQueue.push ( root );
	visited[root] = true;

	while ( !iQueue.empty() ) {
		int y = iQueue.front();
		cout << y << " ";
		iQueue.pop();

		for ( GraphEdge *e = g.vertex[y].edgeStart; e ; e = e->next ) {
			if ( !visited[e->point] ) {
				visited[e->point] = true;
				iQueue.push ( e->point );
			}
		}
	}
}

void GraphBFS ( Graph graph ) {
	/* Initialize the array visited */
	visited = new bool[graph.numOfVertex + 1];
	memset ( visited, false, sizeof ( bool ) * ( graph.numOfVertex + 1 ) );

	for ( int i = 1; i <= graph.numOfVertex ; i++ ) {
		if ( !visited[i] ) {
			__graphBFS ( graph, i );
		}
	}
}

/* Prim*/
void GraphPrim ( Graph graph ) {
	PriQueStruct temp, tempHead;
	/* Initialize the array visited */
	visited = new bool[graph.numOfVertex + 1];
	memset ( visited, false, sizeof ( bool ) * ( graph.numOfVertex + 1 ) );
	/* To find the minmum cost, i use the priority queue */
	priority_queue< PriQueStruct, vector<PriQueStruct>, PriQueStruct > iQueue;

	for ( GraphEdge *e = graph.vertex[1].edgeStart; e ; e = e->next ) {
		temp.value = e->edgeValue;
		temp.x = 1;
		temp.y = e->point;
		iQueue.push ( temp );
		visited[1] = true;
	}

	while ( !iQueue.empty() ) {
		tempHead = iQueue.top();
		iQueue.pop();

		if ( !visited[tempHead.y] ) {
			visited[tempHead.y] = true;
			cout << tempHead.x << "->" << tempHead.y << ":" << tempHead.value << endl;

			for ( GraphEdge *e = graph.vertex[tempHead.y].edgeStart; e ; e = e->next ) {
				temp.value = e->edgeValue;
				temp.x = tempHead.y;
				temp.y = e->point;
				iQueue.push ( temp );
			}
		}
	}
}

/* Kruscal */
int __getFather ( int* f, int root ) {
	if ( f[root] != root ) {
		f[root] = __getFather ( f, f[root] );
	}

	return f[root];
}
void Kruscal ( Graph graph ) {
	// initialization
	int f[graph.numOfVertex + 1];

	for ( int i = 0; i <= graph.numOfVertex ; i++ ) {
		f[i] = i;
	}

	/* To find the minmun cost of the edges, I use the Priority queue.  */
	priority_queue< PriQueStruct, vector<PriQueStruct>, PriQueStruct > iQueue;

	/* Put all the edges into the priority queue */
	for ( int i = 1; i <= graph.numOfVertex ; i++ ) {
		for ( GraphEdge *e = graph.vertex[i].edgeStart; e ; e = e->next ) {
			PriQueStruct temp;
			temp.value = e->edgeValue;
			temp.x = i;
			temp.y = e->point;
			iQueue.push ( temp );
		}
	}

	int totalEdge = 0;

	for ( ; totalEdge < graph.numOfVertex - 1 && !iQueue.empty(); ) {
		PriQueStruct tHead = iQueue.top();
		iQueue.pop();

		if ( __getFather ( f, tHead.x ) != __getFather ( f, tHead.y ) ) {
			cout << tHead.x << "->" << tHead.y << ":" << tHead.value << endl;
			/* Merge the two vertex */
			f[__getFather ( f, tHead.y )] = __getFather ( f, tHead.x );
			totalEdge++;
		}
	}
}
/* Dijkstra */
void Dijkstra ( Graph graph, int source ) {
	int dis[graph.numOfVertex + 1];
	bool used[graph.numOfVertex + 1];
	memset ( dis, 10, sizeof ( dis ) );
	memset ( used, false, sizeof ( used ) );
	dis[source] = 0;
	used[source] = true;

	/* Record default length */
	for ( GraphEdge *e = graph.vertex[source].edgeStart; e ; e = e->next ) {
		dis[e->point] = e->edgeValue;
	}

	for ( int i = 1; i <= graph.numOfVertex ; i++ ) {
		int minmin = oo;
		int position = 0;

		for ( int x = 1; x <= graph.numOfVertex ; x++ ) {
			if ( !used[x] && dis[x] < minmin ) {
				minmin = dis[x];
				position = x;
			}
		}

		used[position] = true;

		for ( GraphEdge *e = graph.vertex[position].edgeStart; e ; e = e->next ) {
			if ( !used[e->point] ) {
				dis[e->point] = min ( dis[e->point], dis[position] + e->edgeValue );
			}
		}
	}

	for ( int i = 1; i <= graph.numOfVertex ; i++ ) {
		cout << source << "->" << i << ":" << dis[i] << endl;
	}
}
/* SPFA */
void SPFA ( Graph graph, int source ) {
	int dis[graph.numOfVertex + 1];
	bool used[graph.numOfVertex + 1];
	memset ( dis, 10, sizeof ( dis ) );
	memset ( used, false, sizeof ( used ) );
	dis[source] = 0;
	used[source] = true;
	queue<int> iQueue;
	iQueue.push ( source );

	for ( ; !iQueue.empty() ; ) {
		int tHead = iQueue.front();
		iQueue.pop();

		for ( GraphEdge *e = graph.vertex[tHead].edgeStart; e ; e = e->next ) {
			int tv = e->point;

			if ( dis[tv] > dis[tHead] + e->edgeValue ) {
				dis[tv] = dis[tHead] + e->edgeValue;

				if ( !used[tv] ) {
					used[tv] = true;
					iQueue.push ( tv );
				}
			}
		}

		used[tHead] = false;
	}

	for ( int i = 1; i <= graph.numOfVertex ; i++ ) {
		cout << source << "->" << i << ":" << dis[i] << endl;
	}
}
int main() {
	//freopen (".in", "r", stdin);
	//freopen (".out", "w", stdout);
	Graph graph;
	GraphInit ( graph );
	cout << "DFS:" << endl;
	GraphDFS ( graph );
	cout << endl;
	cout << "BFS:" << endl;
	GraphBFS ( graph );
	cout << endl;
	cout << "Prim:" << endl;
	GraphPrim ( graph );
	cout << "Kruscal:" << endl;
	Kruscal ( graph );
	cout << "Dijkstra:" << endl;
	Dijkstra ( graph, 1 );
	cout << "SPFA:" << endl;
	SPFA ( graph, 1 );
	//fclose(stdin);
	//fclose(stdout);
	return 0;
}
