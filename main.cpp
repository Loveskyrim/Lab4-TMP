#include <iostream>
#include <vector>
#include <string>

using namespace std;

class TreeNode
{
private:
	TreeNode* parent;
	vector<TreeNode*> children;
	int value;
public:
	TreeNode(int value) : value(value) { }
	int getValue() const { return value; }
	vector<TreeNode*> getChildren() const { return children; }
	void AddChild(TreeNode* child);
};


class Tree
{
private:
	TreeNode* root;
public:
	Tree(TreeNode* root) : root(root) { }
	static void Direct(TreeNode* root);
	static void Reverse(TreeNode* root);
	static void Symmetric(TreeNode* root);
	TreeNode* getRoot() const
      { return root; }
	static TreeNode* Create(int* cursors, int n, TreeNode* root, int k = 0);
	static void CountElements(TreeNode* root, int& n);
};

int main(int argc, char* argv[])
{
	cout << "N = ";
	int n;
	cin >> n;
	int* cursors = new int[n];

	for (int i = 0; i < n; i++)
		cin >> cursors[i];

	TreeNode* root = nullptr;
	int pos = 0;

	for (int i = 0; i < n; i++)
		if (cursors[i] == -1)
		{
			if (!root)
			{
				root = new TreeNode(i);
				pos = i;
			}
			else
			{
				cout << "Bad tree\n";
				return 0;
			}
		}

	if (!root)
	{
		cout << "Root is not found\n";
		return 0;
	}

	Tree tree(Tree::Create(cursors, n, root, pos));
	pos = 1;
	Tree::CountElements(tree.getRoot(), pos);
	
	if (pos != n)
	{
		cout << "Bad tree\n";
		return 0;
	}

	cout << "Direct: "<< endl;
	Tree::Direct(tree.getRoot());
	cout << "\nReverse: " << endl;
	Tree::Reverse(tree.getRoot());
	cout << "\nSymmetric: " << endl;
	Tree::Symmetric(tree.getRoot());
	cout << endl;

	system("pause");
	return 0;
}

void Tree::Direct(TreeNode* root)
{
	if (!root)
		return;
	cout << root->getValue() << "  ";
	vector<TreeNode*> children = root->getChildren();
	for (int i = 0; i < children.size(); i++)
		Direct(children[i]);
}

void Tree::Reverse(TreeNode* root)
{
	if (!root)
		return;
	vector<TreeNode*> children = root->getChildren();
	for (int i = 0; i < children.size(); i++)
		Reverse(children[i]);
	cout << root->getValue() << "  ";
}

void Tree::Symmetric(TreeNode* root)
{
	if (!root)
		return;
	vector<TreeNode*> children = root->getChildren();
	if (children.size() > 0)
		Symmetric(children[0]);
	cout << root->getValue() << "  ";
	for (int i = 1; i < children.size(); i++)
		Symmetric(children[i]);
}

TreeNode* Tree::Create(int * cursors, int n, TreeNode* root, int k)
{
	if (!root)
		return nullptr;

	for (int i = 0; i < n; i++)
	{
		if (cursors[i] == k)
		{
			TreeNode* child = new TreeNode(i);
			root->AddChild(child);
			Create(cursors, n, child, i);
		}
	}
	return root;
}

void Tree::CountElements(TreeNode * root, int& n)
{
	if (!root)
		return;
	vector<TreeNode*> children = root->getChildren();
	for (int i = 0; i < children.size(); i++)
		CountElements(children[i], ++n);
}

void TreeNode::AddChild(TreeNode * child)
{
	child->parent = this;
	children.push_back(child);
}