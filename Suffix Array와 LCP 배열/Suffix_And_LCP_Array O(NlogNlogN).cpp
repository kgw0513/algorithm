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
unsigned long long MOD1 = 1000000363;
unsigned long long MOD2 = 1000000007;
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

int gap;
int group[500005];
int SA[500005];
int temp[500005];
int LCP[500005];
string S;
bool cmp(int a, int b) {
	if (group[a] != group[b])return group[a] < group[b];
	a += gap;
	b += gap;
	if (a < S.size() && b < S.size())return group[a] < group[b];
	return a > b;
}

void Suffix_Array() {
	for (int i = 0; i < S.size(); i++) {
		SA[i] = i;
		group[i] = S[i];
	}
	for (gap = 1;; gap <<= 1) {
		sort(SA, SA + S.size(), cmp);

		for (int i = 0; i < (int)S.size() - 1; i++) {
			temp[i + 1] = temp[i] + cmp(SA[i], SA[i + 1]);
		}

		for (int i = 0; i < S.size(); i++) {
			group[SA[i]] = temp[i];
		}

		if (temp[(int)S.size() - 1] == (int)S.size() - 1)break;

	}
}

void Lcp_Array() {
	for (int i = 0, k = 0; i < S.size(); i++, k = max(k - 1, 0)) {
		if (group[i] == (int)S.size() - 1)continue;
		int j = SA[group[i] + 1];
		while (S[i + k] == S[j + k]) {
			k++;
		}
		LCP[group[i]] = k;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> S;
	Suffix_Array();
	Lcp_Array();
	for (int i = 0; i < S.size(); i++) {
		cout << SA[i] + 1;
		if (i != (int)S.size() - 1)cout << " ";
	}
	cout << "\nx";
	for (int i = 0; i < (int)S.size() - 1; i++) {
		cout << " " << LCP[i];
	}
}
