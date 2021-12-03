#include "binary_trees.h"

/**
 * rotate_left_with_child - Rotates a tree with its children to the left.
 * @tree: A pointer to the node to rotate.
 *
 * Return: The new root node.
 */
binary_tree_t *rotate_left_with_child(binary_tree_t *tree)
{
	binary_tree_t *root, *new_root = tree, *new_root_lc, *root_p, *root_l;

	root = tree, root_p = root->parent;
	if (root_p == NULL)
	{
		if (root->right != NULL)
		{
			new_root = root->right;
			new_root->parent = root->parent;
			new_root_lc = new_root->left, new_root->left = root;
			root->right = new_root_lc, root->parent = new_root;
			if (new_root_lc != NULL)
				new_root_lc->parent = root;
		}
	}
	else
	{
		if (root_p->right == root)
		{
			if ((root_p->parent != NULL) && (root_p->parent->left == root_p))
				root_p->parent->left = root;
			if ((root_p->parent != NULL) && (root_p->parent->right == root_p))
				root_p->parent->right = root;
			root_l = root->left;
			root->left = root_p;
			root->parent = root_p->parent;
			root_p->right = root_l;
			root_p->parent = root;
			if (root_l != NULL)
				root_l->parent = root_p;
			new_root = (root->parent == NULL ? root : new_root);
		}
	}
	return (new_root);
}

/**
 * binary_tree_rotate_left - Rotates a node to the left.
 * @tree: A pointer to the node to rotate.
 *
 * Return: The new root node.
 */
binary_tree_t *binary_tree_rotate_left(binary_tree_t *tree)
{
	binary_tree_t *root, *root_p, *new_root;

	if (tree == NULL)
		return (NULL);
	root = tree, root_p = root->parent, new_root = root;
	if ((root->left == NULL) && (root->right == NULL))
	{
		if (root->parent != NULL)
		{
			if (root->parent->right == root)
			{
				if ((root_p->parent != NULL) && (root_p->parent->right == root_p))
					root_p->parent->right = root;
				if ((root_p->parent != NULL) && (root_p->parent->left == root_p))
					root_p->parent->left = root;
				root->parent = root_p->parent;
				root_p->right = NULL, root_p->parent = root;
				root->left = root_p;
			}
			else
			{
				if ((root_p->parent != NULL) && (root_p->parent->right == root_p))
					root_p->parent->right = root;
				if ((root_p->parent != NULL) && (root_p->parent->left == root_p))
					root_p->parent->left = root;
				root->parent = root_p->parent;
				root_p->left = NULL, root_p->parent = root;
				root->right = root_p;
			}
		}
	}
	else
	{
		new_root = rotate_left_with_child(tree);
	}
	return (new_root);
}
