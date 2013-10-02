#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int Md[] = {31, 37, 41, 43, 47};
int s[6][55][55], bell[6][55];
void init() {
    for(int i = 0;i < 5;i ++)
        s[i][0][0] = 1;
    for(int i = 1;i <= 50; i++) {
        for(int j = 0;j < 5;j ++)
            s[j][i][1] = 1;
        for(int j = 1;j <= i; j++) {
            for(int k = 0;k < 5; k++)
                s[k][i][j] = (s[k][i-1][j-1] + j*s[k][i-1][j])%Md[k];
        }
        for(int j = 0;j < 5; j++) {
            bell[j][i] = 0;
            for(int k = 1;k <= i; k++)
                bell[j][i] = (bell[j][i] + s[j][i][k])%Md[j];
        }
    }
}


int x[5];
void mult(int a[55][55], int b[55][55], int n) {
      int c[55][55] = {0};
      int i, j, k;
      for(k = 0; k < n; k++)
            for(i = 0; i < n; i++) if(a[i][k])
                  for(j = 0; j< n; j++)
                        c[i][j] += a[i][k]*b[k][j];
      for(i = 0; i < n; i++)
            for(j = 0; j < n; j++)
                  a[i][j] = c[i][j] % n;
}
int ans[55][55], A[55][55];
int gao(int n, int mod, int id) {
    //  printf("id = %d\n", id);
      if(n <= mod) return bell[id][n];
      int i, j;
      for(i = 0; i < mod; i++)
            for(j = 0; j < mod; j++) {
                  ans[i][j] = (i==j);
                  A[i][j] = 0;
            }
      for(i = 0; i < mod-1; i++)
            A[i+1][i] = 1;
       //     puts("#$%%");
      A[0][mod-1] = A[1][mod-1] = 1;
      n -= mod;
     // printf("n = %d\n", n);
      while(n > 0) {
            if(n&1) mult(ans, A, mod);
            mult(A, A, mod);
            n >>= 1;
      }
    //  puts("#$%#$5");
     // printf("~~~");
      int ret = 0;
      for(i = 0; i < mod; i++)
            ret += bell[id][i+1]*ans[i][mod-1];
      return ret%mod;
}

void ex_gcd(int a, int b, int &x, int &y) {
      if(!b) {
            x = 1; y = 0;
      }
      else { ex_gcd(b, a%b, y, x); y -= x*(a/b);}
}
int china(int n, int a[], int m[]) {
    int M = 1;
    for(int i = 0;i < n; i++) M *= m[i];
    int ret = 0;
    for(int i = 0;i < n; i++) {
        int w = M/m[i], x, y;
        ex_gcd(w, m[i], x, y);
        ret = (ret + x*w*a[i])%M;
    }
    return (ret + M)%M;
}
int main() {
     // printf("%d\n", 1<<31-1);
      init();
      int i, j, cas, n;
      scanf("%d", &cas);
      while(cas--) {
            scanf("%d", &n);
            for(i = 0; i < 5; i++) {
                    //    printf("i = %d\n", i);
                  x[i] = gao(n, Md[i], i);
                 // printf("i = %d\n", i);
            }
            printf("%d\n", china(5, x, Md));
      }
      return 0;
}
