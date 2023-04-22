#include<bits/stdc++.h>
using namespace std;
#define open(x) freopen(x ".in", "r", stdin);freopen(x ".out", "w", stdout);
#define pb push_back
#define int long long
inline int read(){int f=1;int x=0;char c=getchar();while(c<'0'||c>'9'){if(c=='-'){f=-f;}c=getchar();}while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}return x*f;}
inline void wr(int x){if(x<0){putchar('-');x=-x;}if(x>9){wr(x/10);}putchar(x%10+'0');}
const int p = 1e9 + 7;
const int MAXN = 1e6 + 5;
int f[MAXN][21];
int a[MAXN],b[MAXN],n,m;
inline int find(int x,int l){
	if(x == f[x][l]) return x;
	else return f[x][l] = find(f[x][l],l);
}
inline void toge(int x,int y,int l){
	int r1=find(f[x][l],l);int r2=find(f[y][l],l);
	if(r1!=r2)f[f[r1][l]][l]=r2;
	return;
}
namespace ok{
	inline void A(){
		cin>>n>>m;
		for(int i=1;i<=n;++i){
			for(int j=0;j<=19;++j){
				f[i][j] = i;
			}
		} 
		for(int i=1;i<=m;++i){
			int l1,r1,l2,r2;cin >> l1 >> r1 >> l2 >> r2;
			int k=(int)log2(r1-l1+1);
			toge(l1,l2,k);
			toge(r1-(1<<k)+1,r2-(1<<k)+1,k);
		}
		for(int j=19;j>=1;--j){
			for(int i=1;i+(1<<j)-1<=n;++i){
				int fa=find(i,j);
				if(i!=fa){
					toge(fa,i,j-1);
					toge(fa+(1<<j-1),i+(1<<j-1),j-1);
				}
			}
		}
		int ans = 0;
		for(int i=1;i<=n;++i){
			if(f[i][0]==i){
				if(ans==0)ans = 9;
				else ans=ans*10%p;
			}
		}
		cout << ans;
		return;
	}
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	ok::A();
	return 0;
} 
