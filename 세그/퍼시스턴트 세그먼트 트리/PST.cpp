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

stack<class Node*>remove_d;
class Node {
	int sum = 0;
	Node* left_Node = nullptr;
	Node* right_Node = nullptr;
public:
	Node() {
		/*그냥 Node 생성용*/
	}

	Node(int s,int e){/*초기화 용*/
		if (s >= e)return;
		left_Node = new Node(s,(s+e)/2);
		right_Node = new Node(((s + e) / 2) + 1, e);
		remove_d.push(left_Node);
		remove_d.push(right_Node);
	}

	Node* makeNode(int now_s, int now_e, int find_s, int find_e,int plus) {
		if (now_e < find_s || find_e < now_s)return this;

		if (find_s <= now_s && now_e <= find_e) {
			Node* h = new Node();
			remove_d.push(h);
			h->left_Node = this->left_Node;
			h->right_Node = this->right_Node;
			h->sum = this->sum + plus;
			return h;

		}

		Node* h = new Node();
		remove_d.push(h);
		h->left_Node = this->left_Node->makeNode(now_s, (now_s + now_e) / 2, find_s, find_e, plus);
		h->right_Node = this->right_Node->makeNode(((now_s + now_e) / 2) + 1, now_e, find_s, find_e, plus);
		h->sum = h->left_Node->sum + h->right_Node->sum;
		return h;
	}

	int prefix_sum(int now_s, int now_e, int find_s, int find_e) {
		if (now_e < find_s || find_e < now_s)return 0;

		if (find_s <= now_s && now_e <= find_e)return sum;

		int h = 0;
		if (left_Node != nullptr)h += left_Node->prefix_sum(now_s, (now_s + now_e) / 2, find_s, find_e);
		if (right_Node != nullptr)h += right_Node->prefix_sum(((now_s + now_e) / 2) + 1, now_e, find_s, find_e);
		return h;
	}
};

vector<Node*>trees;//초기 seg
vector<int>inputs[100001];
ll ans() {
	trees.clear();
	trees.resize(100002, nullptr);
	for (int i = 0; i < 100001; i++)inputs[i].clear();

	trees[0] = new Node(1, 100000);

	int n, m, x, y, xs, xe, ys, ye;
	ll sum = 0;
	cin >> n >> m;
	while (n--) {
		cin >> x >> y;
		inputs[x].push_back(y);
	}
	/* PST 만들기 시작*/

	for (x = 0; x <= 100000; x++) {
		if (x != 0)trees[x] = trees[x - 1];
		for (int j = 0; j < inputs[x].size(); j++) {
			y = inputs[x][j];
			trees[x] = trees[x]->makeNode(1, 100000, y, y, 1);
		}
	}

	/* PST 만들기 끝*/

	while (m--) {
		cin >> xs >> xe >> ys >> ye;
		sum += trees[xe]->prefix_sum(1, 100000, ys, ye);
		if (xs != 0)sum -= trees[xs-1]->prefix_sum(1, 100000, ys, ye);
	}

	while (remove_d.size()) {
		delete remove_d.top();
		remove_d.pop();
	}
	return sum;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int t;
	cin >> t;
	while (t--) {
		cout << ans() << "\n";
	}
}
