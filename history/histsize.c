/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   histsize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:40 by hjacque           #+#    #+#             */
/*   Updated: 2017/04/02 16:10:06 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/history.h"

void	update_histfilesize(int histfilesize)
{
	update_history_file(histfilesize);
}

void	update_histsize(int histsize)
{
	FT_INIT(int, i, 1);
	FT_INIT(t_lst *, tmp1, NULL);
	FT_INIT(t_lst *, tmp2, NULL);
	FT_INIT(t_lst *, lst, g_shell.hist);
	if (histsize <= get_histsize("HISTSIZE"))
	{
		while (i++ < histsize && lst->prev)
			lst = lst->prev;
		if (lst->prev)
		{
			tmp1 = lst->prev;
			while (tmp1)
			{
				free(tmp1->content);
				tmp2 = tmp1;
				tmp1 = tmp1->prev;
				free(tmp2);
			}
			lst->prev = NULL;
		}
	}
}

int		get_histsize(char *var)
{
	FT_INIT(int, ret, 500);
	FT_INIT(char *, histsize, get_var(g_shell.env, "HISTSIZE"));
	FT_INIT(char *, histfilesize, get_var(g_shell.env, "HISTFILESIZE"));
	if (!ft_strcmp(var, "HISTSIZE"))
	{
		if (!histsize || ft_strlen(histsize) > 9 || !ft_strisnum(histsize))
			ret = 500;
		else
			ret = ft_atoi(histsize);
	}
	else if (!ft_strcmp(var, "HISTFILESIZE"))
	{
		if (!histfilesize || ft_strlen(histfilesize) > 9 ||
			!ft_strisnum(histfilesize))
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
