/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/30 14:52:21 by sgaudin           #+#    #+#             */
/*   Updated: 2016/10/13 10:56:00 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/redir.h"

int			fdlist_pushback(t_fdlist **fdlist, int key) // Petit pushback adapté à la liste chainée dans la structure (redir.h)
{
	t_fdlist *tmp;
	t_fdlist *new;

	if (!(*fdlist))
	{
		printf("!(*fdlist)\n");
		if (!((*fdlist) = (t_fdlist *)malloc(sizeof(t_fdlist))))
			return (0);
		(*fdlist)->prev = NULL;
		(*fdlist)->next = NULL;
	}
	else
	{
		printf("pushing back\n");
		if (!(new = (t_fdlist *)malloc(sizeof(t_fdlist))))
			return (0);
		new->next = NULL;
		new->key = key;
		while ((*fdlist)->next)
			(*fdlist) = (*fdlist)->next;
		tmp = (*fdlist);
		(*fdlist)->next = new;
		new->prev = tmp;
	}
	return (1);
}

int			create_file(char *filename, t_fdlist **fdlist, int type) // Créé le fichier en fonction du type de redir (soit APPEND, soit TRUNC)
{
	int			fd;

	if (type == SIMPLE)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (0);
	if (!(*fdlist))
	{
		printf("initializing fdlist\n");
		fdlist_pushback(&(*fdlist), 0);
	}
	if (!fdlist_pushback(&(*fdlist), fd))
		return (0);
	free(filename);
	return (fd);
}

void 		free_fdlist(t_fdlist **fdlist)
{
	t_fdlist	*tmp;
	t_fdlist	*tmp_n;

	tmp = (*fdlist);
	while (tmp->prev)
	{
		close(tmp->key);
		tmp = tmp->prev;
	}
	close(tmp->key);
	while (tmp->next)
	{
		tmp_n = tmp->next;
		free(tmp);
		tmp = tmp_n;
	}
	printf("freeing tmp\n");
	free(tmp);
	printf("tmp freed\n");
	tmp = NULL;
	printf("fdlist and tmp freed, have a nice day\n");
	fdlist = NULL;
}

int			detect_out(void)
{
	int		i;

	i = 0;
	while (g_shell.line[i] && g_shell.line[i] != '>')
		i++;
	if (g_shell.line[i - 1] != ' ' && ft_isdigit(g_shell.line[i - 1]))
		return (g_shell.line[i - 1] - 48);
	else
		return (1);
}

void		exec_redir_right(int fd/*, int fd_out*/)
{
	pid_t	child;

	child = fork();
	if (child == -1)
		close(fd);
	else if (child == 0)
	{
		//dup2(fd, fd_out);
		//execve(/* CMD ICI */, /* ARGS de la CMD ICI */, /* ENV ICI */);
		printf("OKOK\n");
	}
	close(fd);
	wait(NULL);
}
