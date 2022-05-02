#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "splaytree.h"
#include "debug_macros.h"

struct Node* newNode(int x)
{
    struct Node* n = malloc(sizeof(struct Node));
    n->parent = NULL;
    n->lchild = NULL;
    n->rchild = NULL;
    n->data = x;
    return n;
}

struct SplayTree newTree()
{
    struct SplayTree t;
    t.root = NULL;
    t.sentinal = newNode(-1);
    return t;
}

bool isLeftChild(struct Node* n)
{
    if (n->parent == NULL)
        return false;
    return n->parent->lchild == n;
}

bool isRightChild(struct Node* n)
{
    if (n->parent == NULL)
        return false;
    return n->parent->rchild == n;
}

// elements are assumed to be unique
int insert(struct SplayTree* t, int x)
{
    if (t->root == NULL) {
        t->root = newNode(x);
        t->root->parent = t->sentinal;
        t->sentinal->rchild = t->root;
        return 0;
    }
    struct Node* n = t->root;
    struct Node* prev_n = NULL;
    while (n != NULL) {
        prev_n = n;
        if (x == n->data)
            return -1;
        if (x < n->data) {
            n = n->lchild;
        } else {
            n = n->rchild;
        }
    }
    n = newNode(x);
    n->parent = prev_n;
    if (x < prev_n->data) {
        prev_n->lchild = n;
    } else {
        prev_n->rchild = n;
    }
    return 0;
}

struct Node* search(struct SplayTree* t, int x)
{
    struct Node* n = t->root;
    while (n != NULL) {
        if (x == n->data) {
            return n;
        } else if (x < n->data) {
            n = n->lchild;
        } else {
            n = n->rchild;
        }
    }
    return NULL;
}

struct Node* successor(struct Node* n)
{
    if (n->rchild == NULL)
        return NULL;
    n = n->rchild;
    while (n->lchild != NULL)
        n = n->lchild;
    return n;
}

int redirectParent(struct Node* n, struct Node* newChild)
{
    if (isLeftChild(n)) {
        n->parent->lchild = newChild;
    } else if (isRightChild(n)) {
        n->parent->rchild = newChild;
    } else {
        return -1;
    }
    return 0;
}

int delete (struct SplayTree* t, int x)
{
    struct Node* n = search(t, x);
    if (n == NULL)
        return -1;

    if (n->lchild && n->rchild) {
        struct Node* succ = successor(n);
        n->data = succ->data;
        if (succ->rchild != NULL) {
            succ->rchild->parent = succ->parent;
            assert(redirectParent(succ, succ->rchild) == 0);
        } else {
            assert(redirectParent(succ, succ->lchild) == 0);
        }
        free(succ);
        succ = NULL;
    } else {
        struct Node* child;
        if (n->lchild == NULL && n->rchild == NULL) {
            child = NULL;
        } else if (n->rchild == NULL) {
            child = n->lchild;
            child->parent = n->parent;
        } else if (n->lchild == NULL) {
            child = n->rchild;
            child->parent = n->parent;
        } else {
            assert(0);
        }
        assert(redirectParent(n, child) == 0);
        t->root = t->sentinal->rchild;
        free(n);
        n = NULL;
    }
    return 0;
}

static void _print_inorder(struct Node* n)
{
    if (n == NULL)
        return;
    _print_inorder(n->lchild);
    printf("%d ", n->data);
    _print_inorder(n->rchild);
}

void print_inorder(struct SplayTree* t)
{
    _print_inorder(t->root);
    printf("\n");
}

void free_postorder(struct Node* n) {
    if (n == NULL) {
        return;
    }
    free_postorder(n->lchild);
    free_postorder(n->rchild);
    free(n);
}

void free_treenodes(struct SplayTree* t) {
    free_postorder(t->sentinal);
}

