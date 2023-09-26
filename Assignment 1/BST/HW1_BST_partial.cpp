#include <cstdio>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

// Implement a BST without height balance property
class BST
{
private:
	struct Node
	{				 // node of a BST tree
		int key;	 // key stored in the node
		Node *left;	 // link to the left child
		Node *right; // link to the right child
		Node(int x)	 // initialize a new node
		{
			key = x;
			left = NULL;
			right = NULL;
		}
	};

	int sz;

public:
	Node *root; // store the root of BST
	BST()
	{ // initialize an empty BST with a null root
		root = NULL;
	}

	void insert(int k)
	{
		Node *insertion = new Node(k);
		if (isEmpty())
		{
			root = insertion;
		}
		else
		{
			Node *ptr = root;
			Node *ptrParent = root;
			while (ptr != NULL)
			{
				if (k > ptr->key)
				{
					ptrParent = ptr;
					ptr = ptr->right;
				}
				else
				{
					ptrParent = ptr;
					ptr = ptr->left;
				}
			} // ptrParent will be the insertion point
			if (k > ptrParent->key)
			{
				ptrParent->right = insertion;
			}
			else
			{
				ptrParent->left = insertion;
			}
		}
		sz++;
	}

	Node *find(Node *node, int k)
	{
		if (node)
		{
			if (k == node->key)
			{
				return node;
			}
			else if (k > node->key)
			{
				return find(node->right, k);
			}
			else
			{
				return find(node->left, k);
			}
		}
		else
		{
			cout << "Searching failed: no element is found!" << endl;
			return NULL;
		}
	}

	Node *find(int k)
	{
		return find(root, k);
	}

	Node *deleteNode(Node *root, int k)
	{
		// Base case
		if (root == NULL)
			return root;
		if (k == root->key)
		{

			if (root->left != NULL && root->right != NULL) // has two children
			{
				Node *r = root->right;
				while (r->left != NULL)
				{
					r = r->left;
				}
				root->key = r->key;
				r = NULL;
			}
			else if (root->left != NULL && root->right == NULL) // has only left child
			{
				Node *l = root->left;
				root->key = l->key;
				root->left = l->left;
				root->right = l->right;
				l = NULL;
			}
			else if (root->left == NULL && root->right != NULL) // has only right child
			{
				Node *r = root->right;
				root->key = r->key;
				root->left = r->left;
				root->right = r->right;
				r = NULL;
			}
			return root;
		}
		else if (k > root->key)
		{
			return deleteNode(root->right, k);
		}
		else
		{
			return deleteNode(root->left, k);
		}
	}

	void remove(int k)
	{
		if (find(k) != NULL)
		{
			deleteNode(root, k); // root =
			sz--;
		}

		else
		{
			cout << "Deletion failed: no such element is found!" << endl;
		}
	}
	void remove(Node *p)
	{
		if (p != NULL)
		{
			deleteNode(root, p->key); // root=
		}

		else
		{
			cout << "Deletion failed: empty pointer!" << endl;
		}
	}

	int size()
	{
		return sz;
	}

	bool isEmpty()
	{
		return root == NULL;
	}

	void printTree(string prefix, Node *node, bool isRight)
	{
		if (node != NULL)
		{
			cout << prefix;					   // print the blank space before the node
			cout << (isRight ? "---" : "|__"); // depend on whether the node is a right child, print different labels
			cout << node->key << endl;		   // print the value of the node
			// enter the next tree level - left and right branch
			printTree(prefix + (isRight ? "|   " : "    "), node->right, true);
			printTree(prefix + (isRight ? "|   " : "    "), node->left, false);
		}
	}

	void printTree()
	{ // print the tree from the root
		printTree("", root, false);
	}
};

// Implement a AVL tree.
class AVL
{
private:
	struct Node
	{				 // node of a BST tree
		int key;	 // key stored in the node
		Node *left;	 // link to the left child
		Node *right; // link to the right child
		int height;	 // store the height of node
		Node(int x)	 // initialize a new node
		{
			key = x;
			left = NULL;
			right = NULL;
			height = 0;
		}
	};

	int sz;

	int bf(Node *n) // Balance Factor of node n.
	{
		if (n->left && n->right)
		{
			return n->left->height - n->right->height;
		}
		else if (n->left && n->right == NULL)
		{
			return n->left->height;
		}
		else if (n->left == NULL && n->right)
		{
			return -n->right->height;
		}
	}

	Node *LLRot(Node *n) // left single rotation
	{
		Node *ptr;
		Node *top;
		ptr = n;
		top = ptr->left;
		ptr->left = top->right;
		top->right = ptr;

		return top;
	}

	Node *RRRot(Node *n) // right single rotation
	{
		Node *ptr;
		Node *top;
		ptr = n;
		top = ptr->right;
		ptr->right = top->left;
		top->left = ptr;
		return top;
	}

	Node *RLRot(Node *n) // Right-Left double rotation
	{
		Node *ptr;
		Node *mid;
		Node *top;
		ptr = n;
		mid = ptr->right;
		top = mid->left;
		ptr->right = top->left;
		mid->left = top->right;
		top->left = ptr;
		top->right = mid;

		return top;
	}

	Node *LRRot(Node *n) // Left-Right double rotation
	{
		Node *ptr;
		Node *mid;
		Node *top;
		ptr = n;
		mid = ptr->left;
		top = mid->right;
		mid->right = top->left;
		ptr->left = top->right;
		top->left = mid;
		top->right = ptr;

		return top;
	}

public:
	Node *root; // store the root of BST

