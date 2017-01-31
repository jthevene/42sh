/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   histsize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 20:33:04 by jules             #+#    #+#             */
/*   Updated: 2017/01/30 11:20:41 by jthevene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/history.h"

void	update_histfilesize(int histfilesize)
{
	update_history_file(NULL, histfilesize);
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
		}
		lst->prev = NULL;
	}
}

int		get_histsize(char *var)
{
	char	*value;
	int		ret;

	ret = 0;
	if (!ft_strcmp(var, "HISTSIZE"))
	{
		if (!(value = get_var(&g_shell, "HISTSIZE")))
			return (500);
		else
			ret = ft_atoi(value);
	}
	else if (!ft_strcmp(var, "HISTFILESIZE"))
	{
		if (!(value = get_var(&g_shell, "HISTFILESIZE")))
			return (500);
		else
			ret = ft_atoi(value);
	}
	if (ret)
		return (500);
	return (500);
}
