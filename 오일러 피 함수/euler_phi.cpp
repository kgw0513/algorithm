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
const long long lINF = 9223372036854775807;
const long long nlINF = 90000000000000;
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
typedef pair<intint, intint> int2_int2;
typedef pair<ll_ll, ll_ll> ll2_ll2;
typedef pair<char, int> char_int;

ll arr[10001];
bool visit[10001];
vector<int>sosu;

ll pow_nm(int n,int m){
	if(m==0)return 1;
	if(m==1)return n;
	ll h=pow_nm(n,m/2);
	h*=h;
	if(m%2==1)h*=n;
	return h;
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	for(int i=2;i<=100;i++){
		if(visit[i])continue;
		for(int j=i*i;j<=10000;j+=i){
			visit[j]=true;
		}
	}
	for(int i=2;i<=10000;i++){
		if(visit[i])continue;
		sosu.push_back(i);
	}
	for(int i=2;i<=10000;i++){
		arr[i]+=arr[i-1];
		int h=i;
		ll ans=1;
		for(int j=0;j<sosu.size();j++){
			int num=sosu[j];
			if(num>h)break;
			if(h%num!=0)continue;
			int counting=0;
			while(h%num==0){
				h/=num;
				counting++;
			}
			ll ans_h=pow_nm(num,counting)-pow_nm(num,counting-1);
			ans*=ans_h;
		}
		arr[i]+=ans;
	}
	int t,w;
	cin>>t;
	while(t--){
		cin>>w;
		cout<<arr[w]+2<<"\n";
	}
}

