//
// Created by wuyusong on 2019/7/19.
//

#include "BPlusTree.h"

#include <cmath>

#include <iostream>
#include <algorithm>
#include <queue>


int BPlusTree::_num_of_keys(TreeNode *p) {
    //
    // real number of keys
    //
    int cnt = 0;
    auto keys = p->_keys;
    for (auto key : keys) {
        if (key != "") {
            cnt++;
        }
    }
    return cnt;
}


int BPlusTree::_num_of_ptrs(TreeNode *p) {
    //
    // real number of pointers
    //
    int cnt = 0;
    auto ptrs = p->_ptrs;
    for (auto ptr : ptrs) {
        if (ptr != NULL) {
            cnt++;
        }
    }
    return cnt;
}


pair<TreeNode*, int> BPlusTree::find(string v) {
    //
    // returns leaf node pointer c and index i such that c->_ptrs[i] points to the first record with search key v
    //
    auto c = this->_root;

    while (c->_type != T_LEAF) {
        int i = INT_MAX;
        // let i be the smallest number such that v <= keys[i]
        for (int j = 0; j < _num_of_keys(c); j++) {
            if (c->_keys[j] >= v) {
                i = j;
                break;
            }
        }
        if (i == INT_MAX) {  // no such i
            // let pm be the last non-null pointer in the node
            TreeNode* pm = NULL;
            for (int k = c->_ptrs.size() - 1; k >=0 ; k--) {
                if (c->_ptrs[k] != NULL) {
                    pm = reinterpret_cast<TreeNode*>(c->_ptrs[k]);
                    break;
                }
            }
            // set c = c.pm
            c = pm;
        } else if (v == c->_keys[i]) {
            c = reinterpret_cast<TreeNode*>(c->_ptrs[i+1]);
        } else{  // v is less than keys[i]
            c  = reinterpret_cast<TreeNode*>(c->_ptrs[i]);
        }
    }
    // c is a leaf node
    int i = INT_MIN;
    // let i be the least value such that keys[i] = v
    for (int j = 0; j < _num_of_keys(c); j++) {
        if (c->_keys[j] == v) {
            i = j;
            break;
        }
    }
    if (i != INT_MIN ) {  // such i exists
        return make_pair(c, i);
    }
    return make_pair(c, -1);  // use -1 to indicate such key value v doesn't exist
}


void BPlusTree::printAll(string v) {
    //
    // B+ tree described in the book may contain duplicate keys
    // printAl prints all the records with key v
    // but here I modified it to print all records with key >= v
    //
    bool done = false;
    auto pair = find(v);
    auto p = pair.first;
    auto i = pair.second;
    if (i == -1) {  // not found
        cout << "no such record" << endl;
        return;
    }
    cout << "i is " << i << endl;
    while (!done and p != NULL) {
         // be careful with special cases, may encounter NULL pointer, size is also a problem (#pointer = #key + 1)
        for (; (i < p->_ptrs.size() && i < p->_keys.size() && v <= p->_keys[i]) or (i == p->_keys.size()); i++) {
            if (p->_ptrs[i] == NULL) {
                continue;
            }
            cout << "record: " << *reinterpret_cast<int*>(p->_ptrs[i]) << endl;
        }
        if (i >= _num_of_keys(p)) {
            p = p->_next;  // move to next leaf node
            i = 0;  // adjust i
        }
        else {
            done = true;
        }
    }
}


void BPlusTree::printTree() {
    //
    // print the whole tree
    //
    queue<TreeNode*> q;
    q.push(_root);
    while(!q.empty()) {
        auto cur = q.front();
        q.pop();
        cout << "node type: " << cur->_type << endl;
        for(int i = 0; i < cur->_keys.size(); i++) {
            cout << "key " << i << " :" << cur->_keys[i] << endl;
        }
        if (cur->_type == T_LEAF) {
            for(int j = 0; j < cur->_ptrs.size(); j++) {
                if (cur->_ptrs[j] == NULL) continue;
                cout << "content " << j << " :" << *(int*)cur->_ptrs[j] << endl;
            }
        }
        if(cur->_type != T_LEAF) {
            for (int k = 0; k < _num_of_ptrs(cur); k++) {
                q.push(reinterpret_cast<TreeNode*>(cur->_ptrs[k]));
            }
        }
        cout << "------" << endl;
    }
}


