#include "binary_trees.h"

/**
 * bst_insert_helper - Inserts a node into a binary search tree.
 * @tree: A pointer to the binary search tree.
 * @value: The value of the new node.
 *
 * Return: A pointer to the created node, otherwise NULL.
 */
bst_t *bst_insert_helper(bst_t **tree, int value)
{
	bst_t *new_node = NULL, *parent = NULL;

	if (tree != NULL)
	{
		parent = *tree;
		if (*tree == NULL)
		{
			new_node = binary_tree_node(*tree, value);
			*tree = new_node;
		}
		else
		{
			while (parent != NULL)
			{
				if ((parent->n > value) && (parent->left != NULL))
					parent = parent->left;
				else if ((parent->n < value) && (parent->right != NULL))
					parent = parent->right;
				else
					break;
			}
			if (parent->n < value)
			{
				new_node = binary_tree_node(parent, value);
				parent->right = new_node;
			}
			else if (parent->n > value)
			{
				new_node = binary_tree_node(parent, value);
				parent->left = new_node;
			}
		}
	}
	return (new_node);
}

/**
 * adjust_balance - Adjusts the balance of a tree.
 * @node: A pointer to the inserted node that changed the tree's balance.
 */
void adjust_balance(avl_t **node)
{
	avl_t *tmp0 = NULL, *tmp1 = NULL;
	char rot[] = "\0\0";

	if (node == NULL)
		return;
	tmp1 = (*node)->parent;
	tmp0 = (tmp1 != NULL ? tmp1->parent : NULL);
	if ((tmp0 != NULL) && (tmp1 != NULL))
	{
		rot[0] = (tmp0->left == tmp1 ? 'L' : 'R');
		rot[1] = (tmp1->left == *node ? 'L' : 'R');
		if ((rot[0] == 'L') && (rot[1] == 'L'))
		{
			binary_tree_rotate_right(tmp0);
		}
		else if ((rot[0] == 'R') && (rot[1] == 'R'))
		{
			binary_tree_rotate_left(tmp0);
		}
		else if ((rot[0] == 'L') && (rot[1] == 'R'))
		{
			binary_tree_rotate_left(*node);
			binary_tree_rotate_right(tmp0);
		}
		else if ((rot[0] == 'R') && (rot[1] == 'L'))
		{
			binary_tree_rotate_right(*node);
			binary_tree_rotate_left(tmp0);
		}
	}
}

/**
 * tree_height_2 - Computes the height of a binary tree.
 * @tree: The binary tree.
 * @n: The accumulated height of the current tree.
 * @height: A pointer to the tree's maximum height value.
 */
void tree_height_2(const binary_tree_t *tree, int n, int *height)
{
	if (tree != NULL)
	{
		if ((tree->left == NULL) && (tree->right == NULL))
		{
			if (n > *height)
			{
				*height = n;
			}
		}
		else
		{
			tree_height_2(tree->left, n + 1, height);
			tree_height_2(tree->right, n + 1, height);
		}
	}
}

/**
 * avl_tree_balance_1 - Recursively checks the balance of a binary tree and \
 * its nodes and sets the balanced flag to 0 if it isn't all balanced.
 * @tree: The binary tree.
 * @is_balanced: A pointer to the balanced flag's value.
 */
void avl_tree_balance_1(const avl_t *tree, int *is_balanced)
{
	int balance_factor = 0;
	int left_height = 0;
	int right_height = 0;

	if (tree != NULL)
	{
		tree_height_2(tree->left, 1, &left_height);
		tree_height_2(tree->right, 1, &right_height);
		balance_factor = left_height - right_height;
		if (!((balance_factor >= -1) && (balance_factor <= 1)))
		{
			if (is_balanced != NULL)
			{
				*is_balanced = 0;
			}
		}
		else
		{
			avl_tree_balance_1(tree->left, is_balanced);
			avl_tree_balance_1(tree->right, is_balanced);
		}
	}
}

/**
 * avl_insert - Inserts a value into an AVL tree.
 * @tree: A pointer to the address of the root node.
 * @value: The value of the new node.
 *
 * Return: A pointer to the created node, otherwise, NULL.
 */
avl_t *avl_insert(avl_t **tree, int value)
{
	avl_t *new_node = NULL;
	int is_bal = 0;

	if (tree != NULL)
	{
		is_bal = 1;
		new_node = bst_insert_helper(tree, value);
		avl_tree_balance_1(*tree, &is_bal);
		if (is_bal == 0)
		{
			adjust_balance(&new_node);
		}
	}
	return (new_node);
}
