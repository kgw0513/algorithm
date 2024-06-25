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

	vector<dd2d>arr;//{{B��,ans��},������ ��ġ}
	vector<ll>ans = { 0 };

	auto cross_cal = [](dd2d& a, dd2d& b) {//���ٽ����� ������ x(= A[i]) ���ϱ�
		return (a.f.s - b.f.s) / (b.f.f - a.f.f);
		};


	for (int i = 1; i < n; i++) {
		dd2d in_h = { {B[i - 1],ans.back()},0 };//�� ó�� ������ ���� ��ġ�� 0���� ����.
		while (arr.size()) {
			in_h.s = cross_cal(arr.back(), in_h); //���ο� �������� in_h�� �־� ���� ���� �������� ���� �ڿ��ִ��� Ȯ��
			if (in_h.s > arr.back().s)break;
			arr.pop_back();
			if (arr.size() == 0)return -1; //��� ���� ����!
		}
		arr.push_back(in_h);

		int p = upper_bound(arr.begin(), arr.end(), dd2d({ { 0,0 } ,double(A[i]) }), cmp) - arr.begin();
		//�̺�Ž������ A[i]�� �ش�Ǵ� ���� ã��

		dd2d h = arr[p - 1]; //ã�� ������ ans�� ����ؼ� �ֱ�
		ans.push_back(h.f.f * A[i] + h.f.s);
	}
	cout << ans.back();
}
