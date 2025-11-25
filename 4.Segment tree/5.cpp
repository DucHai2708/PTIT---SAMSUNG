#include <bits/stdc++.h>
#define fi first
#define se second
 
using namespace std;
using ll = long long;
const int Mod = 1e9+7;

/*
Segment tree tìm gcd của 1 đoạn
Segment tree vào từng đoạn con trong mảng
*/

class seg {
	public:
		int n; vector<int> st;
		seg(int n) {
			this->n = n;
			st.assign(4*n+5,0);
		}
		void build(vector<int> &a, int id, int l, int r) {
			if (l == r) st[id] = a[l];
			else {
				int m = (l + r) / 2;
				build(a,2*id,l,m);
				build(a,2*id+1,m+1,r);
				st[id] = __gcd(st[2*id],st[2*id+1]);
			}
		}
		int query(vector<int> &a, int id, int l, int r, int u, int v) {
			if (v < l or u > r) return 0;
			if (u <= l && r <= v) return st[id];
			int m = (l + r) / 2;
			return __gcd(query(a,2*id,l,m,u,v), query(a,2*id+1,m+1,r,u,v));
		}
};
 
int count_subarray(vector<int> &v) {
	int n = v.size()-1; // ép begin = 1
	if (n == 0) return INT_MAX;
	seg tree(n); tree.build(v,1,1,n);	
	int j = 0; int ans = INT_MAX;
	for (int i = 1; i <= n; i++) {
		if (j < i) j = i;
		while (j <= n && tree.query(v,1,1,n,i,j) > 1) ++j;
		if (j <= n && tree.query(v,1,1,n,i,j) == 1) ans = min(ans,j-i+1);
	}
	return ans;
}

void Haidz() {
	int n, k;
	cin >> n >> k;
	vector<int> a(n+1,0);
	for (int i = 1; i <= n; i++) cin >> a[i];
	int ans = INT_MAX; 
	vector<int> v; v.push_back(-2708);
	for (int i = 1; i <= n; i++) {
		if (a[i] % k == 0) {
			v.push_back(a[i]/k);
		}
		else {
			if (!v.empty()) {
				ans = min(ans,count_subarray(v));
				v.clear();
				v.push_back(-2708);
			}
		}
	}
	if (!v.empty()) ans = min(ans,count_subarray(v));
	if (ans == INT_MAX) cout << -1 << '\n';
	else cout << ans << '\n';
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	//code here
	int tc; cin >> tc;
	while (tc--) {
		Haidz();
	}
}