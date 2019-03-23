#ifndef __RBTREE_H__
#define __RBTREE_H__

#define RBTREE_NODE_PTR rbtree_node<KEY_TYPE, VALUE_TYPE>
#define RBTREE_NODE rbtree_node<KEY_TYPE, VALUE_TYPE>

#define PARENT_PTR(p) ((p)->parent_ptr)
#define GRANDPARENT_PTR(p) ((p)->parent_ptr->parent_ptr)

enum Color { RED, BLACK };

template<class KEY_TYPE, class VALUE_TYPE>
struct rbtree_node {
    KEY_TYPE key;
    VALUE_TYPE value;
    rbtree_node* parent_ptr;
    rbtree_node* left_ptr;
    rbtree_node* right_ptr;
    Color color;

    rbtree_node(const KEY_TYPE &_key = KEY_TYPE(), const VALUE_TYPE &_value = VALUE_TYPE()): key(_key), value(_value), parent_ptr(nullptr), left_ptr(nullptr), right_ptr(nullptr), color(RED) {}
};

template<class KEY_TYPE, class VALUE_TYPE>
class rbtree {
public:
    rbtree(): root_ptr(nullptr), node_size(0) {}
    ~rbtree();
    clear();
    void insert(const KEY_TYPE &key, const VALUE_TYPE &value);

private:
    
    void clear(RBTREE_NODE_PTR node_ptr);
    void new_node(const KEY_TYPE &key, const VALUE_TYPE &value);
    void rbinsert_fixup(RBTREE_NODE_PTR cur_ptr);
    
    RBTREE_NODE_PTR *root_ptr;
    size_t node_size;

};

template<class KEY_TYPE, class VALUE_TYPE>
rbtree<KEY_TYPE, VALUE_TYPE>::~rbtree()
{
    clear(root_ptr);
}

template<class KEY_TYPE, class VALUE_TYPE>
void rbtree<KEY_TYPE, VALUE_TYPE>::clear()
{
    clear(root_ptr);
}

template<class KEY_TYPE, class VALUE_TYPE>
void rbtree<KEY_TYPE, VALUE_TYPE>::clear(RBTREE_NODE_PTR node_ptr)
{
    if (node_ptr == nullptr) return;
    clear(node_ptr->left_ptr);
    clear(node_ptr->right_ptr);
    delete node_ptr;
}

template<class KEY_TYPE, class VALUE_TYPE>
void rbtree<KEY_TYPE, VALUE_TYPE>::insert(const KEY_TYPE &key, const VALUE_TYPE &value)
{
    RBTREE_NODE_PTR cur_ptr = root_ptr, parent_ptr = nullptr;
    while (cur_ptr != nullptr )
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
    cur_ptr = new_node(key, value);
    if (root_ptr == nullptr)
    {
        root_ptr = cur_ptr;
        cur_ptr->color = BLACK;
        return;
    }
    if (parent_ptr->key > key)
        parent_ptr->left_ptr = cur_ptr;
    else 
        parent_ptr->right_ptr = cur_ptr;

    PARENT_PTR(cur_ptr) = parent_ptr;
    rbinsert_fixup(cur_ptr);
}

template<class KEY_TYPE, class VALUE_TYPE>
void rbtree<KEY_TYPE, VALUE_TYPE>::rbinsert_fixup(RBTREE_NODE_PTR cur_ptr)
{
    while (PARENT_PTR(cur_ptr)->color == RED)
    {
        if (PARENT_PTR(cur_ptr) == GRANDPARENT_PTR(cur_ptr)->left_ptr) {
            auto uncle_ptr = GRANDPARENT_PTR(cur_ptr)->right_ptr;   
            if (uncle_ptr->color == RED)
            {
                PARENT_PTR(cur_ptr)->color = BLACK;
                uncle_ptr->color = BLACK;
                GRANDPARENT_PTR(cur_ptr)->color = RED;
            } else if (cur_ptr == PARENT_PTR(cur_ptr)->left);
            

        
        } else {
        }


    }

}

template<class KEY_TYPE, class VALUE_TYPE>
void rbtree<KEY_TYPE, VALUE_TYPE>::new_node(const KEY_TYPE &key, const VALUE_TYPE &value)
{
    auto node = new RBTREE_NODE(key, value);
    ++node_size;
    return node;
}

#endif
