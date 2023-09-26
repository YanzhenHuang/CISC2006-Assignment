#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

using namespace std;

// Data structure to store a min-heap node
class Heap
{

private:
    int sz;
    // vector to store heap elements (Dynamic Arrays)
    vector<int> A;

    // return parent of `A[i]`
    int PARENT(int i)
    {
        if (i == 0)
            return i;
        return (i - 1) / 2;
    }

    // return left child of `A[i]`
    int LEFT(int i)
    {
        return (2 * i + 1);
    }

    // return right child of `A[i]`
    int RIGHT(int i)
    {
        return (2 * i + 2);
    }

    // swap the two nodes
    void swap(int a, int b)
    {
        int temp = A[a];
        A[a] = A[b];
        A[b] = temp;
    }

public:
    // return size of the heap
    unsigned int size()
    {
        return sz;
    }

    // function to check if the heap is empty or not
    bool isEmpty()
    {
        return sz == 0;
    }

    // Check if an index is External
    bool isExternal(int idx)
    {
        int bottomIndex = A.size() - 1;
        return LEFT(idx) > bottomIndex || RIGHT(idx) > bottomIndex;
    }

    // Check if an index is Internal
    bool isInternal(int idx)
    {
        return !isExternal(idx);
    }

    // Up-Heap Bubbling from index 'key'
    void UpHeapBubble(int idx)
    {
        while (A[idx] < A[PARENT(idx)] && idx != 0)
        {
            swap(idx, PARENT(idx));
            idx = PARENT(idx);
        }
    }

    // Down-Heap Bubbling from index 'key'
    void DownHeapBubble(int idx)
    {
        while (isInternal(idx) && (A[idx] > A[LEFT(idx)] || A[idx] > A[RIGHT(idx)]))
        {
            int l = LEFT(idx);
            int r = RIGHT(idx);
            if (A[l] < A[r])
            {
                swap(idx, l);
                idx = l;
            }
            else
            {
                swap(idx, r);
                idx = r;
            }
        }
    }

    // insert key into the heap
    void insert(int key)
    {
        int bottomIdx = A.size() - 1;
        A.resize(A.size() + 1);
        A[bottomIdx + 1] = key;
        UpHeapBubble(bottomIdx + 1);
        sz++;
    }

    // Function to remove an element with the lowest priority (present at the root)
    void removeMin()
    {
        if (isEmpty())
        {
            return;
        }
        else
        {
            int bottomIdx = A.size() - 1;
            A[0] = A[bottomIdx];
            A.pop_back(); // erase the last element
            A.shrink_to_fit();
            DownHeapBubble(0); // Down-Heap this Complete Binary Tree from root.
            sz--;
        }
    }

    // Function to return an element with the lowest priority (present at the root)
    int min()
    {
        return A[0];
    }

    void printPQ()
    {
        cout << "List of elements in the priority queue: ";
        int i = 0;
        while (i < size())
        {
            cout << A[i] << ' ';
            i++;
        }
        cout << endl;
    }
};

int main()
{
    Heap pq;
    pq.insert(5);
    pq.printPQ();

    pq.insert(9);
    pq.printPQ();

    pq.insert(2);
    pq.printPQ();

    pq.insert(7);
    pq.printPQ();

    cout << "The minimum element in priority queue is " << pq.min() << endl;
    pq.removeMin();
    pq.printPQ();

    cout << "The size of the priority queue is " << pq.size() << endl;
    pq.removeMin();
    pq.removeMin();
    pq.removeMin();
    pq.removeMin();

    cout << "The priority queue is empty: " << boolalpha << pq.isEmpty() << endl;

    // sorting using priority queue
    int A[10] = {12, 8, 40, 6, 25, 81, 30, 4, 15, 2}; // given an arry A with 10 numbers
    int B[10];                                        // sort the numbers into another array B
    int i = 0;
    for (int i = 0; i < 10; i++)
    {
        pq.insert(A[i]);
        pq.printPQ();
    }
    for (int i = 0; i < 10; i++)
    {
        B[i] = pq.min();
        pq.removeMin();
        pq.printPQ();
    }
    for (int i = 0; i < 10; i++)
    { // print the array B
        cout << B[i] << " ";
    }

    return 0;
}
