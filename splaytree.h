#include <stdbool.h>
#include <stdlib.h>

#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#define eltype float
struct Node {
    struct Node* parent;
    struct Node* lchild;
    struct Node* rchild;
    eltype data;
};

struct SplayTree {
    struct Node* root;
    // root is the right child of the sentinal node
    struct Node* sentinal;
};

enum traversalorder {
    INORDER,
    PREORDER,
    POSTORDER
};
#endif

struct Node* newNode(eltype x);
struct SplayTree newTree(void);
bool isLeftChild(struct Node* n);
bool isRightChild(struct Node* n);
int insert(struct SplayTree* t, eltype x);
struct Node* search(struct SplayTree* t, eltype x);
struct Node* successor(struct Node* n);
int delete (struct SplayTree* t, eltype x);
void printtree(struct SplayTree* t, int order);
void free_postorder(struct Node* n);
void free_treenodes(struct SplayTree* t);
void rotateright(struct SplayTree* t, struct Node* n);
void rotateleft(struct SplayTree* t, struct Node* n);
void splay(struct SplayTree* t, struct Node* n);
void splayup(struct SplayTree* t, struct Node* n);
