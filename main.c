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

int main()
{
    test1();
    test2();
    return 0;
}
