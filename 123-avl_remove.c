#include "binary_trees.h"
#define DELETE_TREE_NODE_WITH_CHILDREN_PARTS()                             \
	{                                                                        \
		new_node = (*node)->right;                                             \
		while ((new_node != NULL) && (new_node->left != NULL))                 \
			new_node = new_node->left;                                           \
		if ((new_node != NULL) && (new_node == (*node)->right))                \
		{                                                                      \
			*parent = (*node)->parent;                                           \
			new_node->parent = (*node)->parent, new_node->left = (*node)->left;  \
			if ((*node)->left != NULL)                                           \
				(*node)->left->parent = new_node;                                  \
			if (((*node)->parent != NULL) && ((*node)->parent->left == *node))   \
				(*node)->parent->left = new_node;                                  \
			if (((*node)->parent != NULL) && ((*node)->parent->right == *node))  \
				(*node)->parent->right = new_node;                                 \
		}                                                                      \
		else if (new_node != NULL)                                             \
		{                                                                      \
			*parent = new_node->parent;                                          \
			new_node->parent->left = new_node->right;                            \
			if (new_node->right != NULL)                                         \
				new_node->right->parent = new_node->parent;                        \
			new_node->parent = (*node)->parent;                                  \
			new_node->left = (*node)->left, new_node->right = (*node)->right;    \
			(*node)->left->parent = new_node, (*node)->right->parent = new_node; \
			if (((*node)->parent != NULL) && ((*node)->parent->left == *node))   \
				(*node)->parent->left = new_node;                                  \
			if (((*node)->parent != NULL) && ((*node)->parent->right == *node))  \
				(*node)->parent->right = new_node;                                 \
		}                                                                      \
	}

/**
 * find_node_1 - Finds a node with a given value in a binary search tree.
 * @root: The root of the binary search tree.
 * @value: The value of the node.
 *
 * Return: A pointer to the found node, otherwise NULL.
 */
avl_t *find_node_1(avl_t *root, int value)
{
	avl_t *node = NULL;

	if (root != NULL)
	{
		if (root->left != NULL)
			node = root->left->parent;
		if ((node == NULL) && (root->right != NULL))
			node = root->right->parent;
		while (node != NULL)
		{
			if (node->n < value)
				node = node->right;
			else if (node->n > value)
				node = node->left;
			else
				break;
		}
	}
	return (node);
}

/**
 * delete_tree_node - Deletes a node in a binary search tree and replaces \
 * it with its inorder successor, otherwise predecessor.
 * @node: A pointer to the node in the binary search tree.
 * @parent: A pointer to the node of possible imbalance.
 *
 * Return: A pointer to the node's inorder successor node or predecessor.
 */
avl_t *delete_tree_node(avl_t **node, avl_t **parent)
{
	avl_t *new_node;

	*parent = (*node)->parent;
	if (((*node)->left == NULL) && ((*node)->right == NULL))
	{
		if (((*node)->parent != NULL) && ((*node)->parent->left == *node))
			(*node)->parent->left = NULL;
		if (((*node)->parent != NULL) && ((*node)->parent->right == *node))
			(*node)->parent->right = NULL;
	}
	else if (((*node)->left != NULL) ^ ((*node)->right != NULL))
	{
		*parent = (*node)->parent;
		new_node = ((*node)->left != NULL ? (*node)->left : (*node)->right);
		if (((*node)->parent != NULL) && ((*node)->parent->left == *node))
			(*node)->parent->left = new_node;
		else if (((*node)->parent != NULL) && ((*node)->parent->right == *node))
			(*node)->parent->right = new_node;
		new_node->parent = (*node)->parent;
	}
	else
	{
		DELETE_TREE_NODE_WITH_CHILDREN_PARTS();
	}
	if ((node != NULL) && (*node != NULL))
		free(*node);
	return (new_node);
}

/**
 * adjust_balance_1 - Adjusts the balance of an AVL tree by \
 * rotating the unbalanced subtree.
 * @root: A pointer to the address of the root of the tree.
 * @node: A pointer to the inserted node.
 */
void adjust_balance_1(avl_t **root, avl_t *node)
{
	avl_t *cur = node, *new_root = *root;
	int balance = 0;

	while (cur != NULL)
	{
		balance = binary_tree_balance(cur);
		if (!((balance >= -1) && (balance <= 1)))
		{
			if ((balance == 2) && ((binary_tree_balance(cur->left) == 1)
				|| (binary_tree_balance(cur->left) == 0)))
			{
				new_root = binary_tree_rotate_right(cur);
			}
			else if ((balance == 2) && (binary_tree_balance(cur->left) == -1))
			{
				cur->left = binary_tree_rotate_left(cur->left);
				new_root = binary_tree_rotate_right(cur);
			}
			else if ((balance == -2) && ((binary_tree_balance(cur->right) == -1)
				|| (binary_tree_balance(cur->right) == 0)))
			{
				new_root = binary_tree_rotate_left(cur);
			}
			else if ((balance == 2) && (binary_tree_balance(cur->left) == -1))
			{
				cur->right = binary_tree_rotate_right(cur->right);
				new_root = binary_tree_rotate_left(cur);
			}
			new_root = (cur == *root ? new_root : *root);
			break;
		}
		cur = cur->parent;
	}
	*root = new_root;
}

/**
 * avl_remove - Removes a node with a given value from an AVL tree.
 * @root: A pointer to the root of the AVL tree.
 * @value: The value of the node to remove.
 *
 * Return: The new root node, otherwise NULL.
 */
avl_t *avl_remove(avl_t *root, int value)
{
	avl_t *node = NULL, *new_root = root, *new_node = NULL, *parent = NULL;

	if (new_root != NULL)
	{
		node = find_node_1(root, value);
		if ((node != NULL) && (node->n == value))
		{
			new_node = delete_tree_node(&node, &parent);
			if (new_node != NULL)
			{
				new_root = (new_node->parent == NULL ? new_node : new_root);
				adjust_balance_1(&new_root, parent);
			}
		}
	}
	return (new_root);
}