	AVL()
	{ // initialize an empty BST with a null root
		root = NULL;
	}

	int height(Node *node)
	{

		if (node->left && node->right)
		{
			if (node->left->height < node->right->height)
				return node->right->height + 1;
			else
				return node->left->height + 1;
		}
		else if (node->left && node->right == NULL)
		{
			return node->left->height + 1;
		}
		else if (node->left == NULL && node->right)
		{
			return node->right->height + 1;
		}
		return 0;
	}

	Node *insert(Node *node, int k)
	{
		if (node == NULL)
		{
			struct Node *n;
			n = new Node(k);
			node = n;
			node->left = node->right = NULL;
			node->height = 1;
			return node;
		}
		else
		{
			if (k < node->key)
				node->left = insert(node->left, k);
			else
				node->right = insert(node->right, k);
		}

		node->height = height(node);

		if (bf(node) == 2 && bf(node->left) == 1)
		{
			node = LLRot(node);
		}
		else if (bf(node) == -2 && bf(node->right) == -1)
		{
			node = RRRot(node);
		}
		else if (bf(node) == -2 && bf(node->right) == 1)
		{
			node = RLRot(node);
		}
		else if (bf(node) == 2 && bf(node->left) == -1)
		{
			node = LRRot(node);
		}

		return node;
	}

	void insert(int k)
	{
		root = insert(root, k);
	}

	Node *find(Node *node, int k)
	{
		if (node)
		{
			if (k == node->key)
			{
				return node;
			}
			else if (k >= node->key)
			{
				return find(node->right, k);
			}
			else
			{
				return find(node->left, k);
			}
		}
		else
		{
			cout << "Searching failed: no element is found!" << endl;
			return NULL;
		}
	}

	Node *find(int k)
	{
		return find(root, k);
	}

	Node *deleteNode(Node *p, int data)
	{
	}

	Node *getPrev(Node *pivot)
	{
		while (pivot->right)
		{
			pivot = pivot->right;
		}
		return pivot;
	}

	Node *getSuc(Node *pivot)
	{
		while (pivot->left)
		{
			pivot = pivot->left;
		}
		return pivot;
	}

	void remove(int k)
	{
		if (find(k) != NULL)
			root = deleteNode(root, k);
		else
			cout << "Deletion failed: no such element is found!" << endl;
	}

	void remove(Node *p)
	{
		if (p != NULL)
			root = deleteNode(root, p->key);
		else
			cout << "Deletion failed: empty pointer!" << endl;
	}

	int size()
	{
		return sz;
	}

	bool isEmpty()
	{
		return root == NULL;
	}

	void printTree(string prefix, Node *node, bool isRight)
	{
		if (node != NULL)
		{
			cout << prefix;
			cout << (isRight ? "---" : "|__");
			// print the value of the node
			cout << node->key << endl;
			// enter the next tree level - left and right branch
			printTree(prefix + (isRight ? "|   " : "    "), node->right, true);
			printTree(prefix + (isRight ? "|   " : "    "), node->left, false);
		}
	}

	void printTree()
	{
		printTree("", root, false);
	}
};

int main()
{
	BST bstree;	 // build an empty BST
	AVL avltree; // build an empty AVL tree

	cout << "The AVL tree is empty: " << boolalpha << avltree.isEmpty() << endl; // check if the three is empty
	cout << "The BST tree is empty: " << boolalpha << bstree.isEmpty() << endl;	 // check if the three is empty

	int a; // insert elements in A to the BST and the AVL tree
	ifstream arrA;
	arrA.open("testA.txt");
	if (!arrA)
	{
		cout << "Unable to open file!" << endl;
	}
	while (arrA >> a)
	{
		bstree.insert(a);
		avltree.insert(a);
	}
	cout << "The insertions of elements are done!" << endl;

	cout << "The BST is printed as follows:" << endl; // print BST tree
	bstree.printTree();
	cout << "The AVL tree is printed as follows:" << endl; // print AVL tree
	avltree.printTree();

	// The constructed AVL tree would be
	//	|__15
	//		---30
	//		|   ---40
	//		|   |   ---81
	//		|   |__25
	//		|__6
	//		    ---8
	//		    |	---12
	//		    |__2
	//				---4

	int b; // remove all the elements in array B from the BST and the AVL tree
	ifstream arrB;
	arrB.open("testB.txt");
	if (!arrB)
	{
		cout << "Unable to open file!" << endl;
	}
	while (arrB >> b)
	{
		bstree.remove(b);
		avltree.remove(b);
	}
	cout << "The removals of elements are done!" << endl;

	cout << "The BST is printed as follows:" << endl; // print BST after removals
	bstree.printTree();
	cout << "The AVL tree is printed as follows:" << endl; // print AVL tree after removals
	avltree.printTree();

	cout << "Next we find the element with key=6 in both trees, and remove it:" << endl;
	bstree.remove(bstree.find(6)); // removal of element by pointer
	avltree.remove(6);			   // removal of element by key

	cout << "The BST is printed as follows:" << endl; // print BST after the removal
	bstree.printTree();
	cout << "The AVL tree is printed as follows:" << endl; // print AVL tree after the removal
	avltree.printTree();

	cout << "The size of the BST is " << bstree.size() << endl;
	cout << "The size of the AVL tree is " << avltree.size() << endl;
	cout << "The BST tree is empty: " << boolalpha << bstree.isEmpty() << endl;
	cout << "The AVL tree is empty: " << boolalpha << avltree.isEmpty() << endl;
}
