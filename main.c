#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debug_macros.h"
#include "splaytree.h"

#if eltype_num == int_type
void test1(void)
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

void test2(void)
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

void test3(void)
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
#endif

#if eltype_num == float_type
void test4(void)
{
    puts("\n======== test 4 ========");
    struct SplayTree t = newTree();
    int n = 10;
    float max_x = 1;
    for (int i = 0; i < n; i++) {
        float x = max_x * ((float)rand() / (float)(RAND_MAX));
        int err = insert(&t, x);
        assert(err == 0);
    }
    printf("in-order:\t");
    printtree(&t, INORDER);
    printf("pre-order:\t");
    printtree(&t, PREORDER);
    printf("post-order:\t");
    printtree(&t, POSTORDER);
}
#endif

#if eltype_num == int_type

#include "cycle.h"

int findinarray(int *arr, int size, int x) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == x)
            return i;
    }
    return -1;
}

int test5(void)
{
    puts("\n======== test 5 ========");
    FILE *fp = fopen("nums.txt", "r");
    if (fp == NULL) {
        perror("fopen");
        return 1;
    }
    int n = 10000;
    int *nums = malloc(n * sizeof(*nums));
    int size = 10;
    char line[size];
    for (int i = 0; i < n && fgets(line, size, fp); i++)
    {
        line[strcspn(line, "\n")] = 0;
        nums[i] = atoi(line);
    }

    struct SplayTree t = newTree();
    for (int i = 0; i < n; i++) {
        insert(&t, nums[i]);
    }

    ticks t0;
    ticks t1;
    t0 = getticks();
    for (int i = 0; i < n; i++) {
        search(&t, nums[i]);
    }
    t1 = getticks();
    double runtime_tree = elapsed(t1, t0);
    showfloat(runtime_tree);

    t0 = getticks();
    for (int i = 0; i < n; i++) {
        findinarray(nums, n, i);
    }
    t1 = getticks();
    double runtime_arr = elapsed(t1, t0);
    showfloat(runtime_arr);

    double speedup = runtime_arr / runtime_tree;
    showfloat(speedup);
    return 0;
}
#endif

int main(void)
{
#if eltype_num == int_type
    // test1();
    // test2();
    // test3();
#endif
#if eltype_num == float_type
    test4();
#endif
#if eltype_num == int_type
    int err = test5();
    if (err != 0)
        return err;
#endif
    return 0;
}
