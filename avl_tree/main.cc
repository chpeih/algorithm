#include <iostream>
#include "avltree.h"
#include <stdlib.h>
#include <time.h>
#include <map>
#include <vector>
#include <sys/time.h>
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
    int a[] = {21, 24, 22, 18, 6, 20};
    auto tree = avltree<int, int>();
    for(int i = 0; i<6; i++)
    {
        int k = a[i];
        tree.insert(k, k);
        cout << "insert k " << k <<  " isBanlance: " << check_avltree_balance(tree) << endl;
    }
}

void random_set()
{
    cout << "random_set ==================================== " << endl;
    const int MAX_NODE = 3000;
    srand(time(nullptr));
    auto tree = avltree<int, int>();
    for(int i = 0; i<MAX_NODE; i++)
    {
        int k = rand()%MAX_NODE;
        tree.insert(k, k);
        if (!check_avltree_balance(tree))
        {
            cout << "error!!" << endl;
        }
//        cout << "insert k " << k <<  " isBanlance: " << check_avltree_balance(tree) << endl;
    }
    cout << "tree.size() " << tree.size() << endl; 
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
    random_set();
    compare_stl_bst();
    return 0;
}
