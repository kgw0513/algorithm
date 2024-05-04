//문제 : 11377번 백준 열혈강호 3 
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

int Cap[2010][2010]; //cap[a][b]는 a->b로 흐를 양의 크기를 정합니다.
int flow[2010][2010];//flow[a][b]는 a->b로 흐르는 양 상태를 저장합니다.

//1~1000 직원 각 이름
//1001~2000 업무 각 이름
//2005->boss
//2006->팀장1
//2007->팀장2
//2008->result

vector<int>line[2010];
//단순 Cap에 간선을 저장하면 시간복잡도 손해가 되기에
//line이라는 간선 처리 벡터를 하나 만들어 따로 처리합니다.

//에드몬드 카프 알고리즘은 O(VE²)입니다.(V:정점 수,E:간선 수)

int network_flow(int start, int sink) {//최대유량 계산 함수(매개변수는 시작위치, 종료위치를 말합니다.)

	int ans = 0;//최대로 흐를 수 있는 유량을 말합니다.
	while (1) {
		queue<int>arr;
		arr.push(start);
		vector<int>visit(2010, -1);//방문 위치 기록
		visit[start] = 0;
		while (arr.size() && visit[sink] == -1) {
			int now_h = arr.front();
			arr.pop();
			for (int i = 0; i < line[now_h].size(); i++) {
				int new_h = line[now_h][i];
				if (Cap[now_h][new_h] - flow[now_h][new_h] > 0 && visit[new_h] == -1) {
					//흐를 수 있는 상태이면서 방문 한 적 없을때에만 들어 올 수 있습니다.
					visit[new_h] = now_h;
					arr.push(new_h);
				}
				if (visit[sink] != -1)break;
			}
		}

		if (visit[sink] == -1)break;//더이상 종료위치까지 흐르지 못하면 반복문에서 탈출합니다.

		int max_f = INF;
		for (int ne = sink; visit[ne] != 0; ne = visit[ne]) {
			int ns = visit[ne];
			//방문기록을 역순으로 돌아가면서 flow에 제대로 흘렀으면
			//+f, 역순으로 흘렀으면 -f를 더해줍니다.
			//일단 그러기 위해서는 지금 방문에서 흐를 수 있는 최대
			//유량을 구합니다.
			max_f = min(max_f, Cap[ns][ne] - flow[ns][ne]);
		}

		//내가 찾은 길의 최대로 흐를 수 있는 유량을 찾았으면
		//이제 flow에 적용합니다.
		//적용방식은 위에 적힌대로 하면 됩니다.
		for (int ne = sink; visit[ne] != 0; ne = visit[ne]) {
			int ns = visit[ne];
			flow[ns][ne] += max_f;
			flow[ne][ns] -= max_f;
		}

		ans += max_f;//현재 내가 찾은 길의 최대 유량을 결과값에 더해줍니다.
	}
	return ans;//최대로 올 수 있는 유량 결과값을 반환합니다.
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n, m, k, w;
	cin >> n >> m >> k;//n,m,k 입력 받음

	{//boss가 각 직원에게 최대유량으로 명령하는 코드.(초기화 1)
		line[2005].push_back(2006);
		line[2006].push_back(2005);//역간선 역시 넣어야함.
		Cap[2005][2006] = n;
		//보스가 팀장 1에게 n개의 분량 일을 부여합니다.

		line[2005].push_back(2007);
		line[2007].push_back(2005);
		Cap[2005][2007] = k;
		//보스가 팀장 2에게 k개의 분량 일을 부여합니다.

		for (int i = 1; i <= n; i++) {
			line[2006].push_back(i);
			line[i].push_back(2006);
			Cap[2006][i] = 1;
		}
		//팀장 1은 n개의 분량 일을 처리 하기 위해 각 직원에게
		//1개의 일을 지정할 능력을 줍니다.

		for (int i = 1; i <= n; i++) {
			line[2007].push_back(i);
			line[i].push_back(2007);
			Cap[2007][i] = 1;
		}
		//팀장 2는 k개의 분량 일을 처리 하기 위해 각 직원에게
		//1개의 일을 지정할 능력을 줍니다.

	}

	for (int i = 1; i <= n; i++) {//각 직원이 어떤 임무를 처리 할 수 있는지 정합니다.(입력 받기 / 초기화 2)
		int work_count;
		cin >> work_count;
		while (work_count--) {
			cin >> w;
			w += 1000; //w+1000하면 그 직원이 할 업무를 의미하게 됩니다.

			line[i].push_back(w);
			line[w].push_back(i);
			Cap[i][w] = 1;
		}
	}

	{//각 업무가 result로 총 업무를 몇개 할 수 있는지 최대유량을 설정합니다.(초기화 3)
		//각 업무는 1개만 보낼 수 있습니다.
		for (int i = 1001; i <= m + 1000; i++) {
			line[i].push_back(2008);
			line[2008].push_back(i);
			Cap[i][2008] = 1;
		}
	}

	int ans = network_flow(2005, 2008);//시작위치를 보내고 답을 얻습니다.

	cout << ans;
}
