struct ListNode {
	int val;
	ListNode* next;

	ListNode(int val = 0, ListNode* next = nullptr) : val(val), next(next) {}
};

class Solution {
public:
	ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
		// rearrange pointers such that the smaller one is always put before the larger one. 
		// then, put the remainder of the longer one in a separate pass 

		ListNode head; 
		ListNode* tail = &head; 

		while(list1 && list2){
			if(list1->val < list2 ->val){
				tail->next = list1; 
				tail = tail->next; 
				list1 = list1->next; 
			} else{
				tail->next = list2;
				tail = tail->next; 
				list2 = list2->next; 
			}
		}

		tail->next = list1 ? list1 : list2; 
		return head.next; 
	}
};
