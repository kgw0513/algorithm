//5735น๘ น้มุ 
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
#include <cmath>
#include <set>
#include <map>
#include <bitset>
#include <utility>
#include <assert.h>
#include <unordered_set>
#include <unordered_map>
//#include <ext/rope>
#pragma warning(disable:4996)
#define f first
#define s second
using namespace std;
//using namespace __gnu_cxx;

const long long INF = 2147483647;
const long long lINF = 9000000000000000000;
const int nINF = 1000000000;
unsigned long long MOD = 1000000007;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<short, short>sh_sh;
typedef pair<int, int> intint;
typedef pair<int, double> int_d;
typedef pair<intint, double> int2_d;
typedef pair<int, ll> intlong;
typedef pair<ll, ll> ll_ll;
typedef pair<intint, int> int2_int;
typedef pair<int, intint> int_int2;
typedef pair<ll, ll_ll> ll_ll2;
typedef pair<ll_ll, ll>ll2_ll;
typedef pair<intint, intint> int2_int2;
typedef pair<ll_ll, ll_ll> ll2_ll2;
typedef pair<char, int> char_int;

class Trie {
public:
	map<char, Trie*>trie;
	bool is_can = false;
	Trie* fail = nullptr;
	~Trie() {
		for (auto a : trie) {
			delete(a.s);
		}
	}

	void insert(string &w,int p) {
		if (p >= w.size()) {
			is_can = true;
			return;
		}
		if (trie.find(w[p]) == trie.end())trie[w[p]] = new Trie();
		trie[w[p]]->insert(w, p + 1);
	}
};

class Aho {
	Trie* root;
public:
	Aho() {
		root = new Trie();
	}

	void insert(string& w) {
		root->insert(w, 0);
	}

	void bfs_fail() {
		queue<Trie*>arr;
		arr.push(root);

		while (arr.size()) {
			Trie* h = arr.front();
			arr.pop();
			if (h == root) {
				for (auto a : h->trie) {
					a.s->fail = root;
					arr.push(a.s);
				}
				continue;
			}
			for (auto a : h->trie) {
				Trie* k_fail = h->fail;
				while (k_fail != root && (k_fail->trie.find(a.f) == k_fail->trie.end())) {
					k_fail = k_fail->fail;
				}
				if (k_fail->trie.find(a.f) != k_fail->trie.end())k_fail = k_fail->trie[a.f];
				a.s->fail = k_fail;
				if (a.s->fail->is_can)a.s->is_can = true;
				arr.push(a.s);
			}
		}
	}

	int aho_find(string &w) {
		int ans = 0;
		Trie* s = root;
		for (int i = 0; i < w.size(); i++) {
			while (s != root) {
				if (s->trie.find(w[i]) != s->trie.end())
					break;
				s = s->fail;
			}
			if (s->trie.find(w[i]) != s->trie.end()) {
				s = s->trie[w[i]];
				if (s->is_can) {
					ans++;
					s = root;
				}
				continue;
			}
		}
		return ans;
	}
	~Aho() {
		delete(root);
	}
};
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n, m;
	string w;
	while (1) {
		cin >> n >> m;
		cin.ignore();
		if (n == 0 && m == 0)break;
		Aho* home = new Aho();
		while (n--) {
			getline(cin, w);
			home->insert(w);
		}
		home->bfs_fail();

		int ans = 0;
		while (m--) {
			getline(cin, w);
			ans += home->aho_find(w);
		}
		cout << ans << "\n";
		delete(home);
	}
}
