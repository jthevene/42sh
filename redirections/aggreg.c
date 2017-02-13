/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aggreg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 13:01:44 by sgaudin           #+#    #+#             */
/*   Updated: 2017/02/13 12:37:19 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "GitPerso/21sh/libft/includes/libft.h"

int			detect_numbers(char *cmd, int i)
{
	FT_INIT(int, start, i);
	FT_INIT(char *, number, NULL);
	FT_INIT(int, ret, 0);
	while (cmd[i] && ft_isdigit(cmd[i]))
		i++;
	number = ft_strsub(cmd, start, i - start);
	ret = atoi(number);
	printf("number = %s, ret = %d\n", number, ret);
	free(number ? number : NULL);
	return (ret);
}

int		replace_cmd_aggreg(char **cmd, int i, int j)
{
	FT_INIT(char *, tmp, NULL);
	FT_INIT(char *, tmp_replace, NULL);
	while ((*cmd)[i] && ft_isdigit((*cmd)[i]))
		i++;
	if ((*cmd)[i] && !ft_isdigit((*cmd)[i]) && (*cmd)[i] != '-')
		i--;
	tmp = ft_strsub((*cmd), j, i - j + 1);
	tmp_replace = ft_str_replace((*cmd), tmp, "");
	free((*cmd));
	(*cmd) = ft_strdup(tmp_replace);
	free(tmp);
	free(tmp_replace);
	return (1);
}

int			detect_aggreg(char **cmd, int *fd_in, int *fd_out)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, j, 0);
	while ((*cmd)[i])
	{
		if (((*cmd)[i] == '>' || (*cmd)[i] == '<') && (*cmd)[i + 1] && (*cmd)[i + 1] == '&' && (*cmd)[i + 2]
			&& ((*cmd)[i + 2] == '-' || ft_isdigit((*cmd)[i + 2])))
		{
			if ((*cmd)[i - 1] && ft_isdigit((*cmd)[i - 1]))
			{
				j = i - 1;
				while ((*cmd)[j] && j >= 0 && ft_isdigit((*cmd)[j]))
					j--;
				(*fd_in) = detect_numbers((*cmd), ++j);
			}
			(*fd_out) = ft_isdigit((*cmd)[i + 2]) ? detect_numbers((*cmd), i + 2) : -1;
			return (replace_cmd_aggreg(cmd, i + 2, j));
		}
		else if (((*cmd)[i] == '>' || (*cmd)[i] == '<') && (*cmd)[i + 1] && (*cmd)[i + 1] == '&' && (*cmd)[i + 2]
			&& ((*cmd)[i + 2] != '-' || !ft_isdigit((*cmd)[i + 2])))
			return (0);
		i++;
	}
	return (1);
}

int			exec_aggreg(char **cmd, char **env)
{
	FT_INIT(int, fd_in, 0);
	FT_INIT(int, fd_out, 0);
	if (!env)
		return (0);
	printf("Before : cmd = %s\n", (*cmd));
	if (!detect_aggreg(&(*cmd), &fd_in, &fd_out))
		return (0);
	printf("After : (*cmd) = %s\n", (*cmd));
	if (fd_out == -1)
	{
		if (close(fd_in) == -1)
		{
			printf("Failed to close fd_in\n");
			return (0);
		}
	}
	else
	{
		if (dup2(fd_in, fd_out) == -1)
		{
			printf("Failed to dup2\n");
			return (0);
		}
	}
	return (1);
}

int			main(int ac, char **av, char **env)
{
	FT_INIT(char *, cmd, ft_strdup("ls -l coucou 1>&-"));
	if (!ac || !av || !env)
		return (0);
	if (!exec_aggreg(&cmd, env))
	{
		printf("Error\n");
		return (0);
	}
	else
		printf("SUCCESS\n");
	free(cmd);
	return (0);
}