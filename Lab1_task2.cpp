#include <iostream>
using namespace std;

void byPointer (int* a, int* b) {
    int t = *a;
    *a= *b;
    *b = t;
}

void byReference (int& a, int& b) {
    int t = a;
    a = b;
    b = t;
}

int main() {
    int a, b;
    cin >> a;
    cin >> b;
    
    byPointer(&a, &b);
    
    cout << "After byPointer: " << a << " " << b << endl;
    
    byReference(a, b);
    
    cout << "After byReference: " << a << " " << b << endl;
    
    return 0;
}