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
constexpr long long MOD1 = 1000000007;
constexpr long long MOD2 = 1000000009;
constexpr long long MOD3 = 998244353;
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

int n, m, q;

int Union[100002];
int Counting[100002];

void InitUnion() {
    for (int i = 1; i <= n; i++) {
        Union[i] = i;
        Counting[i] = 1;
    }
}

int Find(int n) {
    if (Union[n] == n)return n;
    return Union[n] = Find(Union[n]);
}

void CalUnion(int a, int b) {
    a = Find(a);
    b = Find(b);
    if (a == b)return;
    if (a > b)swap(a, b);
    Counting[a] += Counting[b];
    Union[b] = a;
}

vector<int_int2>lines;

intint QueryInputs[100002];
intint Querylr[100002];
//[이동 간선 수]={쿼리번호}
vector<int>QueryMid[100002];
intint QueryAns[100002];

bool MidSetting() {
    InitUnion();
    bool bIsChange = false;
    for (int i = 0; i <= m; i++)QueryMid[i].clear();
    for (int i = 1; i <= q; i++) {
        if (Querylr[i].fi > Querylr[i].se)continue;
        bIsChange = true;
        QueryMid[(Querylr[i].fi + Querylr[i].se) / 2].push_back(i);
    }
    return bIsChange;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int a, b, c;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        lines.push_back({ c,{a,b} });
    }

    sort(lines.begin(), lines.end());

    cin >> q;
    for (int i = 1; i <= q; i++) {
        cin >> QueryInputs[i].fi >> QueryInputs[i].se;
        Querylr[i] = { 1,m };
    }

    while (MidSetting()) {
        int line_count = 0;
        for (int_int2& line : lines) {
            line_count++;
            CalUnion(line.se.fi, line.se.se);
            for (int p : QueryMid[line_count]) {
                intint QueryInput = QueryInputs[p];
                if (Find(QueryInput.fi) == Find(QueryInput.se)) {
                    QueryAns[p] = { line.fi,Counting[Find(QueryInput.fi)] };
                    Querylr[p].se = line_count - 1;
                }
                else {
                    Querylr[p].fi = line_count + 1;
                }
            }
        }
    }

    for (int i = 1; i <= q; i++) {
        if (QueryAns[i].fi == 0)cout << "-1\n";
        else cout << QueryAns[i].fi << " " << QueryAns[i].se << "\n";
    }
}