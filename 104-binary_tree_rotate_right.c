#include "binary_trees.h"

/**
 * rotate_right_with_parent - Rotates a tree with its parent to the right.
 * @tree: A pointer to the node to rotate.
 *
 * Return: The new root node.
 */
binary_tree_t *rotate_right_with_parent(binary_tree_t *tree)
{
	binary_tree_t *root, *new_root = tree, *new_root_rc, *root_p, *root_r;

	root = tree, root_p = root->parent;
	(void)new_root_rc;
	if (root_p->left == root)
	{
		if ((root_p->parent != NULL) && (root_p->parent->left == root_p))
			root_p->parent->left = root;
		if ((root_p->parent != NULL) && (root_p->parent->right == root_p))
			root_p->parent->right = root;
		root_r = root->right;
		root_p->left = root_r;
		root_p->parent = root;
		root->right = root_p;
		root->parent = root_p->parent;
		(void)root_r;
		if (root_r != NULL)
			root_r->parent = root_p;
		new_root = (root->parent == NULL ? root : new_root);
	}
	else
	{
		if ((root_p->parent != NULL) && (root_p->parent->left == root_p))
			root_p->parent->left = root;
		if ((root_p->parent != NULL) && (root_p->parent->right == root_p))
			root_p->parent->right = root;
		root_r = root->right;
		root_p->left = root_r;
		root_p->parent = root;
		root->right = root_p;
		root->parent = root_p->parent;
		(void)root_r;
		if (root_r != NULL)
			root_r->parent = root_p;
		new_root = (root->parent == NULL ? root : new_root);
	}
	return (new_root);
}

/**
 * rotate_right_with_child - Rotates a tree with its children to the right.
 * @tree: A pointer to the node to rotate.
 *
 * Return: The new root node.
 */
binary_tree_t *rotate_right_with_child(binary_tree_t *tree)
{
	binary_tree_t *root, *new_root = tree, *new_root_rc, *root_p;

	root = tree, root_p = root->parent;
	if (root_p == NULL)
	{
		new_root = root->left, new_root->parent = root->parent;
		new_root_rc = new_root->right, new_root->right = root;
		root->left = new_root_rc, root->parent = new_root;
		if (new_root_rc != NULL)
			new_root_rc->parent = root;
	}
	else
	{
		new_root = rotate_right_with_parent(root);
	}
	return (new_root);
}

/**
 * binary_tree_rotate_right - Rotates a node to the right.
 * @tree: A pointer to the node to rotate.
 *
 * Return: The new root node.
 */
binary_tree_t *binary_tree_rotate_right(binary_tree_t *tree)
{
	binary_tree_t *root, *new_root = tree, *root_p;

	if (tree == NULL)
		return (NULL);
	root = tree, root_p = root->parent;
	if ((root->left == NULL) && (root->right == NULL))
	{
		if (root->parent != NULL)
		{
			if (root->parent->left == root)
			{
				if (root_p->parent != NULL && (root_p->parent->left == root_p))
					root_p->parent->left = root;
				if (root_p->parent != NULL && (root_p->parent->right == root_p))
					root_p->parent->right = root;
				root->parent = root_p->parent;
				root_p->left = NULL, root_p->parent = root;
				root->right = root_p;
			}
			else
			{
				if (root_p->parent != NULL && (root_p->parent->left == root_p))
					root_p->parent->left = root;
				if (root_p->parent != NULL && (root_p->parent->right == root_p))
					root_p->parent->right = root;
				root->parent = root_p->parent;
				root_p->right = NULL, root_p->parent = root;
				root->left = root_p;
			}
		}
	}
	else
	{
		new_root = rotate_right_with_child(tree);
	}
	return (new_root);
}
