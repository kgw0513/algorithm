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
typedef pair<ll_ll, double> dd2d;

bool cmp(const dd2d& a, const dd2d& b) {
	return a.s < b.s;
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n;
	cin >> n;
	vector<int>A(n);
	vector<int>B(n);
	for (int i = 0; i < n; i++)cin >> A[i];
	for (int i = 0; i < n; i++)cin >> B[i];

	vector<dd2d>arr;//{{B값,ans값},교차점 위치}
	vector<ll>ans = { 0 };

	auto cross_cal = [](dd2d& a, dd2d& b) {//람다식으로 교차점 x(= A[i]) 구하기
		return (a.f.s - b.f.s) / (b.f.f - a.f.f);
		};


	for (int i = 1; i < n; i++) {
		dd2d in_h = { {B[i - 1],ans.back()},0 };//맨 처음 교차점 시작 위치는 0으로 가정.
		while (arr.size()) {
			in_h.s = cross_cal(arr.back(), in_h); //새로운 교차점을 in_h에 넣어 이전 선의 교차점과 비교해 뒤에있는지 확인
			if (in_h.s > arr.back().s)break;
			arr.pop_back();
			if (arr.size() == 0)return -1; //상상도 못한 에러!
		}
		arr.push_back(in_h);

		int p = upper_bound(arr.begin(), arr.end(), dd2d({ { 0,0 } ,double(A[i]) }), cmp) - arr.begin();
		//이분탐색으로 A[i]에 해당되는 범위 찾기

		dd2d h = arr[p - 1]; //찾은 범위를 ans에 계산해서 넣기
		ans.push_back(h.f.f * A[i] + h.f.s);
	}
	cout << ans.back();
}
