#include<bits/stdc++.h>
using namespace std;
#define open(x) freopen(x ".in", "r", stdin);freopen(x ".out", "w", stdout);
#define pb push_back
#define int long long
inline int read(){int f=1;int x=0;char c=getchar();while(c<'0'||c>'9'){if(c=='-'){f=-f;}c=getchar();}while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}return x*f;}
inline void wr(int x){if(x<0){putchar('-');x=-x;}if(x>9){wr(x/10);}putchar(x%10+'0');}
const int MAXN = 5e5 + 5;
int a[MAXN] , s[MAXN] , n , k , l , r , f[MAXN][20]; 
namespace ST{
	inline void makeST(){
		for(int i = 1 ; i <= n ; ++i) f[i][0] = i;
		for(int j = 1 ; j <= 19; ++j){
			for(int i = 1 ; i + (1 << j) - 1 <= n ; ++i){
				int x = f[i][j - 1];int y = f[i + (1 << j - 1)][j - 1];
				f[i][j] = (s[x] > s[y] ? x : y);
			}
		}
		return;
	}
	inline int ask(int l,int r){
		int k = (int)log2(r - l + 1);
		int x = f[l][k] ;int y = f[r - (1<<k) + 1][k];
		return (s[x] > s[y] ? x : y);
	}
};
struct Q{
	int h , l , r , t;
	Q(){}
	Q(int h , int l , int r) : h(h),l(l),r(r),t(ST::ask(l,r)) {}
	friend bool operator <(const Q& a , const Q& b){
		return s[a.t]-s[a.h-1] < s[b.t]-s[b.h-1];
	} 
};
priority_queue<Q> q;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> n >> k >> l >> r;
	for(int i=1;i<=n;++i)cin>>a[i];
	for(int i=1;i<=n;++i)s[i]=s[i-1]+a[i];
	ST::makeST();
	for(int i=1;i+l-1<=n;++i){
		q.push({i , i + l - 1 , min(i + r - 1 , n)});
	}
	int out = 0;
	while(k--){
		int h = q.top().h , l = q.top().l , r = q.top().r , t = q.top().t;
		q.pop();out += s[t]-s[h-1];
		//cerr << s[t] - s[h-1] <<endl;
		if(l < t) q.push({h , l , t - 1});
		if(r > t) q.push({h , t + 1 , r});
	}
	cout << out;
	return 0;
}
