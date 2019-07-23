//
// Created by wuyusong on 2019/7/19.
//

// reference: Database System Concepts (6th edition, by Abraham Silberschatz, Henry F. Korth, and S. Sudarshan)

#ifndef BPLUSTREE_H
#define BPLUSTREE_H


// Basic Property of B+ Tree:
// 1) each non-leaf node (also called internal node) has between ceil(n/2) and n children
// 2) for the root, it can contain fewer than ceil(n/2) children, however, it must hold at least 2 children, unless the tree contains only 1 node
// 3) each leaf node has a pointer to next leaf node, and the search key is in ascending order


#include <vector>
#include <string>
using namespace std;

enum NodeType { T_ROOT, T_INTERNAL, T_LEAF, T_DONTCARE };

class TreeNode {
private:
    int _n;  // tree's order
    NodeType _type;  // 4 types, see above, use T_DONTCARE when we do not care the type
    vector<string> _keys;  // search keys, maximum size is n-1
    vector<void*> _ptrs;  // n pointers
    TreeNode* _next;  // link to next leaf if it's a leaf, set to NULL otherwise

public:
    friend class BPlusTree;  // make private members accessible

    TreeNode(int n, NodeType t) {
        _n = n;
        _type = t;
        _keys.resize(_n - 1);  // at most n-1 keys
        _ptrs.resize(_n);  // at most n pointers
        for (int i = 0; i < _n-1; i++) {
            _keys[i] = "";
        }
        for (int i  = 0; i < _n; i++) {
            _ptrs[i] = NULL;
        }
        _next = NULL;
    }

    TreeNode(int n, NodeType t, vector<string> keys, vector<void*> ptrs) {
        _n = n;
        _type = t;
        for (auto key : keys) {
            _keys.emplace_back(key);
        }
        for (auto ptr: ptrs) {
            _ptrs.emplace_back(ptr);
        }
    }
};


class BPlusTree {
private:
    int _n;  // tree's order
    TreeNode* _root;  // tree root

    // private helper functions
    int _num_of_keys(TreeNode *p);  // number of keys, exclude empty string

    int _num_of_ptrs(TreeNode *p);  // number of pointers, exclude NULL

    void _insert_in_leaf(TreeNode *n, string k, void *p);  // the book's insert_in_leaf procedure

    void _insert_in_parent(TreeNode *n, string k, TreeNode *nprime);  // the book's insert_in_parent procedure

    TreeNode* _parent(TreeNode *p);  // get a node's parent

    void _delete_entry();  // the book's delete_entry procedure

public:
    BPlusTree(int n) {
        _n = n;
        _root = NULL;  // root initially set to NULL
    }

    pair<TreeNode*, int> find(string v);  // returns a pair, first member is the pointer to the node, second member is the position

    void printAll(string v);  // print all records with search key >= value v, a liitle different from the book

    void printTree();  // print each node in the tree

    bool do_insertion(string k, void *p);

    bool do_deletion();
};


#endif //BPLUSTREE_H
