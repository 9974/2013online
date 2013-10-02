#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1000006;
int f[maxn], cnt[maxn];
char s[maxn];
int main() {
    int i, j, cas;
    scanf("%d", &cas);
    while(cas--) {
        scanf("%s", s);
        int l = strlen(s);
        j = 0;
        f[0] = 0;
        for(i = 1; i < l; i++) {
            while(j && s[i] != s[j])
                j = f[j - 1];
            if(s[i] == s[j])
                j++;
            f[i] = j;
        }
        //for(i = 0; i < l; i++) printf("%d", f[i]);
        for(i = 0; i < l - 1; i++)
            cnt[f[i]]++;
        j = l;
        int ans = 0;
        while(j) {
            j = f[j - 1];
            if(cnt[j]) {
                ans = j;
                break;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}