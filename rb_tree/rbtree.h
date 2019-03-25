#ifndef __RBTREE_H__
#define __RBTREE_H__
#include <vector>


#define RBTREE_NODE_PTR rbtree_node<KEY_TYPE, VALUE_TYPE>*
#define RBTREE_NODE rbtree_node<KEY_TYPE, VALUE_TYPE>

#define PARENT_PTR(p) ((p)->parent_ptr)
#define GRANDPARENT_PTR(p) (((p)->parent_ptr)->parent_ptr)

enum Color { RED, BLACK };

template<class KEY_TYPE, class VALUE_TYPE>
struct rbtree_node {
    KEY_TYPE key;
    VALUE_TYPE value;
    RBTREE_NODE_PTR parent_ptr;
    RBTREE_NODE_PTR left_ptr;
    RBTREE_NODE_PTR right_ptr;
    Color color;

    rbtree_node(const KEY_TYPE &_key = KEY_TYPE(), const VALUE_TYPE &_value = VALUE_TYPE()): key(_key), value(_value), parent_ptr(nullptr), left_ptr(nullptr), right_ptr(nullptr), color(RED) {}
};

template<class KEY_TYPE, class VALUE_TYPE>
class rbtree {
public:
    rbtree();
    ~rbtree();
    bool empty() { return root_ptr == nil; }
    void clear();
    void insert(const KEY_TYPE &key, const VALUE_TYPE &value);
    void remove(const KEY_TYPE &key);
    RBTREE_NODE_PTR find(const KEY_TYPE &key);
    void inorder(std::vector<KEY_TYPE> *ans) { inorder(root_ptr, ans); }
    int size() { return node_size-1; } // minus nil

    bool check_valid();




private:

    void clear(RBTREE_NODE_PTR node_ptr);
    RBTREE_NODE_PTR new_node(const KEY_TYPE &key, const VALUE_TYPE &value);
    void rbinsert_fixup(RBTREE_NODE_PTR cur_ptr);
    void rotateL(RBTREE_NODE_PTR cur_ptr);
    void rotateR(RBTREE_NODE_PTR cur_ptr);
    void inorder(RBTREE_NODE_PTR node, std::vector<KEY_TYPE> *ans);
    void rbdelete_fixup(RBTREE_NODE_PTR cur_ptr);
    bool check_valid(RBTREE_NODE_PTR cur_ptr, int* height);

    
    RBTREE_NODE_PTR root_ptr;
    RBTREE_NODE_PTR nil;
    size_t node_size;

};

template<class KEY_TYPE, class VALUE_TYPE>
rbtree<KEY_TYPE, VALUE_TYPE>::rbtree(): node_size(0)
{
    nil = new_node(KEY_TYPE(), VALUE_TYPE());
    root_ptr = nil;
    nil->left_ptr = root_ptr; nil->right_ptr = root_ptr; nil->parent_ptr = root_ptr;
}

template<class KEY_TYPE, class VALUE_TYPE>
rbtree<KEY_TYPE, VALUE_TYPE>::~rbtree()
{
    clear(root_ptr);
}

template<class KEY_TYPE, class VALUE_TYPE>
void rbtree<KEY_TYPE, VALUE_TYPE>::clear()
{
    clear(root_ptr);
    delete nil;
}

template<class KEY_TYPE, class VALUE_TYPE>
void rbtree<KEY_TYPE, VALUE_TYPE>::clear(RBTREE_NODE_PTR node_ptr)
{
    if (node_ptr == nil) return;
    clear(node_ptr->left_ptr);
    clear(node_ptr->right_ptr);
    delete node_ptr;
}

