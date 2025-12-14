
 #include<iostream>
using namespace std;

int main(){
 
 
    int reverse(int x) {
        // check if x is negative
        bool negative = x < 0;
        
        // convert x to positive
        x = abs(x);
        
        // reverse the digits of x
        int reversed_x = 0;
        while (x > 0) {
            reversed_x = (reversed_x * 10) + (x % 10);
            x = x / 10;
        }
        
        // add the sign back to reversed_x
        if (negative) {
            reversed_x = -reversed_x;
        }
        
        // check if reversed_x is within the allowed range
        if (reversed_x < -pow(2, 31) || reversed_x > pow(2, 31) - 1) {
            return 0;
        }
        
        return reversed_x;
    }

