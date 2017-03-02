/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvirgile <dvirgile@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:13:29 by dvirgile          #+#    #+#             */
/*   Updated: 2017/03/02 17:10:01 by dvirgile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

char	*finish_line_backslash(char *line)
{
	char *myline;

	ft_strdel(&g_shell.prompt);
	myline = prompt_dquote("> ");
	if (myline)
		myline = ft_strjoin(line, myline);
	ft_putstr("\n");
	free(line);
	return (myline);
}

char	*finish_the_squote(char *line)
{
	char *myline;

	ft_strdel(&g_shell.prompt);
	myline = prompt_dquote("quote> ");
	if (myline)
		myline = ft_strjoinchar(line, myline, '\n');
	ft_putchar('\n');
	free(line);
	return (myline);
}

char	*finish_the_dquote(char *line)
{
	char *myline;

	ft_strdel(&g_shell.prompt);
	myline = prompt_dquote("dquote> ");
	if (myline)
		myline = ft_strjoinchar(line, myline, '\n');
	ft_putchar('\n');
	free(line);
	return (myline);
}

int		quote_in_word(char *line, int pos)
{
	if (line[pos] == '\"')
	{
		pos++;
		while (line[pos] != '\"')
			pos++;
		pos++;
	}
	else if (line[pos] == '\'')
	{
		pos++;
		while (line[pos] != '\'')
			pos++;
		pos++;
	}
	return (pos);
}
