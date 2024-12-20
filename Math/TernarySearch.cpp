// Find the smallest i in [a; b] that maximizes f(i), assuming
// that f(a) < .. < f(i) >= ... >=  f(b)
// Usage: int ind = ternSearch(0,n-1,[&](int i){return a[i];});
template <class F>
int ternSearch(int a, int b, F f) {
  assert(a <= b);
  while (b - a >= 5) {
    int mid = (a + b) / 2;
    if (f(mid) < f(mid + 1))
      a = mid;  // (A)
    else
      b = mid + 1;
  }
  rep(i, a + 1, b + 1) if (f(a) < f(i)) a = i;  // (B)
  return a;
}