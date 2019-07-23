# BPlusTree
C++ implementation of B+ tree in the book **Database System Concepts** (6th edition, Abraham Silberschatz, Henyu F. Korth and S. Sudarshan)
## Introduction
The B+ tree is implemented in C++, following the pseudo-code in the book mentioned above. I've ~~carefully~~ tested it and it works fine so far.  
## Supported Operations
### Find  
Function ```find(string v)``` returns leaf node pointer ```c``` and index ```i``` such that ```c->_ptrs[i]``` points to the first record with search key ```v```. Due to B+ tree's balance property, this should run in ```O(tree height)``` time.
### Print  
Function ```printAll(string v)``` prints all records with search key ```v``` such that ```key >= v```.   
Function ```printTree()``` prints all detailed information about the tree node, for example, node type, keys, values(if it's a leaf), etc. 
### Insert  
Function ```do_insertion(string k, void *p)``` inserts pair ```(k, p)``` to the correct position. It's a complex procedure since the tree node may **split** if its room runs out, meanwhile we need to take care of the node type(T_ROOT, T_INTERNAL and T_LEAF, for example), the node's type may need to be adjusted during insertion.  
### Delete  
Currently unimplemented. Sorry!  
## Limitations  
1. Up to now the key only supports **string** type.  
2. Deletion not ready.  
3. Not robust enough. If you're reading Abraham Silberschatz's book and has the curiosity to convert the pseudo-code into a real program, this repository may be a good reading material, but if you want to use the source code in your project, then maybe you're in the wrong place. Before I well-test the code, I do not recommend you to use it for any serious developing. But believe it will be robust in near future.
## License  
All the source code is distributed under MIT license.
