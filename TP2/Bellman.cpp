#include <stdio.h>
#include <iostream>
#include <limits.h> 

using namespace std;
// structure pour l'arrete pondéré 
struct Edge 
{ 
	int src, dest, weight; 
}; 

// structure pour un graph orienté et pondéré 
struct Graph 
{ 
	// V-> nbr de sommet, E-> nbr d'arrete
	int V, E; 

	// liste d'arrete
	struct Edge* edge; 
}; 

// cree un graph avec V sommet and E arrete
struct Graph* createGraph(int V, int E) 
{ 
	struct Graph* graph = new Graph; 
	graph->V = V; 
	graph->E = E; 
	graph->edge = new Edge[E]; 
	return graph; 
} 

// display
void displayShortestPaths(int dist[], int n, int pere[]) 
{ 
	cout << "Pivot \t    Distance \t   Pere" << endl; 
	for (int i = 0; i < n; ++i) 
		cout << i+1 << "\t\t" << dist[i] << "\t\t" << pere[i] << endl;
} 

// Bellman
void Bellman(struct Graph* graph, int src) 
{ 
	int V = graph->V; 
	int E = graph->E; 
	int dist[V]; 
    int pere[V];

	// On initialise a l'infini 
	for (int i = 0; i < V; i++) 
		dist[i] = INT_MAX, pere[i] = 0; 
    //dist de src a lui meme = 0
	dist[src] = 0; 
    pere[src] = -1;

	for (int i = 1; i <= V; i++) 
	{ 
		for (int j = 0; j < V; j++) 
		{ 
			int u = graph->edge[j].src; 
			int v = graph->edge[j].dest; 
			int weight = graph->edge[j].weight; 
			if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) 
				dist[v] = dist[u] + weight; 
                pere[v] = u;

		} 
	} 


	displayShortestPaths(dist, V, pere); 
} 

int main() 
{ 
	/* Creation de graph */
	int V = 6;
	int E = 7;
	struct Graph* graph = createGraph(V, E); 

	// add edge 1-2
	graph->edge[0].src = 0; 
	graph->edge[0].dest = 1; 
	graph->edge[0].weight = 1; 

	// add edge 1-4
	graph->edge[1].src = 0; 
	graph->edge[1].dest = 3; 
	graph->edge[1].weight = -2; 

	// add edge 1-3
	graph->edge[2].src = 0; 
	graph->edge[2].dest = 2; 
	graph->edge[2].weight = 2; 

	// add edge 2-5
	graph->edge[3].src = 1; 
	graph->edge[3].dest = 4; 
	graph->edge[3].weight = 4; 

	// add edge 4-6 
	graph->edge[4].src = 3; 
	graph->edge[4].dest = 5; 
	graph->edge[4].weight = 2; 

	// add edge 3-4
	graph->edge[5].src = 2; 
	graph->edge[5].dest = 3; 
	graph->edge[5].weight = -5; 

	// add edge 3-5
	graph->edge[6].src = 2; 
	graph->edge[6].dest = 4; 
	graph->edge[6].weight = 5; 

	Bellman(graph, 0); 

	return 0; 
} 