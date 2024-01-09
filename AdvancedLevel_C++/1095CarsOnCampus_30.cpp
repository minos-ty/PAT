#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <string>
#include <map>

using namespace std;
struct node {
    char id[10];
    int time, flag = 0;
};

// 先按车牌号排序， 再按时间排序
bool cmp1(node a, node b) {
    if (strcmp(a.id, b.id) != 0)
        return strcmp(a.id, b.id) < 0;
    else
        return a.time < b.time;
}

bool cmp2(node a, node b) {
    return a.time < b.time;
}

int main() {
    int n, k, maxtime = -1, tempindex = 0;
    scanf("%d%d\n", &n, &k);
    vector<node> record(n), car;
    for (int i = 0; i < n; i++) {
        char temp[5];
        int h, m, s;
        scanf("%s %d:%d:%d %s\n", record[i].id, &h, &m, &s, temp);
        // 1h = 60m, 1m = 60s
        int temptime = h * 3600 + m * 60 + s;
        record[i].time = temptime;
        record[i].flag = strcmp(temp, "in") == 0 ? 1 : -1;
    }
    sort(record.begin(), record.end(), cmp1);
    map<string, int> mapp;
    // car中保存所有有效记录，一个车牌号可能有多条有效记录
    for (int i = 0; i < n - 1; i++) {
        if (strcmp(record[i].id, record[i + 1].id) == 0 && record[i].flag == 1 && record[i + 1].flag == -1) {
            car.push_back(record[i]);
            car.push_back(record[i + 1]);
            // 记录每个车牌号停靠的时长
            mapp[record[i].id] += (record[i + 1].time - record[i].time);
            if (maxtime < mapp[record[i].id]) {
                maxtime = mapp[record[i].id];
            }
        }
    }

    // 第二次对有效数据按时间排序
    sort(car.begin(), car.end(), cmp2);
    // 存放car中对应下标时间节点校园中车辆数量, 这样就避免的了用车牌号做关键词查找的问题
    vector<int> cnt(n);
    for (int i = 0; i < car.size(); i++) {
        if (i == 0)
            cnt[i] += car[i].flag;
        else
            // flag 1 in, -1 out.  不断把这些数据累加就能得到某个点有多少车还在停车场里
            cnt[i] = cnt[i - 1] + car[i].flag;
    }
    for (int i = 0; i < k; i++) {
        int h, m, s;
        scanf("%d:%d:%d", &h, &m, &s);
        int temptime = h * 3600 + m * 60 + s;
        int j;
        for (j = tempindex; j < car.size(); j++) {
            if (car[j].time > temptime) {
                printf("%d\n", cnt[j - 1]);
                // 只要找到一个节点就结束当前循环
                break;
            } else if (j == car.size() - 1) {
                // 遍历完以后没有找到时间结束节点
                // 即要查询的时间比现有记录的时间都要靠后， 相当于查询所有记录里还存在的车数量
                printf("%d\n", cnt[j]);
            }
        }
        // 因为题目本来就表明问询的时间节点时正序排序， 即时间从小到大。所以
        // 查询完成后把当前的index记录下来作为初始值， 这样就不用每个询问都要从头遍历一遍car
        tempindex = j;
    }
    for (auto & it : mapp) {
        // 只要停车时间和最大值相等的车牌号都会输出
        if (it.second == maxtime)
            printf("%s ", it.first.c_str());
    }
    //  maxtime / 3600 s2h  (maxtime % 3600) / 60 s2m  maxtime % 60 秒转换成分钟还剩余的数就是还剩多少秒
    printf("%02d:%02d:%02d\n", maxtime / 3600, (maxtime % 3600) / 60, maxtime % 60);
    return 0;
}