struct ListNode {
	int val;
	ListNode* next;

	ListNode(int val = 0, ListNode* next = nullptr) : val(val), next(next) {}
};

class Solution {
public:
	ListNode* removeNthFromEnd(ListNode* head, int n) {
		ListNode dummy = ListNode(0, head); 
		ListNode* ptr = &dummy; 
		int	r = 0; 

		while(ptr->next){
			r++; 
			ptr = ptr->next; 
		}

		ptr = &dummy; 
		int l = 0; 
		
		while(l < r-n){
			ptr = ptr->next; 
			l++; 
		}
		
		ptr->next = ptr->next->next; 
		return dummy.next; 
	}
};
