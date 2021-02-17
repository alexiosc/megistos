/*
 * tree module for gstat module
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include <megistos/gstat.h>

void
tree_setup (void)
{
	tree.leafs = NULL;
	tree.leafcount = 0;
}


void
tree_addleaf (struct treenode *n, int size)
{
	int     i;

	n->leafs = malloc (size * sizeof (struct treenode));
	n->leafcount = size;
	for (i = 0; i < size; i++) {
		n->leafs[i].leafs = NULL;
		n->leafs[i].leafcount = 0;
	}
}


/* add leaves of size SIZE, to each end-leaf of the tree */
void
tree_addlevel (struct treenode *n, int size)
{
	int     i;

	if (!n->leafs) {
		tree_addleaf (n, size);
		return;
	}

	for (i = 0; i < n->leafcount; i++)
		tree_addlevel (&n->leafs[i], size);
}


/* contains the size of each tree level */
void
tree_init (treekey_t key)
{
	int     i;

	for (i = 0; i < key[0]; i++)
		tree_addlevel (&tree, key[i + 1]);
}


void
tree_freelevel (struct treenode *n)
{
	int     i;

	if (n->leafs)
		for (i = 0; i < n->leafcount; i++)
			tree_freelevel (&n->leafs[i]);

	free (n->leafs);
}

void
tree_free (void)
{
	tree_freelevel (&tree);
}


struct treenode *
tree_getleaf (struct treenode *t, treekey_t key, int idx)
{
	if (idx >= key[0])
		return t;
	if (key[idx + 1] >= t->leafcount)
		return NULL;

	return tree_getleaf (&t->leafs[key[idx + 1]], key, idx + 1);
}

struct treenode *
tree_search (treekey_t key)
{
	return tree_getleaf (&tree, key, 0);
}


void
_key_set (treekey_t key, ...)
{
	int     j;
	va_list ap;

	key[0] = 0;
	va_start (ap, key);
	do {
		j = va_arg (ap, int);

		if (j == -1)
			break;
		key[0]++;
		key[key[0]] = j;
	} while (1);

	va_end (ap);
}


/* if mask[i] is -1 then this field will not be changed */
int
key_next (treekey_t key, const treekey_t mask)
{
	int     i, j;
	struct treenode *n;

//      if(class > key[0])return 0;

	j = key[0];
	for (i = j; i >= 1; i--) {
		if (mask[i] == 1)
			continue;
		key[i]++;
		n = tree_search (key);
		if (n)
			return 1;
		key[i] = 0;
//              if(i==class)break;
	}

	return 0;
}

void
key_copy (treekey_t dst, treekey_t src)
{
	int     i;

	for (i = 0; i < GMAXCLASS + 1; i++)
		dst[i] = src[i];
}

void
test_tree (void)
{
	treekey_t key;
	struct treenode *n;

	tree_setup ();
	key_set (key, 2, 2);

	tree_init (key);

	key_set (key, 1, 1);
	n = tree_search (key);

	n->leafcount = 10;

	key_set (key, 0, 0);
	n = tree_search (key);

	n->leafcount = 9;


	key_set (key, 1, 1);
	n = tree_search (key);
	printf ("leafcount = %i\n", n->leafcount);

	key_set (key, 0, 0);
	n = tree_search (key);
	printf ("leafcount = %i\n", n->leafcount);

	exit (1);
}


/* End of File */
