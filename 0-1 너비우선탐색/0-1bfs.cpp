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

char arr[52][52];
bool brr[52][52];

intint dxdy[4] = { {-1,0},{1,0},{0,-1},{0,1} };
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n;
	cin >> n;
	for (int i = 0; i < 52; i++)
		for (int j = 0; j < 52; j++) {
			brr[i][j] = true;
		}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			cin >> arr[i][j];
			brr[i][j] = false;
		}

	brr[1][1] = true;
	deque<intint>crr;
	crr.push_back({ 1,1 });
	for (int change = 0;; change++) {
		int size = crr.size();
		while (size--) {
			int x = crr.front().f;
			int y = crr.front().s;
			crr.pop_front();
			for (int i = 0; i < 4; i++) {
				int new_x = x + dxdy[i].f;
				int new_y = y + dxdy[i].s;
				if (brr[new_x][new_y])continue;
				if (arr[new_x][new_y] == '1') {
					crr.push_front({ new_x,new_y });
					size++;
				}
				else crr.push_back({ new_x,new_y });
				brr[new_x][new_y] = true;
			}
		}
		if (brr[n][n]) {
			cout << change;
			return 0;
		}
	}
}
