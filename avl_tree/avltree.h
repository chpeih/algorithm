#ifndef __AVLTREE_H__
#define __AVLTREE_H__

#define AVLTREE_NODE avltree_node<KEY_TYPE, VALUE_TYPE>
#define AVLTREE_NODE_PTR avltree_node<KEY_TYPE, VALUE_TYPE>*
#include "util.h"

template<class KEY_TYPE, class VALUE_TYPE>
class avltree_node {
public:
    KEY_TYPE key;
    VALUE_TYPE value;
    int height;
    AVLTREE_NODE_PTR left_ptr;
    AVLTREE_NODE_PTR right_ptr;
    avltree_node(const KEY_TYPE &_key = KEY_TYPE(), const VALUE_TYPE &_value = VALUE_TYPE()): key(_key), value(_value), height(0), left_ptr(nullptr), right_ptr(nullptr) {} 
};

template<class KEY_TYPE, class VALUE_TYPE>
class avltree {
public:
    avltree() : root_ptr(nullptr), node_size(0) {}
    ~avltree();
    void insert(const KEY_TYPE &key, const VALUE_TYPE &value);
    AVLTREE_NODE_PTR get_root() { return root_ptr; }
    void clear();
    int get_height();
    int size() { return node_size; };
    void remove(const KEY_TYPE &key);

private:
    void clear(AVLTREE_NODE_PTR node_ptr);
    int get_height(AVLTREE_NODE_PTR node_ptr);
    AVLTREE_NODE_PTR new_node(const KEY_TYPE& key, const VALUE_TYPE& value);
    AVLTREE_NODE_PTR insert(AVLTREE_NODE_PTR cur_ptr, const KEY_TYPE &key, const VALUE_TYPE &value);
    AVLTREE_NODE_PTR rotateL(AVLTREE_NODE_PTR cur_ptr);
    AVLTREE_NODE_PTR rotateR(AVLTREE_NODE_PTR cur_ptr);
    AVLTREE_NODE_PTR rotateRL(AVLTREE_NODE_PTR cur_ptr);
    AVLTREE_NODE_PTR rotateLR(AVLTREE_NODE_PTR cur_ptr);
    AVLTREE_NODE_PTR remove(AVLTREE_NODE_PTR cur_ptr, const KEY_TYPE &key);
    AVLTREE_NODE_PTR find_min(AVLTREE_NODE_PTR cur_ptr);
    AVLTREE_NODE_PTR find_max(AVLTREE_NODE_PTR cur_ptr);

    AVLTREE_NODE_PTR root_ptr;
    int node_size;
};

template<class KEY_TYPE, class VALUE_TYPE>
avltree<KEY_TYPE, VALUE_TYPE>::~avltree()
{
    clear();
}

template<class KEY_TYPE, class VALUE_TYPE>
void avltree<KEY_TYPE, VALUE_TYPE>::clear()
{
    node_size = 0;
    clear(root_ptr);
}

template<class KEY_TYPE, class VALUE_TYPE>
void avltree<KEY_TYPE, VALUE_TYPE>::clear(AVLTREE_NODE_PTR node_ptr)
{
    if (node_ptr == nullptr) return;
    clear(node_ptr->left_ptr);
    clear(node_ptr->right_ptr);
    delete node_ptr;
}

template<class KEY_TYPE, class VALUE_TYPE>
AVLTREE_NODE_PTR avltree<KEY_TYPE, VALUE_TYPE>::new_node(const KEY_TYPE& key, const VALUE_TYPE &value)
{
    auto node = new AVLTREE_NODE(key, value);
    return node;
}

template<class KEY_TYPE, class VALUE_TYPE>
int avltree<KEY_TYPE, VALUE_TYPE>::get_height()
{
    return get_height(root_ptr);
}

template<class KEY_TYPE, class VALUE_TYPE>
int avltree<KEY_TYPE, VALUE_TYPE>::get_height(AVLTREE_NODE_PTR node_ptr)
{
    if (node_ptr == NULL) return -1;
    return node_ptr->height;
}

