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
const long long lINF = 9223372036854775807;
const long long nlINF = 90000000000000;
const int nINF = 1000000000;
unsigned long long MOD = 1000000007;
/*
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
typedef pair<intint, intint> int2_int2;
typedef pair<ll_ll, ll_ll> ll2_ll2;
typedef pair<char, int> char_int;
*/
#include <stdlib.h>
#include <time.h>
using ll = long long;
using int128 = __int128;
/*
int128 amulb(int128 a, int128 b,ll mul_mod) {
	//지금보니 c++일부는 int128지원해서 이걸 안 써도 되지만
	//안되는 곳도 있으니 이때는 이걸 만들어서 써야함.
	ll sum = 0;
	while (b)
	{
		if (b % 2)sum = (sum + a) % mul_mod;
		b = b >> 1;
		a = (a * 2) % mul_mod;
	}
	return sum;
}*/

int128 apowb(int128 a, int128 b, ll pow_mod) {
	ll sum = 1;
	while (b)
	{
		if (b % 2)sum = (sum * a) % pow_mod;
		b = b >> 1;
		a = (a * a) % pow_mod;
	}
	return sum;
}

bool miller_rabin(ll a, ll n) {
	if (n <= 1)return false;
	int128 k = n - 1;
	while (k % 2 == 0) {
		ll h = apowb(a, k, n);
		if (h == n - 1)return true;
		k = k >> 1;
	}
	ll h = apowb(a, k, n);
	if (h == n - 1 || h == 1)return true;
	return false;
}

bool Is_Prime(ll n) {
	if (n <= 1)return false;
	if (n == 2 || n == 3)return true;
	if (n % 2 == 0)return false;
	ll miller_number[12] = { 2,3,5,7,11,13,17,19,23,29,31,37 };
	for (int i = 0; i < 12; i++) {
		if (n == miller_number[i])return true;
		if (!miller_rabin(miller_number[i], n))return false;
	}
	return true;
}

int128 agcdb(int128 a, int128 b) {
	while (b != 0) {
		int128 c = a % b;
		a = b;
		b = c;
	}
	return a;
}

ll pollard_rho(ll n) {
	if (n <= 0)exit(-1);//error input
	if (n == 1)return 1;
	if (n % 2 == 0)return 2;
	if (Is_Prime(n))return n;

	int128 a = (rand() % (n - 2)) + 2;
	int128 b = a;
	int128 c = (rand() % 20) + 1;
	int128 d = 1;

	auto f = [&c, &n](int128 a) {
		return ((a * a) % n + c) % n;
		};
	while (d == 1) {
		a = f(a);
		b = f(f(b));
		d = agcdb(abs(a - b), n);
		if (d == n) {
			a = (rand() % (n - 2)) + 2;
			b = a;
			c = (rand() % 20) + 1;
			d = 1;
		}
	}
	return pollard_rho(d);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	srand(time(NULL));
	ll n;
	cin >> n;
	vector<ll>arr;
	while (n > 1) {
		ll h = pollard_rho(n);
		n /= h;
		arr.push_back(h);
	}
	set<ll>brr;
	brr.insert(1);
	while (arr.size()) {
		vector<ll>crr;
		ll h = arr.back();
		arr.pop_back();
		for (auto a = brr.begin(); a != brr.end(); a++) {
			crr.push_back((*a) * h);
		}
		while (crr.size()) {
			brr.insert(crr.back());
			crr.pop_back();
		}
	}
	cout << brr.size();
}