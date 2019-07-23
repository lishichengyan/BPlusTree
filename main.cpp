#include "BPlusTree.h"

#include <iostream>

int main() {
    int a[30] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30};  // just like a table in the database

    auto tree = new BPlusTree(4);
    tree->do_insertion("001", &a[0]);
    tree->do_insertion("002", &a[1]);
    tree->do_insertion("003", &a[2]);
    tree->do_insertion("004", &a[3]);
    tree->do_insertion("005", &a[4]);
    tree->do_insertion("006", &a[5]);
    tree->do_insertion("007", &a[6]);
    tree->do_insertion("008", &a[7]);
    tree->do_insertion("009", &a[8]);
    tree->do_insertion("010", &a[9]);
    tree->do_insertion("011", &a[10]);
    tree->do_insertion("012", &a[11]);
    tree->do_insertion("013", &a[12]);
    tree->do_insertion("014", &a[13]);
    tree->do_insertion("015", &a[14]);
    tree->do_insertion("016", &a[15]);
    tree->do_insertion("017", &a[16]);
    tree->do_insertion("018", &a[17]);
    tree->do_insertion("019", &a[18]);
    tree->do_insertion("020", &a[19]);
    tree->do_insertion("021", &a[20]);
    tree->do_insertion("022", &a[21]);
    tree->do_insertion("023", &a[22]);
    tree->do_insertion("024", &a[23]);
    tree->do_insertion("025", &a[24]);
    tree->do_insertion("026", &a[25]);
    tree->do_insertion("027", &a[26]);
    tree->do_insertion("028", &a[27]);
    tree->do_insertion("029", &a[28]);
    tree->do_insertion("030", &a[29]);
    tree->printTree();


//    tree->printAll("025");

//    auto n1 = new TreeNode(4, T_INTERNAL);
//    auto n2 = new TreeNode(4, T_INTERNAL);
//
//    auto n3 = new TreeNode(4, T_LEAF);
//    auto n4 = new TreeNode(4, T_LEAF);
//    auto n5 = new TreeNode(4, T_LEAF);
//    auto n6 = new TreeNode(4, T_LEAF);
//    auto n7 = new TreeNode(4, T_LEAF);

//    tree->_root = new TreeNode(4, T_ROOT);
//
//    tree->_root->_keys[0] = "Mozart";
//    tree->_root->_ptrs[0] = n1;
//    tree->_root->_ptrs[1] = n2;
//
//    n1->_keys[0] = "Einstein";
//    n1->_keys[1] = "Gold";
//
//    n2->_keys[0] = "Srinivasan";
//
//    n1->_ptrs[0] = n3;
//    n1->_ptrs[1] = n4;
//    n1->_ptrs[2] = n5;
//
//    n2->_ptrs[0] = n6;
//    n2->_ptrs[1] = n7;
//
//    n3->_keys[0] = "Brandt";
//    n3->_keys[1] = "Califieri";
//    n3->_keys[2] = "Crick";
//
//    n3->_next = n4;  // link to next leaf
//
//    n4->_keys[0] = "Einstein";
//    n4->_keys[1] = "El Said";
//
//    n4->_next = n5;
//
//    n5->_keys[0] = "Gold";
//    n5->_keys[1] = "Katz";
//    n5->_keys[2] = "Kim";
//
//    n5->_next = n6;
//
//    n6->_keys[0] = "Mozart";
//    n6->_keys[1] = "Singh";
//
//    n6->_next = n7;
//
//    n7->_keys[0] = "Srinivasan";
//    n7->_keys[1] = "Wu";
//
//    n3->_ptrs[0] = &a[0];
//    n3->_ptrs[1] = &a[1];
//    n3->_ptrs[3] = &a[2];
//
//    n4->_ptrs[0] = &a[3];
//    n4->_ptrs[1] = &a[4];
//
//    n5->_ptrs[0] = &a[5];
//    n5->_ptrs[1] = &a[6];
//    n5->_ptrs[2] = &a[7];
//
//    n6->_ptrs[0] = &a[8];
//    n6->_ptrs[1] = &a[9];
//
//    n7->_ptrs[0] = &a[10];
//    n7->_ptrs[1] = &a[11];
//
//    cout << "tree built successfully!" << endl;
//
//
//    int val = 11;
//    tree->do_insertion("Adam", &val);
//    tree->printTree();
//
//    cout << "============ANOTHER TEST BEGINS============" << endl;
//
//    int another_val = 12;
//    tree->do_insertion("Lamport", &another_val);
//    tree->printTree();


    return 0;
}