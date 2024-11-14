struct maximum_bipartite_matching {
  int n, m;
  vector<int> matchX, matchY, dist;
  vector<vector<int>> g;
  int matched;
  maximum_bipartite_matching(int _n, int _m)
      : n(_n), m(_m), matchX(n + 1, -1), matchY(m + 1, -1), dist(n + 1, -1), g(n + 1), matched(0) {}

  void add_edge(int u, int v) { g[u].push_back(v); }
  void bfs() {
    queue<int> q;
    for (int i = 0; i < n; ++i) {
      if (matchX[i] == -1)
        q.push(i), dist[i] = 0;
      else
        dist[i] = -1;
    }
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int v : g[u]) {
        if (matchY[v] != -1 and dist[matchY[v]] == -1) {
          dist[matchY[v]] = dist[u] + 1;
          q.push(matchY[v]);
        }
      }
    }
  }
  bool dfs(int u) {
    for (int v : g[u]) {
      if (matchY[v] == -1) {
        matchX[u] = v, matchY[v] = u;
        return 1;
      }
    }
    for (int v : g[u]) {
      if (dist[matchY[v]] == dist[u] + 1 and dfs(matchY[v])) {
        matchX[u] = v, matchY[v] = u;
        return 1;
      }
    }
    return 0;
  }

  void match() {
    while (1) {
      bfs();
      int augment = 0;
      for (int i = 0; i < n; ++i)
        if (matchX[i] == -1) augment += dfs(i);
      if (!augment) break;
      matched += augment;
    }
  }
  vector<pii> get_edges() {
    vector<pii> res;
    for (int i = 0; i < n; ++i)
      if (matchX[i] != -1) res.push_back({i, matchX[i]});
    return res;
  }
};