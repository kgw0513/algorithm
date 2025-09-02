//문제 : 11375번 백준 열혈강호
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

constexpr double PI = 3.1415926535;
constexpr long long INF = 2147483647;
constexpr long long lINF = 9000000000000000000;
constexpr long long nlINF = lINF / 10000;
constexpr int nINF = 1007483647;
constexpr unsigned long long MOD1 = 1000000007;
constexpr unsigned long long MOD2 = 1000000009;
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

class Hopcroft_Karp {
private:
	//크기 n
	int n;

	//왼쪽 정점을 A, 오른쪽 정점을 B라 두고 각
	//A정점이 가리키는건 자신이 연결된 B	위치를 의미.
	//B정점이 가리키는건 자신이 연결된 A위치를 의미.
	//A와 B에서 -1이 있는 부분은 아직 연결된 부분이 없다는 뜻.
	//dist는 A행렬 기준 0,1,2,... 방문 순서 의미.
	//dist에서 INF가 남을 수 있는데, 이는 0정점에서 방문 가능 방법이 더이상 없다는 것이다. 
	vector<int>A, B, dist;

	//이분 그래프 현재 연결 상태 간선
	vector<vector<int>>lines;

	void bfs() {
		queue<int>arr;
		for (int i = 0; i < n; i++) {
			if (A[i] == -1) {
				dist[i] = 0;
				arr.push(i);
			}
			else dist[i] = INF;
		}

		while (!arr.empty()) {
			int a = arr.front();
			arr.pop();
			for (int b : lines[a]) {
				if (B[b] != -1 && dist[B[b]] == INF) {
					dist[B[b]] = dist[a] + 1;
					arr.push(B[b]);
				}
			}
		}
	}

	bool dfs(int a) {
		for (int b : lines[a]) {
			if (B[b] == -1 || (dist[B[b]] == dist[a] + 1 && dfs(B[b]))) {
				A[a] = b;
				B[b] = a;
				return true;
			}
		}
		dist[a] = INF; //이거 안하면 이미 불가능한걸 알면서도 또 와서 다시 계산하는 시간낭비를 한다.
		return false;
	}
public:
	Hopcroft_Karp(int input_n, int output_n) {
		n = input_n;
		A.resize(input_n, -1);
		B.resize(output_n, -1);
		dist.resize(input_n, INF);
		lines.resize(input_n, vector<int>());
	}

	void add_line(int a, int b) {
		lines[a].push_back(b);
	}

	int solve() {
		int match = 0;
		while (1) {

			bfs();

			int flow_count = 0;
			for (int i = 0; i < n; i++) {
				if (A[i] == -1 && dfs(i))flow_count++;
			}
			if (flow_count == 0)break;
			match += flow_count;
		}
		return match;
	}

	const vector<int>& getA() const {
		return A;
	}
	const vector<int>& getB() const {
		return B;
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n, m, w;
	cin >> n >> m;
	Hopcroft_Karp Karp(n, m);

	for (int i = 0; i < n; i++) {
		cin >> w;
		while (w-- > 0) {
			int j;
			cin >> j;
			Karp.add_line(i, j - 1);
		}
	}

	cout << Karp.solve();
	return 0;
}