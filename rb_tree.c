#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "rb_tree.h"

_tree_node *tree_init(_tree_data *data){
    _tree_node *t = (_tree_node*)malloc(sizeof(_tree_node));
    _tree_data *datanew = (_tree_data*)malloc(sizeof(_tree_data));
    t->right = NULL;
    t->left = NULL;
    t->above = NULL;
    t->data = datanew;
    t->color = RED;
    memcpy(t->data,data,sizeof(_tree_data));
    return t;
}

void list_add_left(_tree_node *t, _tree_node *p, _tree_data *data){
    if(p==NULL){
        fprintf(stderr,"NULL Pointer\n");
    }else if(p->left!=NULL){
        fprintf(stderr,"Not free pointer %c %c\n",p->left->data->n,data->n);
    }else{
        p->left = tree_init(data);
        p->left->above = p;
    }

    if(p->above != NULL){
        printf("tree fixup info: %c %c %s %s \n", p->data->n, p->above != NULL ? p->above->data->n : -1, p->color == BLACK ? "BLACK" : "RED", p->above->color == BLACK ? "BLACK" : "RED");
        tree_fixup(t, p->left);
    }
}

void list_add_right(_tree_node *t, _tree_node *p, _tree_data *data){
    if(p==NULL){
        fprintf(stderr,"NULL Pointer\n");
    }else if(p->right!=NULL){
        fprintf(stderr,"Not free pointer %c %c\n",p->right->data->n,data->n);
    }else{
        p->right = tree_init(data);
        p->right->above = p;
    }

    if(p->above != NULL){
        printf("tree fixup info: %c %c %s %s \n", p->data->n, p->above != NULL ? p->above->data->n : -1, p->color == BLACK ? "BLACK" : "RED", p->above->color == BLACK ? "BLACK" : "RED");
        tree_fixup(t, p->right);
    }
}

int tree_info(_tree_node *tree){
    if(tree!=NULL){
        return (int)tree->data->n;
    }
}

void tree_fixup(_tree_node* tree, _tree_node* z){
    tree_read_preorder(tree);puts("");
    while(z != tree && z->above->color == RED){
        if( z->above == z->above->above->left){
            _tree_node *y = z->above->above->right;
            if(y->color == RED){
                y->color = BLACK;
                z->above->above->color = RED;
                z->above->color = BLACK;
                z = z->above->above;
            }else if(z == z->above->right){
                z = z->above;
                tree_left_rotate(tree,z);
            }
            z->above->color = BLACK;
            z->above->above->color = RED;
            tree_right_rotate(tree, z->above->above);
        }else if( z->above == z->above->above->right){
            _tree_node *y = z->above->above->left;
            if(y!= NULL && y->color == RED){
                y->color = BLACK;
                z->above->above->color = RED;
                z->above->color = BLACK;
                z = z->above->above;
            }else if( z->above != NULL && z == z->above->left){
                z = z->above;
                tree_right_rotate(tree,z);
            }

            tree_read_preorder(tree);puts("");

            if(z->above != NULL){
                z->above->color = BLACK;
                z->above->above->color = RED;

                tree_read_preorder(tree);puts("");

                tree_left_rotate(tree, z->above->above);

                tree_read_preorder(tree);puts("");
            }
        }
    }
    tree->color = BLACK;
}

void tree_right_rotate(_tree_node *tree, _tree_node* x){
    _tree_node *y;

    y = x->left;
    x->left = y->right;
    if(y->right != NULL)
        y->right->above = x;
    y->above = x->above;

    if(x->above == NULL){
        tree = y;
    }else if(x == x->above->right){
        x->above->right = y;
    }else{
        x->above->left = y;
    }

    y->right = x;
    x->above = y;
}

void tree_left_rotate(_tree_node *tree, _tree_node* x){
    _tree_node *y;

    y = x->right;
    x->right = y->left;

    if(y->left != NULL){
        y->left->above = x;
    }

    printf("... %p %p ", x->above, y->above);
    y->above = x->above;
    printf(" %p \n ", y->above);

    if(x->above == NULL){
        tree = y;
    }else if(x == x->above->left){
        x->above->left = y;
    }else{
        x->above->right = y;
    }

    y->left = x;
    x->above = y;


}

void tree_add_sorted(_tree_node *t, _tree_data *data){
    _tree_node *tree, *p, *q;
    q=t;
    p=t;

    while(q!=NULL){
        p = q;
        if(data->n < tree_info(p)){
            q = p->left;
        }else{
            q = p->right;
        }
    }

    if(data->n < tree_info(p)){
        list_add_left(t, p, data);
    }else{
        list_add_right(t, p, data);
    }
}

void tree_read_preorder(_tree_node *n){
    if(n!=NULL){
        //fprintf(stdout,"%d",tree_info(n));
        if(n->above != NULL)
            fprintf(stdout,"-> %c\tl = %c\tr = %c\tp = %c\tcolor = %s\tpcolor = %s \n",tree_info(n),tree_info(n->left),tree_info(n->right),tree_info(n->above),n->color == BLACK ? "BLACK" : "RED", n->above->color == BLACK ? "BLACK" : "RED");
        else
            fprintf(stdout,"-> %c\tl = %c\tr = %c\tp = %c\tcolor = %s\n",tree_info(n),tree_info(n->left),tree_info(n->right),tree_info(n->above),n->color == BLACK ? "BLACK" : "RED");

        tree_read_preorder(n->left);
        tree_read_preorder(n->right);
    }
}

void tree_read_inorder(_tree_node *n){
    if(n!=NULL){
        tree_read_inorder(n->left);
        fprintf(stdout,"%d",tree_info(n));

        tree_read_inorder(n->right);
    }
}

void tree_read_postorder(_tree_node *n){
    if(n!=NULL){
        tree_read_postorder(n->left);
        tree_read_postorder(n->right);
        fprintf(stdout,"%d",tree_info(n));
    }
}

_tree_node *tree_seek(_tree_node *node, _tree_data *data){
    if(node==NULL){
        return NULL;
    }

    if(data->n < node->data->n){
        return tree_seek(node->left,data);
    }else if(data->n < node->data->n){
        return tree_seek(node->right,data);
    }
    return node;
}

/*void tree_remove(_tree_node *node,_tree_data *data){
  _tree_data *n=tree_seek(node,data);

  }*/
