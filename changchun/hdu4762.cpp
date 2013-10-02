#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
using namespace std;
#define LL __int64
int andbit =1000000000; //进位数
const int numbit = 9; //数组一位表示整形数的位数
const int numlen = 2001; //整形数的位数
const int maxn = numlen/numbit + 10; //数组的位数
const char outstr[] = {'%','0','0'+numbit,'d',0}; //标准化输出字符串
int pow[maxn];
struct BigInt
{
    int len;
    int num[maxn];
    BigInt()
    {
        memset(num,0,sizeof(num));
        len=1;
    }
    void ToBig(const char s[])
    {
        int l=0,ret,ten;
        for(int i=(int)strlen(s)-1;i>=0;i-=numbit)
        {
            ret = 0; ten = 1;
            for(int j=0;j<numbit&&i-j>=0;j++)
            {
                ret += (s[i-j]-'0')*ten;
                ten *= 10;
            }
            num[l++]=ret;
        }
        len=l;
        fixlen(*this,len-1);
    }
    void OutBig()
    {
        printf("%d",num[len-1]);
        for(int i=len-2;i>=0;i--)
            printf(outstr,num[i]);
        puts("");
    }
    void fixlen(BigInt &C,int i)
    {
        while(C.num[i]==0&&i>0) i--;
        C.len=i+1;
    }
    BigInt operator+(const BigInt &B)
    {
        BigInt C;
        int i=0,la=len,lb=B.len;
        for(i=0;;i++)
        {
            if(i>=la&&i>=lb) break;
            if(i<la)C.num[i]+=num[i];
            if(i<lb)C.num[i]+=B.num[i];
            if(C.num[i]>=andbit)
            {
                C.num[i+1]++;
                C.num[i]-=andbit;
            }
        }
        fixlen(C,i);
        return C;
    }
    BigInt operator-(const BigInt &B)//A>B
    {
        BigInt C;
        int i=0,la=len,lb=B.len;
        for(i=0;;i++)
        {
            if(i>=la&&i>=lb) break;
            if(i<la)C.num[i]+=num[i];
            if(i<lb)C.num[i]-=B.num[i];
            if(C.num[i]<0)
            {
                C.num[i+1]--;
                C.num[i]+=andbit;
            }
        }
        fixlen(C,i);
        return C;
    }
    BigInt operator*(const BigInt &B)
    {
        BigInt C;
        int i,j;
        LL t;
        for(i=0;i<len;i++)
        {
            for(j=0;j<B.len;j++)
            {
                t = (LL)num[i]*(LL)B.num[j] + C.num[i+j];
                if(t >= andbit)
                {
                    C.num[i+j+1]+=(int)(t/andbit);
                    t %= andbit;
                }
                C.num[i+j]=(int)t;
            }
        }
        fixlen(C,i+j+1);
        return C;
    }
    void div(int d)
    {
        int t=0;
        for(int i=len-1;i>=0;i--)
        {
            t=t*andbit+num[i];
            num[i]=t/d;
            t%=d;
        }
        fixlen(*this,len);
    }
    BigInt(int t)
    {
        num[0]=0;
        len=0;
        while(t)
        {
            num[len++]=t%andbit;
            t/=andbit;
        }
        if(!len)len=1;
        fixlen(*this,len-1);
    }
    int reallen()
    {
        int ret=(len-1)*numbit;
        int t=num[len-1];
        while(t)
        {
            t/=10;
            ret++;
        }
        if(len==1&&num[0]==0)ret++;
        return ret;
    }
    bool operator <(const BigInt &B)const
    {
        if(len<B.len) return 1;
        if(len>B.len) return 0;
        for(int i=len-1;i>=0;i--)
        {
            if(num[i]<B.num[i])return 1;
            if(num[i]>B.num[i])return 0;
        }
        return 0;//1为< 0为>=
    }
};
int gcd(int a, int b) {
    return b ? gcd(b, a%b) : a;
}
int n, m;
int main() {
    int i, j, cas;
    scanf("%d", &cas);
    while(cas--) {
        scanf("%d%d", &m, &n);
        int g = n;
        BigInt s = 1;
        for(i = 1; i < n; i++) {
            int tm = m;
            int t = gcd(g, tm);
            g /= t; tm /= t;
            s = s *BigInt(tm);
        }
        printf("%d/", g);
        s.OutBig();
    }
    return 0;
}