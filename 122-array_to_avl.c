#include "binary_trees.h"


/**
 * swap_items - Swaps two items in an array.
 * @array: The array to modify.
 * @l: The index of the left item.
 * @r: The index of the right item.
 */
void swap_items(int *array, size_t l, size_t r)
{
	int tmp;

	if (array != NULL)
	{
		tmp = array[l];
		array[l] = array[r];
		array[r] = tmp;
	}
}

/**
 * selection_sort - Sorts an array using the selection sort algorithm.
 * @array: The array to sort.
 * @size: The length of the array.
 */
void selection_sort(int *array, size_t size)
{
	size_t i, j, low_idx;

	if (array != NULL)
	{
		for (i = 0; i < size - 1; i++)
		{
			low_idx = i;
			for (j = size - 1; j > i; j--)
			{
				if (array[j] < array[low_idx])
				{
					low_idx = j;
				}
			}
			if (i != low_idx)
			{
				swap_items(array, i, low_idx);
			}
		}
	}
}

/**
 * tree_builder - Builds an AVL tree from a sorted array.
 * @parent: The AVL tree's parent.
 * @array: The sorted array of integers.
 * @size: The length of the given array.
 *
 * Return: A pointer to the root of thhe AVL tree, otherwise NULL.
 */
avl_t *tree_builder(avl_t *parent, int *array, int size)
{
	int *array_l = NULL, *array_r = NULL;
	int size_l = 0, size_r = 0, len = 0;
	avl_t *p = NULL, *l = NULL, *r = NULL;

	if ((size > 0) && (array != NULL))
	{
		p = malloc(sizeof(avl_t));
		if (p != NULL)
		{
			len = size - 1;
			size_l = (len / 2);
			size_r = len - (len / 2);
			if (size_l > 0)
			{
				array_l = array;
				l = tree_builder(p, array_l, size_l);
			}
			if (size_r > 0)
			{
				array_r = array + size_l + 1;
				r = tree_builder(p, array_r, size_r);
			}
			p->parent = parent;
			p->left = l;
			p->right = r;
			p->n = *(array + (size / 2) - (size % 2 == 0 ? 1 : 0));
		}
	}
	return (p);
}

/**
 * array_to_avl - Creates an AVL tree from an array.
 * @array: The array of values.
 * @size: The length of the array.
 *
 * Return: A pointer to the AVL tree, otherwise NULL.
 */
avl_t *array_to_avl(int *array, size_t size)
{
	size_t i;
	int *array_c = NULL;
	avl_t *root = NULL;

	if (array != NULL)
	{
		array_c = malloc(sizeof(int) * size);
		if (array_c != NULL)
		{
			for (i = 0; i < size; i++)
				*(array_c + i) = *(array + i);
			selection_sort(array_c, size);
			root = tree_builder(root, array_c, size);
		}
	}
	return (root);
}
