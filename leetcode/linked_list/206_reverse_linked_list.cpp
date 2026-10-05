struct ListNode {
	int val; 
	ListNode* next; 
	
	ListNode(int val = 0, ListNode* next = nullptr) : val(val), next(next) {}
};

class Solution {
public:
	ListNode* reverseList(ListNode* head) {
		ListNode* prev = nullptr; 
		ListNode* curr = head; 
		
		while(curr){
			ListNode* temp = (*curr).next; 
			(*curr).next = prev; 
			prev = curr; 
			curr = temp;
		}

		return prev; 				
	}
};
