/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:13:29 by apinho            #+#    #+#             */
/*   Updated: 2017/02/24 18:36:54 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

static void	free_commands(char **commands)
{
	FT_INIT(int, i, 0);
	while (commands[i])
	{
		if (commands[i])
			free(commands[i]);
		i++;
	}
	free(commands);
}

static int	echo_is_option(char *line)
{
	FT_INIT(int, i, 0);
	while (line[i] && line[i] != ' ')
		i++;
	if (line[i] == ' ')
	{
		i++;
		if (line[i] == '-' && line[i + 1] == 'n'
			&& (line[i + 2] == ' ' || !line[i + 2]))
			return (1);
	}
	return (0);
}

int			len_tab(char **tabl)
{
	FT_INIT(int, len, 0);
	if (!tabl)
		return (0);
	while (tabl[len])
		len++;
	return (len);
}

int			ft_echo(char *line)
{
	FT_INIT(int, i, 1);
	FT_INIT(int, option, echo_is_option(line));
	FT_INIT(char **, commands,
	ft_strchr(line, ' ') ? ft_strsplit(line, ' ') : NULL);
	if (!commands)
	{
		ft_putchar('\n');
		return (0);
	}
	if (!ft_strcmp(commands[i], "-n"))
		i++;
	while (i < len_tab(commands) && commands[i])
	{
		ft_putstr(commands[i]);
		i++;
		if (commands[i] != NULL)
			ft_putchar(' ');
	}
	if (option != 1)
		ft_putchar('\n');
	free_commands(commands);
	return (0);
}
