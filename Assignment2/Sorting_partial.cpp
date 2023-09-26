#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <cstdlib>
#include <fstream>
#include <time.h>

using namespace std;

// A Doubly Linked List
struct DList
{
    struct Node
    {
        int key;
        Node *prev;
        Node *next;
        Node()
        {
            Node(0, NULL, NULL);
        }
        Node(int k, Node *left, Node *right)
        {
            key = k;
            prev = left;
            next = right;
        }
    };

    int sz;
    Node *head;
    Node *tail;

    void addBetween(int k, Node *pred, Node *succ)
    {
        Node *add = new Node(k, pred, succ);
        pred->next = add;
        succ->prev = add;
        sz++;
    }

    Node *deleteNode(Node *trash)
    {
        Node *pred = trash->prev;
        Node *succ = trash->next;
        pred->next = succ;
        succ->prev = pred;
        trash->prev = NULL;
        trash->next = NULL;
        sz--;
        return trash;
    }

    DList()
    {
        sz = 0;
        head = new Node(0, NULL, NULL);
        tail = new Node(0, head, NULL);
        head->next = tail;
    }
    void insert(int k)
    {
        addBetween(k, tail->prev, tail);
    }

    Node *min()
    {
        Node *ptr = head->next;
        Node *min = ptr;
        while (ptr->next != tail)
        {
            if (ptr->key < min->key)
                min = ptr;
            ptr = ptr->next;
        }
        return min;
    }

    int removeMin()
    {
        return deleteNode(min())->key;
    }
};
/* Swap-based sorting algorithms*/
void swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void InsertionSort(int *num, int n)
{
    for (int i = 0; i < n; i++)
    {
        int e = num[i];
        int j = i - 1;
        while (j >= 0 && num[j] > e)
        {
            num[j + 1] = num[j];
            j--;
        }
        num[j + 1] = e;
    }
}

void BubbleSort(int *num, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1; j++)
        {
            if (num[j] > num[j + 1])
                swap(num[j], num[j + 1]);
        }
    }
}

/* Sort using priority queue (implemented by unsorted list).*/
void SelectionSort(int *num, int n)
{
    DList *USList = new DList(); // Unsorted List

    for (int i = 0; i < n; i++) // Insert
    {
        USList->insert(num[i]);
    }

    for (int i = 0; i < n; i++) // Extraact
    {
        num[i] = USList->removeMin();
    }
    return;
}

void Heap_build(int a[], int root, int length) // Create heap
{
    int lchild = root * 2 + 1;
    if (lchild < length)
    {
        int max_val = lchild;
        int rchild = lchild + 1;
        if (rchild < length)
        {
            if (a[rchild] > a[max_val]) // find the larger value of the two children
            {
                max_val = rchild;
            }
        }
        if (a[root] < a[max_val]) // put the larger value to the parent node
        {
            swap(a[root], a[max_val]);
            Heap_build(a, max_val, length); // recursive fix of the heap-order property
        }
    }
}

void HeapSort(int *a, int len)
{
    for (int i = (len - 1) / 2; i >= 0; --i) // create heap from the last internal node
    {
        Heap_build(a, i, len);
    }

    for (int j = len - 1; j > 0; --j) // j is the length of array (need to reconstruct)
    {
        swap(a[0], a[j]);    // put the larger value to the last position of the array
        Heap_build(a, 0, j); // remove the element at the last position and rebuild the heap
    }
}

/* Sorting using Divide-and-conquer.*/
void *Merge(int *num, int *L, int lenL, int *R, int lenR)
{
    int l = 0, r = 0;
    int length = lenL + lenR;

    for (int i = 0; i < length; i++)
    {
        if (l <= lenL - 1 && r <= lenR - 1)
        {
            if (L[l] <= R[r])
            {
                num[i] = L[l];
                l++;
            }
            else
            {
                num[i] = R[r];
                r++;
            }
        }
        else if (l > lenL - 1 && r <= lenR - 1) // Left reaches end
        {

            num[i] = R[r];
            r++;
        }
        else if (l <= lenL - 1 && r > lenR - 1) // right reaches end
        {

            num[i] = L[l];
            l++;
        }
    }
}

void *MergeSort(int *num, int n)
{
    // Base Case: n<=1
    if (n >= 2)
    {
        // Partition the equation into two parts
        int k = n / 2;
        int *L = (int *)malloc(sizeof(int *) * k);
        int *R = (int *)malloc(sizeof(int *) * (n - k));
        for (int i = 0; i < k; i++)
        {
            L[i] = num[i];
        }
        for (int i = k; i < n; i++)
        {
            R[i - k] = num[i];
        }

        MergeSort(L, k);
        MergeSort(R, n - k);
        Merge(num, L, k, R, n - k);
    }
}

