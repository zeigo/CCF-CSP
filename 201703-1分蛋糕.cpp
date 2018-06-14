#include <iostream>

using namespace std;

int main() {
	int n, k;
	cin >> n >> k;
	int cake, count = 0, sum = 0;
	while(n--) {
		cin >> cake;
		sum += cake;
		if(sum >= k) {
			sum = 0;
			count++;
		}
	}
	if(sum > 0) count++;
	cout << count;
	return 0;
}
