#include <iostream>
#include <algorithm>
#include "binary_search.h"
#include <map>
#include <stdlib.h>
#include <time.h>
using namespace std;

bool test_first_occur()
{
    cout << __func__  << " start " << endl;
    srand(time(NULL));
    const int MAXN = 10000;
    int A[MAXN];
    for(int i = 0; i<MAXN; i++)
    {
        A[i] = rand()%(MAXN/2);
    }
    sort(A, A+MAXN);

    for(int i = 0; i<MAXN; i++)
    {
        int val = rand()%MAXN;
        int f1 = -1;
        for(int j = 0; j<MAXN; j++)
        {
            if(A[j] == val)
            {
                f1 = j;
                break;
            }
        }
        int f2 = binary_search_first_occur(A, MAXN, val);
        if(f1!=f2)
        {
            cout << __func__ << " find A error " << val << endl;
            return false;
        }
    }
    cout << __func__ << " success." << endl;
    return true;
}

bool test_last_occur()
{
    cout << __func__  << " start " << endl;
    srand(time(NULL));
    const int MAXN = 1000;
    int A[MAXN];
    for(int i = 0; i<MAXN; i++)
    {
        A[i] = rand()%(MAXN/2);
    }
    sort(A, A+MAXN);

    for(int i = 0; i<MAXN; i++)
    {
        int val = rand()%MAXN;
        int f1 = -1;
        for(int j = MAXN-1; j>=0; j--)
        {
            if(A[j] == val)
            {
                f1 = j;
                break;
            }
        }
        int f2 = binary_search_last_occur(A, MAXN, val);
        if(f1!=f2)
        {
            cout << __func__ << " find A error " << val << endl;
            return false;
        }
    }
    cout << __func__ << " success." << endl;
    return true;
}

bool test_less_max()
{
    cout << __func__  << " start " << endl;
    srand(time(NULL));
    const int MAXN = 1000;
    int A[MAXN];
    for(int i = 0; i<MAXN; i++)
    {
        A[i] = rand()%(MAXN/2);
    }
    sort(A, A+MAXN);

    for(int i = 0; i<MAXN; i++)
    {
        int val = rand()%MAXN;
        int f1 = -1;
        for(int j = 0; j<MAXN; j++)
        {
            if(A[j] < val)
            {
                f1 = j;
            }
        }
        int f2 = less_max(A, MAXN, val);
        if(f1!=f2)
        {
            cout << __func__ << " find A error " << val << endl;
            return false;
        }
    }
    cout << __func__ << " success." << endl;
    return true;
}

bool test_greater_min()
{
    cout << __func__  << " start " << endl;
    srand(time(NULL));
    const int MAXN = 1000;
    int A[MAXN];
    for(int i = 0; i<MAXN; i++)
    {
        A[i] = rand()%(MAXN/2);
    }
    sort(A, A+MAXN);

    for(int i = 0; i<MAXN; i++)
    {
        int val = rand()%MAXN;
        int f1 = -1;
        for(int j = MAXN-1; j>=0; j--)
        {
            if(A[j] > val)
            {
                f1 = j;
            }
        }
        int f2 = greater_min(A, MAXN, val);
        if(f1!=f2)
        {
            cout << __func__ << " find A error " << val << endl;
            return false;
        }
    }
    cout << __func__ << " success." << endl;
    return true;
}

int main()
{
//    for(int i = 0; i<100; i++)
//        if(!test_first_occur())
//        {
//            break;
//        }
//    for(int i = 0; i<100; i++)if(!test_last_occur())break;
//    for(int i = 0; i<100; i++)if(!test_less_max())break;
    for(int i = 0; i<100; i++)if(!test_greater_min())break;
    return 0;
}


