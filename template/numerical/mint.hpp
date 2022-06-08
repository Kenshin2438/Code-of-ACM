#include "../main.hpp"

template <int mod> struct m32 {
  int v = 0;
  mutable int iv = 0;

  m32(int _ = 0) {
    if ((v = _ % mod) < 0) v += mod;
  }
  m32(long long _ = 0LL) {
    if ((v = _ % mod) < 0) v += mod;
  }
  m32 operator-() const {
    return v ? m32(mod - v) : m32();
  }
  m32 &operator=(const int &m) {
    return this = m32(m), *this;
  }
  m32 &operator+=(const m32 &m) {
    v = (v += m.v) >= mod ? v - mod : v;
    return *this;
  }
  m32 &operator-=(const m32 &m) {
    v = (v -= m.v) < 0 ? v + mod : v;
    return *this;
  }
  m32 &operator*=(const m32 &m) {
    v = ll(v) * m.v % mod;
    return *this;
  }
  m32 &operator/=(const m32 &m) {
    v = ll(v) * m.inv() % mod;
    return *this;
  }
  m32 operator+(const m32 &m) const {
    return m32(*this) += m;
  }
  m32 operator-(const m32 &m) const {
    return m32(*this) -= m;
  }
  m32 operator*(const m32 &m) const {
    return m32(*this) *= m;
  }
  m32 operator/(const m32 &m) const {
    return m32(*this) /= m;
  }
  bool operator==(const m32 &m) const {
    return m.v == v;
  }
  bool operator!=(const m32 &m) const {
    return m.v != v;
  }
  m32 pow(long long n) const {
    if (n == 1) return *this;
    if (n == 0) return m32(1);
    if (v == 0) return m32(0);
    if (n < 0) return inv().pow(-n);
    m32 res = pow(n >> 1);
    return res * res * pow(n % 2);
  }
  m32 inv() const {
    assert(v != 0);
    m32 res(iv);  // check current inv
    if (*this * res == 1) return res;
    return m32(iv = pow(mod - 2).v);
  }
  pair<m32, m32> sqrt() const {
#ifdef CIPOLLA
    return cipolla(v);
#else
    return {1, 1};
#endif
  }
  friend ostream &operator<<(ostream &os, const m32<mod> &m) {
    return os << m.v;
  }
  friend istream &operator>>(istream &is, m32<mod> &m) {
    is >> m.v;
    m.v %= mod;
    if (m.v < 0) m.v += mod;
    return is;
  }
};

using mint = m32<998244353>;