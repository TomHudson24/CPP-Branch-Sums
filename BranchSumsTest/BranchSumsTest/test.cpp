#include "pch.h"


//Base Class for tree
class BinaryTree {
public:
	int value;//value at any node will be stored in this int
	BinaryTree* left;//every node has to have a pointer to the next available left node
	BinaryTree* right;//every node has to have a pointer to the next available rights node

	BinaryTree(int value) {
		//setting the properties of the tree when the contructor is called, could have used initiliaser list but this is fine
		this->value = value;
		left = NULL;
		right = NULL;
	}
};

//Updated Binary Tree class that includes the ability to insert values
class TestBinaryTree : public BinaryTree {
public:
	TestBinaryTree(int value) : BinaryTree(value) {};//local tree

	BinaryTree* insert(std::vector<int> values, int i = 0) {//insertion function
		if (i >= values.size())//make sure the array given to the insertion is not empty. 
			return NULL;
		std::vector<BinaryTree*> queue = { this }; //set up an array to go through and find where the insertion point should be
		while (queue.size() > 0) {//go for as long as the array
			BinaryTree* current = queue[0];//every iteration of the loop the queue is downsized so this should work
			queue.erase(queue.begin());//get rid of that first element 
			if (current->left == NULL) {
				current->left = new BinaryTree(values[i]);//fill that value in from the values array (not the queue array, the original array passed into the func)
				break;
			}
			queue.push_back(current->left);//add that new left node to the queue
			if (current->right == NULL) {//same logic as the left node
				current->right = new BinaryTree(values[i]);
				break;
			}
			queue.push_back(current->right);
		}
		insert(values, i + 1);//recursively run this until no more elements from that values array need to be added to the tree
		return this;
	}
};
void calculateBranchSums(BinaryTree* node, int runningSum, std::vector<int>& sums);//promise this func exists (it does just below the branchSums func)
std::vector<int> branchSums(BinaryTree* root) {
	std::vector<int> sums;//init a sums array 
	calculateBranchSums(root, 0, sums);//call helper func that does the leg work

	return sums;//give the sums array back out for testing
}

void calculateBranchSums(BinaryTree* node, int runningSum, std::vector<int>& sums)
{
	if (node == NULL)//if there is no root node, we can't do anything
	{
		return;
	}
	int newRunningSum = runningSum + node->value;//don't modify the runningSum, create a new one that can be updated as we recurse down the call stack
	if (node->left == NULL && node->right == NULL)//we must be at a leaf node so get outta this branch
	{
		sums.push_back(newRunningSum);//give back the new runnning sum to the sums array as we reached the end of the branch
		return;
	}
	calculateBranchSums(node->left, newRunningSum, sums);//recurse deeper into the left node of the current branch
	calculateBranchSums(node->right, newRunningSum, sums);//recurse deeper into the right node of the current branch
}

TEST(Branch_Sums_Tests, Test_Case_One)
{
	TestBinaryTree* tree = new TestBinaryTree(1);
	tree->insert({ 2, 3, 4, 5, 6, 7, 8, 9, 10 });
	std::vector<int> expected = { 15, 16, 18, 10, 11 };
	ASSERT_EQ(expected, branchSums(tree));
}
TEST(Branch_Sums_Tests, Test_Case_Two)
{
	//Single value array test
	TestBinaryTree* tree = new TestBinaryTree(1);
	std::vector<int> e = {1};
	ASSERT_EQ(e, branchSums(tree));
}
TEST(Branch_Sums_Tests, Test_Case_Three)
{
	//Single addition to the array test
	TestBinaryTree* tree = new TestBinaryTree(1);
	tree->insert({ 2 });
	std::vector<int> expected = { 3 };
	ASSERT_EQ(expected, branchSums(tree));
}
TEST(Branch_Sums_Tests, Test_Case_Four)
{
	TestBinaryTree* tree = new TestBinaryTree(1);
	tree->insert({ 2,3 });
	std::vector<int> expected = { 3,4 };
	ASSERT_EQ(expected, branchSums(tree));
}
TEST(Branch_Sums_Tests, Test_Case_Five)
{
	TestBinaryTree* tree = new TestBinaryTree(1);
	tree->insert({ 2,3,4,5 });
	std::vector<int> expected = { 7,8,4 };
	ASSERT_EQ(expected, branchSums(tree));
}