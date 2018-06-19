#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char const *argv[])
{
    int n;
    cin >> n;
    vector<int> heights(n);
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        heights[i] = x;
    }
    // left[i]：i左边连续不小于heights[i]的个数
    vector<int> left(n), right(n);
    left.front() = 0;
    for(int i = 1; i < n; i++) {
        if(heights[i] > heights[i - 1]) {
            left[i] = 0;
        } else {
            left[i] = 1 + left[i - 1];
            int j = i - left[i] - 1; // 不能确定的位置
            while(j >= 0 && heights[j] >= heights[i]) {
                left[i]++; j--;
            }            
        }
    }
    right.back() = 0;
    for(int i = n - 2; i >= 0; i--) {
        if(heights[i] > heights[i + 1]) {
            right[i] = 0;
        } else {
            right[i] = 1 + right[i + 1];
            int j = i + right[i] + 1; // 不能确定的位置
            while(j < n && heights[j] >= heights[i]) {
                right[i]++; j++;
            }            
        }
    }
    int max_area = 0;
    for(int i = 0; i < n; i++) {
        max_area = max(max_area, heights[i] * (left[i] + right[i] + 1));
    }
    cout << max_area;
    return 0;
}
