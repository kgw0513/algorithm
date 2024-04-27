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
unsigned long long MOD = 1000000007;
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

/**
	S*(1-t)+E*t = (원하는 지점) 
	S : 시작값
	E : 도착값
	t : 0~1초 사이의 값
	n : 만약 n이 0~1초 값이 아닐때 n의 값에 따라 0~1초 값으로 설정
	=> t = t/n

	lerp란 자기간 정한 시간에 맞게 이동 값이 어딘지 계산하는 방식입니다.
	또한 게임에서 자주 쓰이는데 그 이유는 물체의 이동과정에서 
	부드럽게 보이기 위해 주로 쓰입니다.

*/
double lerf(double S, double E, double t, double n) {
	t = t / n;
	return S * (1 - t) + E * t;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
}
