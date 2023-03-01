#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

using ll = long long;
#define all(a) begin(a), end(a)
#define sz(x) (int)((x).size())

void solve() {
  int n; cin >> n;
  vector<int> pos;
  for (int i = 1; i <= n; i++) {
    int x; cin >> x;
    if (x == 2) pos.emplace_back(i);
  }

  if (pos.empty()) {
    cout << "1\n";
  } else {
    if (sz(pos) % 2 == 1) {
      cout << "-1\n";
    } else {
      cout << pos[sz(pos) / 2 - 1] << '\n';
    }
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}