template<class KEY_TYPE, class VALUE_TYPE>
void rbtree<KEY_TYPE, VALUE_TYPE>::insert(const KEY_TYPE &key, const VALUE_TYPE &value)
{
    RBTREE_NODE_PTR cur_ptr = root_ptr;
    RBTREE_NODE_PTR parent_ptr = nil;
    while (cur_ptr != nil )
    {
        parent_ptr = cur_ptr;
        if (cur_ptr->key > key)
            cur_ptr = cur_ptr->left_ptr;
        else if(cur_ptr->key < key)
            cur_ptr = cur_ptr->right_ptr;
        else {
            cur_ptr->value = value;
            return;
        }
    }
    auto insert_ptr = new_node(key, value);
    if (parent_ptr == nil)
    {
        root_ptr = insert_ptr;
        root_ptr->parent_ptr = nil;
        nil->left_ptr = root_ptr;
        nil->right_ptr = root_ptr;
        nil->parent_ptr = root_ptr;
    } else {
        if (key < parent_ptr->key)
          parent_ptr->left_ptr = insert_ptr;
        else
          parent_ptr->right_ptr = insert_ptr;
        insert_ptr->parent_ptr = parent_ptr;
    }
    rbinsert_fixup(insert_ptr);
}

template<class KEY_TYPE, class VALUE_TYPE>
void rbtree<KEY_TYPE, VALUE_TYPE>::rbinsert_fixup(RBTREE_NODE_PTR cur_ptr)
{
    while(cur_ptr->parent_ptr->color == RED)
    {
        if (PARENT_PTR(cur_ptr) == GRANDPARENT_PTR(cur_ptr)->left_ptr) {
            auto uncle_ptr = GRANDPARENT_PTR(cur_ptr)->right_ptr;   
            if (uncle_ptr->color == RED)
            {
                PARENT_PTR(cur_ptr)->color = BLACK;
                uncle_ptr->color = BLACK;
                GRANDPARENT_PTR(cur_ptr)->color = RED;
                cur_ptr = GRANDPARENT_PTR(cur_ptr);
            } else {
                if (cur_ptr == PARENT_PTR(cur_ptr)->right_ptr) {
                    cur_ptr = PARENT_PTR(cur_ptr);
                    rotateL(cur_ptr);
                } else {
                    PARENT_PTR(cur_ptr)->color = BLACK;
                    GRANDPARENT_PTR(cur_ptr)->color = RED;
                    cur_ptr = GRANDPARENT_PTR(cur_ptr);
                    rotateR(cur_ptr);
                }
            }
        } else {
            auto uncle_ptr = GRANDPARENT_PTR(cur_ptr)->left_ptr;
            if (uncle_ptr->color == RED) {
                uncle_ptr->color = BLACK;
                PARENT_PTR(cur_ptr)->color = BLACK;
                GRANDPARENT_PTR(cur_ptr)->color = RED;
                cur_ptr = GRANDPARENT_PTR(cur_ptr);
            } else {
                if (cur_ptr == PARENT_PTR(cur_ptr)->left_ptr) {
                    cur_ptr = PARENT_PTR(cur_ptr);
                    rotateR(cur_ptr);
                } else {
                    PARENT_PTR(cur_ptr)->color = BLACK;
                    GRANDPARENT_PTR(cur_ptr)->color = RED;
                    cur_ptr = GRANDPARENT_PTR(cur_ptr);
                    rotateL(cur_ptr);
                }
            }
        }
    }
    root_ptr->color = BLACK;
}

template<class KEY_TYPE, class VALUE_TYPE>
void rbtree<KEY_TYPE, VALUE_TYPE>::rotateL(RBTREE_NODE_PTR cur_ptr)
{
    if (cur_ptr == nil || cur_ptr->right_ptr == nil) return;
    auto subR = cur_ptr->right_ptr;
    auto subRL = subR->left_ptr;
    cur_ptr->right_ptr = subRL;
    if (subRL != nil)
        PARENT_PTR(subRL) = cur_ptr;

    if (PARENT_PTR(cur_ptr) == nil) {
        root_ptr = subR;
        nil->left_ptr = root_ptr;
        nil->right_ptr = root_ptr;
    } else if (PARENT_PTR(cur_ptr)->left_ptr == cur_ptr) {
        PARENT_PTR(cur_ptr)->left_ptr = subR;
    } else {
        PARENT_PTR(cur_ptr)->right_ptr = subR;
    }
    PARENT_PTR(subR) = PARENT_PTR(cur_ptr);
    PARENT_PTR(cur_ptr) = subR;
    subR->left_ptr = cur_ptr;
}

