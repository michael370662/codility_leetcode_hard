#include "pch.h"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <cstdlib>
#include <stdexcept>

/* Leetcode question: Reverse K group
* This reverse group of k elements in a list. Illegal remainders remain unaltered.
* For example k being 3 in {1,2,3,4,5} as {3,2,1,4,5,}
* k being 2 in {1,2,3,4,5,} as {2,1,4,3,5}
*/

using namespace std;

struct ListNode {
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
	Solution(ListNode* head, int k);
	ListNode* reverseKGroup(ListNode* head, int k);

};

Solution::Solution(ListNode* head, int k) {
	ListNode* cur;
	if (k < 2) {
		do {
			cout << head->val << " ";
			head = head->next;
		} while (head->next != NULL);
		cout << head->val << endl;
	}
	cur = reverseKGroup(head, k);
	cout << "The altered List is as followed" << endl;
	while (cur->next != NULL){
		cout << cur->val<<" ";
		cur = cur->next;
	 } 
	 cout << cur->val << endl;
}



ListNode* Solution::reverseKGroup(ListNode* head, int k) {
	int i;
	i = 0;
	ListNode* cur = head;
	for (i = 0; i < k - 1; ++i) {
		if (head->next == NULL) {
			head = cur;
			return head;
		}
		head = head->next;
	}
	ListNode* forward;
	forward = nullptr;
	ListNode** temp = new ListNode*[k-1];
	if (cur->next != NULL) {
		for (i = 0; i < k-1; i++) {
			if (cur->next == NULL) {
				delete[] temp;
				return head;
			}
			temp[i] = cur;
			cur = cur->next;
		}
		i--;
		forward = cur -> next;
		for (; i >= 0; i--) {
			cur->next = temp[i];
			cur = cur->next;
		}
		cur->next = reverseKGroup(forward, k);
		/*cur = cur->next;*/
	}
	delete[] temp;
	return head;
}





int main() {
	int i;
	ListNode* head;
	ListNode* cur;
	ListNode* temp;
	cur = NULL;
	ifstream inFile;
	try {
		inFile.open("list.txt", ios :: in);
		{
			if (!inFile.is_open())
				throw exception("Cannot open the file with strings");
		}
	}
	catch (const exception& error) {
		cerr << error.what() << endl;
		return(EXIT_FAILURE);
	}
	inFile >> i;
	cur = new ListNode(i);
	head = cur;
	while (!inFile.eof()) {
		inFile >> i;
		cur->next = new ListNode(i);
		cur = cur->next;
	}
	Solution(head, 4);
	while (cur->next != NULL) {
		temp = cur;
		cur = cur->next;
		delete temp;
	}
	delete cur;

}