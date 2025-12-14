class Solution {
public:
    bool isPalindrome(int x) {
       // Negative numbers and numbers ending with 0 (but not 0 itself) can't be palindrome
        if (x < 0 || (x % 10 == 0 && x != 0)) 
            return false;

        long long reversed = 0;
        int original = x;

        while (x > 0) {
            int digit = x % 10;
            reversed = reversed * 10 + digit;
            x /= 10;
        }

        return original == reversed;
    }  
    
};