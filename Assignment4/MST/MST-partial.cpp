#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <cstdlib>
#include <fstream>
#include <queue>
#include <vector>
#include <cstring>
#include <iomanip>

using namespace std;

struct Edge
{
    int endpoint1;
    int endpoint2;
    int weight;
    struct Edge *next;
    Edge(int u, int v, int w)
    {
        endpoint1 = u;
        endpoint2 = v;
        weight = w;
        next = NULL;
    }
    int opposite(int u)
    {
        if (endpoint1 == u)
        {
            return endpoint2;
        }
        else
        {
            return endpoint1;
        }
    }
};

int n, m;
Edge *incidentEdges[100];
Edge *allEdges[1000];  // to store all the edges (for sorting edges in Kruskal's Algorithm)
bool inT[100];         // indicator of whether a node is in T (in Prim's Algorithm)
int parent[100];       // to store the "parent element" in the Union-Find data structure
Edge *chosenEdge[100]; // to store the edges chosen in the MST

void makeSet(int u)
{
    parent[u] = u;
}

int findSet(int u) // return the ID of the set containing a node
{
    if (parent[u] == u)
        return u;
    else
    {
        parent[u] = findSet(parent[u]); // path contraction for speeding up the future query
        return parent[u];
    }
}

void unionSet(int p1, int p2)
{
    parent[p1] = p2; // union the two sets
}

bool cmpEdges(Edge *a, Edge *b)
{
    return a->weight < b->weight;
}

void Kruskal()
{
    for (int u = 0; u < 100; u++)
    { // make-set for each node
        makeSet(u);
    }
    sort(allEdges, allEdges + m, cmpEdges); // sort edges in ascending order of weight
    int total_weight_Krus = 0;              // count the total edge weight
    int numOfChosenEdges = 0;               // count the number of edges in the current solution
    memset(chosenEdge, NULL, 100);          // initialize the set of chosen edges to empty

    /*finish this part*/
    for (int i = 0; i < m; i++) // Traverse every edge (Sorted in allEdges)
    {
        Edge *e = allEdges[i];
        int u = e->endpoint1;
        int v = e->endpoint2;
        if (findSet(u) != findSet(v))
        {
            chosenEdge[numOfChosenEdges++] = e;
            unionSet(findSet(u), findSet(v));
            total_weight_Krus += e->weight;
        }
    }
    /*finish this part*/

    if (numOfChosenEdges < n - 1)
    {
        cout << "No spanning tree: the Graph is disconnected ! \n";
    }
    else
    {
        cout << "Edges in the minimum spanning tree by Kruskal:\n";
        cout << "Node1 Node2 Weight \n------------------\n";
        for (int i = 0; i < n - 1; i++)
        {
            cout << setw(5) << chosenEdge[i]->endpoint1 << " ";
            cout << setw(5) << chosenEdge[i]->endpoint2 << " ";
            cout << setw(5) << chosenEdge[i]->weight << endl;
        }
        cout << "------------------\n";
        cout << "Total edge weight: " << total_weight_Krus << endl;
        cout << "------------------\n";
    }
}

struct compareEdges
{
    bool operator()(Edge *a, Edge *b)
    {
        return a->weight > b->weight;
    }
};

priority_queue<Edge *, vector<Edge *>, compareEdges> q; // each element in the priority queue is an edge

void insertEdgesOf(int u) // inserts all incident edges of u to the queue
{
    /*finish this part*/
    Edge *e = incidentEdges[u];
    while (e != NULL)
    {
        if (!inT[e->opposite(u)])
            q.push(e);
        e = e->next;
    }
    /*finish this part*/
}

void Prim(int s)
{
    int u, total_weight_Prim = 0;
    int numOfChosenEdges = 0;      // count the number of edges in the current solution
    memset(inT, false, 100);       // initialize T = emptyset
    memset(chosenEdge, NULL, 100); // initialize the set of chosen edges to empty
    inT[s] = true;                 // start with T = {s}
    insertEdgesOf(s);              // insert edges incident to s

    while (!q.empty())
    {
        /*finish this part*/
        Edge *e = q.top(); // Let e be the smallest boundary edges
        q.pop();

        if (!inT[e->endpoint1] || !inT[e->endpoint2]) // Only consider boundary edges
        {
            chosenEdge[numOfChosenEdges++] = e; // Choose the found smallest edge
            total_weight_Prim += e->weight;

            int u = inT[e->endpoint1] ? e->endpoint1 : e->endpoint2; // Identify the endpoint that's in T as u, another as v
            int v = e->opposite(u);                                  // Visit its end point that's not in T
            inT[v] = true;

            insertEdgesOf(v);
        }
        /*finish this part*/
    }

    if (numOfChosenEdges < n - 1)
    {
        cout << "No spanning tree: the Graph is disconnected ! \n";
    }
    else
    {
        cout << "Edges in the minimum spanning tree by Prim:\n";
        cout << "Node1 Node2 Weight \n------------------\n";
        for (int i = 0; i < n - 1; i++)
        {
            cout << setw(5) << chosenEdge[i]->endpoint1 << " ";
            cout << setw(5) << chosenEdge[i]->endpoint2 << " ";
            cout << setw(5) << chosenEdge[i]->weight << endl;
        }
        cout << "------------------\n";
        cout << "Total edge weight: " << total_weight_Prim << endl;
        cout << "------------------\n";
    }
}

int main()
{
    ifstream read;
    string path = "/Users/huangyanzhen/Desktop/Year2Sem2/CISC2006/Assignments/Assignment4/MST/";
    string input[] = {path + "input7.txt", path + "input8.txt", path + "input9.txt", path + "input10.txt", path + "input11.txt"};

    for (int i = 0; i < 5; i++)
    { // 5 test cases
        cout << "Test Case: " << i + 1 << "\n------------------\n";
        read.open(input[i].c_str());
        if (!read)
        {
            cout << "Unable to open file !" << endl;
            return -1;
        }

        int u, v, w;
        read >> n; // input the number of nodes
        m = 0;

        for (u = 0; u < 100; u++)
        { // initialization: empty the adjacency lists for all nodes
            incidentEdges[u] = NULL;
        }
        Edge *curr = NULL;
        while (read >> u >> v >> w)
        {
            Edge *newedge1 = new Edge(u, v, w);
            Edge *newedge2 = new Edge(u, v, w);

            if (incidentEdges[u] == NULL)
            {
                incidentEdges[u] = newedge1;
            }
            else
            {
                newedge1->next = incidentEdges[u];
                incidentEdges[u] = newedge1;
            }

            if (incidentEdges[v] == NULL)
            {
                incidentEdges[v] = newedge2;
            }
            else
            {
                newedge2->next = incidentEdges[v];
                incidentEdges[v] = newedge2;
            }

            allEdges[m++] = new Edge(u, v, w);
        }

        cout << "Adjacency List: " << endl;
        for (u = 1; u <= n; u++)
        {
            cout << "Neighbors of node " << u << ": ";
            curr = incidentEdges[u];
            while (curr != NULL)
            {
                cout << curr->opposite(u) << " ";
                curr = curr->next;
            }
            cout << endl;
        }
        cout << "------------------\n";

        Kruskal();

        Prim(1);

        read.close();
    }
    return 0;
}
