/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <hjacque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:40 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/08 14:45:55 by hjacque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void			check_for_hdoc(t_token *token)
{
	t_token *tmp;

	tmp = token;
	while (tmp->next)
	{
		if (tmp->type == DLESS)
		{
			ft_strdel(&(tmp->lexeme));
			tmp->lexeme = ft_strdup("<");
			replace_hdoc(tmp->next);
		}
		tmp = tmp->next;
	}
}

static void		replace_hdoc2(char **myline, char **tmp, char **heredoc,
	t_token *token)
{
	if (ft_strcmp((*myline), token->lexeme) != 0)
	{
		(*tmp) = (*heredoc);
		(*heredoc) = ft_strjoin((*heredoc), (*myline));
		ft_strdel(&(*tmp));
	}
	while (ft_strcmp((*myline), token->lexeme) != 0)
	{
		ft_strdel(&g_shell.prompt);
		ft_putstr("\n");
		(*myline) = prompt_dquote("heredoc> ");
		if (ft_strcmp((*myline), token->lexeme) != 0)
		{
			(*tmp) = (*heredoc);
			(*heredoc) = ft_strjoinchar((*heredoc), (*myline), '\n');
			ft_strdel(&(*tmp));
		}
	}
}

void			replace_hdoc(t_token *token)
{
	char	*myline;
	char	*tmp;
	int		fd_file;

	FT_INIT(char *, heredoc, ft_strdup(""));
	ft_strdel(&g_shell.prompt);
	myline = prompt_dquote("heredoc> ");
	replace_hdoc2(&myline, &tmp, &heredoc, token);
	tmp = heredoc;
	heredoc = ft_strjoin(heredoc, "\n");
	ft_strdel(&tmp);
	fd_file = open("/tmp/heredoc.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	ft_putstr_fd(heredoc, fd_file);
	ft_strdel(&(token->lexeme));
	token->lexeme = ft_strdup("/tmp/heredoc.txt");
	free(heredoc);
	close(fd_file);
	ft_putchar('\n');
}
