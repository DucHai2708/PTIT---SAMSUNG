#include <bits/stdc++.h>
#define fi first
#define se second
 
using namespace std;
using ll = long long;
const int Mod = 1e9+7;

class kmp {
	public:
		vector<int> lps(string pat) {
			int n = pat.size();
			vector<int> pi(n,0);
			for (int i = 1; i < n; i++) {
				int j = pi[i-1];
				while (j > 0 && pat[i] != pat[j]) {
					j = pi[j-1];
				}
				if (pat[i] == pat[j]) j++;
				pi[i] = j;
			}
			return pi;
		}

		vector<int> lpss(string pat) {
			int n = pat.size();
			vector<int> pi(n,0);
			int i = 1, j = 0;
			while (i < n) {
				if (pat[i] == pat[j]) {
					pi[i++] = ++j;
				}
				else {
					if (j != 0) j = pi[j-1];
					else pi[i++] = 0;
				}
			}
			return pi;
		}

		void solve(string txt, string pat) {
			int n = txt.size(), m = pat.size();
			vector<int> pi = lpss(pat);
			int i = 0, j = 0;
			while (i < n) {
				if (txt[i] == pat[j]) {
					++i; ++j;
				}
				if (j == m) {
					cout << i - j + 1 << ' ';
					j = pi[j-1];
				}
				else if (i < n && txt[i] != pat[j]) {
					if (j == 0) ++i;
					else j = pi[j-1];
				}
			}
		}	
};

void Haidz() {
	string txt, pat;
	cin >> txt >> pat;
	kmp KMP;
	KMP.solve(txt,pat);
}
 
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	//code here
	Haidz();
}