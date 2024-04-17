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

int arr[500001];

deque<intint>inputs;
vector<int>line;
vector<int>stats;
bool visible[500001];
bool used[500001];
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n, a, b;
	cin >> n;
	while (n--) {
		cin >> a >> b;
		inputs.push_back({ a,b });
		visible[a] = true;
	}
	sort(inputs.begin(), inputs.end());
	line.push_back(0);
	stats.push_back(0);
	while (inputs.size()) {
		a = inputs.front().f;
		b = inputs.front().s;
		inputs.pop_front();
		int h = lower_bound(line.begin(), line.end(), b) - line.begin();
		//cout << a<<","<<b<<"에서 / h:"<<h << "위치.\n";
		if (h >= line.size()) {
			arr[a] = stats.back();
			line.push_back(b);
			stats.push_back(a);
			continue;
		}
		arr[a] = stats[h - 1];
		line[h] = b;
		stats[h] = a;
	}
	int h = stats.back();
	while (h != 0) {
		used[h] = true;
		h = arr[h];
	}
	queue<int>ans;
	for (int i = 1; i <= 500000; i++) {
		if (visible[i] && !used[i]) {
			ans.push(i);
		}
	}
	cout << ans.size() << "\n";
	while (ans.size()) {
		cout << ans.front() << "\n";
		ans.pop();
	}
}
