#include <cstddef>
#include <iostream>

// Definition for singly-linked list.
struct ListNode {
	int val;
	ListNode *next;
};

class Solution {
public:
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
	if(!l1) {
		return l2;
	}
	if(!l2) {
		return l1;
	}
	ListNode* head = NULL;
	(l1->val > l2->val) ? head = l2 : head = l1;
	while(l1 && l2) {
		if(l1->val > l2->val) {
			if(!l2->next) {
				l2->next = l1;
				return head;
			} else if(l2->next->val > l1->val) {
				ListNode* next = l2->next;
				l2->next = l1;
				l2 = next;
			} else {
				l2 = l2->next;
			}
		} else {
			if(!l1->next) {
				l1->next = l2;
				return head;
			} else if(l1->next->val > l2->val) {
				ListNode* next = l1->next;
				l1->next = l2;
				l1 = next;
			} else {
				l1 = l1->next;
			}
		}
	}
    }
};

int main()
{
	/*
	struct ListNode a3 = {4, NULL};
	struct ListNode a2 = {2, &a3};
	struct ListNode a1 = {1, &a2};

	struct ListNode b3 = {4, NULL};
	struct ListNode b2 = {3, &b3};
	struct ListNode b1 = {1, &b2};
	*/

	struct ListNode a3 = {3, NULL};
	struct ListNode a2 = {2, &a3};
	struct ListNode a1 = {1, &a2};

	struct ListNode b3 = {6, NULL};
	struct ListNode b2 = {5, &b3};
	struct ListNode b1 = {4, &b2};


	Solution sol;
	ListNode* result = sol.mergeTwoLists(&a1, &b1);

	while(result)
	{
		std::cout << result->val << std::endl;
		result = result->next;
	}

	return 0;
}

