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
#define f first
#define s second
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

vector<ll_ll>inputs;

vector<ll>sort_x_y;

map<ll, ll>compression;


struct Seg {
	Seg* left_Seg = nullptr;
	Seg* right_Seg = nullptr;
	ll max_num = 0;

	ll lazy_num = 0;

	Seg(ll l,ll r) {
		if (l == r)return;
		ll mid = (l + r) / 2;
		left_Seg = new Seg(l,mid);
		right_Seg = new Seg(mid + 1, r);
	}

	void lazy_update() {
		max_num = max(max_num, lazy_num);
		if (left_Seg != nullptr)left_Seg->lazy_num = max(left_Seg->lazy_num, lazy_num);
		if (right_Seg != nullptr)right_Seg->lazy_num = max(right_Seg->lazy_num, lazy_num);

		lazy_num = 0;
	}

	void update_Seg(ll l, ll r, ll x_s, ll x_e, ll update_num) {
		lazy_update();
		if (x_s <= l && r <= x_e) { //안에 들어있을시
			lazy_num = update_num;
			lazy_update();
			return;
		}
		if (r < x_s || x_e < l)return;//범위 벗어남
		
		ll mid = (l + r) / 2;
		left_Seg->update_Seg(l, mid, x_s, x_e, update_num);
		right_Seg->update_Seg(mid + 1, r, x_s, x_e, update_num);

		max_num = max(left_Seg->max_num, right_Seg->max_num);
	}

	ll max_Seg(ll l, ll r, ll x_s, ll x_e) {
		lazy_update();
		if (x_s <= l && r <= x_e) { //안에 들어있을시
			return max_num;
		}
		if (r < x_s || x_e < l)return 0;//범위 벗어남
		
		ll mid = (l + r) / 2;
		ll a = left_Seg->max_Seg(l, mid, x_s, x_e);
		ll b = right_Seg->max_Seg(mid + 1, r, x_s, x_e);

		//max_num = max(left_Seg->max_num, right_Seg->max_num);

		return max(a, b);
	}
};
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	ll n, m, t, r, c, insert_num = -1;
	cin >> n >> m >> t;

	sort_x_y.push_back(0);
	sort_x_y.push_back(0);

	for (int i = 0; i < t; i++) {
		cin >> r >> c;

		if (r > n || c > m)continue;
		inputs.push_back({ r,c });

		sort_x_y.push_back(r);
		sort_x_y.push_back(c);
	}
	sort_x_y.push_back(n);
	sort_x_y.push_back(m);

	sort(sort_x_y.begin(), sort_x_y.end());

	for (int num : sort_x_y) {
		if (compression.find(num) != compression.end())continue;
		compression[num] = ++insert_num;
	}

	for (ll_ll& num : inputs) {
		num.f = compression[num.f];
		num.s = compression[num.s];
	}

	n = compression[n];
	m = compression[m];

	sort(inputs.begin(), inputs.end());
	/*
	cout << "시작 : " << 0 << "," << 0 << "\n";
	cout << "끝 : " << n << "," << m << "\n";
	for (ll_ll& num : inputs) {
		cout << num.f << "," << num.s << "\n";
	}
	*/

	Seg* Tree = new Seg(0, m);

	for (int i = 0; i < inputs.size(); i++) {
		ll p_n = inputs[i].f;
		ll p_m = inputs[i].s;
		
		ll p_max = Tree->max_Seg(0, m, p_m, p_m) + 1;

		Tree->update_Seg(0, m, p_m, m, p_max);
	}

	cout << Tree->max_Seg(0, m, 0, m);
}
