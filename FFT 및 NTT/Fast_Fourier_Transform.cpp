//문제 : https://www.acmicpc.net/problem/15576
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

void FFT(vector<cpx>& arr, cpx w) {
    int n = arr.size();
    if (n <= 1)return;
    vector<cpx>odd(n / 2), even(n / 2);
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            even[i / 2] = arr[i];
        }
        else {
            odd[i / 2] = arr[i];
        }
    }

    FFT(odd, w * w);
    FFT(even, w * w);

    cpx hw = cpx(1, 0);
    for (int i = 0; i < n / 2; i++) {
        arr[i] = even[i] + hw * odd[i];
        arr[i + n / 2] = even[i] - hw * odd[i];
        hw *= w;
    }
}

vector<cpx> mul(vector<cpx> arr, vector<cpx> brr) {
    ll n = 1;
    while (n <= arr.size() || n <= brr.size()) n <<= 1;
    n <<= 1;

    arr.resize(n);
    brr.resize(n);
    vector<cpx>crr(n);

    double deg = -2.0 * PI / n;
    cpx w = cpx(cos(deg), sin(deg));
    cpx iw = cpx(cos(deg), -sin(deg));

    FFT(arr, w); FFT(brr, w);

    for (int i = 0; i < n; i++) {
        crr[i] = arr[i] * brr[i];
        //cout << i << ":" << crr[i] << "\n";
    }

    FFT(crr, iw);
    for (int i = 0; i < n; i++) {
        crr[i] /= cpx(n, 0);
        crr[i] = cpx(round(crr[i].real()), round(crr[i].imag()));
    }

    return crr;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string a, b;
    cin >> a >> b;
    if (a == "0" || b == "0") {
        cout << "0";
        return 0;
    }
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    vector<cpx>arr;
    vector<cpx>brr;
    for (char w : a) {
        arr.push_back(w - '0');
    }
    for (char w : b) {
        brr.push_back(w - '0');
    }

    vector<cpx> h = mul(arr, brr);

    vector<int>ans;
    for (int i = 0; i < h.size(); i++) {
        ans.push_back(round(h[i].real()));
    }
    ans.push_back(0);
    for (int i = 1; i < ans.size(); i++) {
        ans[i] += ans[i - 1] / 10;
        ans[i - 1] %= 10;
    }

    while (ans.size() && ans.back() == 0)ans.pop_back();

    reverse(ans.begin(), ans.end());
    for (int h : ans) {
        cout << h;
    }
}
