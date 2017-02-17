/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   histsize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 20:33:04 by jules             #+#    #+#             */
/*   Updated: 2017/02/17 16:41:46 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/history.h"

void	update_histfilesize(int histfilesize)
{
	update_history_file(histfilesize);
}

void	update_histsize(int histsize)
{
	int		i;
	t_lst	*tmp;
	t_lst	*lst;

	i = 1;
	lst = g_shell.hist;
	if (histsize <= get_histsize("HISTSIZE"))
	{
		while (i++ < histsize && lst->prev)
			lst = lst->prev;
		if (lst->prev)
		{
			tmp = lst->prev;
			while (tmp)
			{
				free(tmp->content);
				free(tmp);
				tmp = tmp->prev;
			}
			lst->prev = NULL;
		}
	}
}

int		get_histsize(char *var)
{
	FT_INIT(int, ret, 500);
	FT_INIT(char *, histsize, get_var(&g_shell, "HISTSIZE"));
	FT_INIT(char *, histfilesize, get_var(&g_shell, "HISTFILESIZE"));
	if (!ft_strcmp(var, "HISTSIZE"))
	{
		if (!histsize)
			ret = 500;
		else
			ret = ft_atoi(histsize);
	}
	else if (!ft_strcmp(var, "HISTFILESIZE"))
	{
		if (!histfilesize)
			ret = (500);
		else
			ret = ft_atoi(histfilesize);
	}
	if (histfilesize)
		free(histfilesize);
	if (histsize)
		free(histsize);
	return (ret);
}
