#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn = 33005;
typedef long long ll;
int Q;
bool vis[1055];
int mark[1055];

int ch[maxn][2], n = 1;
vector <int> val[maxn];
void insert(ll ip, int len, int id) {
    int p = 0;
    for(int i = 31; i >= 32 - len; i--) {
        int k = (ip >> i) & 1;
        if(!ch[p][k])
            ch[p][k] = n++;
        p = ch[p][k];
    }
    val[p].push_back(id);
}
void color(ll ip) {
    int p = 0;
    for(int i = 31; i >= 0; i--) {
        int k = (ip >> i) & 1;
        if(!ch[p][k]) return;
        p = ch[p][k];
        for(int j = 0; j < val[p].size(); j++)
            if(vis[val[p][j]])
                mark[val[p][j]] = Q;
    }
}
bool judge(ll ip) {
    int p = 0;
    for(int i = 31; i >= 0; i--) {
        int k = (ip >> i) & 1;
        if(!ch[p][k]) return false;
        p = ch[p][k];
        for(int j = 0; j < val[p].size(); j++) {
            if(mark[val[p][j]] == Q)
                return true;
        }
    }
    return false;
}

ll getIp(int a, int b, int c, int d) {
    ll ret = 0;
    ret |= (ll) a << 24;
    ret |= (ll) b << 16;
    ret |= (ll) c << 8;
    ret |= d;
    return ret;
}

char op[3];
int a, b, c, d, e, id;
int main() {
    while(~scanf("%s", op)) {
        if(op[0] == 'E') {
            int n;
            scanf("%d%d", &id, &n);
            while(n--) {
                scanf("%d.%d.%d.%d/%d", &a, &b, &c, &d, &e);
                insert(getIp(a, b, c, d), e, id);
            }
            vis[id] = 1;
        }
        if(op[0] == 'D') {
            scanf("%d", &id);
            vis[id] = 0;
        }
        if(op[0] == 'F') {
            Q++;
            scanf("%d.%d.%d.%d", &a, &b, &c, &d);
            color(getIp(a, b, c, d));
            scanf("%d.%d.%d.%d", &a, &b, &c, &d);
            puts( judge(getIp(a, b, c, d))? "F" : "D");
        }
    }
    return 0;
}