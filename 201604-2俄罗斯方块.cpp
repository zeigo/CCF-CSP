#include <iostream>
#include <vector>
using namespace std;

void cin_matrix(vector<vector<int> > &vv, int row, int col);

int main() {
	// 输入graph 
	vector<vector<int> > graph(15, vector<int>(10));
	cin_matrix(graph, 15, 10);
	// 输入block
	vector<vector<int> > block(4, vector<int>(4));
	cin_matrix(block, 4, 4);
	int start;
	cin >> start;
	start--;
	// 找到block每列最下方块的位置，没有时为-20 
	vector<int> bottom(4, -20);
	for(int i = 0; i < 4; i++) {
		for(int j = 3; j >= 0; j--) {
			if(block[j][i]) {
				bottom[i] = j; break;
			}
		}
	}
	// 计算对应列block最下方块与graph最上方块间距，找到最小，即为整个block需要下移的距离 
	int min_dis = 19;
	for(int i = 0; i < 4; i++) {
		int k;
		for(k = 0; k < 15; k++) { // 从graph顶端往下 
			if(graph[k][i + start]) {
				break;
			}
		}
		if(3 - bottom[i] + k < min_dis) {
			min_dis = 3 - bottom[i] + k;
		}
	}
	// 假设block[j][i]在graph[j-4][start + i]位置 
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j <= bottom[i]; j++) {
			graph[j - 4 + min_dis][start + i] = block[j][i]; // 从j-4下移min_dis 
		}
	}
	for(int i = 0; i < 15; i++) {
		for(int j = 0; j < 10; j++) {
			cout << graph[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}

void cin_matrix(vector<vector<int> > &vv, int row, int col) {
	int x;
	for(int i = 0; i < row; i++) {
		for(int j = 0; j < col; j++) {
			cin >> x;
			vv[i][j] = x;
		}
	}
}
