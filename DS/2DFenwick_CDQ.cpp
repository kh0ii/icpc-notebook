struct Fenwick
{
    vector<int> bit;
    int n;
    Fenwick(int n)
    {
        this->n = n;
        bit.assign(n, 0);
    }
 
    int sum(int r)
    {
        int ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }
 
    int sum(int l, int r)
    {
        if (l > r) swap(l, r);
        return sum(r) - sum(l - 1);
    }
 
    void add(int idx, int delta)
    {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }
};
 
using iiii = array<int, 5>;
 
struct Node
{
    int t, x, y, v, i, sgn;
};
struct CDT
{
    int n;
    Fenwick ft;
    vi ans;
    vector<iiii> qr;
    vector<Node> v;
 
    CDT(int _n, vector<iiii> _qr): n(_n), qr(_qr), ft(n)
    {
        int i = 0;
        for (auto [op, x1, y1, x2, y2] : qr)
        {
            if (op == 1) v.push_back({i, x1, y1, x2, 0, 0});
            else
            {
                v.push_back({i, x1 - 1, y1 - 1, 0, sz(ans), 1});
                v.push_back({i, x1 - 1, y2, 0, sz(ans), -1});
                v.push_back({i, x2, y1 - 1, 0, sz(ans), -1});
                v.push_back({i, x2, y2, 0, sz(ans), 1});
                ans.pb(0);
            }
            i++;
        }
        cdq(0, sz(v));
        for (auto i : ans) cout << i << '\n';
    }
 
    void cdq(int l, int r)
    {
        if(l + 1 == r) return;
        int m = (l + r) >> 1;
        cdq(l, m);
        cdq(m, r);
        vector<Node> tmp;
        vector<pair<int, int> > his;
        int a = l, b = m;
        while(a < m && b < r)
        {
            if(v[a].x <= v[b].x)
            {
                ft.add(v[a].y, v[a].v);
                his.push_back({v[a].y, -v[a].v});
                tmp.push_back(v[a++]);
            }
            else
            {
                ans[v[b].i] += v[b].sgn * (ft.sum(v[b].y));
                tmp.push_back(v[b++]);
            }
        }
        while(a < m) tmp.push_back(v[a++]);
        while(b < r)
        {
            ans[v[b].i] += v[b].sgn * (ft.sum(v[b].y));
            tmp.push_back(v[b++]);
        }
        for(int i = l ; i < r ; ++i) v[i] = tmp[i - l];
        for(int i = 0 ; i < (int)his.size() ; ++i) ft.add(his[i].fi, his[i].se);
        vector<Node> ().swap(tmp);
        vector<pair<int, int> > ().swap(his);
    }
 // usage

  void solve()
{
    int n, m;
    cin >> n >> m;
    vi a(n + 1), b(n + 1), posa(n + 1), posb(n + 1);
    fore(i, 1, n) cin >> a[i], posa[a[i]] = i;
    fore(i, 1, n) cin >> b[i], posb[b[i]] = i;
    vector<iiii> qr;
    fore(i, 1, n) qr.push_back({1, posa[i], posb[i], 1});
    while (m--)
    {
        int op;
        cin >> op;
        if (op == 2)
        {
            int x, y;
            cin >> x >> y;
            qr.push_back({1, posa[b[x]], x, -1});
            qr.push_back({1, posa[b[x]], y, 1});
            qr.push_back({1, posa[b[y]], y, -1});
            qr.push_back({1, posa[b[y]], x, 1});
            swap(b[x], b[y]);
            posb[b[x]] = x;
            posb[b[y]] = y;
            continue;
        }
        int la, ra, lb, rb;
        cin >> la >> ra >> lb >> rb;
        qr.push_back({2, la, lb, ra, rb});
    }
    CDT cdq(n + 1, qr);
}
};
