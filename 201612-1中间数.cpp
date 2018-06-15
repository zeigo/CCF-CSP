#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef vector<int>::iterator viit;

int main() {
	int n;
	cin >> n;
	vector<int> vi;
	for(int i = 0; i < n; i++) {
		int a;
		cin >> a;
		vi.push_back(a);
	}
	sort(vi.begin(), vi.end());
	viit mid = vi.begin() + (n - 1) / 2;
	int value = *mid;
	viit low = lower_bound(vi.begin(), vi.end(), value),
		up = upper_bound(vi.begin(), vi.end(), value);
	if(n % 2 && up - mid == mid - low + 1) { // 1 2 2 2 3
		cout << value;
	} else if(n % 2 == 0 && up - mid == mid - low + 2) { // 1 2 2 3
		cout << value;
	} else {
		cout << -1;
	}
	return 0;
} 
