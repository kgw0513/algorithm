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
#pragma warning(disable:4996)
#define fi first
#define se second
using namespace std;
/*
rope c++
#include <ext/rope>
using namespace __gnu_cxx;
*/

/*
pbds c++ set전용
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type, less<int>, rb_tree_tag,tree_order_statistics_node_update>

multiset을 쓰고 싶으면 위의 코드에서 마지막 줄만 아래 코드로 변경.(대신 erase가 정상작동 되지 않는다.)
#define ordered_set tree<int, null_type, less_equal<int>, rb_tree_tag,tree_order_statistics_node_update>

이외에 범위를 늘리고 싶으면 타입변경하면 된다.
ex. int->ll, less_equal<ll>
*/

constexpr double PI = 3.1415926535;
constexpr long long INF = 2147483647;
constexpr long long lINF = 9000000000000000000;
constexpr long long nlINF = lINF / 10000;
constexpr int nINF = 1007483647;
constexpr unsigned long long MOD1 = 1000000363;
constexpr unsigned long long MOD2 = 1000000007;
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

inline double dist(intint a, intint b) {
	int x = a.fi - b.fi;
	int y = a.se - b.se;
	return sqrt(x * x + y * y);
}

inline ll ccw(ll_ll a, ll_ll b, ll_ll c) {
	return  (a.fi * b.se + b.fi * c.se + c.fi * a.se)
		- (b.fi * a.se + c.fi * b.se + a.fi * c.se);
}

bool sort_first(intint& a, intint& b) {
	if (a.fi == b.fi)return a.se < b.se;
	return a.fi < b.fi;
}

intint first_point;
bool sort_second(intint& a, intint& b) {
	ll h = ccw(first_point, a, b);
	if (h == 0) {
		return dist(first_point, a) < dist(first_point, b);
	}
	return h > 0;
}

void ConvexHull(deque<intint>& points) {
	deque<intint>h;

	sort(points.begin(), points.end(), sort_first);
	first_point = points.front();
	points.pop_front();
	h.push_back(first_point);

	sort(points.begin(), points.end(), sort_second);

	while (points.size()) {
		if (h.size() < 2) {
			h.push_back(points.front());
			points.pop_front();
			continue;
		}

		while (h.size() >= 2 && ccw(h[h.size() - 2], h[h.size() - 1], points.front()) <= 0) {
			h.pop_back();
		}

		h.push_back(points.front());
		points.pop_front();
		continue;
	}

	points = h;
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	double ans = 0.0;
	int n;
	cin >> n;
	deque<intint>arr(n);
	for (int i = 0; i < n; i++) {
		cin >> arr[i].fi >> arr[i].se;
	}

	ConvexHull(arr);

	n = arr.size();
	assert(n >= 2);
	if (n == 2) {
		ans = max(ans, dist(arr[0], arr[1]));
	}
	else {
		int l = 0, r = 1;
		while (abs(ccw(arr[n - 1], arr[l], arr[r])) < abs(ccw(arr[n - 1], arr[l], arr[(r + 1) % n]))) {
			r++;
		}

		while (r < n) {
			ans = max(ans, dist(arr[l], arr[r]));
			if (abs(ccw(arr[l], arr[(l + 1) % n], arr[r])) < abs(ccw(arr[l], arr[(l + 1) % n], arr[(r + 1) % n]))) r++;
			else l++;
		}
	}
	cout.precision(10);
	cout << ans;
}