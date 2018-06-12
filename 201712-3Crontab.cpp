#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <set>

using namespace std;

// 注意不区分大小写！！
// 思路：首先根据crontab处理字符串，找出各单独参数minute, hour等可取的值，为避免重复，放入set中。
// 之后有两种方法，一种是遍历从开始时间s到结束时间e的所有datetime，看其各元素是否在对应的set中，
// 因为分钟数太多超时； 另一种是将各set元素组合，再加上可行的year，看星期数是否能对上，
// 以及datetime是否在s,e之间

string monStr[13] = {"", "jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec"};
string dayStr[7] = {"sun", "mon", "tue", "wed", "thu", "fri", "sat"};
int daysOfMon[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
map<string, int> monTab, dayTab; // "jan" -> 1, "sun" -> 0
void build_table(); // 记录月份字符对应哪个月，星期字符对应星期几
enum CronType {Minute, Hour, Date, Month, Day};
map<string, vector<string> > output;

// 全转为小写
void all_to_lower(string &s);
// 字符转为整数
int str_to_int(string &s);
// 整数转为字符，整数为1位时补前导0
string int_to_str(int x);
// "Jan", "Sun", "1"等转为对应整数
int timestr_to_int(CronType tag, string &str);
// 根据CronType，将"*", "1,3", "1-3", "Sat"等转化成可以取到的值的set
set<int> cronstr_to_set(string &str, CronType tag);
// 判断是否为闰年
bool is_leap(int year);
// 计算某天为星期几，0-6
int calcDay(int year, int month, int date);

int main(int argc, char const *argv[])
{
     build_table();
     int n;
     string s, e;
     cin >> n >> s >> e;
     string syy = s.substr(0, 4), eyy = e.substr(0, 4);
     int syInt = str_to_int(syy), eyInt = str_to_int(eyy);
     while(n--) {
         string minute, hour, date, month, day, cmd;
         cin >> minute >> hour >> date >> month >> day >> cmd;
         set<int> minutes = cronstr_to_set(minute, Minute);
         set<int> hours = cronstr_to_set(hour, Hour);
         set<int> dates = cronstr_to_set(date, Date);
         set<int> months = cronstr_to_set(month, Month);
         set<int> days = cronstr_to_set(day, Day);
         int curYear = syInt;
         while(curYear <= eyInt) {
             daysOfMon[2] = is_leap(curYear) ? 29 : 28;
             for(set<int>::iterator ii = months.begin(); ii != months.end(); ii++) {
                 int curMonth = *ii;
                 for(set<int>::iterator ji = dates.begin(); ji != dates.end(); ji++) {
                     int curDate = *ji;
                     int curDay = calcDay(curYear, curMonth, curDate);
                     // 星期不匹配或超出天数时失败
                     if(days.find(curDay) == days.end() || curDate > daysOfMon[curMonth]) continue;
                     for(set<int>::iterator ki = hours.begin(); ki != hours.end(); ki++) {
                         for(set<int>::iterator li = minutes.begin(); li != minutes.end(); li++) {
                             string datetime = int_to_str(curYear) + int_to_str(curMonth) +
                                 int_to_str(curDate) + int_to_str(*ki) + int_to_str(*li);
                             if(s <= datetime && datetime < e) { // 判断时间是否生效直接用字符串比较
                                 output[datetime].push_back(cmd);
                             }
                         }
                     }
                 }
             }
             curYear++;
         }
     }
     for(map<string, vector<string> >::iterator it = output.begin(); it != output.end(); it++) {
         for(int i = 0; i < it->second.size(); i++) {
             cout << it->first << " " << it->second[i] << endl;
         }
     }
    return 0;
}

void build_table() {
    for(int i = 1; i <= 12; i++) {
        monTab[monStr[i]] = i;
    }
    for(int i = 0; i < 7; i++) {
        dayTab[dayStr[i]] = i;
    }
}

int str_to_int(string &s) {
    stringstream ss(s);
    int res;
    ss >> res;
    return res;
}

string int_to_str(int x) {
    stringstream ss;
    ss << x;
    string res = ss.str();
    if(res.size() == 1) res = "0" + res;
    return res;
}

void all_to_lower(string &s) {
    for(int i = 0; i < s.size(); i++) {
        s[i] = tolower(s[i]);
    }
}

int timestr_to_int(CronType tag, string &str) {
    if(tag == Month && isalpha(str[0])) { // 月份"Jan"等
        all_to_lower(str);
        return monTab[str];
    } else if(tag == Day && isalpha(str[0])) { // 星期"Sun"等
        all_to_lower(str);
        return dayTab[str];
    } else {
        return str_to_int(str);
    }
}

set<int> cronstr_to_set(string &str, CronType tag) {
    set<int> si;
    if(str == "*") {
        switch (tag) {
            case Minute: str = "0-59"; break;
            case Hour: str = "0-23"; break;
            case Date: str = "1-31"; break;
            case Month: str = "1-12"; break;
            case Day: str = "0-6"; break;
            default: break;
        }
    }
    str += ",";
    size_t comma = str.find(",");
    while(comma != string::npos) {
        string seg = str.substr(0, comma); // 按,截取
        size_t hyphen = seg.find("-");
        if(hyphen == string::npos) { // 无-，离散值
            si.insert(timestr_to_int(tag, seg));
        } else { // 有-，连续值
            string before = seg.substr(0, hyphen);
            string after = seg.substr(hyphen + 1, seg.size() - hyphen - 1);
            int from = timestr_to_int(tag, before), to = timestr_to_int(tag, after);
            while(from <= to) {
                si.insert(from);
                from++;
            }
        }
        str = str.substr(comma + 1, str.size() - comma - 1);
        comma = str.find(",");
    }
    return si;
}

inline bool is_leap(int year) {
    return (year % 400 == 0) || (year % 100 && year % 4 == 0);
}

// 19700101为周四，计算从该天开始经过了多少天
int calcDay(int year, int month, int date) {
    int count = 0, curYear = 1970, curMon = 1;
    while(curYear < year) {
        count += is_leap(curYear) ? 2 : 1; // 365 % 7 = 1
        curYear++;
    }
    // 计算时本年二月已修正
    while(curMon < month) {
         count += daysOfMon[curMon];
        curMon++;
    }
    count += date - 1;
    return (4 + count) % 7;
}
