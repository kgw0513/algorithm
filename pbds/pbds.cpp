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
#define f first
#define s second
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

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds; 
#define ordered_set tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update>

const long long INF = 2147483647;
const long long lINF = 9000000000000000000;
const int nINF = 1007483647;
unsigned long long MOD = 1000000007;
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

bool pbds_erase(ordered_set& arr,int val){
    int p=arr.order_of_key(val);
    auto h=arr.find_by_order(p);
    if(*h!=val)return false;
    arr.erase(h);
    return true;
}

inline int find_middle(ordered_set& arr,ll k){
    int p=(k+1)/2;
    p--;
    return *arr.find_by_order(p);
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	ordered_set arr;
	queue<int>brr;
	
	int n,k,w;
	cin>>n>>k;
	
	ll ans=0;
	for(int i=0;i<k;i++){
	    cin>>w;
	    arr.insert(w);
	    brr.push(w);
	}
	
	ans+=find_middle(arr,k);
	
	n-=k;
	while(n){
	    n--;
	    ll h=brr.front();
	    brr.pop();
	    pbds_erase(arr,h);
	    cin>>w;
	    arr.insert(w);
	    brr.push(w);
	    ans+=find_middle(arr,k);
	}
	cout<<ans;
}
