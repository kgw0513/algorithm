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
#include <complex>
#pragma warning(disable:4996)
#define fi first
#define se second
using namespace std;

//rope c++
//#include <ext/rope>
//using namespace __gnu_cxx;

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
typedef pair<int, char> int_char;
typedef complex<double> cpx;

int n, m;
int maps[10][10];

namespace std {
    struct string_hash {
        size_t operator()(const string n) const {
            hash<string> a{}; size_t sa = a(n);
            return sa;
        }
    };
}

unordered_map<string, int, string_hash>arr[10][10];

void Set_standard(string& state) {
    string h = state;
    bool is_comp[10] = {};
    int set_number = 0;
    for (int i = 0; i < state.size(); i++) {
        if (state[i] != '0' && !is_comp[state[i] - '0']) {
            is_comp[state[i] - '0'] = true;
            set_number++;
            for (int j = state.size() - 1; j >= i; j--) {
                if (state[i] == state[j])h[j] = '0' + set_number;
            }
        }
    }

    state = h;
}

bool bState_counting_overflow(string& state) {
    int counting[10] = {};
    for (char& h : state) {
        counting[h - '0']++;
    }

    int sum = 0;
    for (int i = 1; i < 10; i++) {
        sum += (counting[i] >= 1);
    }

    return sum > 1;
}

bool bCan_abandon_state(string& state) {
    if (state[0] == '0')return true;
    for (int i = 1; i < state.size(); i++) {
        if (state[i] == state[0])return true;
    }
    return false;
}

void Merge_State(intint& p, string& state) {
    string new_state = state;
    new_state.erase(new_state.begin());
    if (p.se == 1) {
        if (state[0] == '0')new_state.push_back('9');
        else new_state.push_back(state[0]);


    }
    else {
        if (state[0] == '0' && state.back() == '0')new_state.push_back('9');
        else if (state[0] == '0')new_state.push_back(state.back());
        else if (state.back() == '0' || state[0] == state.back())new_state.push_back(state[0]);
        else {
            for (char& h : new_state) {
                if (h == state.back())h = state[0];
            }
            new_state.push_back(state[0]);
        }
    }

    Set_standard(new_state);
    state = new_state;
}

int Dfs(intint p, string& state) {
    if (p.fi >= n + 1) {
        if (bState_counting_overflow(state))return nINF; //존재할 수 없는 상태라서 nINF전달
        return 0; //끝까지 왔으니 0
    }

    if (arr[p.fi][p.se].find(state) != arr[p.fi][p.se].end())return arr[p.fi][p.se][state];

    intint new_p = { p.fi,p.se + 1 };
    if (new_p.se >= m + 1)new_p = { p.fi + 1,1 };

    int ans = nINF;

    /*
    * TODO : 현재 DP받을때랑 안받을때 상태 확인
    */

    //현 위치값 안쓰고 버릴때
    if (bCan_abandon_state(state)) { //이전 상태중 버려지는 상태가 없는지 확인 (없으면 통과)
        string new_state = state;
        new_state.erase(new_state.begin());
        new_state.push_back('0');
        Set_standard(new_state);

        ans = min(ans, Dfs(new_p, new_state));
    }

    //현 위치값 쓸때
    string new_state = state;
    Merge_State(p, new_state);

    //cout << Dfs(new_p, new_state) << "+" << maps[p.fi][p.se] << "?\n";
    ans = min(ans, Dfs(new_p, new_state) + maps[p.fi][p.se]);

    if (!bState_counting_overflow(state))ans = min(ans, 0); //지금 상태로 끝내도 되니 확인

    return arr[p.fi][p.se][state] = ans;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> maps[i][j];
        }
    }

    string start_state = "";
    for (int i = 0; i < m; i++)start_state += "0";
    cout << Dfs({ 1,1 }, start_state);
}