#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <cstdlib>
#include <fstream>
#include <time.h>

using namespace std;

struct Item
{
    int id;
    int val;
    int size;
};

void Knapsack_DP(Item items[], int n, int C)
{
    // int i, j;
    int dp[n + 1][C + 1]; // Dynamic Records
    bool t[n + 1][C + 1]; // direction of recursion, True means selecting the item
    int solution[n + 1];  // Collection of items in the solution
    int i = 0, b = 0;
    for (i = 1; i <= n; i++)
    {
        for (b = 1; b <= C; b++) // Capacity
        {
            if (i == 0)
                dp[i][b] = 0;
            if (b >= items[i].size) // Enough capacity for this element
            {

                int value_choose = dp[i - 1][b - items[i].size] + items[i].val; // Value from choosing the element
                int value_notChoose = dp[i - 1][b];                             // Value from not choosing element
                dp[i][b] = max(value_choose, value_notChoose);                  // Select Optimal Solution
                t[i][b] = (value_choose >= value_notChoose) ? true : false;     // Mark solution path
            }
            else // Not enough capacity of this element
            {
                dp[i][b] = dp[i - 1][b];
            }
        }
    }

    int objective = dp[n][C]; // Store the objective solution

    // Print solution path
    cout << "The solution is: ";
    while (i > 0 && b > 0)
    {
        if (t[i][b]) // Yes
        {
            cout << i-- << " ";
            b -= items[i].size;
        }
        else // No
        {
            i--;
        }
    }
    cout << endl;
    cout << "The objective is: " << objective << endl;
}

bool cmp_value(Item a, Item b) // Value Priority
{
    if (a.val != b.val)
        return a.val > b.val;
    return a.size < b.size;
}

bool cmp_size(Item a, Item b) // Size Priority
{
    if (a.size != b.size)
        return a.size < b.size;
    return a.val > b.val;
}

bool cmp_density(Item a, Item b) // Density Priority
{
    int dens[2];
    dens[0] = (a.val) / (a.size);
    dens[1] = (b.val) / (b.size);
    if (dens[0] != dens[1])
    {
        return dens[0] > dens[1];
    }
    else if (a.val != b.val)
    {
        return a.val > b.val;
    }
}

void GreedyMaxValue(Item items[], int n, int C)
{
    int i, j = 0;
    int c = C; // Capacity
    int k = 0; // Solution Index
    int total_val = 0;
    int solution[n];

    sort(items, items + n, cmp_value); // Large value to small value

    while (j < n) // Traverse every item
    {
        if (c >= items[j].size) // Still has remaining capacity
        {
            solution[k++] = items[j].id; // Record current item into the solution
            total_val += items[j].val;   // Add its value
            c -= items[j].size;          // Reduce Capacity
        }
        j++;
    }
    cout << "The solution is: ";

    sort(solution, solution + k);
    for (i = 0; i < k; i++)
    {
        cout << solution[i] << " ";
    }
    cout << endl;
    cout << "The objective is: " << total_val << endl;
}

void GreedyMinSize(Item items[], int n, int C)
{
    int i, j = 0;
    int c = C; // Capacity
    int k = 0; // Solution Index
    int total_val = 0;
    int solution[n];
    sort(items, items + n, cmp_size); // Small size to large size
    while (j < n)
    {
        if (c >= items[j].size)
        {
            solution[k++] = items[j].id;
            total_val += items[j].val;
            c -= items[j].size;
        }
        j++;
    }
    cout << "The solution is: ";

    sort(solution, solution + k);
    for (i = 0; i < k; i++)
    {
        cout << solution[i] << " ";
    }
    cout << endl;
    cout << "The objective is: " << total_val << endl;
}

void GreedyMaxDensity(Item items[], int n, int C)
{
    int i, j = 0;
    int c = C; // Capacity
    int k = 0; // Solution Index
    int total_val = 0;
    int solution[n];
    sort(items, items + n, cmp_density); // Large density to small density
    while (j < n)
    {
        if (c >= items[j].size)
        {
            solution[k++] = items[j].id;
            total_val += items[j].val;
            c -= items[j].size;
        }
        j++;
    }
    cout << "The solution is: ";

    sort(solution, solution + k);
    for (i = 0; i < k; i++)
    {
        cout << solution[i] << " ";
    }
    cout << endl;
    cout << "The objective is: " << total_val << endl;
}

int main()
{
    clock_t Start_time, End_time;
    const int n = 100; // n items, capacity = 300
    int length, C = 300;

    int total = 2, i = 1;
    while (i <= total)
    {
        string filename = "/Users/huangyanzhen/Desktop/Year2Sem2/CISC2006/Assignments/Assignment3/Knapsack/input" + to_string(i) + ".txt";
        cout << endl
             << "-------------------The result for " + filename + "-------------------" << endl
             << endl;

        ifstream arr;
        arr.open(filename);
        i++;

        if (!arr)
        {
            cout << "Unable to open file !" << endl;
            return -1;
        }
        int id, value, size;
        struct Item items[n];
        int k = 0;
        while (arr >> id >> value >> size)
        {
            items[k].id = id;
            items[k].val = value;
            items[k].size = size;
            k++;
        }

        length = k;
        cout << "Reading of array finished, " << length << " items found." << endl;

        cout << "\n-------Knapsack using Dynamic Programming-------" << endl;
        Start_time = clock();
        Knapsack_DP(items, length, C);
        End_time = clock();
        cout << "The running time is: " << static_cast<double>(End_time - Start_time) / CLOCKS_PER_SEC * 1000 << " ms"
             << endl;

        cout << "\n-------Knapsack using Greedy with maximum value first------" << endl;
        Start_time = clock();
        GreedyMaxValue(items, length, C);
        End_time = clock();
        cout << "The running time is: " << static_cast<double>(End_time - Start_time) / CLOCKS_PER_SEC * 1000 << " ms"
             << endl;

        cout << "\n-------Knapsack using Greedy with minimum size first------" << endl;
        Start_time = clock();
        GreedyMinSize(items, length, C);
        End_time = clock();
        cout << "The running time is: " << static_cast<double>(End_time - Start_time) / CLOCKS_PER_SEC * 1000 << " ms"
             << endl;

        cout << "\n-------Knapsack using Greedy with maximum density first------" << endl;
        Start_time = clock();
        GreedyMaxDensity(items, length, C);
        End_time = clock();
        cout << "The running time is: " << static_cast<double>(End_time - Start_time) / CLOCKS_PER_SEC * 1000 << " ms"
             << endl;
    }
    return 0;
}
