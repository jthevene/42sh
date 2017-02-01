/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_right.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 14:35:45 by sgaudin           #+#    #+#             */
/*   Updated: 2016/10/13 10:55:03 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/redir.h"

// Exemple : Sur une commande comme ça : ls -l > test1 > test2 > test3
// On récupère les 3 noms de fichiers, on les créé dans le bon mode
// Et on stocke les fd pour pouvoir les close plus tard
// On récupère également le bon fd dans lequel stocker la sortie
static int		get_filename(int i, int last_fd, t_fdlist **fdlist) 
{
	FT_INIT(int, j, 0);
	FT_INIT(int, tmp, 0);
	while (g_shell.line[i] && g_shell.line[i - 1] != '>')
		i++;
	if (!g_shell.line[i])
		return (last_fd);
	while (g_shell.line[i] && ft_isspace(g_shell.line[i]))
		i++;
	if (!g_shell.line[i])
		return (0);
	tmp = i;
	while (g_shell.line[tmp] && !ft_isspace(g_shell.line[tmp]))
		tmp++;
	FT_INIT(char *, filename, ft_strnew(tmp - i + 1));
	while (g_shell.line[i] && !ft_isspace(g_shell.line[i]))
	{
		filename[j] = g_shell.line[i];
		i++;
		j++;
	}
	filename[j] = '\0';
	FT_INIT(int, fd, create_file(filename, &(*fdlist), SIMPLE));
	if (!fdlist)
		printf("get_filename, fdlist n'existe pas\n");
	return (get_filename(i, fd, fdlist));
}

int				simple_right(void)
{
	int			fd;
	int			fd_out;
	t_fdlist	*fdlist;

	fdlist = NULL;
	printf("Entrée dans simple_right\n");
	if (!ft_strchr(g_shell.line, '>'))
		return (0);
	printf("Redirection détectée\n");
	fd_out = detect_out();
	if (!(fd = get_filename(1, 0, &fdlist))) // Fonction qui récupère tous les fd à ouvrir, créé les fichiers, et stocke tous les fd dans une liste.
		return (0);
	printf("Prêt pour fork la commande et dup la sortie dans le fichier\n");
	printf("fd_out = %d\n", fd_out);
//	exec_redir_right(fd/*, fd_out*/); /* Fonction qui va rediriger la sortie de la commande vers le fichier de la redir */
	if (fdlist->next)
		fdlist = fdlist->next;
	free_fdlist(&fdlist);
	return (1);
}
