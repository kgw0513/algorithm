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
typedef pair<double, double> dd;
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

vector<int>line[30001];

int Articulation_Point(int p, bool root, bool& has_point, vector<int>& num, int& give_num) {
	num[p] = ++give_num;
	int ret = num[p];
	int child = 0;
	for (int i = 0; i < line[p].size(); i++) {
		int new_p = line[p][i];
		if (num[new_p] == 0) {
			child++;
			int h = Articulation_Point(new_p, false, has_point, num, give_num);

			if (!root&&num[p] <= h) {
				has_point = true;
			}
			ret = min(ret, h);
		}
		else {
			ret = min(ret, num[new_p]);
		}
	}
	if (root && child >= 2) {
		has_point = true;
	}
	cout << p << ":" << ret << "\n";
	return ret;
}
void ans() {
	for (int i = 0; i < 30001; i++)
		line[i].clear();
	int n, m, a, b;
	cin >> n >> m;
	vector<int>num(n+1, 0);
	while (m--) {
		cin >> a >> b;
		line[a].push_back(b);
		line[b].push_back(a);
	}
	m = 0;
	bool has_point = false;
	Articulation_Point(1, true, has_point, num, m);

	cout << (has_point ? "YES" : "NO") << "\n";
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int t;
	cin >> t;
	while (t--) {
		ans();
	}
}
