#include <iostream>
#include <cmath>
using namespace std;

int main() {
	int n;
	cin >> n;
	int x, y, _max = 0;
	cin >> x;
	for(int i = 1; i < n; i++) {
		cin >> y;
		_max = max(_max, abs(y - x));
		x = y;
	}
	cout << _max;
	return 0;
}
