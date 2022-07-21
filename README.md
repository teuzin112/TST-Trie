# TST-Trie
Simple project realized during the discipline Algorithms and Data Structures

This project implements all basic operations from a Ternary Search Tree.

If you want to learn more about how this type of binary tree works you can check a very good explanation from the website GeeksforGeeks [here](https://www.geeksforgeeks.org/ternary-search-tree/).

>A ternary search tree is a special trie data structure where the child nodes of a standard trie are ordered as a binary search tree. 

>Representation of ternary search trees: 
>Unlike trie(standard) data structure where each node contains 26 pointers for its children, each node in a ternary search tree contains only 3 pointers: 
>1. The left pointer points to the node whose value is less than the value in the current node. 
>2. The equal pointer points to the node whose value is equal to the value in the current node. 
>3. The right pointer points to the node whose value is greater than the value in the current node.
>Apart from above three pointers, each node has a field to indicate data(character in case of dictionary) and another field to mark end of a string.
