#include "binary_trees.h"

/**
 * enqueue_item - Adds an item to a queue.
 * @queue_h: A pointer to the queue's head.
 * @queue_t: A pointer to the queue's tail.
 * @n: A pointer to the queue's size value.
 * @item: The item to add to the queue.
 */
void enqueue_item(binary_tree_t **queue_h, binary_tree_t **queue_t,
	int *n, void *item)
{
	binary_tree_t *new_node;
	binary_tree_t *node = (binary_tree_t *)item;

	if ((queue_h != NULL) && (queue_t != NULL))
	{
		new_node = malloc(sizeof(binary_tree_t));
		if (new_node == NULL)
			return;
		new_node->left = *queue_t;
		new_node->right = NULL;
		new_node->n = (node != NULL ? node->n : -1);
		new_node->parent = node;
		if (*queue_h == NULL)
			*queue_h = new_node;
		if (*queue_t != NULL)
			(*queue_t)->right = new_node;
		*queue_t = new_node;
		if (n != NULL)
			(*n)++;
	}
}

/**
 * dequeue_item - Removes an item from a queue.
 * @queue_h: A pointer to the queue's head.
 * @queue_t: A pointer to the queue's tail.
 * @n: A pointer to the queue's size value.
 *
 * Return: The value of the removed queue.
 */
binary_tree_t *dequeue_item(binary_tree_t **queue_h,
	binary_tree_t **queue_t, int *n)
{
	binary_tree_t *tmp0;
	binary_tree_t *tmp1;
	binary_tree_t *node = NULL;

	if ((queue_h != NULL) && (queue_t != NULL))
	{
		tmp0 = *queue_h;
		if (tmp0 != NULL)
		{
			node = tmp0->parent;
			if (tmp0->right != NULL)
			{
				tmp1 = tmp0->right;
				tmp1->left = NULL;
				*queue_h = tmp1;
				free(tmp0);
			}
			else
			{
				free(tmp0);
				*queue_h = NULL;
				*queue_t = NULL;
			}
			if (n != NULL)
				(*n)--;
		}
	}
	return (node);
}

/**
 * binary_tree_levelorder - Performs a level order traversal on a tree.
 * @tree: The tree to traverse.
 * @func: The function to handle the traversed node's value.
 */
void binary_tree_levelorder(const binary_tree_t *tree, void (*func)(int))
{
	binary_tree_t *queue_head = NULL;
	binary_tree_t *queue_tail = NULL;
	int n = 0;
	binary_tree_t *current = NULL;

	if (tree != NULL)
	{
		enqueue_item(&queue_head, &queue_tail, &n, (void *)tree);
		while (n > 0)
		{
			current = queue_head;
			func(current->n);
			if (((current->parent) != NULL) && (current->parent->left != NULL))
			{
				enqueue_item(
					&queue_head, &queue_tail, &n, (void *)(current->parent->left)
				);
			}
			if (((current->parent) != NULL) && (current->parent->right != NULL))
			{
				enqueue_item(
					&queue_head, &queue_tail, &n, (void *)(current->parent->right)
				);
			}
			dequeue_item(&queue_head, &queue_tail, &n);
		}
	}
}