int PickPivot(int *num, int low, int high) // Pick 3 numbers at random and take the median value
{

    srand(time(0)); // initialize the random seed

    int diff = high - low;
    int randId_1 = low + (rand() % (diff + 1));
    int randId_2 = low + (rand() % (diff + 1));
    int randId_3 = low + (rand() % (diff + 1));

    int temp;
    if ((randId_1 > randId_2) ^ (randId_1 > randId_3)) // randId_1 is median
    {
        temp = randId_1;
    }
    else if ((randId_2 < randId_1) ^ (randId_2 < randId_3)) // randId_2 is median
    {
        temp = randId_2;
    }
    else
    {
        temp = randId_3;
    }
    return temp;
}

void QuickSort(int *num, int low, int high)
{

    if (low < high)
    {
        int temp = PickPivot(num, low, high); // pick a random number
        int random = num[temp];

        swap(num[temp], num[high]);

        int i = low - 1; // Stores the previous value that is larger than pivot.
        for (int j = low; j < high; j++)
        {
            if (num[j] <= random) // the current value is smaller than pivot
            {
                ++i;
                swap(num[i], num[j]); // swap backward the one bigger than pivot
            }
        }

        int pivot = i + 1; // Largest value
        swap(num[pivot], num[high]);

        QuickSort(num, low, pivot - 1);
        QuickSort(num, pivot + 1, high);
    }
}
/* Utilities*/
void print(int *num, int length)
{
    for (int i = 0; i < length; i++)
        cout << num[i] << " ";
    cout << endl;
}

int main()
{
    clock_t Start_time, End_time;
    const int Len = 100000;
    int num[Len], k = 0, new_num, a[Len], length;

    ifstream arr;
    arr.open("input.txt");

    if (!arr)
    {
        cout << "Unable to open file !" << endl;
        return -1;
    }

    while (arr >> new_num)
    {
        a[k++] = new_num;
    }
    length = k;
    cout << "Reading of array finished, " << length << " elements found." << endl;

    cout << "\n-------Sorting using InsertionSort-------" << endl;
    for (int i = 0; i < length; i++)
    {
        num[i] = a[i];
    }
    Start_time = clock();
    InsertionSort(num, length);
    End_time = clock();
    cout << "The running time of InsertionSort is: " << static_cast<double>(End_time - Start_time) / CLOCKS_PER_SEC * 1000 << " ms" << endl;
    cout << "The first 20 elements are : ";
    print(num, min(20, length));

    cout << "\n-------Sorting using BubbleSort-------" << endl;
    for (int i = 0; i < length; i++)
    {
        num[i] = a[i];
    }
    Start_time = clock();

    BubbleSort(num, length);
    End_time = clock();
    cout << "The running time of BubbleSort is: " << static_cast<double>(End_time - Start_time) / CLOCKS_PER_SEC * 1000 << " ms" << endl;
    cout << "The first 20 elements are : ";
    print(num, min(20, length));

    cout << "\n-------Sorting using SelectionSort-------" << endl;
    for (int i = 0; i < length; i++)
    {
        num[i] = a[i];
    }
    Start_time = clock();
    SelectionSort(num, length);
    End_time = clock();
    cout << "Total running time SelectionSort is: " << static_cast<double>(End_time - Start_time) / CLOCKS_PER_SEC * 1000 << " ms" << endl;
    cout << "The first 20 elements are : ";
    print(num, min(20, length));

    cout << "\n-------Sorting using HeapSort-------" << endl;
    for (int i = 0; i < length; i++)
    {
        num[i] = a[i];
    }
    Start_time = clock();
    HeapSort(num, length);
    End_time = clock();
    cout << "Total running time HeapSort is: " << static_cast<double>(End_time - Start_time) / CLOCKS_PER_SEC * 1000 << " ms" << endl;
    cout << "The first 20 elements are : ";
    print(num, min(20, length));

    cout << "\n-------Sorting using MergeSort-------" << endl;
    for (int i = 0; i < length; i++)
    {
        num[i] = a[i];
    }
    Start_time = clock();
    MergeSort(num, length);
    End_time = clock();
    cout << "Total running time MergeSort is: " << static_cast<double>(End_time - Start_time) / CLOCKS_PER_SEC * 1000 << " ms" << endl;
    cout << "The first 20 elements are : ";
    print(num, min(20, length));

    cout << "\n-------Sorting using QuickSort-------" << endl;
    for (int i = 0; i < length; i++)
    {
        num[i] = a[i];
    }
    Start_time = clock();
    QuickSort(num, 0, length - 1);
    End_time = clock();
    cout << "Total running time QuickSort is: " << static_cast<double>(End_time - Start_time) / CLOCKS_PER_SEC * 1000 << " ms" << endl;
    cout << "The first 20 elements are : ";
    print(num, min(20, length));

    return 0;
}
