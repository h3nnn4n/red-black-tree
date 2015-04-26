typedef enum {RED, BLACK} _color ;

typedef struct{
    //int n;
    char n;
}_tree_data;

typedef struct __tree_node{
    _color color;
    _tree_data *data;
    struct __tree_node *right;
    struct __tree_node *left;
    struct __tree_node *above;
}_tree_node;

_tree_node *tree_del(_tree_node*);
_tree_node *tree_init(_tree_data*);
_tree_node *tree_seek(_tree_node*, _tree_data*);

int tree_info(_tree_node*);

void tree_left_rotate (_tree_node*, _tree_node*);
void tree_right_rotate(_tree_node*, _tree_node*);

void list_add_left(_tree_node*, _tree_node*, _tree_data*);
void list_add_right(_tree_node*, _tree_node*, _tree_data*);

void tree_add_sorted(_tree_node*, _tree_data*);

void tree_read_inorder(_tree_node*);
void tree_read_postorder(_tree_node*);
void tree_read_preorder(_tree_node*);

void tree_fixup(_tree_node*, _tree_node*);

void tree_remove(_tree_data*,_tree_data*);
