#include "../main.hpp"

ll qpow(ll x, ll n, ll mod) {
  ll res = 1LL;
  for (x %= mod; n > 0LL; n >>= 1, x = x * x % mod) {
    if (n & 1LL) res = res * x % mod;
  }
  return (res + mod) % mod;
}

// δΈθ¬ O(log p); ζε O(log^2 p);
ll Tonelli_Shanks(ll a, ll p) {
  a = (a % p + p) % p;
  if (a == 0) return 0LL;

  if (qpow(a, (p - 1) / 2, p) != 1LL) return -1LL;  // No Solution

  if (p % 4 == 3) return qpow(a, (p + 1) / 4, p);

  ll k = __builtin_ctzll(p - 1), h = p >> k, N = 2;
  // p = 1 + h * 2^k
  while (qpow(N, (p - 1) / 2, p) == 1) N++;
  // find a non-square mod p

  ll x = qpow(a, (h + 1) / 2, p);
  ll g = qpow(N, h, p);
  ll b = qpow(a, h, p);

  for (ll m = 0;; k = m) {
    ll t = b;
    for (m = 0; m < k && t != 1LL; m++) {
      t = t * t % p;
    }

    if (m == 0) return x;
    ll gs = qpow(g, 1 << (k - m - 1), p);

    g = gs * gs % p;
    b = b * g % p;
    x = x * gs % p;
  }

  assert(false);
  return -1;
}