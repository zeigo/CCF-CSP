#include <iostream>
#include <vector>
using namespace std;
// 。。。辣鸡csp，c++11都用不了
// 将1s内的所有运动分解成一个一个球的运动，先运动的球到某个位置，记录该位置上有哪个球，
// 后运动的球如果也到该位置，则检测到碰撞，一起变向 
struct ball {
    int pos;
    int speed;
};
 
int main(int argc, char const *argv[])
{
    int n, l, t;
    cin >> n >> l >> t;
    vector<ball> balls;
    vector<int> filled; // filled[i]表示位置i上球的编号，-1时无球 
    for(int i = 0; i < l + 1; i++) {
        filled.push_back(-1);
    }
    int pos;
    for(int i = 0; i < n; i++) {
    	cin >> pos;
        balls.push_back(ball{pos, 1});
    }
    for(int i = 0; i < t; i++) {
        for(int j = 0; j < n; j++) {
            ball &ba = balls[j];
            filled[ba.pos] = -1;
            if(ba.pos == 0 || ba.pos == l) { // 在两端时变向 
            	ba.speed *= -1;
			}
            int next = ba.pos + ba.speed;
            ba.pos = next;
            if(filled[next] >= 0) { // 检测到碰撞，两个都变向 
                ba.speed *= -1;
                balls[filled[next]].speed *= -1;
            } else {
                filled[next] = j;
            }
        }
    }
    for(int i = 0; i < n; i++) {
        cout << balls[i].pos << " ";
    }
    return 0;
}
