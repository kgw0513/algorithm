//14444번 백준문제 풀이 코드 
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

int arr[200002];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	string s = "#";
	string w;
	int ans = 1;
	cin >> w;
	for (int i = 0; i < w.size(); i++) {
		s.push_back(w[i]);
		s.push_back('#');
	}
	cout << s << "상태.\n";
	int max_r = 0;
	int mid_p = 0;
	for (int i = 1; i < s.size(); i++) {
		cout << i << "번째 :\n";
		if (max_r >= i) {
			arr[i] = min(arr[mid_p * 2 - i], max_r - i);
		}
		else arr[i] = 0;

		cout << arr[i] << "상태로 시작.\n";
		while (i - arr[i] - 1 >= 0 && i + arr[i] + 1 < s.size() && (s[i - arr[i] - 1] == s[i + arr[i] + 1]))
			arr[i]++;

		if (i + arr[i] > max_r) {
			max_r = i + arr[i];
			mid_p = i;
		}

		ans = max(ans, arr[i]);

		cout << "끝 : " << arr[i] << "/" << max_r << "," << mid_p << "\n";
	}
	cout << ans;
}
