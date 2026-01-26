# DFS Notes

* Basic definition: DFS uses stack instead of queue
* Visiting vertices in a different order
* Search deep down one path and then backtrack to find other paths
* Still visits every node, still O(m+n) (or O(m) if n is small)


```c++
  void DFS(int source) {
    stack<int> stck;
    vector<bool> visited (n(), 0);

    visited[source] = true;
    stck.push(source);

    while (stck.size() > 0) {
      int cur = stck.top();
      stck.pop();
      for (auto neighbor : adjLists_[cur]) {
        if (!visited[neighbor]) {
          visited[neighbor] = true;
          stck.push(neighbor);
        }
      }
     
    }
  }
```

* Recursive implementation

```c++
void DFSHelper(int cur, std::vector<bool> &visited) {
    //here
    for (auto neighbor : adjLists_[cur]) {
      if (!visited[neighbor]) {
        visited[neighbor] = true;
        DFSHelper(neighbor, visited);
      }
    }
  }

  void DFS(int source) {
    std::vector<bool> visited (n(), 0);
    visited[source] = true;
    DFSHelper(source, visited);
  }
```