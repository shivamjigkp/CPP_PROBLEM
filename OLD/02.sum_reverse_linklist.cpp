#include <iostream>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// Function to add two numbers represented as linked lists
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode* dummy = new ListNode(0);  // Dummy head node
    ListNode* curr = dummy;
    int carry = 0;

    // Traverse both lists
    while (l1 != nullptr || l2 != nullptr || carry != 0) {
        int v1 = (l1 != nullptr) ? l1->val : 0;
        int v2 = (l2 != nullptr) ? l2->val : 0;

        int sum = v1 + v2 + carry;
        carry = sum / 10;

        curr->next = new ListNode(sum % 10);
        curr = curr->next;

        if (l1 != nullptr) l1 = l1->next;
        if (l2 != nullptr) l2 = l2->next;
    }

    return dummy->next;
}

// Helper function to print linked list
void printList(ListNode* head) {
    while (head != nullptr) {
        cout << head->val;
        if (head->next) cout << " -> ";
        head = head->next;
    }
    cout << endl;
}

// Example usage
int main() {
    // l1 = 2 -> 4 -> 3  (represents 342)
    ListNode* l1 = new ListNode(2);
    l1->next = new ListNode(4);
    l1->next->next = new ListNode(3);

    // l2 = 5 -> 6 -> 4  (represents 465)
    ListNode* l2 = new ListNode(5);
    l2->next = new ListNode(6);
    l2->next->next = new ListNode(4);

    ListNode* result = addTwoNumbers(l1, l2);

    // Expected output: 7 -> 0 -> 8  (represents 807)
    cout << "Result: ";
    printList(result);

    return 0;
}