TreeNode* BPlusTree::_parent(TreeNode *p) {
    //
    // find the parent of node *p
    // using level order traversal
    //
    queue<TreeNode*> q;
    q.push(_root);
    while (!q.empty()) {
        auto cur = q.front();
        if (cur->_type == T_LEAF) break;
        q.pop();
        for (auto t : cur->_ptrs) {
            if (t == p) {
                return reinterpret_cast<TreeNode*>(cur);
            }
        }
        for (auto t : cur->_ptrs) {
            if (t != NULL) {
                q.push(reinterpret_cast<TreeNode*>(t));
            }
        }
    }
    return NULL;
}


void BPlusTree::_insert_in_leaf(TreeNode *n, string k, void *p) {
    //
    // insert in leaf
    //
    if (k < n->_keys[0]) {
        // insert p, k into node just before the first element
        n->_keys.insert(n->_keys.begin(), k);
        n->_ptrs.insert(n->_ptrs.begin(), p);
    }
    else{
        // find the highest key that is less than k
        int j = _num_of_keys(n) - 1;
        for (; j >= 0; j--) {
            if (n->_keys[j] < k) break;
        }
        n->_keys.insert(n->_keys.begin()+j+1, k);  // insert behind
        n->_ptrs.insert(n->_ptrs.begin()+j+1, p);
    }
    // insertion makes the size 1 bigger, should pop_back, this is dirty, any more elegant way???
    n->_keys.pop_back();
    n->_ptrs.pop_back();
}


void BPlusTree::_insert_in_parent(TreeNode *n, string k, TreeNode *nprime) {
    //
    // insert in parent
    //
    if (n->_type == T_ROOT) {  // if node is root
        // create a new node r containing n. k, nprime
        auto r = new TreeNode(_n, T_ROOT);
        r->_keys[0] = k;
        r->_ptrs[0] = n;
        r->_ptrs[1] = nprime;
        // and make it the new root
        _root = r;
        // adjust n's type, possible choices: leaf or internal, should be the same with nprime
        n->_type = nprime->_type;
        return;
    }
    // let p be parent(n)
    // if p has less than n pointers
    auto p = _parent(n);
    if(_num_of_ptrs(p) < _n) {
        // insert kprime nprime in p just after n ???
        // the textbook's description is misleading, correct: find the position of the pointer to n, insert after this posiiton
        int i = 0;
        for(; i< p->_ptrs.size(); i++) {
            if (p->_ptrs[i] == n) break;
        }
        p->_keys.insert(p->_keys.begin() + i, k);
        p->_ptrs.insert(p->_ptrs.begin() + i + 1, nprime);

        // insertion makes the size 1 bigger, should pop_back, this is dirty, any more elegant way???
        p->_keys.pop_back();
        p->_ptrs.pop_back();
    }
    else{  // split p
        // copy p to a block of memory t that can hold p and kprime nprime
        auto t = new TreeNode(_n+1, T_DONTCARE);
        for (int i = 0; i < p->_ptrs.size(); i++) {
            t->_ptrs[i] = p->_ptrs[i];
        }
        for (int j = 0; j < p->_keys.size(); j++) {
            t->_keys[j] = p->_keys[j];
        }

        // insert kprime nprime into t just after n
        for (int i = 0; i < t->_ptrs.size(); i++) {
            if (t->_ptrs[i] == n) {
                t->_keys.insert(t->_keys.begin() + i, k);
                t->_ptrs.insert(t->_ptrs.begin() + i + 1, nprime);
                // insertion makes the size 1 bigger, should pop_back, this is dirty, any more elegant way???
                t->_keys.pop_back();
                t->_ptrs.pop_back();
                break;
            }
        }

        // erase all entries from p
        for (int i = 0; i < p->_ptrs.size(); i++) {
            p->_ptrs[i] = NULL;
        }
        for (int j = 0; j < p->_keys.size(); j++) {
            p->_keys[j] = "";
        }

        // create pprime
        auto pprime = new TreeNode(_n, T_INTERNAL);  // it will never be a leaf

        // copy first half to p
        for (int i = 0; i < (int)ceil(_n/2); i++) {
            p->_keys[i] = t->_keys[i];
        }
        for (int ii = 0; ii <= (int)ceil(_n/2); ii++) {
            p->_ptrs[ii] = t->_ptrs[ii];
        }

        // let kprimeprime = key[ceil(n/2)]
        auto kprimeprime = t->_keys[ceil(_n/2)];

        // copy another half to pprime
        int j = 0;
        for (int jj = (int)ceil(_n/2) + 1; jj < _n; jj++ ) {
            pprime->_keys[j] = t->_keys[jj];
            j += 1;
        }
        j = 0;
        for (int jj = (int)ceil(_n/2) + 1; jj <= _n; jj++ ) {
            pprime->_ptrs[j] = t->_ptrs[jj];
            j += 1;
        }

        // recursively call insert to parent
        _insert_in_parent(p, kprimeprime, pprime);
    }
}


