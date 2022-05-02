#include <assert.h>
#include <stdio.h>

#include "splaytree.h"
#include "debug_macros.h"

void test1()
{
    puts("\ntest1");
    struct Node root;
    struct Node a;
    struct Node b;
    root.parent = NULL;
    root.lchild = &a;
    root.rchild = &b;
    a.parent = &root;
    a.lchild = NULL;
    a.rchild = NULL;
    b.parent = &root;
    b.lchild = NULL;
    b.rchild = NULL;
}

void test2() // deprecated
{
    puts("\ntest2");
    struct Node root;
    root.data = 0;
    root.parent = NULL;
    root.lchild = NULL;
    root.rchild = NULL;
    struct SplayTree t;
    t.root = &root;
    insert(&t, 1);
    showptr(t.root->lchild);
    showint(t.root->rchild->data);
    assert(t.root->rchild->data == 1);
    free_treenodes(&t);
}

void test3()
{
    puts("\ntest3");
    struct SplayTree t = newTree();
    insert(&t, 5);
    insert(&t, 6);
    showint(t.root->data);
    showint(t.root->rchild->data);
    showptr(t.root->lchild);
    assert(t.root->rchild->data == 6);
    free_treenodes(&t);
}

void test4()
{
    puts("\ntest4");
    struct SplayTree t = newTree();
    for (int i = 0; i < 10; i++)
        insert(&t, i);
    print_inorder(&t);
    free_treenodes(&t);
}

void test5()
{
    puts("\ntest5");
    struct SplayTree t = newTree();
    insert(&t, 1);
    insert(&t, 6);
    insert(&t, 2);
    insert(&t, 5);
    insert(&t, 3);
    struct Node* n = successor(t.root);
    showint(t.root->data);
    showint(n->data);
    assert(n->data == 2);
    struct Node* n2 = successor(n);
    showint(n2->data);
    assert(n2->data == 3);
    free_treenodes(&t);
}

void test6()
{
    puts("\ntest6");
    struct SplayTree t = newTree();
    insert(&t, 1);
    insert(&t, 0);
    insert(&t, 9);
    insert(&t, 2);
    insert(&t, 5);
    insert(&t, 3);
    assert(delete (&t, 7) == -1);

    struct Node* n = search(&t, 5);
    showint(n->data);
    showint(n->lchild->data);

    puts("deleting 3");
    delete (&t, 3);
    showptr(n->lchild);
    assert(n->lchild == NULL);

    puts("deleting 2");
    delete (&t, 2);
    showint(n->parent->data);
    assert(n->parent->data == 9);

    puts("deleting 1");
    showint(t.root->data);
    delete (&t, 1);
    showint(t.root->data);
    n = search(&t, 9);
    showint(n->data);
    showptr(n->lchild);
    free_treenodes(&t);
}

void test7()
{
    puts("\ntest7");
    struct SplayTree t = newTree();
    insert(&t, 1);
    insert(&t, 0);
    insert(&t, 5);
    insert(&t, 2);
    insert(&t, 4);
    insert(&t, 3);

    for (int i = 0; i < 6; i++) {
        printf("deleting %d\n", i);
        assert(delete (&t, i) == 0);
    }
    free_treenodes(&t);
}

void test8()
{
    puts("\ntest8");
    struct SplayTree t = newTree();
    insert(&t, 5);
    delete (&t, 5);
    assert(t.root == NULL);
    free_treenodes(&t);
}

void test9() {
    puts("\ntest9");
    struct SplayTree t = newTree();
    insert(&t, 2);
    insert(&t, 1);
    insert(&t, 3);
    free_treenodes(&t);
}

int main()
{
    test1();
    //test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();

    return 0;
}
