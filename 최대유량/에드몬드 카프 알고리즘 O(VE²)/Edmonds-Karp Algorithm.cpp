//���� : 11377�� ���� ������ȣ 3 
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

int Cap[2010][2010]; //cap[a][b]�� a->b�� �带 ���� ũ�⸦ ���մϴ�.
int flow[2010][2010];//flow[a][b]�� a->b�� �帣�� �� ���¸� �����մϴ�.

//1~1000 ���� �� �̸�
//1001~2000 ���� �� �̸�
//2005->boss
//2006->����1
//2007->����2
//2008->result

vector<int>line[2010];
//�ܼ� Cap�� ������ �����ϸ� �ð����⵵ ���ذ� �Ǳ⿡
//line�̶�� ���� ó�� ���͸� �ϳ� ����� ���� ó���մϴ�.

//������ ī�� �˰����� O(VE��)�Դϴ�.(V:���� ��,E:���� ��)

int network_flow(int start, int sink) {//�ִ����� ��� �Լ�(�Ű������� ������ġ, ������ġ�� ���մϴ�.)

	int ans = 0;//�ִ�� �带 �� �ִ� ������ ���մϴ�.
	while (1) {
		queue<int>arr;
		arr.push(start);
		vector<int>visit(2010, -1);//�湮 ��ġ ���
		visit[start] = 0;
		while (arr.size() && visit[sink] == -1) {
			int now_h = arr.front();
			arr.pop();
			for (int i = 0; i < line[now_h].size(); i++) {
				int new_h = line[now_h][i];
				if (Cap[now_h][new_h] - flow[now_h][new_h] > 0 && visit[new_h] == -1) {
					//�带 �� �ִ� �����̸鼭 �湮 �� �� ���������� ��� �� �� �ֽ��ϴ�.
					visit[new_h] = now_h;
					arr.push(new_h);
				}
				if (visit[sink] != -1)break;
			}
		}

		if (visit[sink] == -1)break;//���̻� ������ġ���� �帣�� ���ϸ� �ݺ������� Ż���մϴ�.

		int max_f = INF;
		for (int ne = sink; visit[ne] != 0; ne = visit[ne]) {
			int ns = visit[ne];
			//�湮����� �������� ���ư��鼭 flow�� ����� �귶����
			//+f, �������� �귶���� -f�� �����ݴϴ�.
			//�ϴ� �׷��� ���ؼ��� ���� �湮���� �带 �� �ִ� �ִ�
			//������ ���մϴ�.
			max_f = min(max_f, Cap[ns][ne] - flow[ns][ne]);
		}

		//���� ã�� ���� �ִ�� �带 �� �ִ� ������ ã������
		//���� flow�� �����մϴ�.
		//�������� ���� ������� �ϸ� �˴ϴ�.
		for (int ne = sink; visit[ne] != 0; ne = visit[ne]) {
			int ns = visit[ne];
			flow[ns][ne] += max_f;
			flow[ne][ns] -= max_f;
		}

		ans += max_f;//���� ���� ã�� ���� �ִ� ������ ������� �����ݴϴ�.
	}
	return ans;//�ִ�� �� �� �ִ� ���� ������� ��ȯ�մϴ�.
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n, m, k, w;
	cin >> n >> m >> k;//n,m,k �Է� ����

	{//boss�� �� �������� �ִ��������� ����ϴ� �ڵ�.(�ʱ�ȭ 1)
		line[2005].push_back(2006);
		line[2006].push_back(2005);//������ ���� �־����.
		Cap[2005][2006] = n;
		//������ ���� 1���� n���� �з� ���� �ο��մϴ�.

		line[2005].push_back(2007);
		line[2007].push_back(2005);
		Cap[2005][2007] = k;
		//������ ���� 2���� k���� �з� ���� �ο��մϴ�.

		for (int i = 1; i <= n; i++) {
			line[2006].push_back(i);
			line[i].push_back(2006);
			Cap[2006][i] = 1;
		}
		//���� 1�� n���� �з� ���� ó�� �ϱ� ���� �� ��������
		//1���� ���� ������ �ɷ��� �ݴϴ�.

		for (int i = 1; i <= n; i++) {
			line[2007].push_back(i);
			line[i].push_back(2007);
			Cap[2007][i] = 1;
		}
		//���� 2�� k���� �з� ���� ó�� �ϱ� ���� �� ��������
		//1���� ���� ������ �ɷ��� �ݴϴ�.

	}

	for (int i = 1; i <= n; i++) {//�� ������ � �ӹ��� ó�� �� �� �ִ��� ���մϴ�.(�Է� �ޱ� / �ʱ�ȭ 2)
		int work_count;
		cin >> work_count;
		while (work_count--) {
			cin >> w;
			w += 1000; //w+1000�ϸ� �� ������ �� ������ �ǹ��ϰ� �˴ϴ�.

			line[i].push_back(w);
			line[w].push_back(i);
			Cap[i][w] = 1;
		}
	}

	{//�� ������ result�� �� ������ � �� �� �ִ��� �ִ������� �����մϴ�.(�ʱ�ȭ 3)
		//�� ������ 1���� ���� �� �ֽ��ϴ�.
		for (int i = 1001; i <= m + 1000; i++) {
			line[i].push_back(2008);
			line[2008].push_back(i);
			Cap[i][2008] = 1;
		}
	}

	int ans = network_flow(2005, 2008);//������ġ�� ������ ���� ����ϴ�.

	cout << ans;
}
