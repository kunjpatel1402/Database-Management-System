// C program to insert a node in AVL tree
#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include "row.h"
// An AVL tree node


struct Node
{
    struct row key;
    struct Node *left;
    struct Node *right;
    int height;
};

// A utility function to get maximum of two integers
int max(int a, int b);

// A utility function to get the height of the tree
int height(struct Node *N)
{
    if (N == NULL)
        return 0;
    return 1 + max(height(N->left), height(N->right));
}

// A utility function to get maximum of two integers
int max(int a, int b)
{
    return (a > b) ? a : b;
}

/* Helper function that allocates a new node with the given key and
    NULL left and right pointers. */
struct Node *newNode(struct row key)
{
    struct Node *node = (struct Node *)
        malloc(sizeof(struct Node));
    row_copy(&node->key ,&key);
    node->left = NULL;
    node->right = NULL;
    node->height = 0; // new node is initially added at leaf
    return (node);
}

// A utility function to right rotate subtree rooted with y
// See the diagram given above.
struct Node *rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = height(y);
    x->height = height(x);

    // Return new root
    return x;
}

// A utility function to left rotate subtree rooted with x
// See the diagram given above.
struct Node *leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = height(x);
    y->height = height(y);

    // Return new root
    return y;
}

// Get Balance factor of node N
int getBalance(struct Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Recursive function to insert a key in the subtree rooted
// with node and returns the new root of the subtree.
struct Node *insert(struct Node *node, struct row key)
{
    /* 1. Perform the normal BST insertion */
    if (node == NULL)
        return (newNode(key));

    if (key.sr_no < node->key.sr_no)
        node->left = insert(node->left, key);
    else if (key.sr_no > node->key.sr_no)
        node->right = insert(node->right, key);
    else{ 
        printf("Duplicate Sr No.\n");
        // Equal keys are not allowed in BST
        return node;
    }
    /* 2. Update height of this ancestor node */
    node->height = height(node);

    /* 3. Get the balance factor of this ancestor
        node to check whether this node became
        unbalanced */
    int balance = getBalance(node);

    // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (balance > 1 && key.sr_no < node->left->key.sr_no)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key.sr_no > node->right->key.sr_no)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key.sr_no > node->left->key.sr_no)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key.sr_no < node->right->key.sr_no)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}

// A utility function to print preorder traversal
// of the tree.
// The function also prints height of every node
void preOrder(struct Node *root)
{
    if (root != NULL)
    {
        row_print(&root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}
struct Node *minValueNode(struct Node *node)
{
    struct Node *current = node;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;

    return current;
}

// Recursive function to delete a node with given key
// from subtree with given root. It returns root of
// the modified subtree.
struct Node *deleteNode(struct Node *root, int key, bool *ok)
{
    // STEP 1: PERFORM STANDARD BST DELETE

    if (root == NULL)
        return root;

    // If the key to be deleted is smaller than the
    // root's key, then it lies in left subtree
    if (key < root->key.sr_no)
        root->left = deleteNode(root->left, key, ok);

    // If the key to be deleted is greater than the
    // root's key, then it lies in right subtree
    else if (key > root->key.sr_no)
        root->right = deleteNode(root->right, key, ok);

    // if key is same as root's key, then This is
    // the node to be deleted
    else
    {
        *ok = true;
        // node with only one child or no child
        if ((root->left == NULL) || (root->right == NULL))
        {
            struct Node *temp = root->left ? root->left : root->right;

            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else               // One child case
                *root = *temp; // Copy the contents of
                               // the non-empty child
            free(temp);
        }
        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            struct Node *temp = minValueNode(root->right);

            // Copy the inorder successor's data to this node
            root->key = temp->key;

            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->key.sr_no, ok);
        }
    }

    // If the tree had only one node then return
    if (root == NULL)
    {
        //printf("This");
        return root;
    }

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = 1 + max(height(root->left),   height(root->right));

    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to
    // check whether this node became unbalanced)
    int balance = getBalance(root);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

struct MyAVLManager{
    struct Node *root;
    int mysize;
};

struct MyAVLManager *myAVLManager_construct(){
    struct MyAVLManager *manager = (struct MyAVLManager *)malloc(sizeof(struct MyAVLManager));
    manager->root = NULL;
    manager->mysize = 0;
    return manager;
}

//copy constructor for avlmanager
void manager_copy(struct MyAVLManager *dest, const struct MyAVLManager *src){
    dest->mysize = src->mysize;
    dest->root = src->root;
}

void avl_insert(struct MyAVLManager *avl, struct row key){
    avl->root = insert(avl->root, key);
    (avl->mysize)++;
}
void avl_delete(struct MyAVLManager *avl, int key){
    bool ok = false;
    avl->root = deleteNode(avl->root, key, &ok);
    if (ok)(avl->mysize)--;
}
void avl_print(struct MyAVLManager *avl){
    printf("%d\n", avl->mysize);
    preOrder(avl->root);
}



void preorder_insert(struct Node *node, struct row *array, int *i)
{
    if (node == NULL)
    {
        return;
    }
    else
    {
       // row_print(&node->key);
        array[*i].sr_no = node->key.sr_no;
        array[*i].no_of_char_values = node->key.no_of_char_values;
        array[*i].no_of_int_values = node->key.no_of_int_values;
        array[*i].no_of_double_values = node->key.no_of_double_values;
        array[*i].no_of_string_values = node->key.no_of_string_values;

        array[*i].int_values = (long long int *)malloc(sizeof(long long int) * node->key.no_of_int_values);
        for (int j = 0; j < node->key.no_of_int_values; j++)
        {
            array[*i].int_values[j] = node->key.int_values[j];
        }

        array[*i].double_values = (double *)malloc(sizeof(double) * node->key.no_of_double_values);
        for (int j = 0; j < node->key.no_of_double_values; j++)
        {
            array[*i].double_values[j] = node->key.double_values[j];
        }

        array[*i].char_values = (char *)malloc(sizeof(char) * node->key.no_of_char_values);
        for (int j = 0; j < node->key.no_of_char_values; j++)
        {
            array[*i].char_values[j] = node->key.char_values[j];
        }

        array[*i].string_values = (char **)malloc(sizeof(char *) * node->key.no_of_string_values);
        for (int j = 0; j < node->key.no_of_string_values; j++)
        {
            array[*i].string_values[j] = (char *)malloc(sizeof(char) * (strlen(node->key.string_values[j]) + 1));
            strcpy(array[*i].string_values[j], node->key.string_values[j]);
        }
    }
    (*i)++;
    preorder_insert(node->left, array, i);
    preorder_insert(node->right, array, i);
}

void print_row_array(struct row *array, int size)
{   
    for (int i = 0; i < size; i++)
    {
        row_print(&array[i]);
    }
}

void sort_rows(struct MyAVLManager *avl, int col)
{   
   // printf("called");
    col--;
    /*if (avl->root==NULL){
        printf("no");
    }*/
   // printf("%d", avl->mysize);
    struct row array[avl->mysize];
   // printf("here");
    int index = 0;
    preorder_insert(avl->root, array, &index);
   // print_row_array(array, avl->size);
    if ((col < array[0].no_of_int_values)&&(col >= 0))
    {
        // compare array[i].int_values[col] with array[i+1].int_values[col]
        for (int i = 0; i < (sizeof(array) / sizeof(array[0]) - 1); i++)
        {
            for (int j = i + 1; j < (sizeof(array) / sizeof(array[0])); j++)
            {
                if (array[i].int_values[col] > array[j].int_values[col])
                {
                    struct row temp = array[i];
                    array[i] = array[j];
                    array[j] = temp;
                }
            }
        }
    }
    else if ((col >= array[0].no_of_int_values)&&(col < array[0].no_of_int_values + array[0].no_of_double_values))
    {
        col = col - array[0].no_of_int_values;
        // compare array[i].double_values[col] with array[i+1].double_values[col]
        for (int i = 0; i < (sizeof(array) / sizeof(array[0]) - 1); i++)
        {
            for (int j = i + 1; j < (sizeof(array) / sizeof(array[0])); j++)
            {
                if (array[i].double_values[col] > array[j].double_values[col])
                {
                    struct row temp = array[i];
                    array[i] = array[j];
                    array[j] = temp;
                }
            }
        }
    }
    else if ((col >= array[0].no_of_int_values + array[0].no_of_double_values) && (col < array[0].no_of_int_values + array[0].no_of_double_values + array[0].no_of_char_values))
    {
        col = col - array[0].no_of_int_values - array[0].no_of_double_values;
        // compare array[i].char_values[col] with array[i+1].char_values[col]
        for (int i = 0; i < (sizeof(array) / sizeof(array[0]) - 1); i++)
        {
            for (int j = i + 1; j < (sizeof(array) / sizeof(array[0])); j++)
            {
                if (array[i].char_values[col] > array[j].char_values[col])
                {
                    struct row temp = array[i];
                    array[i] = array[j];
                    array[j] = temp;
                }
            }
        }
    }
    else if ((col >= array[0].no_of_int_values + array[0].no_of_double_values + array[0].no_of_char_values) && (col < array[0].no_of_int_values + array[0].no_of_double_values + array[0].no_of_char_values + array[0].no_of_string_values))
    {
        col = col - array[0].no_of_int_values - array[0].no_of_double_values - array[0].no_of_char_values;
        // compare array[i].string_values[col] with array[i+1].string_values[col]
        for (int i = 0; i < (sizeof(array) / sizeof(array[0]) - 1); i++)
        {
            for (int j = i + 1; j < (sizeof(array) / sizeof(array[0])); j++)
            {
                if (strcmp(array[i].string_values[col], array[j].string_values[col]) > 0)
                {
                    struct row temp = array[i];
                    array[i] = array[j];
                    array[j] = temp;
                }
            }
        }
    }
    else
    {
        printf("Invalid column number\n");
        return ;
    }
   // printf("%d", avl->mysize);
    print_row_array(array, avl->mysize);
}

struct Qnode
{
    struct row *data;
    struct Qnode *next;
};

struct Queue
{
    struct Qnode *front;
    struct Qnode *rear;
};
void InsertinQ(struct row r, struct Queue *q)
{
    struct Qnode *temp = (struct Qnode *)malloc(sizeof(struct Qnode));
    struct row *temp1 = (struct row *)malloc(sizeof(struct row));
    row_copy(temp1, &r);
    temp->data = temp1;
    temp->next = NULL;
    if (q->front == NULL)
    {
        q->front = temp;
        q->rear = temp;
    }
    else
    {
        q->rear->next = temp;
        q->rear = temp;

    }
}

void subRoutine_search_tree(struct Node *node, char *search_value_string, int col, struct Queue *queue, int data_flag)
{
    if (node == NULL)
        return;
    else
    {
        if (data_flag == 1)
        {
            if (node->key.int_values[col] == atoi(search_value_string))
            {
                InsertinQ(node->key, queue);
            }
        }
        else if (data_flag == 2)
        {
            if (node->key.double_values[col] == atof(search_value_string))
            {
                InsertinQ(node->key, queue);
            }
        }
        else if (data_flag == 3)
        {
            if (node->key.char_values[col] == search_value_string[0])
            {
                InsertinQ(node->key, queue);
            }
        }
        else if (data_flag == 4)
        {
            if (strcmp(node->key.string_values[col], search_value_string) == 0)
            {
                InsertinQ(node->key, queue);
            }
        }
        subRoutine_search_tree(node->left, search_value_string, col, queue, data_flag);
        subRoutine_search_tree(node->right, search_value_string, col, queue, data_flag);
    }
}

// search and insert matched columns in the queue
void search_tree_main(struct Node *node, char *search_value, int col)
{
    struct Queue queue;
    queue.front = NULL;
    queue.rear = NULL;
    int data_flag = 0;
    if (search_value[0] == '\0')
    {
        return;
    }
    col--;
    if ((col < node->key.no_of_int_values) && (col >= 0))
    {
        data_flag=1;
    }
    else if ((col >= node->key.no_of_int_values) && (col < node->key.no_of_int_values + node->key.no_of_double_values))
    {
        data_flag = 2;
        col = col - node->key.no_of_int_values;
    }
    else if ((col >= node->key.no_of_int_values + node->key.no_of_double_values) && (col < node->key.no_of_int_values + node->key.no_of_double_values + node->key.no_of_char_values))
    {
        data_flag = 3;
        col = col - node->key.no_of_int_values - node->key.no_of_double_values;
    }
    else if ((col >= node->key.no_of_int_values + node->key.no_of_double_values + node->key.no_of_char_values) && (col < node->key.no_of_int_values + node->key.no_of_double_values + node->key.no_of_char_values + node->key.no_of_string_values))
    {
        data_flag = 4;
        col = col - node->key.no_of_int_values - node->key.no_of_double_values - node->key.no_of_char_values;
    }
    else
    {
        printf("Invalid column number\n");
        return;
    }
    subRoutine_search_tree(node, search_value, col, &queue, data_flag);
    //print queue
    struct Qnode *temp = queue.front;
    while (temp != NULL)
    {
        row_print(temp->data);
        temp = temp->next;
    }
}

void search(struct MyAVLManager *manager, char *search_value, int col)
{
    search_tree_main(manager->root, search_value, col);
}


void change_values(struct Node* node, int data_flag, int col, char *change_value, int sr_no)
{
    if (node == NULL)
        return;
    else
    {   //printf("%lld %d\n", node->key.sr_no, sr_no);
        
        if (node->key.sr_no > sr_no)
        change_values(node->left, data_flag, col, change_value, sr_no);
        else if (node->key.sr_no == sr_no){
            if (data_flag == 1)
            {
                if (node->key.sr_no == sr_no)
                {
                    node->key.int_values[col] = atoi(change_value);
                }
            }
            else if (data_flag == 2)
            {
                if (node->key.sr_no == sr_no)
                {
                    node->key.double_values[col] = atof(change_value);
                }
            }
            else if (data_flag == 3)
            {
                if (node->key.sr_no == sr_no)
                {
                    node->key.char_values[col] = change_value[0];
                }
            }
            else if (data_flag == 4)
            {
                if (node->key.sr_no == sr_no)
                {
                    strcpy(node->key.string_values[col], change_value);
                }
            }
        }
        else change_values(node->right, data_flag, col, change_value, sr_no);
    }
}


void replace(struct MyAVLManager* manager, int col, char *change_value, int sr_no)
{
    int data_flag = 0;
    col--;
    if ((col < manager->root->key.no_of_int_values) && (col >= 0))
    {
        data_flag = 1;
    }
    else if ((col >= manager->root->key.no_of_int_values) && (col < manager->root->key.no_of_int_values + manager->root->key.no_of_double_values))
    {
        data_flag = 2;
        col = col - manager->root->key.no_of_int_values;
    }
    else if ((col >= manager->root->key.no_of_int_values + manager->root->key.no_of_double_values) && (col < manager->root->key.no_of_int_values + manager->root->key.no_of_double_values + manager->root->key.no_of_char_values))
    {
        data_flag = 3;
        col = col - manager->root->key.no_of_int_values - manager->root->key.no_of_double_values;
    }
    else if ((col >= manager->root->key.no_of_int_values + manager->root->key.no_of_double_values + manager->root->key.no_of_char_values) && (col < manager->root->key.no_of_int_values + manager->root->key.no_of_double_values + manager->root->key.no_of_char_values + manager->root->key.no_of_string_values))
    {
        data_flag = 4;
        col = col - manager->root->key.no_of_int_values - manager->root->key.no_of_double_values - manager->root->key.no_of_char_values;
    }
    else
    {
        printf("Invalid column number\n");
        return;
    }
    change_values(manager->root, data_flag, col, change_value, sr_no);
}