template<class KEY_TYPE, class VALUE_TYPE>
void rbtree<KEY_TYPE, VALUE_TYPE>::rotateR(RBTREE_NODE_PTR cur_ptr)
{
    if (cur_ptr == nil || cur_ptr->left_ptr == nil) return;
    auto subL = cur_ptr->left_ptr;
    auto subLR = subL->right_ptr;
    cur_ptr->left_ptr = subLR;
    if (subLR != nil)
        PARENT_PTR(subLR) = cur_ptr;
    if (PARENT_PTR(cur_ptr) == nil) {
        root_ptr = subL;
        nil->left_ptr = nil->right_ptr = root_ptr;
    } else if(PARENT_PTR(cur_ptr)->left_ptr == cur_ptr) {
        PARENT_PTR(cur_ptr)->left_ptr = subL;
    } else {
        PARENT_PTR(cur_ptr)->right_ptr = subL;
    }
    PARENT_PTR(subL) = PARENT_PTR(cur_ptr);
    PARENT_PTR(cur_ptr) = subL;
    subL->right_ptr = cur_ptr;
}

template<class KEY_TYPE, class VALUE_TYPE>
RBTREE_NODE_PTR rbtree<KEY_TYPE, VALUE_TYPE>::new_node(const KEY_TYPE &key, const VALUE_TYPE &value)
{
    auto node = new RBTREE_NODE(key, value);
    node->right_ptr = nil;
    node->left_ptr = nil;
    ++node_size;
    return node;
}

template<class KEY_TYPE, class VALUE_TYPE>
RBTREE_NODE_PTR rbtree<KEY_TYPE, VALUE_TYPE>::find(const KEY_TYPE &key)
{
    auto cur_ptr = root_ptr;
    while (cur_ptr != nil)
    {
      if (cur_ptr->key == key) 
          break;
      else if (cur_ptr->key > key)
          cur_ptr = cur_ptr->left_ptr;
      else
          cur_ptr = cur_ptr->right_ptr;
    }
    return cur_ptr;
}

template<class KEY_TYPE, class VALUE_TYPE>
void rbtree<KEY_TYPE, VALUE_TYPE>::remove(const KEY_TYPE &key)
{
    RBTREE_NODE_PTR key_ptr = find(key);
    if (key_ptr == nil) return;
    if (key_ptr->left_ptr != nil && key_ptr->right_ptr != nil)
    {
        auto successor = key_ptr->right_ptr;
        while(successor->left_ptr != nil)
        {
            successor = successor->left_ptr;
        }
        key_ptr->key = successor->key;
        key_ptr->value = successor->value;
        key_ptr = successor;
    }
    RBTREE_NODE_PTR child = nil;
    if (key_ptr->left_ptr == nil)
        child = key_ptr->right_ptr;
    else
        child = key_ptr->left_ptr;

    auto parent_ptr = PARENT_PTR(key_ptr);
    PARENT_PTR(child) = parent_ptr;
    if (parent_ptr == nil)
    {
        root_ptr = child;
        child->left_ptr = root_ptr;
        child->right_ptr = root_ptr;
        PARENT_PTR(child) = root_ptr;
    } else if (parent_ptr->left_ptr == key_ptr) {
        parent_ptr->left_ptr = child;
    } else {
        parent_ptr->right_ptr = child;
    }

    if (key_ptr->color == BLACK && !empty())
    {
        rbdelete_fixup(child);
    }
    delete key_ptr;
    node_size--;
    return;
}

