//문제 : https://www.acmicpc.net/problem/34036 (34036번 걸어가요)
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
typedef pair<int, char> int_char;
typedef complex<double> cpx;

//{g}
ll gcd(ll a, ll b) {
    assert(a != 0 && b != 0);
    while (a % b != 0) {
        ll c = a % b;
        a = b;
        b = c;
    }
    return b;
}

//{{s,t},g}
ll2_ll xgcd(ll a, ll b) {
    ll s, t;
    ll r1 = a, r2 = b, s1 = 1, s2 = 0, t1 = 0, t2 = 1;
    ll r, q;
    while (r2) {
        q = r1 / r2;
        r = r1 % r2;
        r1 = r2, r2 = r;
        s = s1 - q * s2;
        s1 = s2, s2 = s;
        t = t1 - q * t2;
        t1 = t2, t2 = t;
    }
    s = s1;
    t = t1;
    return { {s, t}, r1 };
}

//{나머지,모듈러}
ll_ll crt(vector<ll_ll>arr) {
    pair<__int128, __int128> a = arr[0];
    a.fi %= a.se;
    for (int i = 1; i < arr.size(); i++) {
        pair<__int128, __int128> b = arr[i];
        ll g = gcd(a.se, b.se);
        if (a.fi % g != b.fi % g) {
            return { -1,-1 };
        }
        ll2_ll h = xgcd(a.se / g, b.se / g);
        __int128 mod = a.se / g * b.se;
        pair<__int128, __int128> c = {
            ((((a.fi * (b.se / g)) % mod) * h.fi.se) % mod) +
            ((((b.fi * (a.se / g)) % mod) * h.fi.fi) % mod),
            mod
        };
        c.fi = (c.fi + mod) % mod;
        a = c;
    }
    return a;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<ll_ll>arr(n);
    for (ll_ll& w : arr) {
        cin >> w.fi >> w.se;
    }

    ll_ll h = crt(arr);
    if (h.se == -1) {
        cout << -1;
        return 0;
    }

    for (ll_ll& w : arr) {
        while (w.fi > h.fi)h.fi += h.se;
    }
    cout << h.fi;
}