
#include <iostream>
using namespace std;

int countEvenDivideDigit(int n) {
    int count = 0;
    int digit;
    int temp = n;
    while (temp != 0) {
        digit = temp % 10;
        if (digit != 0 && n % digit == 0) {
            count++;
        }
        temp /= 10;
    }
    return count;
}

int main() {
    int n;
    cout << "Enter a number: ";
    cin >> n;
    int result = countEvenDivideDigit(n);
    cout << "The number of digits in " << n << " that are evenly divisible by the input's digits is: " << result;
    return 0;
}
