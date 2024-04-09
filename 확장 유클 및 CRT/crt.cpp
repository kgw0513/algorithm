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

ll2_ll update_gcd(ll a, ll b) {
	vector<ll>arr = { 1,0 };
	vector<ll>brr = { 0,1 };
	vector<ll>r = { a,b };
	vector<ll>q = { INF ,a / b };
	while ((r[r.size() - 2] - (q.back() * r[r.size() - 1])) != 0) {
		arr.push_back(arr[arr.size() - 2] - arr[arr.size() - 1] * q.back());
		brr.push_back(brr[brr.size() - 2] - brr[brr.size() - 1] * q.back());
		r.push_back(r[r.size() - 2] - r[r.size() - 1] * q.back());
		q.push_back(r[r.size() - 2] / r[r.size() - 1]);
	}

	ll gcd = a * arr.back() + b * brr.back();

	return { {arr.back(),brr.back()},gcd };
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
}
