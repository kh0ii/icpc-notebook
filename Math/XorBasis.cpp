struct XorBasis {
    const int K = 20;
    array<int, K> basis;
    vector<int> vec;
    int sz = 0;
    void reset() {
        sz = 0;
        vec.clear();
        for (int i = 0; i < K; i++) basis[i] = 0;
    }
    int reduce(int x) {
        for (int i = K - 1; i >= 0; i--) {
            if (x >> i & 1) {
                x ^= basis[i];
            }
        }
        return x;
    }
    bool add(int x, int id) {
        x = reduce(x);
        if (x) {
            int msb = -1;
            for (int i = K - 1; i >= 0; i--) {
                if (x >> i & 1) {
                    basis[i] = x;
                    sz++;
                    msb = i;
                    vec.pb(id);
                    break;
                }
            }
            if (msb != -1) {
                for (int i = K - 1; i >= 0; i--) {
                    if (i == msb) continue;
                    if (basis[i] >> msb & 1) basis[i] ^= x;
                }
                return 1;
            }
        }
        return 0;
    }
    int kth(int k) {
        if (k < 1 || k > (1 << sz)) return - 1;
        k--;
        int x = 0;
        int cnt = sz - 1;
        for (int i = K - 1; i >= 0; i--) {
            if (basis[i] == 0) continue;
            if (k >> cnt & 1) {
                x ^= basis[i];
            }
            cnt--;
        }
        return x;
    }
    int count_le(int x) {
        if (x < 0) {
            return 0;
        }
        int ret = 0;
        int cnt = sz - 1;
        int cur = 0;
        for (int i = K - 1; i >= 0; i--) {
            if (basis[i] == 0) continue;
            if (x >= (cur ^ basis[i])) {
                cur ^= basis[i];
                ret += (1 << cnt);
            }
            cnt--;
        }
        if (x > cur) {
            ret++;
        }
        return ret;
    }
    int count_leq(int x) {
        return count_le(x + 1);
    }
    int jump(int val, int k) {
        int p = count_leq(val);
        return kth(p + k);
    }
};
