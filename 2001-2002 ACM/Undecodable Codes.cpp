// Author: minstradamuss

// к сожалению, из-за неумения правильно считать время до конца контеста, 
// не удалось прогнать исправленную версию на тестах системы, но 
// эта версия вроде должна была пройти


#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

//#define DEBUG
#define ll long long
#define ld long double
#define null NULL
#define all(a) a.begin(), a.end()
#define ff first
#define ss second
#define forn(m) for (int i = 0; i < m; i += 1)
#define loop(j) for (int j = !i; j < m; ++j, j += (i == j))
#define push(n) prior_queue.push(nodes[tmp] = nt);
#define sz(x) (int) x.size()

string codeword[21];

struct Node {
	string s;
	string total;
	bool operator <(const Node &other) const {
		if (sz(total) == sz(other.total)) {
		    return total > other.total;
		}
		return sz(total) > sz(other.total);
	}
};

unordered_map<string, Node> nodes;
unordered_set<string> vis;

bool pred_processing (const string &s1, const string &s2) {
	if (sz(s1) < sz(s2)) {
	    return 0;
	}
	else {
	    if (s2 == s1.substr(0, s2.size())) {
	        return 1;
	    }
	    return 0;
	}
}

int m;
string change() {
	priority_queue <Node> prior_queue;
	vis.clear();
	nodes.clear();
	string tmp;
	forn(m) {
	    loop (j) {
	        if (pred_processing(codeword[i], codeword[j])) {
				tmp = codeword[i].substr(sz(codeword[j]));
				Node nt = {tmp, codeword[i]};
				if (!nodes.count(tmp) or nodes[tmp] < nt) {
				    push(nodes[tmp] = nt);
				}
			}
	    }
	}

	while (!prior_queue.empty()) {
		Node node = prior_queue.top();
		prior_queue.pop();

		if (vis.count(node.s)) {
		    continue;
		}
		vis.insert(node.s);

		for (int i = 0; i < m; i++) {
			if (node.s == codeword[i]) {
			    return node.total;
			}

			if (pred_processing(codeword[i], node.s)) {
				string tmp = codeword[i].substr(node.s.size());
				Node nt = {tmp, node.total + tmp};
				if (!nodes.count(tmp) or nodes[tmp] < nt) {
				    push(nodes[tmp] = nt);
				}
			}

			if (pred_processing (node.s, codeword[i])) {
				string tmp = node.s.substr(codeword[i].size());
				Node nt = {tmp, node.total};
				if (!nodes.count(tmp) or nodes[tmp] < nt) {
				    push(nodes[tmp] = nt);
				}
			}
		}
	}
	assert(1);
	//return prior_queue;
}

int main() {
	int case_num = 0;

	string res;

	while (cin >> m && m != 0) {
		for (int i = 0; i < m; ++i)
			cin >> codeword[i];

		res = change();
		case_num += 1;
		cout << "Code" << " " << case_num << ":" << " " << sz(res) << " " << "bits" << endl;
		while (sz(res) > 20) {
		    cout << res.substr(0, 20) << endl;
		    res = res.substr(20);
		}
		cout << res << endl;
	}
}
