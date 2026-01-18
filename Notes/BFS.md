**BFS Notes**

* Breadth First Search
* DFS = Depth First Search
* Good for finding shortest path solutions
* Specifically finding social network connected users
* Good for understanding algorithms and possibly interviews
* Starts from the origin and works its way out
* Shortest path counts edges not vertices

**Basic BFS Implementation**

```c++
void Graph::BFS(int source)
{
    queue<int> q; //O(1)
    // bool visited[n()];
    vector<bool> visited(n(), 0); //O(n)
    // Add Shweta
    visited[source] = true;
    q.push(source);
    while (q.size() > 0) //O(n+m)
    {
        int cur = q.front();
        cout << cur << endl;
        q.pop();
        for (int neighbor : adjLists_[cur])
        {
            if (!visited[neighbor])
            {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}
```

**BFS Prev Implementation**

```c++
vector<int> shortestPath(int from, int to) {
    queue<int> q;
    vector<bool> visited (n(), 0);
    // prev[v] is the vertex that visited/queued v
    vector<int> prev (n(), -1); // new

    visited[from] = true;
    q.push(from);

    for (int i = 0; i < n(); i ++) {
      cout << prev[i] << " ";
    }
    cout << endl;

    while (q.size() > 0) {
      int cur = q.front();
      q.pop();
      for (auto neighbor : adjLists_[cur]) {
        if (!visited[neighbor]) {
          prev[neighbor] = cur; // new
          visited[neighbor] = true;
          q.push(neighbor);
        }
      }

      for (int i = 0; i < n(); i ++) {
        cout << prev[i] << " ";
      }
      cout << endl;
    }
    vector<int> output;
    int cur = to;
    // version 1
    while (cur != -1 ) { //Not ending at from because we want to include from in output. We can also manually add from at the end if we prefer
      output.push_back(cur);
      cur = prev[cur];
    }

    reverse(output.begin(), output.end());
    return output;
  }```

