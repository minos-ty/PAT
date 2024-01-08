#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;
struct node {
    string name;
    int status, month, time, day, hour, minute;
};

bool cmp(node a, node b) {
    // 名称不相同就按名字来排序，相同就按时间来排序
    return a.name != b.name ? a.name < b.name : a.time < b.time;
}

// 10 10 10 10 10 10 20 20 20 15 15 15 15 15 15 15 20 30 20 15 15 10 10 10   cents/minute
// 00-01 01-02 02-03 03-04 04-05 05-06 ...... 23 - 24

// todo 这里把时间全部先转换成分钟来计算会不会更简单？
// todo 貌似不行， 因为每个时间段的计费标准不一样， 这种方式貌似是效率最高的
double billFromZero(node call, int *rate) {
    // 直接计算从当月第一天到通话时间的花费
    // ate[call.hour] * call.minute 分钟的花费
    // 一整天的费用： 10*60 + 10*60 + 10*10 .... 15*60 .... = 60*(每一个时段相加)， 简单的数学题
    // rate[24]-费用的累加  rate[24] * 60-打一天电话的花费  rate[24] * 60 * call.day-从一号开始打到当前日的花费
    double total = rate[call.hour] * call.minute + rate[24] * 60 * call.day;

    // 计算每个小时的花费
    for (int i = 0; i < call.hour; i++)
        total += rate[i] * 60;
    return total / 100.0;  // cents to dollar    100cents = 1dollar
}

int main() {
    int rate[25] = {0}, n;
    for (int i = 0; i < 24; i++) {
        scanf("%d", &rate[i]);
        rate[24] += rate[i]; //  a*60+b*60+c*60... = 60*(a + b + c) 累加后可以方便计算通话一整天的花费
    }
    scanf("%d", &n);
    vector <node> data(n);
    for (int i = 0; i < n; i++) {
        cin >> data[i].name;
        // 主要这里的读取时间的方式， 这样直接读取数字就避免去处理带:的字符串了
        scanf("%d:%d:%d:%d", &data[i].month, &data[i].day, &data[i].hour, &data[i].minute);
        string temp;
        cin >> temp;
        data[i].status = (temp == "on-line") ? 1 : 0;
        data[i].time = data[i].day * 24 * 60 + data[i].hour * 60 + data[i].minute;
    }
    sort(data.begin(), data.end(), cmp);
    map <string, vector<node>> custom;
    for (int i = 1; i < n; i++) {
        if (data[i].name == data[i - 1].name && data[i - 1].status == 1 && data[i].status == 0) {
            custom[data[i - 1].name].push_back(data[i - 1]);
            custom[data[i].name].push_back(data[i]);
        }
    }
    for (auto it: custom) {
        vector <node> temp = it.second;
        cout << it.first;
        printf(" %02d\n", temp[0].month);
        double total = 0.0;
        for (int i = 1; i < temp.size(); i += 2) {
            double t = billFromZero(temp[i], rate) - billFromZero(temp[i - 1], rate);
            printf("%02d:%02d:%02d %02d:%02d:%02d %d $%.2f\n", temp[i - 1].day, temp[i - 1].hour, temp[i - 1].minute,
                   temp[i].day, temp[i].hour, temp[i].minute, temp[i].time - temp[i - 1].time, t);
            total += t;
        }
        printf("Total amount: $%.2f\n", total);
    }
    return 0;
}