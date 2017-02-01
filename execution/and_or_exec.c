#include "../includes/42sh.h"

static int verif_content(char *content)
{
	return(ft_isope(content[0]));
}

int 	execute_or_and(t_tree *tree)
{
	distrib_functions(tree->left->content);
	if (g_shell.all_results == -99)
		g_shell.all_results = g_shell.result_exec;
	else if (tree->type == OR)
		g_shell.all_results = g_shell.all_results || g_shell.result_exec;
	else if (tree->type == AND)
		g_shell.all_results = g_shell.all_results && g_shell.result_exec;
	if (tree->type == OR && g_shell.all_results)
		if (!verif_content(tree->right->content))
			distrib_functions(tree->right->content);

	if (tree->type == AND && !g_shell.all_results)
		if (!verif_content(tree->right->content))
			distrib_functions(tree->right->content);
	return (g_shell.all_results);
}