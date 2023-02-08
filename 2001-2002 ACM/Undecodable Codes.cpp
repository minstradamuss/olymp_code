#include <bits/stdtr1c++.h>
#include <ext/numeric>

using namespace std;

struct node {
	int len, last, suff;
	string s;

	bool operator<(const node &x) const {
		if (len != x.len) {
			return len < x.len;
		}
		if (s != x.s) {
			return s < x.s;
		}
		if (last != x.last) {
			return last < x.last;
		}
		return suff < x.suff;
	}
};

int n, dist[22][22];
vector<string> codes;

string solve() {
    
	memset(dist, -1, sizeof dist);
	multiset<node> S;
	
	for (int i = 0; i < n; i++) {
		S.insert( {(int) codes[i].size(), i, (int) codes[i].size(), codes[i]} );
	}
	
	while (S.size()) {
		node cur = *S.begin();
		S.erase(S.begin());
		
		if (dist[cur.last][cur.suff] != -1) {
			continue;
		}
		
		if (cur.suff == 0) {
			return cur.s;
		}
		
		dist[cur.last][cur.suff] = cur.len;
		string suff = cur.s.substr(cur.len - cur.suff, cur.suff);
		
		for (int i = 0; i < n; i++) {
			string temp = codes[i].substr(0, cur.suff);
			
			if (temp != suff.substr(0, temp.size()) || (temp == codes[i] && i == cur.last)) {
				continue;
			}
			
			string rem = codes[i].substr(temp.size());
			
			if ((int) codes[i].size() < cur.suff) {
				S.insert( {cur.len, cur.last, cur.suff - (int) codes[i].size(), cur.s} );
			}
			
			else {
				S.insert( {cur.len + (int) rem.size(), i, (int) rem.size(), cur.s + rem} );
		}
	}
	return "NO";
}

int main() {
	
	cin.tie(0); cout.tie(0);
	ios::sync_with_stdio(false);

	int t = 0;
	while (cin >> n, n) {
		codes.resize(n);
		
		for (int i = 0; i < n; i++) {
			cin >> codes[i];
		}
		string ans = solve();
		
		cout << "Code " << ++t << ": " << ans.size() << " bits" << endl;
		
		for (int i = 0; i < (int) ans.size(); i += 20) {
			cout << ans.substr(i, 20) << endl;
		}
		
		cout << endl;
	}
	
	return 0;
}