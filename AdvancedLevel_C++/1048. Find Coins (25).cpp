#include <iostream>
using namespace std;
int a[1001];
int main() {
    int n, m, temp;
    scanf("%d %d", &n, &m);
    for(int i = 0; i < n; i++) {
        scanf("%d", &temp);
        a[temp]++;
    }
    for(int i = 0; i < 1001; i++) {
        if(a[i]) {
            // 因为 m - i 还是可能会等于i, 如果i位置的coin只出现一次，但是两次这个位置相加刚好等于需要支付的钱， 那么就会出错
            // 所以这里暂时把数量减去1，当前判断做完后再把记录加回来
            a[i]--;
            if(m > i && a[m-i]) {
                printf("%d %d", i, m - i);
                return 0;
            }
            a[i]++;
        }
    }
    printf("No Solution");
    return 0;
}