template<class KEY_TYPE, class VALUE_TYPE>
void avltree<KEY_TYPE, VALUE_TYPE>::insert(const KEY_TYPE &key, const VALUE_TYPE &value)
{
    root_ptr = insert(root_ptr, key, value);
    return;
}

template<class KEY_TYPE, class VALUE_TYPE>
AVLTREE_NODE_PTR avltree<KEY_TYPE, VALUE_TYPE>::insert(AVLTREE_NODE_PTR cur_ptr, const KEY_TYPE &key, const VALUE_TYPE &value)
{
    if (cur_ptr == nullptr) {
        cur_ptr = new_node(key, value);
        ++node_size;

    } else if (key < cur_ptr->key) {
        cur_ptr->left_ptr = insert(cur_ptr->left_ptr, key, value);
        if (get_height(cur_ptr->left_ptr) - get_height(cur_ptr->right_ptr) == 2)
        {
            if (key < cur_ptr->left_ptr->key)
                cur_ptr = rotateR(cur_ptr);
            else 
                cur_ptr = rotateLR(cur_ptr);
        }

    } else if (key > cur_ptr->key) {
        cur_ptr->right_ptr = insert(cur_ptr->right_ptr, key, value);
        if (get_height(cur_ptr->left_ptr) - get_height(cur_ptr->right_ptr) == -2)
        {
            if (key < cur_ptr->right_ptr->key)
                cur_ptr = rotateRL(cur_ptr);
            else
                cur_ptr = rotateL(cur_ptr);
        }
    } else {
        cur_ptr->value = value;
    }
    cur_ptr->height = max(height(cur_ptr->left_ptr), height(cur_ptr->right_ptr)) + 1;
    return cur_ptr;
}

