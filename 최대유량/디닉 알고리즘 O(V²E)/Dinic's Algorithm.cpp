//13161번 백준 분단의 슬픔 
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
//#define f first
//#define s second
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

int visit[503];
int save[503];
//501->A진영 사람들.
//502->B진영 사람들.

vector<int>line[503];

int Cap[503][503];
int Flow[503][503];

bool In_A[503];
bool bfs(int s, int e) {
	fill(visit, visit + 503, -1);

	queue<int>arr;
	arr.push(s);
	visit[s] = 0;
	while (arr.size()) {
		int now_h = arr.front();
		arr.pop();
		for (int new_h : line[now_h]) {
			if (visit[new_h] != -1)continue;
			if (Cap[now_h][new_h] - Flow[now_h][new_h] <= 0)continue;
			visit[new_h] = visit[now_h] + 1;
			arr.push(new_h);
		}
	}

	return visit[e] != -1;
}

int dfs(int s, int e, int f) {
	if (s == e)return f;
	for (int& i = save[s]; i < line[s].size(); i++) {
		int now_h = s;
		int new_h = line[s][i];
		if (visit[new_h] != visit[now_h] + 1)continue;
		if (Cap[now_h][new_h] - Flow[now_h][new_h] <= 0)continue;
		int h = dfs(new_h, e, min(f, Cap[now_h][new_h] - Flow[now_h][new_h]));
		if (h > 0) {
			Flow[now_h][new_h] += h;
			Flow[new_h][now_h] -= h;
			return h;
		}
	}
	return 0;
}

bool check_left_A(int s, int e) {
	queue<int>arr;
	arr.push(s);
	In_A[s] = 0;
	while (arr.size()) {
		int now_h = arr.front();
		arr.pop();
		for (int i = 0; i < line[now_h].size(); i++) {
			int new_h = line[now_h][i];
			if (In_A[new_h])continue;
			if (Cap[now_h][new_h] - Flow[now_h][new_h] <= 0)continue;
			In_A[new_h] = true;
			arr.push(new_h);
		}
	}

	return In_A[e];
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n, w;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> w;
		if (w == 1) {
			line[501].push_back(i);
			line[i].push_back(501);
			Cap[501][i] = nINF;
			continue;
		}
		if (w == 2) {
			line[i].push_back(502);
			line[502].push_back(i);
			Cap[i][502] = nINF;
			continue;
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> w;
			if (w == 0)continue;
			line[i].push_back(j);
			Cap[i][j] = w;
		}
	}

	int ans = 0;
	while (bfs(501, 502)) {
		fill(save, save + 503, 0);
		while (int f = dfs(501, 502, INF)) {
			ans += f;
		}
	}

	if (check_left_A(501, 502)) {
		cout << "ERROR!\n";
		return -1;
	}

	cout << ans << "\n";
	bool first_write = true;
	for (int i = 1; i <= n; i++) {
		if (In_A[i]) {
			if (first_write) {
				first_write = false;
				cout << i;
			}
			else cout << " " << i;
		}
	}
	cout << "\n";
	first_write = true;
	for (int i = 1; i <= n; i++) {
		if (!In_A[i]) {
			if (first_write) {
				first_write = false;
				cout << i;
			}
			else cout << " " << i;
		}
	}
	cout << "\n";
}
