#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct peo{
    int id, ge, gi, fin;
    vector<int> choice;
};
bool cmp(peo& a, peo& b) {
    if (a.fin != b.fin) return a.fin > b.fin;
    return a.ge > b.ge;
}
bool cmp2(peo& a, peo& b) {
    return a.id < b.id;
}
int main(){
    int n, m, k, quota[110], cnt[110] = {0};
    scanf("%d%d%d", &n, &m, &k);
    // sch 是一个二维数组
    vector<peo> stu(n), sch[110];
    for(int i = 0; i < m; i++)
        scanf("%d",&quota[i]);
    for(int i = 0; i < n; i++) {
        scanf("%d%d", &stu[i].ge, &stu[i].gi);
        stu[i].id = i;
        stu[i].fin = stu[i].ge + stu[i].gi;
        stu[i].choice.resize(k);
        for(int j = 0; j < k; j++)
            scanf("%d", &stu[i].choice[j]);
    }
    sort(stu.begin(), stu.end(), cmp);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < k; j++) {
            int schid = stu[i].choice[j];
            int lastindex = cnt[schid] - 1; // cnt[schid]是n， sch[schid]就存的有至少n个学生
            // &&(and)的运算优先级高于||(or)
            // (stu[i].fin == sch[schid][lastindex].fin) && stu[i].ge == sch[schid][lastindex].ge)
            // 判断招生人数是否超过定额，并且当前学生和已招的最后一名学生的总分和统考分数是否相同，如果相同当前学生就算招生人数满了也要被录取
            if(cnt[schid] < quota[schid] || (stu[i].fin == sch[schid][lastindex].fin) && stu[i].ge == sch[schid][lastindex].ge) {
                sch[schid].push_back(stu[i]);
                cnt[schid]++;
                break;
            }
        }
    }
    for(int i = 0; i < m; i++) {
        // 输出要求按学生学号从小到大排序
        sort(sch[i].begin(), sch[i].end(), cmp2);
        for(int j = 0; j < cnt[i]; j++) {
            if(j != 0) printf(" ");
            printf("%d", sch[i][j].id);
        }
        printf("\n");
    }
    return 0;
}