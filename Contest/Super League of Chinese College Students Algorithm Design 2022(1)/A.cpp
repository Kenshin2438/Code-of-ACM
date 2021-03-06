#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

struct SuffixArray {
  vector<int> SA, LCP, RK;

  SuffixArray() {}
  SuffixArray(const string &s, char first = 'a', char last = 'z') {
    get_sa(s, first, last), get_lcp(s);
  }
  #define sz(x) int((x).size())
  // O(n)
  vector<int> SA_IS(const vector<int> &v, int K) {
    const int n = sz(v);
    vector<int> SA(n), lms;
    vector<bool> sl(n, false);
    for (int i = n - 2; i >= 0; i--) {
      sl[i] = (v[i] == v[i + 1] ? sl[i + 1] : v[i] > v[i + 1]);
      if (sl[i] && !sl[i + 1]) lms.push_back(i + 1);
    }
    reverse(all(lms));
    auto induced_sort = [&](const vector<int> &LMS) {
      vector<int> l(K, 0), r(K, 0);
      for (const int &x : v) {
        if (x + 1 < K) l[x + 1]++;
        ++r[x];
      }
      partial_sum(all(l), begin(l));
      partial_sum(all(r), begin(r));
      fill(all(SA), -1);
      for (int i = LMS.size() - 1; i >= 0; i--) {
        int p = LMS[i];
        SA[--r[v[p]]] = p;
      }
      for (const int &p : SA) if (p >= 1 && sl[p - 1]) {
        SA[l[v[p - 1]]++] = p - 1;
      }
      fill(all(r), 0);
      for (const int &x : v) ++r[x];
      partial_sum(all(r), begin(r));
      for (int i = SA.size() - 1; i >= 1; i--) {
        int p = SA[i];
        if (p >= 1 && !sl[p - 1]) SA[--r[v[p - 1]]] = p - 1;
      }
    };
    induced_sort(lms);
    vector<int> new_lms(sz(lms)), new_v(sz(lms));
    for (int i = 0, k = 0; i < n; i++) {
      if (!sl[SA[i]] && SA[i] >= 1 && sl[SA[i] - 1]) {
        new_lms[k++] = SA[i];
      }
    }
    int cur = SA.back() = 0;
    for (int k = 1; k < sz(new_lms); k++) {
      int i = new_lms[k - 1], j = new_lms[k];
      if (v[i] != v[j]) { SA[j] = ++cur; continue; }
      bool flag = false;
      for (int a = i + 1, b = j + 1;; a++, b++) {
        if (v[a] != v[b]) { flag = true; break; }
        if ((!sl[a] && sl[a - 1]) || (!sl[b] && sl[b - 1])) {
          flag = !((!sl[a] && sl[a - 1]) && (!sl[b] && sl[b - 1]));
          break;
        }
      }
      SA[j] = (flag ? ++cur : cur);
    }
    for (int i = 0; i < sz(lms); i++) new_v[i] = SA[lms[i]];
    if (cur + 1 < sz(lms)) {
      auto lms_SA = SA_IS(new_v, cur + 1);
      for (int i = 0; i < sz(lms); i++) new_lms[i] = lms[lms_SA[i]];
    }
    induced_sort(new_lms);
    return SA;
  }

  void get_sa(const string &s, char first = 'a', char last = 'z') {
    vector<int> v(s.size() + 1);
    copy(all(s), begin(v));
    for (auto &&x : v) x -= first - 1;
    v.back() = 0;
    this->SA = SA_IS(v, last - first + 2);
    this->SA.erase(begin(this->SA));
  }

  void get_lcp(const string &s) {
    int n = sz(s);
    vector<int> rank(n), lcp(n);
    for (int i = 0; i < n; i++) rank[SA[i]] = i;
    for (int i = 0, p = 0; i < n; i++, p ? p--: 0) {
      if (rank[i] == 0) { p = 0; continue; }
      int j = SA[rank[i] - 1];
      while (i + p < n && j + p < n && s[i + p] == s[j + p]) p++;
      lcp[rank[i]] = p;
    }
    this->LCP = move(lcp);
    this->RK = move(rank);
  }
};

template <typename T> struct ST {
  vector<vector<T>> st;
  T f(const T &a, const T &b) { 
    return min<T>(a, b);
  }

  ST() = default;
  ST(const vector<T> &v) : st(1, v) {
    for (int pw = 1, k = 1; (pw << 1) <= sz(v); pw <<= 1, k++) {
      st.emplace_back(sz(v) - (pw << 1) + 1);
      for (int i = 0; i < sz(st[k]); i++) {
        st[k][i] = f(st[k - 1][i], st[k - 1][i + pw]);
      }
    }
  }
  ~ST() = default;

  T query(int l, int r) {  // query [l, r)
    int dep = 31 - __builtin_clz(r - l);
    return f(st[dep][l], st[dep][r - (1 << dep)]);
  }
};

void solve() {
  string s; s.reserve((int) 1e6);
  int k; 

  cin >> s >> k;

  auto SAIS = SuffixArray(s);
  SAIS.LCP[0] = s.length();
  auto RMQ = ST<int>(SAIS.LCP);

  int n = s.length();
  vector<vector<int>> S(k);
  for (int i = 0; i < k; i++) {
    S[i] = vector<int>((n - 1 - i) / k + 1 + 1, 0);
  }

  for (int i = 1; i < n; i++) {
    int l = SAIS.RK[0], r = SAIS.RK[i];
    if (l > r) swap(l, r);
    int lcp = RMQ.query(l + 1, r + 1);

    int d = i - 0;
    if (d + k > lcp) continue;
    int L = i + d - 1 + k;
    int R = i + d - 1 + ((lcp - d) / k) * k;

    int pos = L % k;
    // S[pos].range_add((L - pos) / k, (R - pos) / k + 1, 1);
    S[pos][(L - pos) / k] += 1;
    S[pos][(R - pos) / k + 1] -= 1;
  }

  const int mod = 998244353;
  ll ans = 1;
  for (int pos = 0; pos < k; pos++) {
    ll F = 0;
    for (int i = 0; i < S[pos].size() - 1; i++) {
      F += S[pos][i];
      ans = (F + 1 + (pos == k - 1)) % mod * ans % mod;
    }
  }
  cout << ans << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  
  int T; cin >> T;
  while (T--) solve();

  return 0;
}