#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n,k;
int main() {
    int i, j;
    while( ~scanf("%d%d", &n, &k)&&(n|k)) {
        int t=n%(k+1);
        if(t==1)
            puts("Jiang");
        else
            puts("Tang");
    }
    return 0;
}