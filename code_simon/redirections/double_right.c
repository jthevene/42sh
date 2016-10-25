/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_right.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 14:35:45 by sgaudin           #+#    #+#             */
/*   Updated: 2016/10/13 10:55:21 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/redir.h"

static int	get_filename_double(int i, int last_fd)
{
	FT_INIT(int, j, 0);
	while (g_shell.line[i] && g_shell.line[i - 1] != '>')
		i++;
	if (g_shell.line[i - 1] == '>' && g_shell.line[i] != '>')
		return (0);
	if (!g_shell.line[++i])
		return (last_fd);
	while (g_shell.line[i] && ft_isspace(g_shell.line[i]))
		i++;
	if (!g_shell.line[i])
		return (0);
	FT_INIT(int, tmp, i);
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
	FT_INIT(int, fd, open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644));
	printf("FD créé : %d\n", fd);
	free(filename);
	return (get_filename_double(i, fd));
}

int			double_right(void)
{
	int		fd;
	int		fd_out;

	printf("Entrée dans double_right\n");
	if (!ft_strchr(g_shell.line, '>'))
		return (0); /* Pas de redirection(s) droite */
	printf("Redirection détectée\n");
	fd_out = detect_out();
	printf("Detect_out OK : %d\n", fd_out);
	if (!(fd = get_filename_double(1, 0)))
		return (0); /* Pas de fichier spécifié pour la redirection ou pas de double redir */
	printf("Test 2 OK, fichier créé, on a récup le fd %d\n", fd);
	printf("Prêt pour fork la commande et dup la sortie dans le fichier\n");
	close(fd);
//	exec_redir_right(fd);
	return (1);
}
