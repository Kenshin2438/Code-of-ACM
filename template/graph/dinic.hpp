const int maxn = 2e4 + 10;
const int inf = 0x3f3f3f3f;
template <typename T> struct Dinic_Graph {
  int n, s, t;
  struct edge {
    int from, to, rev;
    T c;
    edge(int _from, int _to, int _rev, T _c) {
      from = _from, to = _to, rev = _rev, c = _c;
    }
  };
  vector<edge> G[maxn];
  queue<int> Q;
  T d[maxn];

  void init(int _n) {
    n = _n;
    for (int i = 0; i <= n; i++) G[i].clear();
    while (!Q.empty()) Q.pop();
  }

  inline void ins(int u, int v, T c) {
    debug(u, v, c);
    G[u].emplace_back(u, v, 0, c);
    G[v].emplace_back(v, u, 0, 0);
    G[u].back().rev = int(G[v].size()) - 1;
    G[v].back().rev = int(G[u].size()) - 1;
  }

  inline bool bfs() {
    for (int i = 0; i <= n; i++) d[i] = inf;
    Q.push(s);
    d[s] = 0;
    while (!Q.empty()) {
      int v = Q.front();
      Q.pop();
      for (edge& e : G[v]) {
        if (e.c > 0 && d[e.to] > d[v] + 1) {
          d[e.to] = d[v] + 1;
          Q.push(e.to);
        }
      }
    }
    return d[t] != inf;
  }

  inline T dfs(int v, T flow) {
    if (v == t || flow == 0) return flow;
    T res = 0, cur = 0;
    for (edge &e : G[v]) {
      if (e.c > 0 && d[e.to] == d[v] + 1) {
        if ((cur = dfs(e.to, min(flow, e.c))) > 0) {
          res += cur;
          flow -= cur;
          e.c -= cur;
          G[e.to][e.rev].c += cur;
        }
      }
    }
    if (res == 0) d[v] = -1;
    return res;
  }

  T Dinic(int _s, int _t) {
    s = _s, t = _t;
    T res = 0, cur = 0;
    while (bfs()) {
      while ((cur = dfs(s, inf)) > 0) {
        res += cur;
      }
    }
    return res;
  }
};
Dinic_Graph<int> G;
