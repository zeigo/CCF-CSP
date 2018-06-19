#include <iostream>
#include <string>
using namespace std;

int main(int argc, char const *argv[])
{
    string isbn;
    cin >> isbn;
    int code = 0, factor = 1;
    for(int i = 0; i < 11; i++) {
        if(i == 1 || i == 5) continue;
        code += factor * (isbn[i] - '0');
        factor++;
    }
    code %= 11;
    char last = code == 10 ? 'X' : '0' + code;
    if(last == isbn[12]) {
        cout << "Right";
    } else {
        isbn[12] = last;
        cout << isbn;
    }
    return 0;
}
