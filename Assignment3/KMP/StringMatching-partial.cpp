#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <cstdlib>
#include <fstream>
#include <time.h>

using namespace std;

int BruteForce(string T, string P) // T is text string, P is pattern string
{
    // Lengths
    int n = T.length();
    int m = P.length();
    int i = 0, j = 0;
    // Comparison
    for (i = 0; i <= n - m; i++)
    {
        j = 0;
        while (j < m)
        {
            if (P[j] == T[i + j])
            {
                j++;
            }
            else
            {
                break;
            }
        }
        if (j == m)
        {
            return i;
        }
    }
    return -1;
}

void computeFailureFunction(string P, int *f) // compute the failure function on P
{
    int i = 1, j = 0, m = P.size();
    f[0] = 0;
    while (i < m)
    {
        if (P[i] == P[j]) // Matches, both step in
        {
            f[i] = j + 1;
            i++, j++;
        }
        else if (j == 0) // Doesn't mach here & no previous matches
        {
            f[i] = 0;
            i++;
        }
        else // Doesn't mach here & have previous
        {
            j = f[j - 1]; // Jump to position that supports the last match
        }
    }
}

int KMP(string T, string P)
{
    int n = T.size(), m = P.size();
    int f[m];
    int i = 0, j = 0;
    computeFailureFunction(P, f);
    // // Debug
    // cout << "Debug: Failure Function";
    // for (i = 0; i < m; i++)
    // {
    //     cout << f[i] << " ";
    // }
    // // Debug
    while (i < n)
    {
        if (T[i] == P[j]) // Matches
        {
            if (j == m - 1) // Reach end, output
            {
                return i - m + 1;
            }
            else // Not reach end, step up
            {
                i++, j++;
            }
        }
        else // Doesn't match
        {
            if (j == 0) // No previous matches
            {
                i++;
            }
            else // Has previous matches
            {
                j = f[j - 1]; // Jump to the position that supports the previous match
            }
        }
    }
    return -1;
}

int main()
{
    clock_t Start_time, End_time;
    const int n = 200000, t = 8;
    string str;
    string p[t] = {"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBCCCCCCCCCCCCCCC",
                   "FJZRVSAMACSRXNTGGVVKTFXBWYDTQJMJTF",
                   "CCCCCCCCCCCCCCCAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBB",
                   "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBCCCCCCCCCZYOENZLXS",
                   "AAAAAAAAAAAAAAAAAAAAAAAAABC",
                   "NWYWCRGBGECHHROVBRHLJXHLHPPLAYOLJO",
                   "AAABBBBBBCCCCCCCCCCAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBCCCCCCCCCCAAA",
                   "AAABBBBBBCCCCCCCCCCAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBCCCCCCCCCCAAB"};

    ifstream arr;
    arr.open("/Users/huangyanzhen/Desktop/Year2Sem2/CISC2006/Assignments/Assignment3/KMP/string.txt");
    if (!arr)
    {
        cout << "Unable to open file !" << endl;
        return -1;
    }

    char c;
    int k = 0, result;
    while (arr >> c)
    { // load string from input file
        str += c;
        k++;
    }
    cout << "Reading of string T finished. Length = " << k << endl;

    for (int i = 0; i < t; i++)
    {
        cout << "\n-------String Matching (Round-" << i + 1 << ")-------" << endl;
        cout << "P = " << p[i] << endl
             << endl;

        cout << "using BruteForce algorithm" << endl;
        Start_time = clock();
        result = BruteForce(str, p[i]);
        if (result == -1)
            cout << " P is not a sub-string of T" << endl;
        else
            cout << " P = T[" << result << ", " << result + p[i].size() - 1 << "]" << endl;
        End_time = clock();
        cout << " running time: " << static_cast<double>(End_time - Start_time) / CLOCKS_PER_SEC * 1000 << " ms" << endl;

        cout << "using KMP algorithm" << endl;
        Start_time = clock();
        result = KMP(str, p[i]);
        if (result == -1)
            cout << " P is not a sub-string of T" << endl;
        else
            cout << " P = T[" << result << ", " << result + p[i].size() - 1 << "]" << endl;
        End_time = clock();
        cout << " running time: " << static_cast<double>(End_time - Start_time) / CLOCKS_PER_SEC * 1000 << " ms" << endl;
    }

    return 0;
}