template<class KEY_TYPE, class VALUE_TYPE>
AVLTREE_NODE_PTR avltree<KEY_TYPE, VALUE_TYPE>::rotateL(AVLTREE_NODE_PTR cur_ptr)
{
    auto subR_ptr = cur_ptr->right_ptr;
    auto subRL_ptr = subR_ptr->left_ptr;

    cur_ptr->right_ptr = subRL_ptr;
    subR_ptr->left_ptr = cur_ptr;

    cur_ptr->height = max(get_height(cur_ptr->left_ptr), get_height(cur_ptr->right_ptr)) + 1;
    subR_ptr->height = max(get_height(subR_ptr->left_ptr), get_height(subR_ptr->right_ptr)) + 1;
    return subR_ptr;
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
AVLTREE_NODE_PTR avltree<KEY_TYPE, VALUE_TYPE>::rotateRL(AVLTREE_NODE_PTR cur_ptr)
{
    cur_ptr->right_ptr = rotateR(cur_ptr->right_ptr);
    return rotateL(cur_ptr);

}

template<class KEY_TYPE, class VALUE_TYPE>
AVLTREE_NODE_PTR avltree<KEY_TYPE, VALUE_TYPE>::rotateR(AVLTREE_NODE_PTR cur_ptr)
{
    auto subL_ptr = cur_ptr->left_ptr;
    auto subLR_ptr = subL_ptr->right_ptr;
    
    cur_ptr->left_ptr = subLR_ptr;
    subL_ptr->right_ptr = cur_ptr;

    cur_ptr->height = max(get_height(cur_ptr->left_ptr), get_height(cur_ptr->right_ptr)) + 1;
    subL_ptr->height = max(get_height(subL_ptr->left_ptr), get_height(subL_ptr->right_ptr)) + 1;
    return subL_ptr;
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
AVLTREE_NODE_PTR avltree<KEY_TYPE, VALUE_TYPE>::rotateLR(AVLTREE_NODE_PTR cur_ptr)
{
    cur_ptr->left_ptr = rotateL(cur_ptr->left_ptr);
    return rotateR(cur_ptr);
}

template<class KEY_TYPE, class VALUE_TYPE>
void avltree<KEY_TYPE, VALUE_TYPE>::remove(const KEY_TYPE& key)
{
    root_ptr = remove(root_ptr, key);
}

template<class KEY_TYPE, class VALUE_TYPE>
AVLTREE_NODE_PTR avltree<KEY_TYPE, VALUE_TYPE>::find_min(AVLTREE_NODE_PTR cur_ptr)
{
    if (cur_ptr == nullptr || cur_ptr->left_ptr == nullptr) return cur_ptr;
    return find_min(cur_ptr->left_ptr);
}

template<class KEY_TYPE, class VALUE_TYPE>
AVLTREE_NODE_PTR avltree<KEY_TYPE, VALUE_TYPE>::find_max(AVLTREE_NODE_PTR cur_ptr)
{
    if (cur_ptr == nullptr || cur_ptr->right_ptr == nullptr) return cur_ptr;
    return find_max(cur_ptr->right_ptr);
}

template<class KEY_TYPE, class VALUE_TYPE>
AVLTREE_NODE_PTR avltree<KEY_TYPE, VALUE_TYPE>::remove(AVLTREE_NODE_PTR cur_ptr, const KEY_TYPE &key)
{
    AVLTREE_NODE_PTR temp = nullptr;
    if (cur_ptr == nullptr)
        return nullptr;
    else if (key < cur_ptr->key)
        cur_ptr->left_ptr = remove(cur_ptr->left_ptr, key);
    else if (key > cur_ptr->key)
        cur_ptr->right_ptr = remove(cur_ptr->right_ptr, key);
    else if (cur_ptr->left_ptr && cur_ptr->right_ptr)
    {
        temp = find_min(cur_ptr->right_ptr);
        cur_ptr->key = temp->key;
        cur_ptr->value = temp->value;
        cur_ptr->right_ptr = remove(cur_ptr->right_ptr, cur_ptr->key);
    } else {
        temp = cur_ptr;
        if (cur_ptr->left_ptr == nullptr)
            cur_ptr = cur_ptr->right_ptr; 
        else if (cur_ptr->right_ptr == nullptr) 
            cur_ptr = cur_ptr->left_ptr; 
        delete temp; 
        node_size--; 
    }

    if (cur_ptr == nullptr) return cur_ptr;

    auto left_height = height(cur_ptr->left_ptr), right_height = height(cur_ptr->right_ptr);
    cur_ptr->height = max(left_height, right_height) + 1;

    if (left_height - right_height == 2) {
        if (height(cur_ptr->left_ptr->right_ptr) > height(cur_ptr->left_ptr->left_ptr))
            return rotateLR(cur_ptr);
        else
            return rotateR(cur_ptr);

    } else if (right_height - left_height == 2) {
        if (height(cur_ptr->right_ptr->left_ptr) > height(cur_ptr->right_ptr->right_ptr))
            return rotateRL(cur_ptr);
        else
            return rotateL(cur_ptr);
    }
    return cur_ptr;
}

template<class KEY_TYPE, class VALUE_TYPE>
bool check_avltree_balance(avltree<KEY_TYPE, VALUE_TYPE> &tree)
{
    return check_avltree_balance(tree.get_root());
}

template<class KEY_TYPE, class VALUE_TYPE>
int height(AVLTREE_NODE_PTR root_ptr)
{
    if (root_ptr == nullptr) return -1;
    return root_ptr->height;
}

template<class KEY_TYPE, class VALUE_TYPE>
bool check_avltree_balance(AVLTREE_NODE_PTR root_ptr)
{
    if (root_ptr == nullptr) return true;
    return check_avltree_balance(root_ptr->left_ptr) && check_avltree_balance(root_ptr->right_ptr) && myabs(height(root_ptr->left_ptr) - height(root_ptr->right_ptr)) <= 1;
}

#endif
