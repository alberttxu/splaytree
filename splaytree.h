#include <stdbool.h>
#include <stdlib.h>

#ifndef SPLAYTREE_H
#define SPLAYTREE_H
struct Node {
    struct Node* parent;
    struct Node* lchild;
    struct Node* rchild;
    int data;
};

struct SplayTree {
    struct Node* root;
    // root is the right child of the sentinal node
    struct Node* sentinal;
};
#endif

struct Node* newNode(int x);
struct SplayTree newTree();
bool isLeftChild(struct Node* n);
bool isRightChild(struct Node* n);
int insert(struct SplayTree* t, int x);
struct Node* search(struct SplayTree* t, int x);
struct Node* successor(struct Node* n);
int delete (struct SplayTree* t, int x);
static void _print_inorder(struct Node* n);
void print_inorder(struct SplayTree* t);
void free_postorder(struct Node* n);
void free_treenodes(struct SplayTree* t);
void rotateright(struct SplayTree* t, struct Node* n);
void rotateleft(struct SplayTree* t, struct Node* n);
void splay(struct SplayTree* t, struct Node* n);
void splayup(struct SplayTree* t, struct Node* n);
