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

int employer[500001];
int arr_in[500001];
int arr_out[500001];
int deep = 0;

vector<int>line[500001];
void dfs(int p) {
	arr_in[p] = ++deep;
	for (int i = 0; i < line[p].size(); i++) {
		dfs(line[p][i]);
	}
	arr_out[p] = deep;
}

int fenwick[500001];

void add_fenwick(int n, int plus) {
	while (n < 500001) {
		fenwick[n] += plus;
		n += n & -n;
	}
}
int fenwick_sum(int n) {
	int sum = 0;
	while (n) {
		sum += fenwick[n];
		n -= n & -n;
	}
	return sum;
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n, m, a, b;
	char w;
	cin >> n >> m;
	cin >> employer[1];
	for (int i = 2; i <= n; i++) {
		cin >> employer[i] >> a;
		line[a].push_back(i);
	}
	dfs(1);
	while (m--) {
		cin >> w;
		if (w == 'p') {
			cin >> a >> b;
			add_fenwick(arr_in[a] + 1, b);
			add_fenwick(arr_out[a] + 1, -b);
			continue;
		}
		cin >> a;
		cout << employer[a] + fenwick_sum(arr_in[a]) << "\n";
	}

