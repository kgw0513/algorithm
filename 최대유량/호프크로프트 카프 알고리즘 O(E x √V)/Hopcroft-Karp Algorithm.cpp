//���� : 11375�� ���� ������ȣ
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
pbds c++ set����
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type, less<int>, rb_tree_tag,tree_order_statistics_node_update>

multiset�� ���� ������ ���� �ڵ忡�� ������ �ٸ� �Ʒ� �ڵ�� ����.(��� erase�� �����۵� ���� �ʴ´�.)
#define ordered_set tree<int, null_type, less_equal<int>, rb_tree_tag,tree_order_statistics_node_update>

�̿ܿ� ������ �ø��� ������ Ÿ�Ժ����ϸ� �ȴ�.
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
	//ũ�� n
	int n;

	//���� ������ A, ������ ������ B�� �ΰ� ��
	//A������ ����Ű�°� �ڽ��� ����� B	��ġ�� �ǹ�.
	//B������ ����Ű�°� �ڽ��� ����� A��ġ�� �ǹ�.
	//A�� B���� -1�� �ִ� �κ��� ���� ����� �κ��� ���ٴ� ��.
	//dist�� A��� ���� 0,1,2,... �湮 ���� �ǹ�.
	//dist���� INF�� ���� �� �ִµ�, �̴� 0�������� �湮 ���� ����� ���̻� ���ٴ� ���̴�. 
	vector<int>A, B, dist;

	//�̺� �׷��� ���� ���� ���� ����
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
		dist[a] = INF; //�̰� ���ϸ� �̹� �Ұ����Ѱ� �˸鼭�� �� �ͼ� �ٽ� ����ϴ� �ð����� �Ѵ�.
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