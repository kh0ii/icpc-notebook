#include "bits/stdc++.h"
using namespace std;

using ll = long long;
using pii = pair<int, int>;

#define F first
#define S second
#define sz(x) (int)((x).size())
#define all(x) (x).begin(), (x).end()

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll get_rand(ll l, ll r) {
    assert(l <= r);
    return uniform_int_distribution<ll> (l, r)(rng);
}

void solve(){
    
}

int32_t main() {
    cin.tie(nullptr)->sync_with_stdio(0);
    int test = 1;
    while(test--) solve();
    #ifdef LOCAL
        cerr << "\n[Time]: " << 1000.0 * clock() / CLOCKS_PER_SEC << " ms.\n";

    return 0;
}
