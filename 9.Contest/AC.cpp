#include <bits/stdc++.h>
#define fi first
#define se second
 
using namespace std;
using ll = long long;
const int Mod = 1e9+7;
const int maxn = 1e5+5;

int n, a[maxn]; ll prefix[maxn];

class seg {
	public:
		int st[4*maxn];
		
		void build(int id, int l, int r) {
			if (l == r) st[id] = a[l];
			else {
				int m = (l + r) / 2;
				build(2*id,l,m);
				build(2*id+1,m+1,r);
				st[id] = (st[2*id] <= st[2*id+1] ? st[2*id] : st[2*id+1]);
			}
		}

		int query(int id, int l, int r, int u, int v) {
			if (v < l or u > r) return a[0];
			if (u <= l && r <= v) return st[id];
			int m = (l + r) / 2;
			return min(
				query(2*id,l,m,u,v),
				query(2*id+1,m+1,r,u,v)
			);
		}
};

bool cmp(pair<double,int> p1, pair<double,int> p2) {
	if (p1.fi == p2.fi) return p1.se < p2.se;
	return p1.fi >= p2.fi;
}
 
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	//code here
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) prefix[i] = prefix[i-1] + a[i];
	a[0] = INT_MAX;
	seg tree; tree.build(1,1,n);
	vector<pair<double,int>> v;
	double res = 0;
	for (int k = 1; k <= n-2; k++) {
		ll s = prefix[n] - prefix[k];
		// cout << s << ' ' << k << '\n';
		int minn = tree.query(1,1,n,k+1,n);
		// cout << minn << ' ' << k << '\n';
		double avg = 1.0*(s-minn)/(n-k-1);
		// cout << avg << ' ' << k << '\n';
		res = max(res,avg);
		v.push_back({avg,k});
	}
	// cout << res << '\n';
	sort(v.begin(),v.end(),cmp);
	for (int i = 0; i < v.size(); i++) {
		if (v[i].fi != res) break;
		cout << v[i].se << ' ';
	}
}
