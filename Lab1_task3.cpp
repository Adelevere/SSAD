#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N;
    
    cin >> N;
    
    vector<int> numbers;
    
    for(int i = 0; i < N; i++) {
        int num;
        cin >> num;
        numbers.push_back(num);
    }
    
    vector<int> uniqueNumbers;
    
    for(int i = 0; i < numbers.size(); i++) {
        bool isDuplicate = false;
        
        for(int j = 0; j < uniqueNumbers.size(); j++) {
            if(numbers[i] == uniqueNumbers[j]) {
                isDuplicate = true;
                break;
            }
        }

        if(!isDuplicate) {
            uniqueNumbers.push_back(numbers[i]);
        }
    }
    
    for(int i = 0; i < uniqueNumbers.size(); i++) {
        cout << uniqueNumbers[i] << " ";
    }
    cout << endl;
    
    return 0;
}