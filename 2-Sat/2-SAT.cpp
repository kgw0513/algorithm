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

vector<int>line[20002];
vector<int>reverse_line[20002];

stack<int>cosaraju;

int visit[20002];
void dfs1(int p) {
	if (visit[p])return;
	visit[p] = 1;
	for (int next_p : line[p]) {
		dfs1(next_p);
	}
	cosaraju.push(p);
}

void dfs2(int p,const int& give_num) {
	if (visit[p])return;
	//cout << p << "에" << give_num << "설정.\n";
	visit[p] = give_num;
	for (int next_p : reverse_line[p]) {
		//cout << p << "->" << next_p << "\n";
		dfs2(next_p,give_num);
	}
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n, m, a, b;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> a >> b;
		int now_a_state = abs(a);
		int reverse_a_state = abs(a);
		if (a > 0)reverse_a_state = m + a;
		else now_a_state = m + abs(a);

		int now_b_state = abs(b);
		int reverse_b_state = abs(b);
		if (b > 0)reverse_b_state = m + b;
		else now_b_state = m + abs(b);

		line[reverse_a_state].push_back(now_b_state);
		//cout << reverse_a_state << "->" << now_b_state << "생성.\n";
		line[reverse_b_state].push_back(now_a_state);
		//cout << reverse_b_state << "->" << now_a_state << "생성.\n";

		reverse_line[now_b_state].push_back(reverse_a_state);
		reverse_line[now_a_state].push_back(reverse_b_state);
	}

	for (int i = 1; i <= 2 * m; i++) {
		dfs1(i);
	}

	fill(visit, visit + 20002, 0);
	int give_num = 0;
	while (cosaraju.size()) {
		dfs2(cosaraju.top(), ++give_num);
		cosaraju.pop();
	}

	for (int i = 1; i <= 2 * m; i++) {
		if (visit[i] == visit[m + i]) {
			cout << "OTL";
			return 0;
		}
	}
	cout << "^_^";
}
