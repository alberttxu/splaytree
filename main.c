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

int findinarray(int* arr, int size, int x)
{
    for (int i = 0; i < size; i++) {
        if (arr[i] == x)
            return i;
    }
    return -1;
}

// benchmark regular bst search vs array scan
int test5(void)
{
    puts("\n======== test 5 ========");
    FILE* fp = fopen("nums.txt", "r");
    if (fp == NULL) {
        perror("fopen");
        return -1;
    }
    int n = 5;
    int* nums = malloc(n * sizeof(*nums));
    int linelen = 10;
    char line[linelen];
    for (int i = 0; i < n && fgets(line, linelen, fp); i++) {
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

void test6(void)
{
    puts("\n======== test 6 ========");
    struct SplayTree t = newTree();
    struct Node* n1 = insert(&t, 1);
    struct Node* n2 = insert(&t, 2);
    rotateleft(&t, n2);
    assert(t.root == n2);
    assert(t.sentinal->rchild == n2);
    assert(n2->parent == t.sentinal);
    assert(n2->lchild == n1);
    assert(n2->rchild == NULL);
    assert(n1->parent == n2);
    assert(n1->lchild == NULL);
    assert(n1->rchild == NULL);
}

void test7(void)
{
    puts("\n======== test 7 ========");
    struct SplayTree t = newTree();
    struct Node* n1 = insert(&t, 1);
    struct Node* n2 = insert(&t, 2);
    struct Node* n3 = insert(&t, 3);
    rotateleft(&t, n3);
    assert(t.root == n1);
    assert(n1->parent == t.sentinal);
    assert(n1->lchild == NULL);
    assert(n1->rchild == n3);
    assert(n3->parent == n1);
    assert(n3->lchild == n2);
    assert(n3->rchild == NULL);
    assert(n2->parent == n3);
    assert(n2->lchild == NULL);
    assert(n2->rchild == NULL);
}

int* readnums(int n)
{

    FILE* fp = fopen("nums.txt", "r");
    if (fp == NULL) {
        perror("fopen");
        return NULL;
    }
    int* nums = malloc(n * sizeof(*nums));
    int linelen = 10;
    char line[linelen];
    for (int i = 0; i < n && fgets(line, linelen, fp); i++) {
        line[strcspn(line, "\n")] = 0;
        nums[i] = atoi(line);
    }
    return nums;
}

int test8(void)
{
    puts("\n======== test 8 ========");
    int n = 10000;
    int* nums = readnums(n);
    assert(nums != NULL);

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
    double runtime_nosplay = elapsed(t1, t0);
    showfloat(runtime_nosplay);

    t0 = getticks();
    for (int i = 0; i < n; i++) {
        // showint(i);
        // showint(nums[i]);
        assert(search_splayup(&t, nums[i]) == 0);
    }
    t1 = getticks();
    double runtime_splay = elapsed(t1, t0);
    showfloat(runtime_splay);

    double speedup = runtime_nosplay / runtime_splay;
    showfloat(speedup);
    return 0;
}

/** Bi-modal search distribution with m frequently accessed elements.
 *
 * We generate n unique numbers and partition them into 2 groups, A & B with n-m & m elements.
 * To generate a query:
 *     Flip a weighted coin with P(head) = 1-p, and P(tail) = p, 0 < p < 1.
 *     If heads, pick a random element of A. Otherwise, pick a random element of B.
 *
 * The 2 parameters we can adjust are m and p. Intuitively the runtime speedup of using
 * a splay tree vs BST should decrease in m and increase in p.
 *
 * We also compare the performance of using a BST with a simple array cache of size m.
 */
void benchmark(int *nums, int n, int n_queries, int m, float p, FILE* f)
{
    showint(m);
    showfloat(p);

    struct SplayTree t = newTree();
    for (int i = 0; i < n; i++) {
        insert(&t, nums[i]);
    }

    int queries[n_queries];
    int* A = nums;
    int* B = &nums[n - m];
    unsigned seed = 0;
    srand(seed);
    for (int i = 0; i < n_queries; i++) {
        int r = rand();
        float coin = (float)r / (float)(RAND_MAX);
        int query;
        if (coin < p) {
            query = B[r % m];
        } else {
            query = A[r % (n - m)];
        }
        queries[i] = query;
    }

    ticks t0;
    ticks t1;
    t0 = getticks();
    for (int i = 0; i < n_queries; i++) {
        assert(search(&t, queries[i]) != NULL);
    }
    t1 = getticks();
    double runtime_bst = elapsed(t1, t0);
    // showfloat(runtime_bst);

    struct Node* cache[m];
    for (int i = 0; i < m; i++) {
        cache[i] = search(&t, B[i]);
    }

    // simple array cache, and bst search on a miss
    t0 = getticks();
    for (int i = 0; i < n_queries; i++) {
        int query = queries[i];

        bool incache = false;
        int j = findinarray(B, m, query);
        if (j != -1) {
            struct Node* n = cache[j];
            incache = true;
        }
        if (!incache) {
            assert(search(&t, query) != NULL);
        }
    }
    t1 = getticks();
    double runtime_arraycache = elapsed(t1, t0);
    double speedup_arraycache = runtime_bst / runtime_arraycache;
    // showfloat(runtime_arraycache);

    t0 = getticks();
    for (int i = 0; i < n_queries; i++) {
        assert(search_splayup(&t, queries[i]) == 0);
    }
    t1 = getticks();
    double runtime_splay = elapsed(t1, t0);
    double speedup_splay = runtime_bst / runtime_splay;
    // showfloat(runtime_splay);

    // showfloat(speedup_splay);
    // showfloat(speedup_arraycache);

    if (f) {
        fprintf(f, "%d,%f,%f,%f\n", m, p, speedup_arraycache, speedup_splay);
    }
}

void test9(void)
{
    puts("\n======== test 9 ========");
    int n = 10000;
    int* nums = readnums(n);
    assert(nums != NULL);

    FILE *f = fopen("benchmark.csv", "w");
    assert(f != NULL);
    fprintf(f, "m,p,speedup_arraycache,speedup_splay\n");

    int n_queries = 100000;
    // int m = 30;
    // float p = 0.95;

    for (int m = 1; m < 50; m++) {
        for (float p = 0.5; p < 1.0; p += 0.025)
            benchmark(nums, n, n_queries, m, p, f);
    }
    fclose(f);
}

#endif

int main(void)
{
#if eltype_num == float_type
    test4();
#elif eltype_num == int_type
    // test1();
    // test2();
    // test3();
    // assert(test5() == 0);
    // test6();
    // test7();
    // test8();
    test9();
#endif
    return 0;
}
