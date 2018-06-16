#include <iostream>
#include <vector>
using namespace std;

int main() {
	int n;
	cin >> n;
	vector<int> vi;
	while(n--) {
		int x;
		cin >> x;
		vi.push_back(x);
	}
	int cnt = 0;
	for(int i = 1; i < vi.size() - 1; i++) {
		if((vi[i] > vi[i - 1] && vi[i] > vi[i + 1]) || (vi[i] < vi[i - 1] && vi[i] < vi[i + 1])) {
			cnt++;
		}
	}
	cout << cnt;
	return 0;
}
