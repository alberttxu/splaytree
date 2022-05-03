#include <assert.h>
#include <stdio.h>

#include "debug_macros.h"
#include "splaytree.h"

void test1()
{
    puts("\n======== test 1 ========");
    struct SplayTree t = newTree();
    insert(&t, 2);
    insert(&t, 1);
    struct Node* n = search(&t, 1);
    showint(n->data);
    showint(t.root->data);
    puts("rotate right");
    rotateright(&t, n);
    showint(t.root->data);
    assert(t.root == n);
}

void test2()
{
    puts("\n======== test 2 ========");
    struct SplayTree t = newTree();
    insert(&t, 1);
    insert(&t, 2);
    struct Node* n = search(&t, 2);
    showint(n->data);
    showint(t.root->data);
    puts("rotate left");
    rotateleft(&t, n);
    showint(t.root->data);
    assert(t.root == n);
}

void test3()
{
    puts("\n======== test 3 ========");
    struct SplayTree t = newTree();
    insert(&t, 1);
    insert(&t, 2);
    insert(&t, 3);
    insert(&t, 4);
    insert(&t, 5);
    struct Node* n = search(&t, 5);
    splayup(&t, n);
    showint(t.root->data);
    showint(t.root->lchild->data);
    showint(t.root->lchild->lchild->data);
    showint(t.root->lchild->rchild->data);
    showint(t.root->lchild->rchild->lchild->data);
    assert(t.root == n);
    assert(t.root->lchild->data == 2);
    assert(t.root->lchild->lchild->data == 1);
    assert(t.root->lchild->rchild->data == 4);
    assert(t.root->lchild->rchild->lchild->data == 3);
}

int main()
{
    test1();
    test2();
    test3();
    return 0;
}
