#include <iostream>
#include "rbtree.h"
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

bool checkBST(rbtree<int, int>* tree)
{
    vector<int> keys;
    tree->inorder(&keys);
//    for(auto k: keys)
//        cout << " " << k;
//    cout << endl;
    for(int i = 1; i<keys.size(); i++)
    {
      if(keys[i]<=keys[i-1]) return false;
    }
    return true;
}


void test_set()
{
    cout << "test_set ==================================== " << endl;
    int a[] = {36 , 39 , 32 , 47 , 45 , 23 , 5 , 42 , 17 , 37 , 25 , 31 , 2 , 8 , 2 , 0 , 19 , 39 , 44 , 41 , 15 , 21 , 15 , 41 , 32 , 17 , 13 , 4 , 33 , 33 , 26 , 19 , 24 , 10 , 18 , 19 , 35 , 23 , 11 , 4 , 11 , 38 , 35 , 15 , 46 , 39 , 17 , 18 , 28 , 12 };
    int remove[] = {37, 39, 10, 32, 35, 44, 15, 36, 15, 13, 19, 36, 39, 31, 25};

//    int a[] = {0, 4, 3};
    auto tree = rbtree<int, int>();
    for(int i = 0; i<sizeof(a)/sizeof(int); i++)
    {
        int k = a[i];
        tree.insert(k, k);
        if (!checkBST(&tree)){
            cout << "Invalid rbtree nor bst" << endl;
        }
    }

    for(int i = 0; i<sizeof(remove)/sizeof(int); i++)
    {
        tree.remove(remove[i]);
        if (!checkBST(&tree)){
            cout << "remove Invalid rbtree nor bst" << endl;
        }

    }

}

void random_set()
{
    cout << "random_set ==================================== " << endl;
    const int MAX_NODE = 500;
    srand(time(nullptr));
    auto tree = rbtree<int, int>();
    for(int i = 0; i<MAX_NODE; i++)
    {
        int k = rand()%MAX_NODE;
        tree.insert(k, k);
//        cout << "insert k " << k << endl;
        if (!checkBST(&tree)){
            cout << "Invalid rbtree nor bst" << endl;
        }
    }
}

void compare_stl_bst()
{
    srand(time(nullptr));
    vector<int> input;
    const int MAX_NODE = 30000;
    for (int i = 0; i<MAX_NODE; i++) input.push_back(rand()%MAX_NODE);
    auto tree = rbtree<int, int>();
    auto cur = currentMSTime();
    for(auto a: input)
    {
        tree.insert(a, a);
    }
    cout << "rbtree cost : " << currentMSTime() - cur << endl;
    cur = currentMSTime();
    map<int, int> b;
    for(auto a:input)
    {
        b.insert(make_pair(a, a));
    }
    cout << "stl rb tree cost : " << currentMSTime() - cur << endl;

    if (!checkBST(&tree)){
        cout << "Invalid rbtree nor bst" << endl;
    }

    if (!tree.check_valid())
    {
        cout << "invalid rbtree nor rbtree" << endl;
    }

    for(int i = 0; i<MAX_NODE/10; i++)
    {
        auto it = input.begin();
        advance(it, rand()%input.size());
        tree.remove(*it);
        b.erase(*it);
    }
    cout << "map.size() " << b.size() << endl;
    cout << "tree.size() " << tree.size() << endl; 

    if (!tree.check_valid())
    {
        cout << "invalid rbtree nor rbtree" << endl;
    }

}


int main()
{
    test_set();
    random_set();
    compare_stl_bst();
    return 0;
}
