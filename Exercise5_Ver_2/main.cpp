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
#define NUM_OF_VERTEX 100

using namespace std;

/* Something else... */
bool *visited;

/* Graph */
struct Graph {
	int numOfEdge, numOfVertex;
	int vertex[NUM_OF_VERTEX][NUM_OF_VERTEX];
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
	graph.vertex[x][y] = min ( graph.vertex[x][y], v );
	graph.vertex[y][x] = min ( graph.vertex[y][x], v );
}

void GraphInit ( Graph &graph ) {
	int x, y, v;
	freopen ( "graphBuild.in", "r", stdin );
	/* Input the number of Vertex and Edge  */
	cin >> graph.numOfVertex >> graph.numOfEdge;
	/* Initialize  */
	memset ( graph.vertex, 10, sizeof ( graph.vertex ) );

	/* input the all edges */
	for ( int i = 1; i <= graph.numOfEdge ; i++ ) {
		cin >> x >> y >> v;
		__addEdge ( graph, x, y, v );
		__addEdge ( graph, y, x, v );
	}

	for ( int i = 1; i <= graph.numOfVertex ; i++ ) {
		graph.vertex[i][i] = 0;
	}

	fclose ( stdin );
}

void __graphDFS ( Graph g, int root ) {
	/* Visit it */
	cout << root << " ";
	/* Mark it */
	visited[root] = true;

	/* Continue DFS */
	for ( int i = 1; i <= g.numOfVertex; i++ ) {
		if ( ( !visited[i] ) && ( g.vertex[root][i] != oo ) ) {
			__graphDFS ( g, i );
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
		int qHead = iQueue.front();
		cout << qHead << " ";
		iQueue.pop();

		for ( int i = 1; i <= g.numOfVertex; i++ ) {
			if ( ( !visited[i] ) && ( g.vertex[qHead][i] != oo ) && ( qHead != i ) ) {
				visited[i] = true;
				iQueue.push ( i );
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

	for ( int i = 1; i <= graph.numOfVertex ; i++ ) {
		if ( ( graph.vertex[1][i] != oo ) && ( i != 1 ) ) {
			temp.value = graph.vertex[1][i];
			temp.x = 1;
			temp.y = i;
			iQueue.push ( temp );
		}

		visited[1] = true;
	}

	while ( !iQueue.empty() ) {
		tempHead = iQueue.top();
		iQueue.pop();

		if ( !visited[tempHead.y] ) {
			visited[tempHead.y] = true;
			cout << tempHead.x << "->" << tempHead.y << ":" << tempHead.value << endl;

			for ( int i = 1; i <= graph.numOfVertex ; i++ ) {
				if ( ( graph.vertex[tempHead.y][i] != oo ) && ( i != 1 ) ) {
					temp.value = graph.vertex[tempHead.y][i];
					temp.x = tempHead.y;
					temp.y = i;
					iQueue.push ( temp );
				}

				visited[tempHead.y] = true;
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
		for ( int j = 1; j <= graph.numOfVertex ; j++ ) {
			if ( ( i != j ) && ( graph.vertex[i][j] != oo ) ) {
				PriQueStruct temp;
				temp.value = graph.vertex[i][j];
				temp.x = i;
				temp.y = j;
				iQueue.push ( temp );
			}
		}
	}

	int totalEdge = 0;

	for ( ; ( totalEdge < graph.numOfVertex - 1 ) && ( !iQueue.empty() ); ) {
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
	for ( int i = 1; i <= graph.numOfVertex ; i++ ) {
		dis[i] = graph.vertex[source][i];
	}

	dis[source] = 0;

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

		for ( int i = 1; i <= graph.numOfVertex ; i++ ) {
			if ( ( i != position ) && ( !used[i] ) ) {
				dis[i] = min ( dis[i], dis[position] + graph.vertex[position][i] );
			}
		}
	}

	for ( int i = 1; i <= graph.numOfVertex ; i++ ) {
		cout << source << "->" << i << ":" << dis[i] << endl;
	}
}
/* Floyd */
void Floyd ( Graph graph, int source ) {
	for ( int k = 1; k <= graph.numOfVertex ; k++ ) {
		for ( int i = 1; i <= graph.numOfVertex ; i++ ) {
			if ( k != i ) {
				for ( int j = 1; j <= graph.numOfVertex ; j++ ) {
					if ( k != j ) {
						if ( i != j ) {
							graph.vertex[i][j] = min ( graph.vertex[i][j], graph.vertex[i][k] + graph.vertex[k][j] );
						}
					}
				}
			}
		}
	}

	for ( int i = 1; i <= graph.numOfVertex ; i++ ) {
		for ( int j = 1; j <= graph.numOfVertex ; j++ ) {
			cout << graph.vertex[i][j] << "\t";
		}

		cout << endl;
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
	cout << "Floyd:" << endl;
	Floyd ( graph, 1 );
	//fclose(stdin);
	//fclose(stdout);
	return 0;
}
