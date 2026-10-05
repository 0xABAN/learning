#include <unordered_set>

using namespace std;

// Each node is an employee; left and right are their direct reports.
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;

	TreeNode(int val = 0, TreeNode* left = nullptr, TreeNode* right = nullptr)
		: val(val), left(left), right(right) {}
};

class Solution {
public:
	/*
	 * Return the lowest node that is an ancestor of every requested employee.
	 * The hierarchy is a binary tree, not necessarily a BST.
	 * Employees are identified by node pointers, not by val.
	 * The employee set is nonempty; all pointers are non-null and in the tree.
	 * A node counts as its own ancestor.
	 *
	 * Follow-ups:
	 * - Improve query complexity for K employees and tree height H.
	 * - Consider preprocessing for large employee sets or repeated queries.
	 */
	TreeNode* lowestCommonManager(TreeNode* root, const unordered_set<TreeNode*>& employees) {
		// TODO: implement
		return nullptr;
	}
};