bool BPlusTree::do_insertion(string k, void *p) {
    //
    // insertion
    //
    TreeNode* leaf = NULL;
    if (_root == NULL) {  // tree is empty
        _root = new TreeNode(_n, T_LEAF);  // new a root node
        leaf = _root;
    }
    else {
        // find the leaf node that should contain k

        leaf = _root;
        while (leaf ->_type != T_LEAF) {
            if (leaf->_keys[_num_of_keys(leaf) - 1] < k) {  // k is the largest
                leaf = reinterpret_cast<TreeNode*>(leaf->_ptrs[_num_of_ptrs(leaf) - 1]);
            }
            else{
                for (int i = 0; i < leaf->_keys.size(); i++) {
                    if (leaf->_keys[i] > k) {
                        leaf = reinterpret_cast<TreeNode*>(leaf->_ptrs[i]);
                    }
                }
            }
        }
    }
    // if leaf has less than n-1 key values
    if (_num_of_keys(leaf) < _n - 1) {
        _insert_in_leaf(leaf, k, p);
    }
    else{  // leaf has n-1 keys already, split it
        // attention!!!
        // 一开始插入的时候root被标记成了leaf，要在这里改过来
        if(_parent(leaf) == NULL) {
            leaf->_type = T_ROOT;
        }

        auto lprime = new TreeNode(_n, T_LEAF);  // create a node* l', mark it as leaf, MAY CAUSE POTENTIAL BUG BECAUSE LPRIME MAY BE INSERTED TO A LEAF'S PARENT

        // copy leaf's content to a block of memory t
        auto t = new TreeNode(_n + 1, T_DONTCARE, leaf->_keys, leaf->_ptrs);  // a bigger node
        _insert_in_leaf(t, k, p);

        // adjust linked list
        lprime->_next = leaf->_next;
        leaf->_next = lprime;

        // erase leaf
        for (int i = 0; i < _n; i++) {
            leaf->_ptrs[i] = NULL;
        }
        for (int i = 0; i < _n - 1; i++) {
            leaf->_keys[i] = "";
        }

        // split and copy
        for (int i = 0; i < (int)ceil(_n/2); i++) {
            // p0 k0 p1 k1 p2 k2 p3 -> p0 k0 p1 k1, p2 k2 p3
            // copy first half to leaf, second half to lprime
            leaf->_keys[i] = t->_keys[i];
            leaf->_ptrs[i] = t->_ptrs[i];
        }
        int j = 0;
        for (int jj = (int)ceil(_n/2); jj < _n; jj++ ) {
            lprime->_keys[j] = t->_keys[jj];
            j += 1;
        }
        j = 0;
        for (int jj = (int)ceil(_n/2); jj <= _n; jj++) {  // notice #pointer is 1 bigger!!!!!!
            lprime->_ptrs[j] = t->_ptrs[jj];
            j += 1;
        }

        // let kprime be the smallest key in lprime
        auto kprime = lprime->_keys[0];
        _insert_in_parent(leaf, kprime, lprime);
    }
}
