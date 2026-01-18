**Graphs Lecture**

* A graph is a collection of vertices and edges
* Node <-> Vertex
* Vertex 0 and Vertex 1 are adjacent
* The neighbors of vertx 0 are vertices 1 and 4
* vertex 0 has degree 2 (degre = #neighbors)
* N is the number of vertices, m is the number of edges
* Vertex = 1, vertices = more than 1
* Undirected graphs have edges go both ways, directed graphs include a direction
* Vertices and edges need to be stored

Method 1: Edge List

```c++
// Edge List
vector<pair<int,int> > edges;
[(0,1),(0,4),(1,2),(1,3),(1,4),(2,3),(3,4)]
```

Method 2: Adcjacency Matrix

```c++
// Adjacency Matrix
// Adj[i][j] = 1 if vertices i and j adjacent
bool Adj[N][N];
```

Methord 3: Adjacency Lists

```c++
// Adjacency lists
// AdjLists[i] contains the neighbors of vertex i
vector<set<int> > AdjLists;
set<int> AdjLists[N];
AdjLists[0] = set<int> {1,4}
AdjLists[1] = set<int> {0,2,3,4}
AdjLists[2] = set<int> {1,3}
AdjLists[3] = set<int> {1,2,4}
AdjLists[4] = set<int> {0,1,3}
```

* Adjacency lists are more efficient for social networks because of sparse connections. Save on memory usage.

Sample User Adjacency List:

```c++
// Adjacency lists
// AdjLists[i] contains the neighbors of vertex i
class User {
private:
set<int> friends;
};
class Network {
private:
vector<User> users;
};
```