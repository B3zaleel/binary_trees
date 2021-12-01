#include "binary_trees.h"

/**
 * bst_checker - Checks if a binary tree is a binary search tree.
 * @tree: The binary tree.
 * @min: The minimum value of the tree.
 * @max: The mazimum value of the tree.
 * @is_bst: A pointer to the tree's validation flag.
 */
void bst_checker(const binary_tree_t *tree, int min, int max, int *is_bst)
{
	if (tree != NULL)
	{
		if ((tree->n > min) && (tree->n < max))
		{
			bst_checker(tree->left, min, tree->n, is_bst);
			bst_checker(tree->right, tree->n, max, is_bst);
		}
		else
		{
			if (is_bst != NULL)
			{
				*is_bst = 0;
			}
		}
	}
}

/**
 * tree_height_c - Computes the height of a binary tree.
 * @tree: The binary tree.
 * @n: The accumulated height of the current tree.
 * @height: A pointer to the tree's maximum height value.
 */
void tree_height_c(const binary_tree_t *tree, int n, int *height)
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
			tree_height_c(tree->left, n + 1, height);
			tree_height_c(tree->right, n + 1, height);
		}
	}
}

/**
 * bin_tree_balance - Computes the balance factor of a binary tree.
 * @tree: The binary tree.
 *
 * Return: The balance factor of the given binary tree.
 */
int bin_tree_balance(const binary_tree_t *tree)
{
	int balance_factor = 0;
	int left_height = 0;
	int right_height = 0;

	if (tree != NULL)
	{
		tree_height_c(tree->left, 1, &left_height);
		tree_height_c(tree->right, 1, &right_height);
	}
	balance_factor = left_height - right_height;
	return (balance_factor);
}

/**
 * binary_tree_is_avl - Checks if the given tree is an AVL tree.
 * @tree: The tree to check.
 *
 * Return: 1 if the tree is an AVL tree, otherwise 0.
 */
int binary_tree_is_avl(const binary_tree_t *tree)
{
	int diff = 0;
	int is_bst = 0;
	int is_avl = 0;

	if (tree != NULL)
	{
		is_bst = 1;
		bst_checker(tree, INT_MIN, INT_MAX, &is_bst);
		if (is_bst == 1)
		{
			diff = bin_tree_balance(tree->left) - bin_tree_balance(tree->right);
			if ((diff >= -1) && (diff <= 1))
			{
				is_avl = 1;
			}
		}
	}
	return (is_avl);
}
