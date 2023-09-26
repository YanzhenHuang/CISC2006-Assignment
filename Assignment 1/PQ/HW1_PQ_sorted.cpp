// Implement a prioprity queue using a sorted doubly linked list
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdexcept>
using namespace std;

struct Node
{					   // node of a doubly linked list
	int val;		   // value stored at the node
	struct Node *next; // link to the next node
	struct Node *prev; // link to the previous node
	Node(int x)		   // initialize a new node
	{
		val = x;
		next = NULL;
		prev = NULL;
	}
};

class SortedPQ
{

private:
	Node *head;
	Node *tail;
	int length; // store the size of priority queue

	// General Insertion Method
	void addBetween(int x, Node *pred, Node *succ)
	{
		Node *node = new Node(x);
		pred->next = node;
		node->prev = pred;
		succ->prev = node;
		node->next = succ;
		length++;
	}
	// General Deletion Method
	void deleteNode(Node *node)
	{
		if (isEmpty())
		{
			return;
		}
		else
		{
			Node *pred = node->prev;
			Node *succ = node->next;
			pred->next = succ;
			succ->prev = pred;
			node->next = NULL;
			node->prev = NULL;
			node->val = NULL;
			length--;
		}
	}

public:
	// Constructor
	SortedPQ()
	{ // initialize an empty priority queue with a head and a tail of an empty doubly linked list
		head = new Node(NULL);
		tail = new Node(NULL);
		head->next = tail; // link between head and tail
		tail->prev = head;
		length = 0;
	}

	// Insert Value, sort while insertion
	void insert(int val)
	{
		if (isEmpty())
		{
			addBetween(val, head, tail);
		}
		else
		{
			Node *idx = head;
			while (val > (idx->next->val) && idx->next != tail)
			{
				idx = idx->next;
			}
			addBetween(val, idx, idx->next);
		}
	}

	// Return the minimum value
	Node *min()
	{
		return head->next;
	}

	// Remove the minimum value, don't need to sort.
	void removeMin()
	{
		deleteNode(head->next);
	}

	// Return size of this Priority Queue.
	int size()
	{
		return length;
	}

	// Check whether this Priority Queue is empty.
	bool isEmpty()
	{
		return length == 0;
	}

	// Print this Priority Queue.
	void printPQ()
	{
		cout << "List of elements in the priority queue: ";
		Node *temp = head->next;
		while (temp != tail)
		{ // print the value of each element one-by-one
			cout << temp->val << " ";
			temp = temp->next;
		}
		cout << endl; // end the line
	}
};

int main()
{
	SortedPQ pq;
	pq.insert(5);
	pq.printPQ();

	pq.insert(9);
	pq.printPQ();

	pq.insert(2);
	pq.printPQ();

	pq.insert(7);
	pq.printPQ();

	cout << "The minimum element in the priority queue is: " << pq.min()->val << endl;
	pq.removeMin();
	pq.printPQ();

	cout << "The size of the priority queue is: " << pq.size() << endl;
	pq.removeMin();
	pq.removeMin();
	pq.removeMin();
	pq.removeMin();

	cout << "The priority queue is empty: " << boolalpha << pq.isEmpty() << endl;

	// sorting using priority queue
	int A[10] = {12, 8, 40, 6, 25, 81, 30, 4, 15, 2}; // given an arry A with 10 numbers
	int B[10];										  // sort the numbers into another array B
	int i = 0;
	for (int i = 0; i < 10; i++)
	{
		pq.insert(A[i]);
		pq.printPQ();
	}
	for (int i = 0; i < 10; i++)
	{
		B[i] = pq.min()->val;
		pq.removeMin();
		pq.printPQ();
	}
	for (int i = 0; i < 10; i++)
	{ // print the array B
		cout << B[i] << " ";
	}

	return 0;
}
