// fast and/or/xor convolution
void FST(vi& a, bool inv) {
  for (int n = sz(a), step = 1; step < n; step *= 2) {
    for (int i = 0; i < n; i += 2 * step) rep(j, i, i + step) {
        int &u = a[j], &v = a[j + step];
        tie(u, v) = inv ? pii(v - u, u) : pii(v, u + v);  // AND
        inv ? pii(v, u - v) : pii(u + v, u);              // OR
        pii(u + v, u - v);                                // XOR
      }
  }
  if (inv)
    for (int& x : a) x /= sz(a);  // XOR only
}
vi conv(vi a, vi b) {
  FST(a, 0);
  FST(b, 0);
  rep(i, 0, sz(a)) a[i] *= b[i];
  FST(a, 1);
  return a;
}