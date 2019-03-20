#ifndef __AVLTREE_H__
#define __AVLTREE_H__
#include "avltree_node.h"

template<class KEY_TYPE, class VALUE_TYPE>
class avltree {
public:
    avltree() : root(nullptr) {}
    ~avltree();
    bool insert(const KEY_TYPE &key, const VALUE_TYPE &value);
    avltree_node<KEY_TYPE, VALUE_TYPE>* get_root() { return root; }
    void destroy(avltree_node<KEY_TYPE, VALUE_TYPE>*);

private:
    void rotateL(avltree_node<KEY_TYPE, VALUE_TYPE>* parent);
    void rotateR(avltree_node<KEY_TYPE, VALUE_TYPE>* parent);
    void rotateRL(avltree_node<KEY_TYPE, VALUE_TYPE>* parent);
    void rotateLR(avltree_node<KEY_TYPE, VALUE_TYPE>* parent);

    avltree_node<KEY_TYPE, VALUE_TYPE>* root;
};

template<class KEY_TYPE, class VALUE_TYPE>
avltree<KEY_TYPE, VALUE_TYPE>::~avltree()
{
    destroy(root);
}

template<class KEY_TYPE, class VALUE_TYPE>
void avltree<KEY_TYPE, VALUE_TYPE>::destroy(avltree_node<KEY_TYPE, VALUE_TYPE>* node)
{
    if (node == nullptr) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}

template<class KEY_TYPE, class VALUE_TYPE>
bool avltree<KEY_TYPE, VALUE_TYPE>::insert(const KEY_TYPE &key, const VALUE_TYPE &value)
{
    if (root == nullptr)
    {
        root = new avltree_node<KEY_TYPE, VALUE_TYPE>(key, value);
        return true;
    }
    avltree_node<KEY_TYPE, VALUE_TYPE> *parent = nullptr, *cur = root;
    while (cur != nullptr)
    {
        if (cur->key == key) return false;
        else if (cur->key < key) {
            parent = cur;
            cur = cur->right;
        } else {
            parent = cur;
            cur = cur->left;
        }
    }
    cur = new avltree_node<KEY_TYPE, VALUE_TYPE>(key, value);
    cur->parent = parent;
    if (parent->key < key)
    {
        parent->right = cur;
    } else {
        parent->left = cur;
    }
    
    while(parent != nullptr)
    {
        if (parent->left == cur)
        {
            parent->balance--;
        } else {
            parent->balance++;
        }

        if (parent->balance == 0) {
            break;
        } else if (parent->balance == 1 || parent->balance == -1) {
            cur = parent;
            parent = parent->parent;
        } else {
            if (parent->balance == 2)
            {
                if (cur->balance == 1) {
                    rotateL(parent);
                } else {
                    rotateRL(parent);
                }
                
            } else if (parent->balance == -2) {
                if (cur->balance == -1) {
                    rotateR(parent);
                } else {
                    rotateLR(parent);
                }
            }
            break;
        }
    }
    return true;
}

template<class KEY_TYPE, class VALUE_TYPE>
void avltree<KEY_TYPE, VALUE_TYPE>::rotateL(avltree_node<KEY_TYPE, VALUE_TYPE>* cur)
{
    auto parent = cur->parent;
    auto subR = cur->right;
    auto subRL = cur->right->left;
    
    cur->right = subRL;
    if (subRL)
    {
        subRL->parent = cur;
    }

    subR->left = cur;
    cur->parent = subR;
    
    subR->parent = parent;
    if (parent)
    {
        if (parent->left == cur) {
            parent->left = subR;
        } else {
            parent->right = subR;
        }
    } else {
        root = subR;
    }

    cur->balance = 0;
    subR->balance = 0;
}

/* RL(D rotates to the right, then C rotates to the left):
         k3                         k3                          k2
        /  \                       /  \                        /  \
       A    k1                    A    k2                     k3   k1 
           /  \       ==>             /  \         ==>       /  \  / \
          k2   B                     C    k1                A   C D   B
         /  \                            /  \
        C    D                          D    B 
*/


template<class KEY_TYPE, class VALUE_TYPE>
void avltree<KEY_TYPE, VALUE_TYPE>::rotateRL(avltree_node<KEY_TYPE, VALUE_TYPE>* parent)
{
    auto subR = parent->right;
    auto subRL = subR->left;
    auto balance = subRL->balance;

    rotateR(subR);
    rotateL(parent);

    if (balance == 1)
    {
        parent->balance = -1;
        subR->balance = 0;
    } else if (balance == -1)
    {
        parent->balance = 0;
        subR->balance = 1;
    } else {
        parent->balance = 0;
        subR->balance = 0;
    }
}

template<class KEY_TYPE, class VALUE_TYPE>
void avltree<KEY_TYPE, VALUE_TYPE>::rotateR(avltree_node<KEY_TYPE, VALUE_TYPE>* cur)
{
    auto parent = cur->parent;
    auto subL = cur->left;
    auto subLR = subL->right;

    cur->left = subLR;
    if (subLR){
        subLR->parent = cur;
    }
    subL->right = cur;
    cur->parent = subL;
    
    subL->parent = parent;

    if (parent) {
        if (parent->left == cur)
        {
            parent->left = subL;
        } else {
            parent->right = subL;
        }
    } else {
        root = subL;
    }

    subL->balance = 0;
    cur->balance = 0;
}

/* LR(B rotates to the left, then C rotates to the right):
         k3                         k3                       k2
        /  \                       /  \                     /  \
       k1   D                     k2   D                   k1   k3
      /  \         ==>           /  \        ==>          / \   / \
     A    k2                    k1   C                   A  B  C   D
         /  \                  /  \
        B    C                A    B
*/
template<class KEY_TYPE, class VALUE_TYPE>
void avltree<KEY_TYPE, VALUE_TYPE>::rotateLR(avltree_node<KEY_TYPE, VALUE_TYPE>* cur)
{
    auto subL = cur->left;
    auto subLR = subL->right;
    int balance = subLR->balance;
    
    rotateL(subL);
    rotateR(cur);

    if (balance == 1)
    {
        subL->balance = -1;
        cur->balance = 0;
    } else if (balance == -1)
    {
        subL->balance = 0;
        cur->balance = 1;
    } else {
        subL->balance = 0;
        cur->balance = 0;
    }
}


template<class KEY_TYPE, class VALUE_TYPE>
bool check_avltree_balance(avltree<KEY_TYPE, VALUE_TYPE> &tree)
{
    int height = 0;
    return check_avltree_balance(tree.get_root(), height);
}

template<class KEY_TYPE, class VALUE_TYPE>
bool check_avltree_balance(avltree_node<KEY_TYPE, VALUE_TYPE>* root, int &height)
{
    height = 0;
    if (root == nullptr) return true;
    int l = 0, r = 0;
    if (!check_avltree_balance(root->left, l)) return false;
    if (!check_avltree_balance(root->right, r)) return false;
    if (r-l != root->balance) return false;
    if (root->balance >= 2 || root->balance <= -2) return false;
    height = 1+(l<r?r:l);
    return true;
}























#endif
