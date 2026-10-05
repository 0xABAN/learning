struct ListNode {
	int val;
	ListNode* next;

	ListNode(int val = 0, ListNode* next = nullptr) : val(val), next(next) {}
};

class Solution {
public:
	void reorderList(ListNode* head) {
		if(!head || !head->next) return; 	
		
		ListNode* slow = head; 
		ListNode* fast = head->next; 

		while(fast && fast->next){
			slow = slow->next; 
			fast = fast->next->next; 
		}
		
		ListNode* l1 = head; 
		ListNode* l2 = slow->next; 
		slow->next = nullptr; 
		// reverse 2nd list 
		
		ListNode* prev = nullptr; 
		ListNode* curr = l2; 

		while(curr){
			ListNode* temp = curr->next; 
			curr->next = prev; 
			prev = curr; 
			curr = temp; 
		}
		
		l2 = prev; 

		// merge 
		while(l1 && l2){
			ListNode* temp1 = l1->next; 
			ListNode* temp2 = l2->next; 
			
			l1->next = l2; 
			l2->next = temp1; 

			l1 = temp1; 
			l2 = temp2; 
		}
		
	}
};
