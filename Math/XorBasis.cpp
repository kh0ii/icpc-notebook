struct Basis {
  const int LGX = 19;
  vector<int> a;
  Basis() : a(LGX + 1, 0) {}
  void add(int x) {
    for (int i = LGX; i >= 0; --i) {
      if (x & (1 << i)) {
        if (a[i])
          x ^= a[i];
        else {
          a[i] = x;
          break;
        }
      }
    }
  }
  void add(Basis o) {
    for (int i = LGX; i >= 0; --i) add(o.a[i]);
  }
  bool is_spannable(int x) {
    for (int i = LGX; i >= 0; --i)
      if (x & (1 << i)) x ^= a[i];
    return (x == 0);
  }
};