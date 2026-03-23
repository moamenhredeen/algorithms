#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

#include "data_structures.h"

struct BinaryTree {
    int item;
    struct BinaryTree *parent;
    struct BinaryTree *left;
    struct BinaryTree *right;
};

binary_tree_t *binary_tree_create(int item)
{
    binary_tree_t *tree;
    tree = malloc(sizeof *tree);
    tree->item = item;
    tree->parent = NULL;
    tree->left = NULL;
    tree->right = NULL;
    return tree;
}

void binary_tree_destroy(binary_tree_t *tree)
{
    if (tree == NULL)
        return;
    if (tree->left != NULL)
        binary_tree_destroy(tree->left);
    if (tree->right != NULL)
        binary_tree_destroy(tree->right);
    free(tree);
}

binary_tree_t *binary_tree_search(binary_tree_t *tree, int item)
{
    if (tree == NULL) {
        return NULL;
    }

    if (item == tree->item)
        return tree;
    else if (item > tree->item)
        return binary_tree_search(tree->right, item);
    else
        return binary_tree_search(tree->left, item);
}

binary_tree_t *binary_tree_find_minimum(binary_tree_t *tree)
{
    if (tree == NULL)
        return NULL;

    binary_tree_t *current = tree;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

binary_tree_t *binary_tree_find_maximum(binary_tree_t *tree)
{
    if (tree == NULL)
        return NULL;

    binary_tree_t *current = tree;
    while (current->right != NULL) {
        current = current->right;
    }
    return current;
}

void binary_tree_traverse(binary_tree_t *tree, void (*func)(binary_tree_t *node, void *user_data),
                          void *user_data)
{
    if (tree != NULL) {
        binary_tree_traverse(tree->left, func, user_data);
        func(tree, user_data);
        binary_tree_traverse(tree->right, func, user_data);
    }
}

int get_item(binary_tree_t *tree)
{
    assert(tree != NULL);
    return tree->item;
}
