#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 111111;
const LL INF = 1LL<<32;
LL a[maxn],b[maxn],c[maxn];
int cnt=0;
LL cal(LL A,LL B,LL C){
    if(A>B)
        return 0;
    LL ans=(B-A)/C+1;
    return ans;
}
int go(int n,LL m){
    int ans=0;
    for(int i=0;i<n;++i){
        ans+=cal(a[i],min<LL>(m,b[i]),c[i]);
    }
    return ans;
}
LL binary(int n,LL l,LL r){
    LL m=0,ans=-1;
    while(l<=r){
        m=(l+r)>>1;
        if(go(n,m)&1)
            ans=m,r=m-1;
        else
            l=m+1;
    }
    return ans;
}
int gao(int n,LL t){
    int ans=0;
    for(int i=0;i<n;++i){
        if(t>=a[i]&&t<=b[i])
            ans+=((t-a[i])%c[i]==0);
    }
    return ans;
}
int main()
{
    int n,i;
    while(~scanf("%d",&n)){
        for(i=0;i<n;++i){
            scanf("%I64d%I64d%I64d",a+i,b+i,c+i);
        }
        LL l=0,r=INF;

        LL ans=binary(n,l,r);
        if(~ans){
            printf("%d %d\n",(int)ans,gao(n,ans));
        }
        else
            puts("DC Qiang is unhappy.");
    }
    return 0;
}