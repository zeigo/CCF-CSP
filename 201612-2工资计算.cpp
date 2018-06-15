#include <iostream>

using namespace std;

int main() {
	int t, s = 0;
	cin >> t;
	int money[8] = {3500, 1500, 3000, 4500, 26000, 20000, 25000, 300000};
	float tax[8] = {0, 0.03, 0.1, 0.2, 0.25, 0.3, 0.35, 0.45};
	int i = 0;
	while(i < 8 && t > 0) {
		if(t < money[i] * (1 - tax[i])) {
			s += t / (1 - tax[i]);
			break;
		} else {
			s += money[i];
			t -= money[i] * (1 - tax[i]);
			i++;
		}
	}	
	cout << s;
	return 0;
} 
