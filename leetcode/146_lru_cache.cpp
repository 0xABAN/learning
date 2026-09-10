#include <unordered_map>

using namespace std; 

struct Node {
	int key=0; 
	int val=0;
	Node* next=nullptr;
	Node* prev =nullptr; 
}; 

class LRUCache {
	int capacity;
	unordered_map<int, Node*> cache; 

	Node* head = new Node();  
	Node* tail = new Node();  

public:
	LRUCache(int cap) 
	: capacity(cap) {
		head->next = tail; 
		tail->prev = head; 
	}

	void remove(Node* node) {
		node->prev->next = node->next; 
		node->next->prev = node->prev; 
		node->prev = nullptr; 
		node->next = nullptr; 
	}
	
	void add_front(Node* node) {
		Node* tmp = head->next;
		
		head->next = node; 
		node->prev = head; 
		node->next = tmp;
		tmp->prev = node; 
	}
	
	int get(int key) {
		if (cache.contains(key)){
			remove(cache[key]);
			add_front(cache[key]); 
				
			return cache[key]->val; 
		}
		return -1;
	}

	void put(int key, int value) {
		if (cache.contains(key)){
			Node* node = cache[key]; 
			node->val = value; 
			remove(node); 
			add_front(node); 
			return; 
		}	
		
		if(cache.size()+1 > capacity){
			Node* node = tail->prev; 	
			remove(node); 
			cache.erase(node->key); 
			delete node; 
		}
		Node* node = new Node(key, value); 
		add_front(node);
		cache[key] = node; 
	}
};
