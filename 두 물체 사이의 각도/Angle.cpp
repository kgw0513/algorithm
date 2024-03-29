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
#include<unordered_map>
#include <bitset>
//#include <fstream> //txt입출력 헤더함수
#pragma warning(disable:4996)
#define f first
#define s second
using namespace std;

const int INF = 2147483647;
const int nINF = 10000000;

typedef long long ll;
typedef pair<double, double> t_double;
typedef pair<int, int> intint;
typedef pair<int, ll> intlong;
typedef pair<intint, int> int2_int;
typedef pair<intint, intint> int2_int2;
typedef pair<int, char> int_char;

const ll mod = 1000000007;

vector<intint>output;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    t_double a, b;
    cout << "p1 player의 기준으로 봤을때 p2과의 각도 계산기.\n";
    cout << "p1 x,y: ";
    cin >> a.f >> a.s;
    cout << "p2 x,y:";
    cin >> b.f >> b.s;
    t_double xy = { b.f - a.f,b.s - a.s };
    double radian = atan2(xy.s, xy.f);
    double pi = 3.1415926535;
    double degree = 180 * radian / pi;
    cout << "각도 값:" << degree;
}