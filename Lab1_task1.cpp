#include <iostream>
using namespace std;

int main() {
    int a;
    cin >> a;
    int h, m, s;
    h = a / 3600;
    m = (a % 3600) / 60;
    s = a % 60;
    cout << h << ":" << m << ":" << s << endl;
    return 0;
}