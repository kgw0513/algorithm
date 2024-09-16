//BOJ 3033번 문제 
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

const long long INF = 2147483647;
const long long lINF = 9000000000000000000;
const long long nlINF = lINF / 100;
const int nINF = 1007483647;
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

ll c = 2;
const ll MOD1 = 10007;

bool find_string(int len, string w) {
	unordered_map<ll, vector<int>>arr;
	ll sum1 = 0;
	ll max_c1 = 1;
	for (int i = 0; i < len; i++) {
		if (i >= 1) {
			max_c1 = (max_c1 * c) % MOD1;
		}
		sum1 = ((sum1 * c) + w[i]) % MOD1;
	} 

	arr[sum1].push_back(0);
	for (int i = 1; i <= w.size() - len; i++) {
		sum1 = (sum1 - w[i - 1] * max_c1) % MOD1;
		sum1 = (((sum1 + MOD1) * c) + w[i + len - 1]) % MOD1;
		for (ll h : arr[sum1]) {
			if (w.compare(i, len, w, h, len) == 0) return true;
		}
		arr[sum1].push_back(i);
	}
	return false;
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	string w;
	cin >> w >> w;
	//cout << find_string(1,w);
	//return 0;
	int s = 1, e = w.size();
	int ans = 0;
	while (s <= e) {
		int mid = (s + e) / 2;
		if (find_string(mid, w)) {
			ans = mid;
			s = mid + 1;
		}
		else {
			e = mid - 1;
		}
	}
	cout << ans;
}
