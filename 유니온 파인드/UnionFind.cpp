//BOJ 20040 사이클 게임 
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
unsigned long long MOD = 1000003;
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

int Union[500001];
int find(int n) {
	if (Union[n] != n)return Union[n] = find(Union[n]);
	return n;
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	for (int i = 0; i < 500001; i++)Union[i] = i;
	int n, m, a, b;
	cin >> n >> m;
	for(int i=1;i<=m;i++){
		cin >> a >> b;
		a++; b++;
		int h_a = find(a);
		int h_b = find(b);
		if (h_a == h_b) {
			cout << i;
			return 0;
		}
		if (h_a > h_b)swap(h_a, h_b);
		Union[h_a] = h_b;
	}
	cout << 0;
}
