#include <iostream>
#include "avltree.h"
#include <stdlib.h>
#include <time.h>
#include <map>
#include <vector>
#include <sys/time.h>
#include <sstream>
using namespace std;

static uint64_t currentMSTime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return static_cast<uint64_t>(t.tv_sec) * 1000 + t.tv_usec / 1000;
}

void test_set()
{
    cout << "test_set ==================================== " << endl;
    int a[] = {36 , 39 , 32 , 47 , 45 , 23 , 5 , 42 , 17 , 37 , 25 , 31 , 2 , 8 , 2 , 0 , 19 , 39 , 44 , 41 , 15 , 21 , 15 , 41 , 32 , 17 , 13 , 4 , 33 , 33 , 26 , 19 , 24 , 10 , 18 , 19 , 35 , 23 , 11 , 4 , 11 , 38 , 35 , 15 , 46 , 39 , 17 , 18 , 28 , 12 };
    int remove[] = {37, 39, 10, 32, 35, 44, 15, 36, 15, 13, 19, 36, 39, 31, 25};
    auto tree = avltree<int, int>();
    for(int i = 0; i<sizeof(a)/sizeof(int); i++)
    {
        int k = a[i];
        tree.insert(k, k);
        cout << "insert k " << k <<  " isBanlance: " << check_avltree_balance(tree) << endl;
    }

    for(int i = 0; i<sizeof(remove)/sizeof(int); i++)
    {
//        cout << i << endl;
        tree.remove(remove[i]);
    }


}

void random_set()
{
    stringstream inputsstr, removesstr;
    cout << "random_set ==================================== " << endl;
    const int MAX_NODE = 50;
    srand(time(nullptr));
    auto tree = avltree<int, int>();
    vector<int> input;
    for(int i = 0; i<MAX_NODE; i++)
    {
        int k = rand()%MAX_NODE;
        input.push_back(k);
        tree.insert(k, k);
        if (!check_avltree_balance(tree))
        {
            cout << "error!!" << endl;
        }
        cout << "insert k " << k <<  " isBanlance: " << check_avltree_balance(tree) << endl;
        inputsstr << k <<  " , ";
    }
    cout << "tree.size() " << tree.size() << endl; 
    cout <<  inputsstr.str() << endl;

    for(int i = 0; i<MAX_NODE; i++)
    {
        auto it = input.begin();
        advance(it, rand()%input.size());
        removesstr << *it  << ", ";
        cout << removesstr.str() <<endl;
        tree.remove(*it);
        cout << "remove " << *it << endl;
    }
    
    cout << "after delete tree.size() " << tree.size() << endl; 
}



void compare_stl_bst()
{
    srand(time(nullptr));
    vector<int> input;
    const int MAX_NODE = 1000000;
    for (int i = 0; i<MAX_NODE; i++) input.push_back(rand()%MAX_NODE);
    auto tree = avltree<int, int>();
    auto cur = currentMSTime();
    for(auto a: input)
    {
        tree.insert(a, a);
    }
    cout << "avltree cost : " << currentMSTime() - cur << endl;
    cur = currentMSTime();
    map<int, int> b;
    for(auto a:input)
    {
        b.insert(make_pair(a, a));
    }
    cout << "stl rb tree cost : " << currentMSTime() - cur << endl;
    cout << "rbtree.size() " << b.size() << endl;
    cout << "tree.size() " << tree.size() << endl; 

    for(int i = 0; i<1000; i++)
    {
        auto it = input.begin();
        advance(it, rand()%input.size());
        tree.remove(*it);
        b.erase(*it);
    }
    cout << "rbtree.size() " << b.size() << endl;
    cout << "tree.size() " << tree.size() << endl; 
  


}


int main()
{
    test_set();
//    random_set();
//    compare_stl_bst();
    return 0;
}
