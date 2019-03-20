#ifndef __AVLTREE_NODE_H__
#define __AVLTREE_NODE_H__ 
template<class KEY_TYPE, class VALUE_TYPE>
class avltree_node {
public:
    KEY_TYPE key;
    VALUE_TYPE value;
    int balance;
    avltree_node<KEY_TYPE, VALUE_TYPE>* parent;
    avltree_node<KEY_TYPE, VALUE_TYPE>* left;
    avltree_node<KEY_TYPE, VALUE_TYPE>* right;

    avltree_node(const KEY_TYPE &_key = KEY_TYPE(), const VALUE_TYPE &_value = VALUE_TYPE()): key(_key), value(_value), balance(0), parent(nullptr), left(nullptr), right(nullptr) {} 
};
#endif
