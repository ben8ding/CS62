1. 

2. 

```c++

vector<int> Graph::dist5(int from)
{
    queue<int> q;
    vector<bool> visited(n(), false);
    vector<int> dist(n(),-1);
    visited[from] = true;
    q.push(from);
    //set dist to 0 because everything else is -1
    dist[from] = 0;

    while (q.size() > 0)
    {
        int cur = q.front();
        q.pop();

        for (int neighbor : adjLists_[cur])
        {
        
            if (!visited[neighbor])
            {
                visited[neighbor] = true;
                q.push(neighbor);
                dist[neigh] = dist[cur] + 1;
            }
        }
    }
    
    //process nodes with distance of 5
    vector<int> output;
    for(int i = 0; i< n(); i++){
        if(dist[i] == 5){
            output.push(i);
        }
    }
}

```

3. 

```c++
//finish
int Graph::diameter(){
    queue<int> q;
    vector<bool> visited (n(), 0);
    vector<int> prev (n(), -1); 

    visited[0] = true;
    q.push(0);

    while (q.size() > 0) {
      int cur = q.front();
      q.pop();
      for (auto neighbor : adjLists_[cur]) {
        if (!visited[neighbor]) {
          prev[neighbor] = cur; 
          visited[neighbor] = true;
          q.push(neighbor);
        }
      }

    }
}
//slow function
int disameterSlow() {
    int diam = -1
    for(int i = 0; i < n(); i++){
        for(int j = 0; j < n(); j++>){
            if(shortestPathLength(i,j) == -1)
                return -1;
            diam = max(diam, shortestPathLength(i,j));
        }
    }
    return diam;
}

```

4. 

```c++
int countA(const char *fname)
{
    ifstream ifs(fname);
    if (!ifs.is_open())
        return;

    getline(ifs, line);
    stringstream ss(line);

    int count;
    char letter;
    while (ss >> letter) {
        if(letter == a || letter ==A){
            count++;
        }
    }
    
    ifs.close();
}

int countA(const char* fname)
{
    int count = 0;
    ifstream fin (fname);
    string s;

    while (fin >> s) {
        for(int i = o; i < s.length(); i ++) {
            if(s[i] == 'A'){
                count++
            }
        }
    }

    for (char c : s){
        count += (c == 'A');
            if (c== 'A');
                count++
    }

    char c;
    while(fin >> c){
        count += (c == 'A'); //will be true if 1
    }
}
```
