#include "nary_trees.h"


/**
 * nary_tree_insert- func
 * @parent: nary_tree_t *
 * @str: char const *
 * Return: nary_tree_t *
 */
nary_tree_t *nary_tree_insert(nary_tree_t *parent, char const *str)
{
	char *ns = NULL;
	nary_tree_t *node = NULL;

	if (!str)
		return (NULL);
	ns = strdup(str);
	node = malloc(sizeof(nary_tree_t));
	if (!ns || !node)
		return (NULL);
	node->parent = parent;
	node->nb_children = 0;
	node->content = ns;
	if (parent)
	{
		node->next = parent->children;
		parent->children = node;
		parent->nb_children++;
	}
	else
		node->next = NULL;
	return (node);
}
