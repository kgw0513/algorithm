//백준 2316번 풀이 코드. 
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

int Cap[1210][1210];
int flow[1210][1210];

bool is_in_line[1210][1210];
vector<int>line[1210];

int visit[1210];
int visit_rem = 0;
int dfs(int v, int cf, int Finish) {
	//cout << v << "방문.\n";
	visit[v] = visit_rem;
	if (v == Finish)return cf;

	for (int i = 0; i < line[v].size(); i++) {
		int next_v = line[v][i];
		if (visit[next_v] == visit_rem)continue;
		if (Cap[v][next_v] - flow[v][next_v] <= 0)continue;

		int res = dfs(next_v, min(cf, Cap[v][next_v] - flow[v][next_v]), Finish);

		if (res) {
			flow[v][next_v] += res;
			flow[next_v][v] -= res;
			return res;
		}
	}

	return 0;
}
int network_flow() {
	
	int sum = 0;

	while (1) {
		visit_rem++;
		int h = dfs(401, INF, 802);
		if (h == 0)break;
		sum += h;
		//cout << visit_rem << "통과.\n";
	}

	return sum;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n, p, a, b;
	cin >> n >> p;
	for (int i = 1; i <= p; i++) {
		cin >> a >> b;
		int a_s = a + 400;//a입구
		int a_e = a + 800;//a출구
		int b_s = b + 400;//b입구
		int b_e = b + 800;//b출구

		if (!is_in_line[a_s][a_e]) {
			is_in_line[a_s][a_e] = true;
			line[a_s].push_back(a_e);
			line[a_e].push_back(a_s);
			if (a == 1 || a == 2)
				Cap[a_s][a_e] = nINF;
			else 
				Cap[a_s][a_e] = 1;
		}

		if (!is_in_line[b_s][b_e]) {
			is_in_line[b_s][b_e] = true;
			line[b_s].push_back(b_e);
			line[b_e].push_back(b_s);
			if (b == 1 || b == 2)
				Cap[b_s][b_e] = nINF;
			else
				Cap[b_s][b_e] = 1;
		}

		if (!is_in_line[a_e][b_s]) {
			is_in_line[a_e][b_s] = true;
			line[a_e].push_back(b_s);
			line[b_s].push_back(a_e);
			Cap[a_e][b_s] = nINF;
		}

		if (!is_in_line[b_e][a_s]) {
			is_in_line[b_e][a_s] = true;
			line[b_e].push_back(a_s);
			line[a_s].push_back(b_e);
			Cap[b_e][a_s] = nINF;
		}
	}

	cout << network_flow();
}
