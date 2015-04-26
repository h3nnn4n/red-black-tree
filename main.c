#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "rb_tree.h"

int main(int argc, char *argv[]){
    int i, n;//=atoi(argv[1]);
    _tree_node *tree;
    _tree_data data;

    data.n='b';

    srand(time(NULL));

    tree=tree_init(&data);
    tree->color=BLACK;
    tree_read_preorder(tree);puts("");

    data.n='a'; tree_add_sorted(tree, &data);
    data.n='a'; tree_add_sorted(tree, &data);

    /*
    time_t t=clock();

    for(i=0;i<n;i++){
        data.n=i+'a';
        tree_add_sorted(tree, &data);
        tree_read_preorder(tree);puts("");
    }

    t=clock()-t;

    printf("%f %d\n", (double)t/CLOCKS_PER_SEC,n);*/

    tree_read_preorder(tree);puts("");
    // tree_read_inorder(tree);puts("");
    // tree_read_postorder(tree);puts("");

    // printf("%c %c %c\n",tree->data->n,tree->left->data->n,tree->right->data->n);

    return EXIT_SUCCESS;
}
