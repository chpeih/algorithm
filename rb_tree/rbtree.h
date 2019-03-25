#ifndef __RBTREE_H__
#define __RBTREE_H__

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
    RBTREE_NODE_PTR get_root() { return root_ptr; }
    void remove(const KEY_TYPE &key);
    RBTREE_NODE_PTR find(const KEY_TYPE &key);

private:

//    inline RBTREE_NODE_PTR PARENT_PTR(RBTREE_NODE_PTR p) { return p->parent_ptr; }
//    inline RBTREE_NODE_PTR GRANDPARENT_PTR(RBTREE_NODE_PTR p) { return PARENT_PTR(p)->parent_ptr; }
    void clear(RBTREE_NODE_PTR node_ptr);
    RBTREE_NODE_PTR new_node(const KEY_TYPE &key, const VALUE_TYPE &value);
    void rbinsert_fixup(RBTREE_NODE_PTR cur_ptr);
    void rotateL(RBTREE_NODE_PTR cur_ptr);
    void rotateR(RBTREE_NODE_PTR cur_ptr);

    
    RBTREE_NODE_PTR root_ptr;
    RBTREE_NODE_PTR nil;
    size_t node_size;

};

template<class KEY_TYPE, class VALUE_TYPE>
rbtree<KEY_TYPE, VALUE_TYPE>::rbtree()
{
    nil = new_node(KEY_TYPE(), VALUE_TYPE());
    root_ptr = nil;
    nil->left_ptr = root_ptr;
    nil->right_ptr = root_ptr;
    nil->parent_ptr = root_ptr;
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
        nil->left_ptr = nil;
        nil->right_ptr = root_ptr;
        nil->parent_ptr = root_ptr;
    } else {
        if (key < insert_ptr->key)
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
    auto subR = cur_ptr->right_ptr;
    auto subRL = subR->left_ptr;
    cur_ptr->right_ptr = subRL;
    if (subRL)
        PARENT_PTR(subRL) = cur_ptr;

    if (PARENT_PTR(cur_ptr) == nullptr) {
        root_ptr = subR;
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
    auto subL = cur_ptr->left_ptr;
    auto subLR = subL->right_ptr;
    cur_ptr->left_ptr = subLR;
    if (subLR)
        PARENT_PTR(subLR) = cur_ptr;
    if (PARENT_PTR(cur_ptr) == nullptr) {
        root_ptr = subL;
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
void remove(const KEY_TYPE &key)
{
    RBTREE_NODE_PTR key_ptr = find(key);
    if (key_ptr == nullptr) return;
    Color key_color = key_ptr->color;
    RBTREE_NODE_PTR child = nullptr;
    

//    if (key_ptr->left_ptr &&  key_ptr->right_ptr)
//    {
//        y = key_ptr;
//    } else if
        


}


#endif
