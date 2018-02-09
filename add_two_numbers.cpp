/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int l1val = 0;
        int l2val = 0;
        int carry = 0;
        int sum = 0;

        if(l1 != NULL) {
            l1val = l1->val;
            l1 = l1->next;
        }
        
        if(l2 != NULL) {
            l2val = l2->val;
            l2 = l2->next;
        }
        
        sum = l1val + l2val;

        if(sum > 9) {
            carry = 1;
            sum = sum - 10;
        }
        
        ListNode* head = new ListNode(sum);
        ListNode* index = head;
        
        while(true) {
            l1val = 0;
            l2val = 0;
            sum = 0;

            if(l1 != NULL) {
                l1val = l1->val;
                l1 = l1->next;
            }

            if(l2 != NULL) {
                l2val = l2->val;
                l2 = l2->next;
            }

            sum = l1val + l2val + carry;

            if(sum > 9) {
                carry = 1;
                sum = sum - 10;
            } else {
                carry = 0;
            }
            
            if((l1 == NULL) && (l2 == NULL) && (sum == 0) && (carry == 0)) {
                return head;
            } else {
                index->next = new ListNode(sum);
                index = index->next;
            }
        }

    }
};