template<class KEY_TYPE, class VALUE_TYPE>
void rbtree<KEY_TYPE, VALUE_TYPE>::rbdelete_fixup(RBTREE_NODE_PTR cur_ptr)
{
    while (cur_ptr != root_ptr && cur_ptr->color == BLACK)
    {
        if (cur_ptr == PARENT_PTR(cur_ptr)->left_ptr) {
            auto brother = PARENT_PTR(cur_ptr)->right_ptr;
            if (brother->color == RED) {
                brother->color = BLACK;
                PARENT_PTR(cur_ptr)->color = RED;
                rotateL(PARENT_PTR(cur_ptr));
            } else {
                if (brother->left_ptr->color == BLACK && brother->right_ptr->color == BLACK)
                {
                    brother->color = RED;
                    cur_ptr = PARENT_PTR(cur_ptr);
                } else if (brother->right_ptr->color == BLACK) {
                    brother->left_ptr->color = BLACK;
                    brother->color = RED;
                    rotateR(brother);
                } else if (brother->right_ptr->color == RED) {
                    brother->color = PARENT_PTR(cur_ptr)->color;
                    PARENT_PTR(cur_ptr)->color = BLACK;
                    brother->right_ptr->color = BLACK;
                    rotateL(PARENT_PTR(cur_ptr));
                    cur_ptr = root_ptr;
                }
            }
        } else {
            auto brother = PARENT_PTR(cur_ptr)->left_ptr;
            if (brother->color == RED)
            {
                brother->color = BLACK;
                PARENT_PTR(cur_ptr)->color = RED;
                rotateR(PARENT_PTR(cur_ptr));
            } else {
                if (brother->left_ptr->color == BLACK & brother->right_ptr->color == BLACK)
                {
                    brother->color = RED;
                    cur_ptr = PARENT_PTR(cur_ptr);
                } else if (brother->left_ptr->color == BLACK){ 
                    brother->color = RED;
                    brother->right_ptr->color = BLACK;
                    rotateL(brother);
                } else if (brother->left_ptr->color == RED) {
                    brother->color = PARENT_PTR(cur_ptr)->color;
                    PARENT_PTR(cur_ptr)->color = BLACK;
                    brother->left_ptr->color = BLACK;
                    rotateR(PARENT_PTR(cur_ptr));
                    cur_ptr = root_ptr;
                }
            }
        }
    }
    nil->parent_ptr = root_ptr;
    cur_ptr->color = BLACK;
}

template<class KEY_TYPE, class VALUE_TYPE>
void rbtree<KEY_TYPE, VALUE_TYPE>::inorder(RBTREE_NODE_PTR node, std::vector<KEY_TYPE> *ans)
{
    if (node == nil) return;
    inorder(node->left_ptr, ans);
    ans->push_back(node->key);
    inorder(node->right_ptr, ans);
}

template<class KEY_TYPE, class VALUE_TYPE>
bool rbtree<KEY_TYPE, VALUE_TYPE>::check_valid()
{
    if (root_ptr == nil) return true;
    int height = 0;
    return check_valid(root_ptr, &height);
}

#include <iostream>
using namespace std;

template<class KEY_TYPE, class VALUE_TYPE>
bool rbtree<KEY_TYPE, VALUE_TYPE>::check_valid(RBTREE_NODE_PTR cur_ptr, int *height)
{
    *height = 0;
    if (cur_ptr == nil) return true;
    int left = 0, right = 0;
    if (!check_valid(cur_ptr->left_ptr, &left)) return false;
    if (!check_valid(cur_ptr->right_ptr, &right)) return false;
    if (left != right) {
        cout << left << " " << right << endl;
        return false;
    }
    auto parent_ptr = PARENT_PTR(cur_ptr);
    if (parent_ptr != nil && parent_ptr->color == cur_ptr->color && cur_ptr->color == RED)
        return false;
    //if (PARENT_PTR(cur_ptr) != nil && (PARENT_PTR)->


    *height = left + (cur_ptr->color == BLACK?1:0);
    return true;
}

#endif
